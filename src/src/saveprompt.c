#include "../include/common.h"

void destroySavePrompt(void) {
	if (SavePromptActor) {
		deleteActor(SavePromptActor);
		SavePromptActor = 0;
		SavePromptTimer = 0;
	}
}

void clearSavePromptFlag(void) {
	SavePromptIsSaving = 0;
}

void displaySavePrompt(void) {
	TextOverlay* textOverlay;
	if (ShowSavePrompts) {
		if ((TransitionSpeed > 0) || (CutsceneActive == 6)) {
			destroySavePrompt();
		} else {
			if (SavePromptTimer == 0) {
				if (SavePromptIsSaving) {
					SavePromptTimer = 60;
					spawnTextOverlay(10,240,210,"SAVING...",0,0,2,0);
					textOverlay = (TextOverlay *)CurrentActorPointer;
					if (textOverlay) {
						SavePromptActor = textOverlay;
						textOverlay->opacity = 0xFF;
					}
				}
			} else {
				SavePromptTimer--;
				if (SavePromptTimer == 0) {
					destroySavePrompt();
				}
			}
		}
	}
}