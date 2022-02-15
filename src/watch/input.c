#include "../../include/common.h"

static spriteDisplay aSprite;
static spriteDisplay bSprite;
static spriteDisplay zSprite;
static spriteDisplay startSprite;
static spriteDisplay lSprite;
static spriteDisplay rSprite;
static spriteDisplay cuSprite;
static spriteDisplay cdSprite;
static spriteDisplay clSprite;
static spriteDisplay crSprite;
static spriteDisplay joystickCircleSprite;
static spriteDisplay joystickPosSprite;
static spriteDisplay fairyBoxSprite;
// Order ABZSLR C:UDLR
static const short root_x[] = {0x00,0xB0,0x00,0xB0};
static const short root_y[] = {0x00,0x00,0xA0,0xA0};
static const short x_positions[] = {0x54, 0x48, 0x34, 0x34, 0x20, 0x78, 0x68, 0x68, 0x58, 0x78, 0x20};
static const short y_positions[] = {0x38, 0x2C, 0x34, 0x20, 0x20, 0x20, 0x24, 0x34, 0x2C, 0x2C, 0x34};

#define BUTTONTYPE_GREY 0
#define BUTTONTYPE_START 1
#define BUTTONTYPE_A 2
#define BUTTONTYPE_B 3
#define BUTTONTYPE_C 4

static const short xsimp_positions[] = {0x2E, 0x23, 0x16, 0x16, 0x16, 0x48, 0x39, 0x39, 0x2E, 0x44, 0x20};
static const short ysimp_positions[] = {0x37, 0x2C, 0x2C, 0x1F, 0x16, 0x16, 0x16, 0x2C, 0x21, 0x21, 0x34};
static const char simp_types[] = {
	BUTTONTYPE_A,
	BUTTONTYPE_B,
	BUTTONTYPE_GREY,
	BUTTONTYPE_START,
	BUTTONTYPE_GREY,
	BUTTONTYPE_GREY,
	BUTTONTYPE_C,
	BUTTONTYPE_C,
	BUTTONTYPE_C,
	BUTTONTYPE_C,
};

static const unsigned char simptype_red[] = {0x12,0x1F,0x00,0x00,0x1A};
static const unsigned char simptype_green[] = {0x12,0x00,0x00,0x1E,0x1A};
static const unsigned char simptype_blue[] = {0x12,0x00,0x1D,0x00,0x00};

static const unsigned char sprite_table_indexes[] = {0x6E,0x6F,0x70,0x91,0x88,0x87,0x72,0x71,0x73,0x73};
static const unsigned short button_bits[] = {A_Button,B_Button,Z_Button,Start_Button,L_Button,R_Button,C_Up,C_Down,C_Left,C_Right};
static const float target_size[] = {0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,-0.5f};
spriteDisplay* displaySlots[13] = {
	&aSprite,
	&bSprite,
	&zSprite,
	&startSprite,
	&lSprite,
	&rSprite,
	&cuSprite,
	&cdSprite,
	&clSprite,
	&crSprite,
	&joystickCircleSprite,
	&joystickPosSprite,
	&fairyBoxSprite,
};
spriteControl* spriteSlots[13] = {};
otherSpriteControl* otherSpriteData[13] = {};
static char overlay_spawned = 0;

