#include "../include/common.h"

static TextOverlay* fairy_dot;
static TextOverlay* fairy_info;
static char fairy_info_text[40] = "";
static char fairy_dot_text[] = ".";
// Bounds
	// X: 0x8A -> 0xB0
	// Y: 0x61 -> 0x87

void spawnFairyViewer(void) {
	TextOverlay* textOverlay;
	if (FairyViewerOpen == 0) {
		if ((CurrentMap != 0x53) && (CurrentMap != 0xC5)) {
			if (spriteSlots[12]) {
				spriteSlots[12]->scale = 1.25; // 1.2 was too short on right
			}
			if (otherSpriteData[12]) {
				otherSpriteData[12]->transparency1 = 60; // R
				otherSpriteData[12]->transparency2 = 60; // G
				otherSpriteData[12]->transparency3 = 60; // B
			}
			// Dot
			spawnTextOverlay(10,10,10,"TEST",0,0,2,0);
			textOverlay = (TextOverlay *)CurrentActorPointer;
			if (textOverlay) {
				fairy_dot = textOverlay;
				textOverlay->style = 128;
				textOverlay->string = (char *)fairy_dot_text;
				textOverlay->red = 0xFF;
				textOverlay->green = 0;
				textOverlay->blue = 0;
				textOverlay->opacity = 0xFF;
			}
			// Fairy Info
			spawnTextOverlay(0,50,150,"No fairies in view",0,0,2,0);
			textOverlay = (TextOverlay *)CurrentActorPointer;
			if (textOverlay) {
				fairy_info = textOverlay;
				textOverlay->string = (char *)fairy_info_text;
				textOverlay->style = 128;
				textOverlay->opacity = 0xFF;
			}
			FairyViewerOpen = 1;
		}
	}
}

void destroyFairyViewer(void) {
	if (FairyViewerOpen) {
		FairyViewerOpen = 0;
		if (otherSpriteData[12]) {
			otherSpriteData[12]->xScale = 0;
			otherSpriteData[12]->yScale = 0;
		}
		if (fairy_dot) {
			deleteActor(fairy_dot);
			fairy_dot = 0;
		}
		if (fairy_info) {
			deleteActor(fairy_info);
			fairy_info = 0;
		}
	}
}

void destroyViewerOnTransition(void) {
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		destroyFairyViewer();
	}
};

void toggleFairyViewer(void) {
	if (FairyViewerOpen) {
		destroyFairyViewer();
	} else {
		spawnFairyViewer();
	}
}

void controlFairyViewer(void) {
	float xDist = 0;
	float zDist = 0;
	float xzDist = 0;
	int fairySpawned = 0;
	int diff = 0;
	if (FairyViewerOpen) {
		if (otherSpriteData[12]) {
			otherSpriteData[12]->some_pointer = 0;
			otherSpriteData[12]->xScale = 4 * 1.2975;
			otherSpriteData[12]->yScale = 4 * 1.245;
			otherSpriteData[12]->xPos = 631;
			otherSpriteData[12]->yPos = 487.25;
		}
		if (FairyViewerFocus) {
			if (isAddressActor(FairyViewerFocus)) {
				fairySpawned = 1;
			}
		}
		if ((FairyViewerData.max_dist_allowed > 0) && (FairyViewerData.xPos != 0x4000) && (FairyViewerData.yPos != 0x4000) && (fairySpawned)) {
			fairy_dot->opacity = 0xFF;
			if (Player) {
				if ((Player->control_state > 1) && (Player->control_state < 6) && (CutsceneActive == 0)) {
					xDist = SwapObject->cameraPositions[0].xPos - FairyViewerFocus->xPos;
					zDist = SwapObject->cameraPositions[0].zPos - FairyViewerFocus->zPos;
					xzDist = dk_sqrt((xDist * xDist) + (zDist * zDist));
					fairy_dot->xPos = 4 * FairyViewerData.xPos;
					fairy_dot->yPos = 4 * FairyViewerData.yPos - 20;
					diff = FairyViewerData.max_dist_allowed - (int)xzDist;
					if (diff > 0) {
						fairy_info->red = 0;
						fairy_info->green = 0x64;
						fairy_info->blue = 0;
					} else {
						fairy_info->red = 0x8B;
						fairy_info->green = 0;
						fairy_info->blue = 0;
					}
					dk_strFormat((char *)fairy_info_text,"Max: %d, Fairy: %d",FairyViewerData.max_dist_allowed,(int)xzDist);
				}
			}
		} else {
			fairy_dot->opacity = 0;
			fairy_info->red = 0xFF;
			fairy_info->green = 0xFF;
			fairy_info->blue = 0xFF;
			dk_strFormat((char *)fairy_info_text,"No fairies in view");
		}
	}
}