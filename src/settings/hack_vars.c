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

static char hack_savecombo_off[] = "{ SAVESTATE SHORTHAND COMBO";
static char hack_savecombo_on[] = "} SAVESTATE SHORTHAND COMBO";

static char hack_castle_on[] = "} LIGHTNING EFFECTS";
static char hack_castle_off[] = "{ LIGHTNING EFFECTS";

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
	hack_savecombo_on,
	hack_castle_on,
};

static char* hack_true[] = {
	hack_quickstartup_off,
	hack_forcedstoryskip_on,
	0,
	hack_dpadnavigate_off,
	hack_transformautostock_off,
	hack_savenotifs_on,
	0,
	0,
	hack_fileinitqol_off,
	hack_inputmax_127,
	hack_inputtype_lowlag,
	0,
	hack_sfx_off,
	hack_savecombo_off,
	hack_castle_off,
};

static char* hack_false[] = {
	hack_quickstartup_on,
	hack_forcedstoryskip_off,
	0,
	hack_dpadnavigate_on,
	hack_transformautostock_on,
	hack_savenotifs_off,
	0,
	0,
	hack_fileinitqol_on,
	hack_inputmax_70,
	hack_inputtype_detailed,
	0,
	hack_sfx_on,
	hack_savecombo_on,
	hack_castle_on,
};

static char* hack_addr[] = {
	(char*)&DisableStartupSkip,
	(char*)&DisableForcedStorySkip,
	0,
	(char*)&MenuShortcutButtonsOff,
	(char*)&TransformAutoRestockOff,
	(char*)&ShowSavePrompts,
	0,
	0,
	(char*)&FileInitQOLOff,
	(char*)&InputStickMax,
	(char*)&InputDisplayType,
	0,
	(char*)&disableCustomSFX,
	(char*)&disableSavestateCombo,
	(char*)&disablelightning,
};

static char* hack_console_list[] = {
	hack_console_none,
	hack_console_n64,
	hack_console_wiiu,
	hack_console_emu,
};

void openHackVarsMenu(void) {
	for (int i = 0; i < sizeof(hack_addr)/4; i++) {
		if (hack_addr[i] != 0) {
			if (*(char*)hack_addr[i]) {
				hack_array[i] = hack_true[i];
			} else {
				hack_array[i] = hack_false[i];
			}
		}
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
	hack_array[11] = hack_console_list[(int)assignedConsole];
	changeMenu(ACTIVEMENU_SCREEN_SETTINGS_HACK);
};

void togglePauseVolume(void) {
	PauseMenuMusicSetting += 1;
	if (PauseMenuMusicSetting > 2) {
		PauseMenuMusicSetting = 0;
	};
	saveSettings();
	openHackVarsMenu();
}

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

void toggleConsole(void) {
	if (assignedConsole < 3) {
		assignedConsole += 1;
	} else {
		assignedConsole = 1;
	}
	saveSettings();
	openHackVarsMenu();
}

void lightning_handle(int disable) {
	if (
		(CurrentMap == 0x6F) || // Pufftoss
		(CurrentMap == 8) || // Japes Dillo
		(CurrentMap == 0x57) || // Castle
		(CurrentMap == 0xC7) // King Kut Out
	) {
		actorData* lzcontroller = (actorData*)findActorWithType(0xC);
		char* lzpaad = (char*)lzcontroller->paad;
		*(char*)(lzpaad) = 3 - disable;
	}
}

void controlLightning(void) {
	if (disablelightning) {
		lightning_handle(TimerData.Mode != 1);
	}
}

void toggleSetting(void) {
	int pos = ActiveMenu.positionIndex;
	if (hack_addr[pos] != 0) {
		*(char*)hack_addr[pos] = 1 ^ *(char*)hack_addr[pos];
	}
	saveSettings();
	if (hack_addr[pos] == (char*)&InputDisplayType) {
		closeOverlay();
		spawnOverlay();
	}
	if (hack_addr[pos] == (char*)&disablelightning) {
		int handle_byte = 0;
		if (TimerData.Mode != 1) {
			handle_byte = disablelightning;
		}
		lightning_handle(handle_byte);
	}
	openHackVarsMenu();
}

static const int hack_functions[] = {
	(int)&toggleSetting,
	(int)&toggleSetting,
	(int)&togglePauseVolume,
	(int)&toggleSetting,
	(int)&toggleSetting,
	(int)&toggleSetting,
	(int)&togglePrecision,
	(int)&toggleKRoolRoundSetting,
	(int)&toggleSetting,
	(int)&toggleSetting,
	(int)&toggleSetting,
	(int)&toggleConsole,
	(int)&toggleSetting,
	(int)&toggleSetting,
	(int)&toggleSetting,
};

const Screen hack_struct = {
	.TextArray = (int*)hack_array,
	.FunctionArray = hack_functions,
	.ArrayItems = 15,
	.ParentScreen = ACTIVEMENU_SCREEN_SETTINGS_ROOT,
	.ParentPosition = 3
};