void spawnOverlay(void) {
	if (InputDisplayType == 0) {
		if (spriteSlots[0] == 0) {
			if (overlay_spawned == 0) {
				if ((CurrentMap != 0x53) && (CurrentMap != 0xC5)) { // Both Dogadon maps cause graphical glitches galore
					if (InputDisplayQuadrant < 4) {
						for (int i = 0; i < 10; i++) {
							if (displaySlots[i]) {
								displaySlots[i]->disappear = 0;
							}
							sprite_translucency = 0;
							displaySprite(displaySlots[i],sprite_table[(int)sprite_table_indexes[i]],root_x[(int)InputDisplayQuadrant] + x_positions[i],root_y[(int)InputDisplayQuadrant] + y_positions[i],(int)target_size[i],0,4);
							spriteSlots[i] = (spriteControl*)SpriteAddress;
							otherSpriteData[i] = (otherSpriteControl*)getOtherSpritePointer();
						}
						// Stick Bowl
						displaySlots[10]->disappear = 0;
						sprite_translucency = 1;
						// 0x67
						displaySprite(displaySlots[10],sprite_table[0xA3],root_x[(int)InputDisplayQuadrant] + 0x20,root_y[(int)InputDisplayQuadrant] + 0x34,0.25f,0,4);
						spriteSlots[10] = (spriteControl*)SpriteAddress;
						otherSpriteData[10] = (otherSpriteControl*)getOtherSpritePointer();
						// Stick Position
						displaySlots[11]->disappear = 0;
						sprite_translucency = 1;
						displaySprite(displaySlots[11],sprite_table[0x91],root_x[(int)InputDisplayQuadrant] + 0x20,root_y[(int)InputDisplayQuadrant] + 0x34,0.2f,0,4);
						spriteSlots[11] = (spriteControl*)SpriteAddress;
						otherSpriteData[11] = (otherSpriteControl*)getOtherSpritePointer();
						// Fairy Box
						// displaySlots[12]->disappear = 0;
						// sprite_translucency = 1;
						// displaySprite(displaySlots[12],sprite_table[0x60],0x9E,0x79,1.1f,0,4);
						// spriteSlots[12] = (spriteControl*)SpriteAddress;
						// otherSpriteData[12] = (otherSpriteControl*)getOtherSpritePointer();

						InputSpritesSpawned = 0;
						overlay_spawned = 1;
					}
				}
			}
		}
	}
}

void closeOverlay(void) {
	if (overlay_spawned) {
		// for (int i = 0; i < 13; i++) {
		for (int i = 0; i < 12; i++) {
			spriteSlots[i] = 0;
			otherSpriteData[i] = 0;
		}
		InputSpritesSpawned = 0;
	}
	overlay_spawned = 0;
}

void openInputOnTransition(void) {
	if ((TransitionSpeed < 0) || ((CutsceneActive == 6) && (CurrentMap != 0x50))) {
		if ((InputDisplayOpen) && (InputDisplayType == 0)) {
			spawnOverlay();
		}
	}
};

void closeInputOnTransition(void) {
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		if (((InputDisplayOpen) && (InputDisplayType == 0)) || (FairyViewerOpen)) {
			closeOverlay();
		}
	}
};

