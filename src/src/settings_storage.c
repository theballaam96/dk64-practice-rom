#include "../include/common.h"

void loadSettings(void) {
	
}

void saveSettings(void) {
	if (NewlyPressedControllerInput.Buttons & L_Button) {
		
		SaveGame();
	}
}