#include "../include/common.h"

static short fairy_x = 0;
static short fairy_y = 0;
static char show_dot = 0;
// Bounds
	// X: 0x8A -> 0xB0
	// Y: 0x61 -> 0x87

void spawnFairyViewer(void) {
	TextOverlay* textOverlay;
	if (FairyViewerOpen == 0) {
		if ((CurrentMap != 0x53) && (CurrentMap != 0xC5)) {
			FairyViewerOpen = 1;
		}
	}
}

void destroyFairyViewer(void) {
	if (FairyViewerOpen) {
		FairyViewerOpen = 0;
	}
}

int* displayFairy(int* dl) {
	if (FairyViewerOpen) {
		dl = drawImage(dl, 48, RGBA16, 32, 32, *(int*)(0x807FFF50), *(int*)(0x807FFF54), *(float*)(0x807FFF58), *(float*)(0x807FFF5C), 0x80);
		if (show_dot) {
			dl = drawTextContainer(dl, 128, FairyViewerData.xPos, (FairyViewerData.yPos * 1.06f) + 69.4f, ".", 0xFF, 0x0, 0x0, 0xFF, 0);
		}
	}
	return dl;
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
		if (FairyViewerFocus) {
			if (isAddressActor(FairyViewerFocus)) {
				fairySpawned = 1;
			}
		}
		if ((FairyViewerData.max_dist_allowed > 0) && (FairyViewerData.xPos != 0x4000) && (FairyViewerData.yPos != 0x4000) && (fairySpawned)) {
			show_dot = 1;
			if (Player) {
				if ((Player->control_state > 1) && (Player->control_state < 6) && (CutsceneActive == 0)) {
					xDist = SwapObject->cameraPositions[0].xPos - FairyViewerFocus->xPos;
					zDist = SwapObject->cameraPositions[0].zPos - FairyViewerFocus->zPos;
					xzDist = dk_sqrt((xDist * xDist) + (zDist * zDist));
					fairy_x = FairyViewerData.xPos;
					fairy_y = 4 * FairyViewerData.yPos - 20;
					diff = FairyViewerData.max_dist_allowed - (int)xzDist;
					// if (diff > 0) {
					// 	fairy_info->red = 0;
					// 	fairy_info->green = 0x64;
					// 	fairy_info->blue = 0;
					// } else {
					// 	fairy_info->red = 0x8B;
					// 	fairy_info->green = 0;
					// 	fairy_info->blue = 0;
					// }
					//dk_strFormat((char *)fairy_info_text,"Max: %d, Fairy: %d",FairyViewerData.max_dist_allowed,(int)xzDist);
				}
			}
		} else {
			show_dot = 0;
			actorData* vehicle = Player->vehicle_actor_pointer;
			if (vehicle) {
				if (vehicle->actorType == 202) {
					show_dot = 1;
				}
			}
			// fairy_info->red = 0xFF;
			// fairy_info->green = 0xFF;
			// fairy_info->blue = 0xFF;
			// dk_strFormat((char *)fairy_info_text,"No fairies in view");
		}
	}
}