#include "../include/common.h"

void cancelCutscene(void) {
	if ((TBVoidByte & 2) == 0) {
		if (CutsceneActive) {
			if (CutsceneTypePointer) {
				if (CutsceneTypePointer->cutscene_databank) {
					int* databank = (int *)(CutsceneTypePointer->cutscene_databank);
					short cam_state = *(short *)(getObjectArrayAddr(databank,0xC,CutsceneIndex));
					// short cam_state = *( short*)(cs_databank + (0xC * CutsceneIndex));
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