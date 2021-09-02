#include "../../include/common.h"

static char hack_quickstartup_on[] = "Quick Startup: On";
static char hack_quickstartup_off[] = "Quick Startup: Off";

static char hack_forcedstoryskip_on[] = "Forced Story Skip: On";
static char hack_forcedstoryskip_off[] = "Forced Story Skip: Off";

static char hack_pausevolume_normal[] = "Pause Volume: Normal";
static char hack_pausevolume_quiet[] = "Pause Volume: Quiet";
static char hack_pausevolume_silent[] = "Pause Volume: Silent";

static char hack_dpadnavigate_on[] = "D-Pad to Navigate Menu: On";
static char hack_dpadnavigate_off[] = "D-Pad to Navigate Menu: Off";

static char hack_transformautostock_on[] = "Transform Cheat Auto-Restock: On";
static char hack_transformautostock_off[] = "Transform Cheat Auto-Restock: Off";

static char hack_savenotifs_on[] = "Save Notifications: On";
static char hack_savenotifs_off[] = "Save Notifications: Off";

static char hack_precision[16] = "Precision: 0";

static char hack_kroolround_random[] = "K. Rool Round Number: Random";
static char hack_kroolround_forcedsequential[] = "K. Rool Round Number: Forced Sequential";
static char hack_kroolround_normal[] = "K. Rool Round Number: Normal";

static char hack_fileinitqol_on[] = "File Start State: Prepared";
static char hack_fileinitqol_off[] = "File Start State: Vanilla";

static char hack_inputmax_70[] = "Input Stick Max: Threshold";
static char hack_inputmax_127[] = "Input Stick Max: Full Magnitude";

static char* hack_array[] = {
	hack_quickstartup_on,
	hack_forcedstoryskip_on,
	hack_pausevolume_normal,
	hack_dpadnavigate_on,
	hack_transformautostock_on,
	hack_savenotifs_on,
	hack_precision,
	hack_kroolround_random,
	hack_fileinitqol_on,
	hack_inputmax_70,
};

void openHackVarsMenu(void) {
	if (DisableStartupSkip) {
		hack_array[0] = hack_quickstartup_off;
	} else {
		hack_array[0] = hack_quickstartup_on;
	}
	if (DisableForcedStorySkip) {
		hack_array[1] = hack_forcedstoryskip_off;
	} else {
		hack_array[1] = hack_forcedstoryskip_on;
	}
	if (PauseMenuMusicSetting == 2) {
		hack_array[2] = hack_pausevolume_silent;
	} else {
		if (PauseMenuMusicSetting == 1) {
			hack_array[2] = hack_pausevolume_quiet;
		} else {
			hack_array[2] = hack_pausevolume_normal;
		}
	}
	if (MenuShortcutButtonsOff) {
		hack_array[3] = hack_dpadnavigate_off;
	} else {
		hack_array[3] = hack_dpadnavigate_on;
	}
	if (TransformAutoRestockOff) {
		hack_array[4] = hack_transformautostock_off;
	} else {
		hack_array[4] = hack_transformautostock_on;
	}
	if (ShowSavePrompts) {
		hack_array[5] = hack_savenotifs_on;
	} else {
		hack_array[5] = hack_savenotifs_off;
	}
	dk_strFormat((char *)hack_precision,"Precision: %d",Precision);
	if (KRoolRoundSetting == 2) {
		hack_array[7] = hack_kroolround_normal;
	} else {
		if (KRoolRoundSetting == 1) {
			hack_array[7] = hack_kroolround_forcedsequential;
		} else {
			hack_array[7] = hack_kroolround_random;
		}
	}
	if (FileInitQOLOff) {
		hack_array[8] = hack_fileinitqol_off;
	} else {
		hack_array[8] = hack_fileinitqol_on;
	}
	if (InputStickMax) {
		hack_array[9] = hack_inputmax_127;
	} else {
		hack_array[9] = hack_inputmax_70;
	}
	changeMenu(69);
};

void toggleQuickStartup(void) {
	DisableStartupSkip = 1 - DisableStartupSkip;
	saveSettings();
	openHackVarsMenu();
}

void toggleForcedStorySkip(void) {
	DisableForcedStorySkip = 1 - DisableForcedStorySkip;
	saveSettings();
	openHackVarsMenu();
}

void togglePauseVolume(void) {
	PauseMenuMusicSetting += 1;
	if (PauseMenuMusicSetting > 2) {
		PauseMenuMusicSetting = 0;
	};
	saveSettings();
	openHackVarsMenu();
}

void toggleDPadNavigation(void) {
	MenuShortcutButtonsOff = 1 - MenuShortcutButtonsOff;
	saveSettings();
	openHackVarsMenu();
}

void toggleTransformAutostock(void) {
	TransformAutoRestockOff = 1 - TransformAutoRestockOff;
	saveSettings();
	openHackVarsMenu();
}

void toggleSaveNotifications(void) {
	ShowSavePrompts = 1 - ShowSavePrompts;
	saveSettings();
	openHackVarsMenu();
};

void togglePrecision(void) {
	Precision += 1;
	if (Precision > 6) {
		Precision = 0;
	}
	saveSettings();
	openHackVarsMenu();
}

void toggleKRoolRoundSetting(void) {
	KRoolRoundSetting += 1;
	if (KRoolRoundSetting > 1) {
		KRoolRoundSetting = 0;
	};
	saveSettings();
	openHackVarsMenu();
}

void toggleFileStartState(void) {
	FileInitQOLOff = 1 - FileInitQOLOff;
	saveSettings();
	openHackVarsMenu();
}

void toggleInputMax(void) {
	InputStickMax = 1 - InputStickMax;
	saveSettings();
	openHackVarsMenu();
}

static const int hack_functions[] = {
	(int)&toggleQuickStartup,
	(int)&toggleForcedStorySkip,
	(int)&togglePauseVolume,
	(int)&toggleDPadNavigation,
	(int)&toggleTransformAutostock,
	(int)&toggleSaveNotifications,
	(int)&togglePrecision,
	(int)&toggleKRoolRoundSetting,
	(int)&toggleFileStartState,
	(int)&toggleInputMax,
};

const Screen hack_struct = {
	.TextArray = (int*)hack_array,
	.FunctionArray = hack_functions,
	.ArrayItems = 10,
	.ParentScreen = 57,
	.ParentPosition = 3
};