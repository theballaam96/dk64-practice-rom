#include "../../include/common.h"

static const char toggles_moonkick_off[] = "Auto-Moonkick: Off";
static const char toggles_moonkick_on[] = "Auto-Moonkick: On";

static const char toggles_phase_off[] = "Auto-Phase State: Off";
static const char toggles_phase_on[] = "Auto-Phase State: On";

static const char toggles_sandstorm_unk[] = "Aztec Sandstorm: ?";
static const char toggles_sandstorm_off[] = "Aztec Sandstorm: Off";
static const char toggles_sandstorm_on[] = "Aztec Sandstorm: On";

static const char toggles_enemyspawn_off[] = "Enemy Spawning: Off";
static const char toggles_enemyspawn_on[] = "Enemy Spawning: On";

static const char toggles_minigamems_off[] = "Minigame Timers: Normal";
static const char toggles_minigamems_on[] = "Minigame Timers: Milliseconds";

static const char toggles_infhealth_off[] = "Infinite Health: Off";
static const char toggles_infhealth_on[] = "Infinite Health: On";

static const char toggles_ltocancelcs_off[] = "L to Cancel Cutscene: Off";
static const char toggles_ltocancelcs_on[] = "L to Cancel Cutscene: On";

static const char toggles_ltoendminigame_off[] = "L to End Minigame: Off";
static const char toggles_ltoendminigame_on[] = "L to End Minigame: On";

static const char toggles_levitate_off[] = "L to Levitate: Off";
static const char toggles_levitate_on[] = "L to Levitate: On";

static const char toggles_ltotoggletb_off[] = "L to Toggle Tag Barrel Void: Off";
static const char toggles_ltotoggletb_on[] = "L to Toggle Tag Barrel Void: On";

static const char toggles_superspeed_off[] = "L to Superspeed: Off";
static const char toggles_superspeed[20] = "L to Superspeed: 1x";
static const char toggles_toggletb[] = "Toggle Tag Barrel Void";
static const char toggles_visify[] = "Toggle Visibility";
static const char toggles_turnoffall[] = "Turn off all cheats";

static const char* toggles_array[] = {
	toggles_moonkick_off,
	toggles_phase_off,
	toggles_sandstorm_unk,
	toggles_enemyspawn_off,
	toggles_minigamems_off,
	toggles_infhealth_off,
	toggles_ltocancelcs_off,
	toggles_ltoendminigame_off,
	toggles_levitate_off,
	toggles_superspeed,
	toggles_ltotoggletb_off,
	toggles_toggletb,
	toggles_visify,
	toggles_turnoffall,
};

void openTogglesMenu(void) {
	if (AutoMoonkickOn) {
		toggles_array[0] = toggles_moonkick_on;
	} else {
		toggles_array[0] = toggles_moonkick_off;
	}
	if (AutoPhaseStateOn) {
		toggles_array[1] = toggles_phase_on;
	} else {
		toggles_array[1] = toggles_phase_off;
	}
	if (CurrentMap == 0x26) {
		if (*(char *)SandstormAddress) {
			toggles_array[2] = toggles_sandstorm_on;
		} else {
			toggles_array[2] = toggles_sandstorm_off;
		}
	} else {
		toggles_array[2] = toggles_sandstorm_unk;
	}
	if (EnemySpawnOff) {
		toggles_array[3] = toggles_enemyspawn_off;
	} else {
		toggles_array[3] = toggles_enemyspawn_on;
	}
	if (MinigameTimersInMS) {
		toggles_array[4] = toggles_minigamems_on;
	} else {
		toggles_array[4] = toggles_minigamems_off;
	}
	if (InfiniteHealthCheatOn) {
		toggles_array[5] = toggles_infhealth_on;
	} else {
		toggles_array[5] = toggles_infhealth_off;
	}
	if (LToCancelCSOn) {
		toggles_array[6] = toggles_ltocancelcs_on;
	} else {
		toggles_array[6] = toggles_ltocancelcs_off;
	}
	if (LToEndGameOn) {
		toggles_array[7] = toggles_ltoendminigame_on;
	} else {
		toggles_array[7] = toggles_ltoendminigame_off;
	}
	if (LToLevitateOn) {
		toggles_array[8] = toggles_levitate_on;
	} else {
		toggles_array[8] = toggles_levitate_off;
	}
	dk_strFormat((char *)toggles_superspeed,"L to Superspeed: %dx",IsSuperspeedOn);
	if (IsSuperspeedOn == 1) {
		toggles_array[9] = toggles_superspeed_off;
	} else {
		toggles_array[9] = toggles_superspeed;
	}
	if (LToToggleTBOn) {
		toggles_array[10] = toggles_ltotoggletb_on;
	} else {
		toggles_array[10] = toggles_ltotoggletb_off;
	}
	changeMenu(71);
}

