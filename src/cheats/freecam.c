#include "../../include/common.h"

static char kong_frozen = 0;
static char render_frozen = 0;
static char freecam_enabled = 0;
static char holding_cr = 0;
static char holding_cl = 0;
static char holding_s = 0;
static char hud_hidden = 0;

void applyButtonBans_New(subinput_struct* input) {
    char x_enabled = JoystickEnabledX;
    char y_enabled = JoystickEnabledY;
    unsigned short button_enabled = ButtonsEnabledBitfield;
    if ((freecam_enabled) && (kong_frozen)) {
        x_enabled = 0;
        y_enabled = 0;
        button_enabled = L_Button | R_Button | D_Down | D_Up | D_Right | D_Left; // Buttons needed to operate active menu
    }
    getControllerContainer(input);
    for (int i = 0; i < 4; i++) {
        input[i].controller.stickX &= x_enabled;
        input[i].controller.stickY &= y_enabled;
        input[i].controller.Buttons &= button_enabled;
    }
}

int* showFreecamAttributes(int* dl) {
    if ((!ActiveMenu.isOpen) && (freecam_enabled) && (!hud_hidden)) {
        int y = 25;
        if (kong_frozen) {
            dl = drawPixelTextContainer(dl, 25, y, "CONTROLLING CAMERA", 0xFF, 0xFF, 0xFF, 0xFF, 1);
        } else {
            dl = drawPixelTextContainer(dl, 25, y, "CONTROLLING KONG", 0xFF, 0xFF, 0xFF, 0xFF, 1);
        }
        y += 13;
        if (render_frozen) {
            dl = drawPixelTextContainer(dl, 25, y, "RENDER: FROZEN", 0xFF, 0xFF, 0xFF, 0xFF, 1);
        } else {
            dl = drawPixelTextContainer(dl, 25, y, "RENDER: FOLLOW CAMERA", 0xFF, 0xFF, 0xFF, 0xFF, 1);
        }
    }
    return dl;
}

#define POS_CHANGE 20
#define FOCUS_DIFF 100

int deg_to_dk64u(float deg) {
    deg *= 4096;
    deg /= 360;
    return deg;
}

float dk64u_to_deg(int dk64u) {
    float deg = dk64u;
    deg *= 360;
    deg /= 4096;
    return deg;
}

void applyStickThresholds(int* value) {
    if ((*value > -5) && (*value < 5)) {
        *value = 0;
    }
}

void newCameraCode(void) {
    /*
        -camera_position: Change swap->0x210,0x214,0x218 to change coordinates of where the camera is
        -camera_render_point: Change swap->0x21C,0x220,0x224 to change coordinates of where the camera load point is (Shifting this changes opacity of trees/dk etc)
        -camera_focus_point: Change swap->0x228,0x22C,0x230 to change the position which the camera is focusing on
    */
    /*
        Controls:
        - A: Raise
        - B: Lower
        - C-Left: Toggle Freeze Kong
        - C-Right: Toggle whether load position matches camera position
        - Stick: Change Position
        - C-Buttons: Change angle
    */
    int stick_x = ControllerInput.stickX;
    int stick_y = ControllerInput.stickY;
    applyStickThresholds(&stick_x);
    applyStickThresholds(&stick_y);
    if (kong_frozen) {
        if (SwapObject) {
            if (ControllerInput.Buttons & A_Button) {
                // Raise
                SwapObject->camera_position.yPos += POS_CHANGE;
                SwapObject->camera_focus_point.yPos += POS_CHANGE;
            } else if (ControllerInput.Buttons & B_Button) {
                // Lower
                SwapObject->camera_position.yPos -= POS_CHANGE;
                SwapObject->camera_focus_point.yPos -= POS_CHANGE;
            }
            // Change Rotation
            if (ControllerInput.Buttons & (C_Up | C_Down)) {
                int diff = -POS_CHANGE;
                if (ControllerInput.Buttons & C_Down) {
                    diff = POS_CHANGE;
                }
                int y_rot = deg_to_dk64u(Camera->viewportXRotation) + (2 * diff);
                if (y_rot < 0) {
                    y_rot = 0;
                } else if (y_rot > 2048) {
                    y_rot = 2048;
                }
                Camera->viewportXRotation = dk64u_to_deg(y_rot);
            }
            Camera->viewportRotation = (Camera->viewportRotation - stick_x) % 4096;
            // Change Position
            float x_ratio = determineXRatioMovement(Camera->viewportRotation);
            float z_ratio = determineZRatioMovement(Camera->viewportRotation);
            float x_diff = x_ratio * (stick_y >> 3);
            float z_diff = z_ratio * (stick_y >> 3);
            SwapObject->camera_position.xPos += x_diff;
            SwapObject->camera_position.zPos += z_diff;
            // Fix focus point
            SwapObject->camera_focus_point.xPos = SwapObject->camera_position.xPos + (x_ratio * FOCUS_DIFF);
            float deg_fixed = -(Camera->viewportXRotation - 90);
            int dk64u_fixed = deg_to_dk64u(deg_fixed);
            SwapObject->camera_focus_point.yPos = SwapObject->camera_position.yPos + (FOCUS_DIFF * determineXRatioMovement(dk64u_fixed));
            SwapObject->camera_focus_point.zPos = SwapObject->camera_position.zPos + (z_ratio * FOCUS_DIFF);
            // Fix unknown position
            SwapObject->camera_unk_position.xPos = SwapObject->camera_position.xPos;
            SwapObject->camera_unk_position.yPos = SwapObject->camera_position.yPos;
            SwapObject->camera_unk_position.zPos = SwapObject->camera_position.zPos;
            if (ControllerInput.Buttons & Start_Button) {
                if (!holding_s) {
                    hud_hidden = 1 ^ hud_hidden;
                }
                holding_s = 1;
            } else {
                holding_s = 0;
            }
        }
    }
    // Fix render position
    if (!render_frozen) {
        SwapObject->camera_render_point.xPos = SwapObject->camera_position.xPos;
        SwapObject->camera_render_point.yPos = SwapObject->camera_position.yPos;
        SwapObject->camera_render_point.zPos = SwapObject->camera_position.zPos;
    }
    // Handle Toggles
    if (ControllerInput.Buttons & C_Left) {
        if (!holding_cl) {
            kong_frozen = 1 ^ kong_frozen;
        }
        holding_cl = 1;
    } else {
        holding_cl = 0;
    }
    if (ControllerInput.Buttons & C_Right) {
        if (!holding_cr) {
            render_frozen = 1 ^ render_frozen;
        }
        holding_cr = 1;
    } else {
        holding_cr = 0;
    }
}

void setFreecam(int value) {
    freecam_enabled = value;
    if (freecam_enabled) {
        *(int*)(0x8074C390) = (int)&newCameraCode;
        render_frozen = 1;
        kong_frozen = 1;
        hud_hidden = 0;
    } else {
        *(int*)(0x8074C390) = 0x8068BBF8;
    }
}

void toggleFreecam(void) {
    setFreecam(1 ^ freecam_enabled);
    openCheatsMenu();
}

int getFreecamState(void) {
    return freecam_enabled;
}