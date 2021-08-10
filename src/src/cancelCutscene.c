#include "../include/common.h"

void cancelCutscene(void) {
	if ((TBVoidByte & 2) == 0) {
		if (CutsceneActive != 0) {
			if (CutsceneTypePointer) {
				cs_databank = *(int *)(CutsceneTypePointer + 0xD0);
				if (cs_databank) {
					short cam_state = *( short*)(cs_databank + (0xC * CutsceneIndex));
					CurrentCameraState = cam_state;
					PreviousCameraState = cam_state;
					CameraStateChangeTimer = 0;
					if (Player) {
						Player->control_state = 0xC;
					}
				}
			}
		}
	}
}

void toggleCancelCutsceneWithL(void) {
	char _mode = LToCancelCSOn;
	LToCancelCSOn = 1 - _mode;
	// Finish this
}

void LToCancelCS(void) {
	if (LToCancelCSOn) {
		if (ActiveMenu.isOpen == 0) {
			if (ClosingMenu == 0) {
				if (NewlyPressedControllerInput.Buttons & L_Button) {
					cancelCutscene();
				}
			}
		}
	}
}