void toggleAutokick(void) {
	AutoMoonkickOn = 1- AutoMoonkickOn;
	openTogglesMenu();
}

void toggleAutophase(void) {
	AutoPhaseStateOn = 1 - AutoPhaseStateOn;
	openTogglesMenu();
}

void toggleInfHealth(void) {
	InfiniteHealthCheatOn = 1 - InfiniteHealthCheatOn;
	openTogglesMenu();
}

void toggleLToCancelCS(void) {
	LToCancelCSOn = 1 - LToCancelCSOn;
	openTogglesMenu();
}

void toggleLToEndGame(void) {
	LToEndGameOn = 1 - LToEndGameOn;
	openTogglesMenu();
}

void toggleLevitate(void) {
	LToLevitateOn = 1 - LToLevitateOn;
	openTogglesMenu();
}

void toggleLtoTB(void) {
	LToToggleTBOn = 1 - LToToggleTBOn;
	openTogglesMenu();
}

void toggleSuperspeed(void) {
	IsSuperspeedOn += 1;
	if (IsSuperspeedOn > 7) {
		IsSuperspeedOn = 1;
	}
	openTogglesMenu();
}

void infiniteHealth(void) {
	if (InfiniteHealthCheatOn) {
		CollectableBase.Health = CollectableBase.Melons << 2;
	}
};

void toggleMinigameTimers(void) {
	MinigameTimersInMS = 1 - MinigameTimersInMS;
	changeTimer_button();
	openTogglesMenu();
}

void resetAllCheats(void) {
	AutoMoonkickOn = 0;
	AutoPhaseStateOn = 0;
	InfiniteHealthCheatOn = 0;
	LToCancelCSOn = 0;
	LToEndGameOn = 0;
	LToLevitateOn = 0;
	LToToggleTBOn = 0;
	IsSuperspeedOn = 1;
	MinigameTimersInMS = 0;
	if (EnemySpawnOff) {
		toggleSpawnPrevention();
	}
	if (CurrentMap == 0x26) {
		if (*(char *)SandstormAddress == 0) {
			toggleSandstorm();
		};
	};
	openTogglesMenu();
}

static const int toggles_functions[] = {
	(int)&toggleAutokick,
	(int)&toggleAutophase,
	(int)&toggleSandstorm,
	(int)&toggleSpawnPrevention,
	(int)&toggleMinigameTimers,
	(int)&toggleInfHealth,
	(int)&toggleLToCancelCS,
	(int)&toggleLToEndGame,
	(int)&toggleLevitate,
	(int)&toggleSuperspeed,
	(int)&toggleLtoTB,
	(int)&toggleTBVoid,
	(int)&toggleVisify,
	(int)&resetAllCheats,
};

const Screen toggles_struct = {
	.TextArray = (int*)toggles_array,
	.FunctionArray = toggles_functions,
	.ArrayItems = 14,
	.ParentScreen = 55,
	.ParentPosition = 5
};