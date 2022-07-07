#include "include/common.h"

int* displaySavePrompt(int* dl) {
	if (ShowSavePrompts) {
		if (SavePromptTimer == 0) {
			if (SavePromptIsSaving) {
				if (player_count == 1) {
					int _ingameover = DetectGameOver();
					int _inadventure = DetectAdventure();
					if ((_ingameover) || (_inadventure)) {
						SavePromptTimer = HERTZ;
					}
				}
			}
		} else if (SavePromptTimer > 0) {
			SavePromptTimer--;
			dl = drawPixelTextContainer(dl, 230, 207, "SAVING...", 0xFF, 0xFF, 0xFF, 0xFF, 1);
		}
	}
	return dl;
}