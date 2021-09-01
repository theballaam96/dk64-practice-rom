#include "../../include/common.h"

static const char toggles_moonkick_off[] = "AUTO-MOONKICK: OFF";
static const char toggles_moonkick_on[] = "AUTO-MOONKICK: ON";

static const char toggles_phase_off[] = "AUTO-PHASE STATE: OFF";
static const char toggles_phase_on[] = "AUTO-PHASE STATE: ON";

static const char toggles_sandstorm_unk[] = "AZTEC SANDSTORM: UNKNOWN";
static const char toggles_sandstorm_off[] = "AZTEC SANDSTORM: OFF";
static const char toggles_sandstorm_on[] = "AZTEC SANDSTORM: ON";

static const char toggles_enemyspawn_off[] = "ENEMY SPAWNING: OFF";
static const char toggles_enemyspawn_on[] = "ENEMY SPAWNING: ON";

static const char toggles_infhealth_off[] = "INFINITE HEALTH: OFF";
static const char toggles_infhealth_on[] = "INFINITE HEALTH: ON";

static const char toggles_ltocancelcs_off[] = "L TO CANCEL CUTSCENE: OFF";
static const char toggles_ltocancelcs_on[] = "L TO CANCEL CUTSCENE: ON";

static const char toggles_ltoendminigame_off[] = "L TO END MINIGAME: OFF";
static const char toggles_ltoendminigame_on[] = "L TO END MINIGAME: ON";

static const char toggles_levitate_off[] = "L TO LEVITATE: OFF";
static const char toggles_levitate_on[] = "L TO LEVITATE: ON";

static const char toggles_ltotoggletb_off[] = "L TO TOGGLE TAG BARREL VOID: OFF";
static const char toggles_ltotoggletb_on[] = "L TO TOGGLE TAG BARREL VOID: ON";

static const char toggles_superspeed_off[] = "L TO SUPERSPEED: OFF";
static const char toggles_superspeed[20] = "L TO SUPERSPEED: 1x";
static const char toggles_toggletb[] = "TOGGLE TAG BARREL VOID";
static const char toggles_visify[] = "TOGGLE VISIBILITY";
static const char toggles_turnoffall[] = "TURN OFF ALL CHEATS";

static const char* toggles_array[] = {
	toggles_moonkick_off,
	toggles_phase_off,
	toggles_sandstorm_unk,
	toggles_enemyspawn_off,
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
	if (InfiniteHealthCheatOn) {
		toggles_array[4] = toggles_infhealth_on;
	} else {
		toggles_array[4] = toggles_infhealth_off;
	}
	if (LToCancelCSOn) {
		toggles_array[5] = toggles_ltocancelcs_on;
	} else {
		toggles_array[5] = toggles_ltocancelcs_off;
	}
	if (LToEndGameOn) {
		toggles_array[6] = toggles_ltoendminigame_on;
	} else {
		toggles_array[6] = toggles_ltoendminigame_off;
	}
	if (LToLevitateOn) {
		toggles_array[7] = toggles_levitate_on;
	} else {
		toggles_array[7] = toggles_levitate_off;
	}
	dk_strFormat((char *)toggles_superspeed,"L TO SUPERSPEED: %dx",IsSuperspeedOn);
	if (IsSuperspeedOn == 1) {
		toggles_array[8] = toggles_superspeed_off;
	} else {
		toggles_array[8] = toggles_superspeed;
	}
	if (LToToggleTBOn) {
		toggles_array[9] = toggles_ltotoggletb_on;
	} else {
		toggles_array[9] = toggles_ltotoggletb_off;
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

void resetAllCheats(void) {
	AutoMoonkickOn = 0;
	AutoPhaseStateOn = 0;
	InfiniteHealthCheatOn = 0;
	LToCancelCSOn = 0;
	LToEndGameOn = 0;
	LToLevitateOn = 0;
	LToToggleTBOn = 0;
	IsSuperspeedOn = 1;
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
	.ArrayItems = 13,
	.ParentScreen = 55,
	.ParentPosition = 5
};