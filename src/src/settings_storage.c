#include "../include/common.h"

void loadSettings(void) {
	if (StoredSettings.hasSavedData) {
		for (int i = 0; i < 5; i++) {
			kongcolors[i] = StoredSettings.kongColors[i];
		}
		DisableStartupSkip = StoredSettings.quickStartup;
		DisableForcedStorySkip = StoredSettings.forcedStorySkip;
		DisablePositionButtons = StoredSettings.DPadLRFunction;
		DisableTagAnywhere = StoredSettings.DPadDFunction;
		PauseMenuMusicSetting = StoredSettings.pauseVolume;
		MenuShortcutButtonsOff = StoredSettings.navigateMenuMode;
		ShowSavePrompts = StoredSettings.displaySavePrompt;
		Precision = StoredSettings.precision;
	} else {
		StoredSettings.hasSavedData = 1;
		StoredSettings.kongColors[0] = 1;
		StoredSettings.kongColors[1] = 2;
		StoredSettings.kongColors[2] = 2;
		StoredSettings.kongColors[3] = 2;
		StoredSettings.kongColors[4] = 1;
		StoredSettings.quickStartup = 0;
		StoredSettings.forcedStorySkip = 0;
		StoredSettings.pauseVolume = 0;
		StoredSettings.navigateMenuMode = 0;
		StoredSettings.DPadLRFunction = 0;
		StoredSettings.DPadDFunction = 0;
		StoredSettings.displaySavePrompt = 0;
		StoredSettings.precision = 2;
		SaveToGlobal();
		loadSettings();
	}
}

void saveSettings(void) {
	for (int i = 0; i < 5; i++) {
		StoredSettings.kongColors[i] = kongcolors[i];
	}
	StoredSettings.quickStartup = DisableStartupSkip;
	StoredSettings.forcedStorySkip = DisableForcedStorySkip;
	StoredSettings.DPadLRFunction = DisablePositionButtons;
	StoredSettings.DPadDFunction = DisableTagAnywhere;
	StoredSettings.pauseVolume = PauseMenuMusicSetting;
	StoredSettings.navigateMenuMode = MenuShortcutButtonsOff;
	StoredSettings.displaySavePrompt = ShowSavePrompts;
	StoredSettings.precision = Precision;
	SaveToGlobal();
}