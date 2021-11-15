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
		if (InputDisplayOpen) {
			spawnOverlay();
		}
	}
};

void closeInputOnTransition(void) {
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		if ((InputDisplayOpen) || (FairyViewerOpen)) {
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
				if ((ActiveMenu.isOpen) && (InputDisplayOpen)) {
					spriteSlots[i]->scale = 0;
					otherSpriteData[i]->xScale = 0;
					otherSpriteData[i]->yScale = 0;
					InputSpritesSpawned = 0;
				} else {
					if (InputDisplayOpen) {
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