void displayInput(void) {
	float scale_factor;
	float stick_x;
	float stick_y;
	if ((CurrentMap != 0x53) && (CurrentMap != 0xC5)) { // Both Dogadon maps cause graphical glitches galore
		if (InputStickMax) {
			scale_factor = 0.3f;
		} else {
			scale_factor = 0.476f;
		}
		if (InputSpritesSpawned) {
			if (otherSpriteData[9]) {
				otherSpriteData[9]->some_pointer = 0;
				otherSpriteData[9]->xScale = 4 * target_size[9];
				otherSpriteData[9]->yScale = (-target_size[9]) * 4;
				otherSpriteData[9]->xPos = (4 * (float)(root_x[(int)InputDisplayQuadrant] + x_positions[9]));
				otherSpriteData[9]->yPos = (4 * (float)(root_y[(int)InputDisplayQuadrant] + y_positions[9]));
			}
		}
		for (int i = 0; i < 12; i++) {
			if (spriteSlots[i]) {
				if ((ActiveMenu.isOpen) && (InputDisplayOpen) && (InputDisplayType == 0)) {
					spriteSlots[i]->scale = 0;
					otherSpriteData[i]->xScale = 0;
					otherSpriteData[i]->yScale = 0;
					InputSpritesSpawned = 0;
				} else {
					if ((InputDisplayOpen) && (InputDisplayType == 0)) {
						if (i < 10) {
							if (InputSpritesSpawned == 0) {
								spriteSlots[i]->scale = target_size[i];
							}
							if (otherSpriteData[i]) {
								if (ControllerInput.Buttons & button_bits[i]) {
									otherSpriteData[i]->transparency1 = 255;
									otherSpriteData[i]->transparency2 = 255;
									otherSpriteData[i]->transparency3 = 255;
								} else {
									otherSpriteData[i]->transparency1 = 100;
									otherSpriteData[i]->transparency2 = 100;
									otherSpriteData[i]->transparency3 = 100;
								}
							}
						} else {
							if (InputSpritesSpawned == 0) {
								spriteSlots[i]->scale = 0.35f;
							}
							if (i == 10) {
								// otherSpriteData[i]->transparency1 = 150;
								// otherSpriteData[i]->transparency2 = 150;
								// otherSpriteData[i]->transparency3 = 150;
							}
							if (i == 11) {
								// Joystick Position
								spriteSlots[i]->scale = 0.2f;
								stick_x = ControllerInput.stickX;
								stick_y = ControllerInput.stickY;
								if (InputStickMax == 0) {
									if (stick_x > 80) {
										stick_x = 80;
									} else if (stick_x < -80) {
										stick_x = -80;
									}
									if (stick_y > 80) {
										stick_y = 80;
									} else if (stick_y < -80) {
										stick_y = -80;
									}
								}
								spriteSlots[i]->xPos = (root_x[(int)InputDisplayQuadrant] * 4) + 127 + (scale_factor * stick_x);
								spriteSlots[i]->yPos = (root_y[(int)InputDisplayQuadrant] * 4) + 210 - (scale_factor * stick_y);
							}
						}
						if (i < 11) {
							spriteSlots[i]->xPos = (4 * (float)(root_x[(int)InputDisplayQuadrant] + x_positions[i]));
							spriteSlots[i]->yPos = (4 * (float)(root_y[(int)InputDisplayQuadrant] + y_positions[i]));
						}
					}
				}
			}
		}
		if ((ActiveMenu.isOpen == 0) && (InputDisplayOpen)) {
			InputSpritesSpawned = 1;
		}
	}
};

int* drawInputRect(int* dl, int x1, int y1, int x2, int y2, int red, int green, int blue) {
	dl = drawScreenRect(dl, x1, y1, x2, y2, red, green, blue, 1);
	return dl;
}

#define INPUT_QUAD_THICKNESS 5
#define INPUT_QUAD_SIZE 84
#define INPUT_BORDER_COLOR 0x12
#define INPUT_INNER_QUAD_COLOR 0x8
#define INPUT_BORDER_MULT 2
#define INPUT_STICKBOX_THICKNESS 10
#define INPUT_TL_OFFSET 2

