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
// Order ABZSLR C:UDLR
static const short root_x[] = {0x00,0xB0,0x00,0xB0};
static const short root_y[] = {0x00,0x00,0xA0,0xA0};
static const short x_positions[] = {0x54, 0x48, 0x34, 0x34, 0x20, 0x78, 0x68, 0x68, 0x58, 0x78, 0x20};
static const short y_positions[] = {0x38, 0x2C, 0x34, 0x20, 0x20, 0x20, 0x24, 0x34, 0x2C, 0x2C, 0x34};
static const unsigned char sprite_table_indexes[] = {0x6E,0x6F,0x70,0x91,0x88,0x87,0x72,0x71,0x73,0x73};
static const unsigned short button_bits[] = {A_Button,B_Button,Z_Button,Start_Button,L_Button,R_Button,C_Up,C_Down,C_Left,C_Right};
static const float target_size[] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5};
static spriteDisplay* displaySlots[] = {
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
};
static spriteControl* spriteSlots[12] = {};
static otherSpriteControl* otherSpriteData[12] = {};

void openInputOnTransition(void) {
	char _movement_style;
	if ((TransitionSpeed < 0) || ((CutsceneActive == 6) && (CurrentMap != 0x50))) {
		if (spriteSlots[0] == 0) {
			if (InputDisplayQuadrant < 4) {
				for (int i = 0; i < 10; i++) {
					if (displaySlots[i]) {
						displaySlots[i]->disappear = 0;
					}
					sprite_translucency = 0;
					_movement_style = 4;
					displaySprite(displaySlots[i],sprite_table[(int)sprite_table_indexes[i]],root_x[(int)InputDisplayQuadrant] + x_positions[i],root_y[(int)InputDisplayQuadrant] + y_positions[i],(int)target_size[i],0,_movement_style);
					spriteSlots[i] = (spriteControl*)SpriteAddress;
					otherSpriteData[i] = (otherSpriteControl*)getOtherSpritePointer();
				}
				displaySlots[10]->disappear = 0;
				sprite_translucency = 1;
				displaySprite(displaySlots[10],sprite_table[0x67],root_x[(int)InputDisplayQuadrant] + 0x20,root_y[(int)InputDisplayQuadrant] + 0x34,0.5,0,4);
				spriteSlots[10] = (spriteControl*)SpriteAddress;
				otherSpriteData[10] = (otherSpriteControl*)getOtherSpritePointer();
				displaySlots[11]->disappear = 0;
				sprite_translucency = 1;
				// 0x22
				displaySprite(displaySlots[11],sprite_table[0x91],root_x[(int)InputDisplayQuadrant] + 0x20,root_y[(int)InputDisplayQuadrant] + 0x34,0.2,0,4);
				spriteSlots[11] = (spriteControl*)SpriteAddress;
				otherSpriteData[11] = (otherSpriteControl*)getOtherSpritePointer();
				InputSpritesSpawned = 0;
			}
		}
	}
};

void closeInputOnTransition(void) {
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		for (int i = 0; i < 12; i++) {
			spriteSlots[i] = 0;
			otherSpriteData[i] = 0;
		}
		InputSpritesSpawned = 0;
	}
};

void displayInput(void) {
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
			if ((ActiveMenu.isOpen) || (InputDisplayOpen == 0)) {
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
							spriteSlots[i]->scale = 0.5;
						}
						if (i == 10) {
							otherSpriteData[i]->transparency1 = 150;
							otherSpriteData[i]->transparency2 = 150;
							otherSpriteData[i]->transparency3 = 150;
						}
						if (i == 11) {
							// Joystick Position
							spriteSlots[i]->scale = 0.2;
							spriteSlots[i]->xPos = (root_x[(int)InputDisplayQuadrant] * 4) + 127 + (0.3 * (float)(ControllerInput.stickX));
							spriteSlots[i]->yPos = (root_y[(int)InputDisplayQuadrant] * 4) + 210 - (0.3 * (float)(ControllerInput.stickY));
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
};
