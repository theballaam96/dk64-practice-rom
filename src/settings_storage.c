#include "../include/common.h"

void resetSettings(void) {
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
	StoredSettings.input_quadrant = 0;
	StoredSettings.transform_autostock = 0;
	StoredSettings.krool_round_setting = 0;
	StoredSettings.file_init_qol = 0;
	StoredSettings.input_max = 0;
	StoredSettings.console = 0;
	StoredSettings.input_type = 0;
	StoredSettings.jetman_color = 0;
	StoredSettings.savestate_bitfield = 0;
	SaveToGlobal();
	loadSettings();
}

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
		InputDisplayQuadrant = StoredSettings.input_quadrant;
		TransformAutoRestockOff = StoredSettings.transform_autostock;
		KRoolRoundSetting = StoredSettings.krool_round_setting;
		FileInitQOLOff = StoredSettings.file_init_qol;
		InputStickMax = StoredSettings.input_max;
		assignedConsole = StoredSettings.console;
		InputDisplayType = StoredSettings.input_type;
		jetmanColorIndex = StoredSettings.jetman_color;
		savestateSettingsBitfield = StoredSettings.savestate_bitfield;
	} else {
		resetSettings();
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
	StoredSettings.input_quadrant = InputDisplayQuadrant;
	StoredSettings.transform_autostock = TransformAutoRestockOff;
	StoredSettings.krool_round_setting = KRoolRoundSetting;
	StoredSettings.file_init_qol = FileInitQOLOff;
	StoredSettings.input_max = InputStickMax;
	StoredSettings.console = assignedConsole;
	StoredSettings.input_type = InputDisplayType;
	StoredSettings.jetman_color = jetmanColorIndex;
	StoredSettings.savestate_bitfield = savestateSettingsBitfield;
	SaveToGlobal();
}