int* displaySimpleInput(int* dl) {
	float position_mult = 3.5f;
	if (InputDisplayOpen) {
		if (InputDisplayType == 1) {
			for (int i = 0; i < 10; i++) {
				int x_min = (xsimp_positions[i] * 4) + ((float)(root_x[(int)InputDisplayQuadrant]) * position_mult);
				int y_min = ysimp_positions[i] * 4 + ((float)(root_y[(int)InputDisplayQuadrant]) * position_mult);
				int x_max = x_min + 40;
				int y_max = y_min + 40;
				if (button_bits[i] == Z_Button) {
					y_max = y_min + 80;
				}
				if ((button_bits[i] == L_Button) || (button_bits[i] == R_Button)) {
					x_max = x_min + 80;
					y_max = y_min + 20;
				}
				int buttontype = simp_types[i];
				float color_mult = 0.5f;
				if (ControllerInput.Buttons & button_bits[i]) {
					color_mult = 1.0f;
				}
				dl = drawInputRect(dl, x_min, y_min, x_max, y_max, simptype_red[buttontype] * color_mult, simptype_green[buttontype] * color_mult, simptype_blue[buttontype] * color_mult);
			}
			int stick_quad_x = 0x46 * 4 + ((float)(root_x[(int)InputDisplayQuadrant]) * position_mult);
			int stick_quad_y = 0x2E * 4 + ((float)(root_y[(int)InputDisplayQuadrant]) * position_mult);
			dl = drawInputRect(dl, 
								stick_quad_x, 
								stick_quad_y, 
								stick_quad_x + INPUT_QUAD_SIZE, 
								stick_quad_y + INPUT_QUAD_SIZE,
								INPUT_BORDER_COLOR, 
								INPUT_BORDER_COLOR, 
								INPUT_BORDER_COLOR);
			// Top Left
			dl = drawInputRect(dl,
								stick_quad_x + INPUT_TL_OFFSET + (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								stick_quad_y + INPUT_TL_OFFSET + (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								stick_quad_x + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) - INPUT_QUAD_THICKNESS,
								stick_quad_y + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) - INPUT_QUAD_THICKNESS,
								INPUT_INNER_QUAD_COLOR,
								INPUT_INNER_QUAD_COLOR,
								INPUT_INNER_QUAD_COLOR);
			// Top Right
			dl = drawInputRect(dl,
								stick_quad_x + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) + INPUT_QUAD_THICKNESS,
								stick_quad_y + INPUT_TL_OFFSET + (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								stick_quad_x + INPUT_TL_OFFSET + INPUT_QUAD_SIZE - (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								stick_quad_y + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) - INPUT_QUAD_THICKNESS,
								INPUT_INNER_QUAD_COLOR, 
								INPUT_INNER_QUAD_COLOR, 
								INPUT_INNER_QUAD_COLOR);
			// Bottom Left
			dl = drawInputRect(dl,
								stick_quad_x + INPUT_TL_OFFSET + (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								stick_quad_y + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) + INPUT_QUAD_THICKNESS,
								stick_quad_x + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) - INPUT_QUAD_THICKNESS,
								stick_quad_y + INPUT_TL_OFFSET + INPUT_QUAD_SIZE - (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								INPUT_INNER_QUAD_COLOR,
								INPUT_INNER_QUAD_COLOR,
								INPUT_INNER_QUAD_COLOR);
			// Bottom Right
			dl = drawInputRect(dl,
								stick_quad_x + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) + INPUT_QUAD_THICKNESS,
								stick_quad_y + INPUT_TL_OFFSET + (INPUT_QUAD_SIZE / 2) + INPUT_QUAD_THICKNESS,
								stick_quad_x + INPUT_TL_OFFSET + INPUT_QUAD_SIZE - (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								stick_quad_y + INPUT_TL_OFFSET + INPUT_QUAD_SIZE - (INPUT_BORDER_MULT * INPUT_QUAD_THICKNESS),
								INPUT_INNER_QUAD_COLOR, 
								INPUT_INNER_QUAD_COLOR, 
								INPUT_INNER_QUAD_COLOR);
			int stick_x = ControllerInput.stickX;
			int stick_y = ControllerInput.stickY;
			float stick_mult = 0.31496f;
			if (InputStickMax == 0) {
				if (stick_x > 80) {
					stick_x = 80;
				} else if (stick_x < -80) {
					stick_x = -80;
				}
				if (stick_y > 80) {
					stick_y = 80;
				} else if (stick_y < -80) {
					stick_y = -80;
				}
				stick_mult = 0.5f;
			}
			float input_square_x = (stick_quad_x + (INPUT_QUAD_SIZE / 2)) + (stick_mult * stick_x) + INPUT_TL_OFFSET;
			float input_square_y = (stick_quad_y + (INPUT_QUAD_SIZE / 2)) - (stick_mult * stick_y) + INPUT_TL_OFFSET;
			dl = drawInputRect(dl,
								input_square_x - INPUT_STICKBOX_THICKNESS,
								input_square_y - INPUT_STICKBOX_THICKNESS,
								input_square_x + INPUT_STICKBOX_THICKNESS,
								input_square_y + INPUT_STICKBOX_THICKNESS,
								0x1F, 0x0, 0x0);
		}
	}
	return dl;
}