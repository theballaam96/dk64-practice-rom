#include "../../include/common.h"

static char hack_quickstartup_on[] = "} QUICK STARTUP";
static char hack_quickstartup_off[] = "{ QUICK STARTUP";

static char hack_forcedstoryskip_on[] = "{ FORCED STORY SKIP";
static char hack_forcedstoryskip_off[] = "} FORCED STORY SKIP";

static char hack_pausevolume_normal[] = "PAUSE VOLUME:NORMAL";
static char hack_pausevolume_quiet[] = "PAUSE VOLUME:QUIET";
static char hack_pausevolume_silent[] = "PAUSE VOLUME:SILENT";

static char hack_dpadnavigate_on[] = "} D-PAD TO NAVIGATE MENU";
static char hack_dpadnavigate_off[] = "{ D-PAD TO NAVIGATE MENU";

static char hack_transformautostock_on[] = "TRANSFORM CHEAT:DON^T CONSUME";
static char hack_transformautostock_off[] = "TRANSFORM CHEAT:CONSUME";

static char hack_savenotifs_on[] = "} SAVE NOTIFICATIONS";
static char hack_savenotifs_off[] = "{ SAVE NOTIFICATIONS";

static char hack_precision[16] = "PRECISION:0";

static char hack_kroolround_random[] = "K.ROOL ROUND NUMBER:RANDOM";
static char hack_kroolround_forcedsequential[] = "K.ROOL ROUND NUMBER:FORCED SEQUENTIAL";
static char hack_kroolround_normal[] = "K.ROOL ROUND NUMBER:NORMAL";

static char hack_fileinitqol_on[] = "FILE START STATE:PREPARED";
static char hack_fileinitqol_off[] = "FILE START STATE:VANILLA";

static char hack_inputmax_70[] = "INPUT STICK MAX:THRESHOLD";
static char hack_inputmax_127[] = "INPUT STICK MAX:FULL MAGNITUDE";

static char hack_inputtype_detailed[] = "INPUT TYPE:DETAILED";
static char hack_inputtype_lowlag[] = "INPUT TYPE:LOW LAG";

static char hack_console_none[] = "CONSOLE:NONE";
static char hack_console_n64[] = "CONSOLE:NINTENDO 64";
static char hack_console_wiiu[] = "CONSOLE:WII U";
static char hack_console_emu[] = "CONSOLE:EMULATOR";

static char hack_sfx_off[] = "{ PRACTICE ROM SOUND EFFECTS";
static char hack_sfx_on[] = "} PRACTICE ROM SOUND EFFECTS";

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
	hack_inputtype_detailed,
	hack_console_none,
	hack_sfx_on,
};

static char* hack_console_list[] = {
	hack_console_none,
	hack_console_n64,
	hack_console_wiiu,
	hack_console_emu,
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
	dk_strFormat((char *)hack_precision,"PRECISION: %d",Precision);
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
	if (InputDisplayType) {
		hack_array[10] = hack_inputtype_lowlag;
	} else {
		hack_array[10] = hack_inputtype_detailed;
	}
	hack_array[11] = hack_console_list[(int)assignedConsole];
	if (disableCustomSFX) {
		hack_array[12] = hack_sfx_off;
	} else {
		hack_array[12] = hack_sfx_on;
	}
	changeMenu(69);
};

void toggleQuickStartup(void) {
	DisableStartupSkip = 1 ^ DisableStartupSkip;
	saveSettings();
	openHackVarsMenu();
}

void toggleForcedStorySkip(void) {
	DisableForcedStorySkip = 1 ^ DisableForcedStorySkip;
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
	MenuShortcutButtonsOff = 1 ^ MenuShortcutButtonsOff;
	saveSettings();
	openHackVarsMenu();
}

void toggleTransformAutostock(void) {
	TransformAutoRestockOff = 1 ^ TransformAutoRestockOff;
	saveSettings();
	openHackVarsMenu();
}

void toggleSaveNotifications(void) {
	ShowSavePrompts = 1 ^ ShowSavePrompts;
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
	FileInitQOLOff = 1 ^ FileInitQOLOff;
	saveSettings();
	openHackVarsMenu();
}

void toggleInputMax(void) {
	InputStickMax = 1 ^ InputStickMax;
	saveSettings();
	openHackVarsMenu();
}

void toggleConsole(void) {
	if (assignedConsole < 3) {
		assignedConsole += 1;
	} else {
		assignedConsole = 1;
	}
	saveSettings();
	openHackVarsMenu();
}

void toggleInputType(void) {
	InputDisplayType = 1 ^ InputDisplayType;
	saveSettings();
	closeOverlay();
	spawnOverlay();
	openHackVarsMenu();
}

void toggleSFX(void) {
	disableCustomSFX = 1 ^ disableCustomSFX;
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
	(int)&toggleInputType,
	(int)&toggleConsole,
	(int)&toggleSFX,
};

const Screen hack_struct = {
	.TextArray = (int*)hack_array,
	.FunctionArray = hack_functions,
	.ArrayItems = 13,
	.ParentScreen = 57,
	.ParentPosition = 3
};