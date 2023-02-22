#include "../../include/common.h"

static short fairy_x = 0;
static short fairy_y = 0;
static int fairy_dist = 0;
static int max_dist = 0;
static char show_dot = 0;
static char fairy_text[25];
// Bounds
	// X: 0x8A -> 0xB0
	// Y: 0x61 -> 0x87

void spawnFairyViewer(void) {
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
	if (FairyViewerOpen && !ActiveMenu.isOpen) {
		int y = 140;
		dl = drawImage(dl, IMAGE_FAIRYBOX, RGBA16, 32, 32, 623, 467, 5.19f, 4.83f, 0x80);
		if (show_dot) {
			dl = drawImage(dl, IMAGE_FAIRYDOT, RGBA16, 16, 16, (3.9498f * fairy_x) + 8.5118f, (3.9178f * fairy_y) + 10.822f, 1.0f, 1.0f, 0xFF);
			int diff = max_dist - fairy_dist;
			int red_col = 0xFF;
			dk_strFormat(fairy_text, "DIST:%d",diff);
			if (diff > 0) {
				red_col = 0;
			}
			//dl = drawTextContainer(dl, 128, 135, y, (char*)fairy_text, red_col, 0xFF - red_col, 0x00, 0xFF, 1);
			dl = drawPixelTextContainer(dl, 135, y, (char *)fairy_text, red_col, 0xFF - red_col, 0x00, 0xFF, 1);
		} else {
			//dl = drawTextContainer(dl, 128, 100, y, "No Fairies in View", 0xFF, 0xFF, 0xFF, 0xFF, 1);
			dl = drawPixelTextContainer(dl, 85, y, "NO FAIRIES IN VIEW", 0xFF, 0xFF, 0xFF, 0xFF, 1);
		}
	}
	return dl;
}

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
	int fairySpawned = 0;
	if (FairyViewerOpen) {
		if (FairyViewerFocus) {
			if (isAddressActor(FairyViewerFocus)) {
				fairySpawned = 1;
			}
		}
		if ((FairyViewerData.max_dist_allowed > 0) && (FairyViewerData.xPos != 0x4000) && (FairyViewerData.yPos != 0x4000) && (fairySpawned)) {
			show_dot = 1;
			if (Player) {
				if ((Player->control_state > 1) && ((Player->control_state < 6) || (Player->control_state == 100)) && (CutsceneActive == 0)) {
					xDist = SwapObject->camera_position.xPos - FairyViewerFocus->xPos;
					zDist = SwapObject->camera_position.zPos - FairyViewerFocus->zPos;
					if (Player->control_state != 100) {
						actorData* vehicle = Player->vehicle_actor_pointer;
						int pass = 1;
						if (vehicle) {
							if (vehicle->actorType == 202) {
								pass = 0;
							}
						}
						if (pass) {
							fairy_dist = dk_sqrt((xDist * xDist) + (zDist * zDist)) - SwapObject->near;
						}
					}
					fairy_x = FairyViewerData.xPos;
					fairy_y = FairyViewerData.yPos;
					max_dist = FairyViewerData.max_dist_allowed;
				}
			}
		} else {
			show_dot = 0;
			actorData* vehicle = Player->vehicle_actor_pointer;
			if (vehicle) {
				if (vehicle->actorType == 202) {
					if (Player) {
						if (Player->fairy_state > -1) {
							show_dot = 1;
						}
					}
				}
			}
		}
	}
}