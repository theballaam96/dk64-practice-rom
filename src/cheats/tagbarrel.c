#include "../include/common.h"

void toggleTBVoid(void) {
	if (TBVoidByte & 0x30) {
		TBVoidByte = TBVoidByte & 0xCF;
	} else {
		TBVoidByte = TBVoidByte | 0x30;
	}
}

void handleLToTBV(void) {
	if (LToToggleTBOn) {
		if (ActiveMenu.isOpen == 0) {
			if (ClosingMenu == 0) {
				if (NewlyPressedControllerInput.Buttons & L_Button) {
					toggleTBVoid();
				}
			}
		}
	}
}