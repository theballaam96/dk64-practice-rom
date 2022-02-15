#include "../../include/common.h"

static const char toggles_sandstorm_unk[] = "? AZTEC SANDSTORM";
static const char toggles_sandstorm_off[] = "{ AZTEC SANDSTORM";
static const char toggles_sandstorm_on[] = "} AZTEC SANDSTORM";

static const char toggles_enemyspawn_off[] = "} DISABLE ENEMY SPAWNING";
static const char toggles_enemyspawn_on[] = "{ DISABLE ENEMY SPAWNING";

static const char toggles_minigamems_off[] = "{ MINIGAME TIMERS IN MILLISECONDS";
static const char toggles_minigamems_on[] = "} MINIGAME TIMERS IN MILLISECONDS";

static const char toggles_infhealth_off[] = "{ INFINITE HEALTH";
static const char toggles_infhealth_on[] = "} INFINITE HEALTH";

static const char toggles_ltocancelcs_off[] = "{ L TO CANCEL CUTSCENE";
static const char toggles_ltocancelcs_on[] = "} L TO CANCEL CUTSCENE";

static const char toggles_ltoendminigame_off[] = "{ L TO END MINIGAME";
static const char toggles_ltoendminigame_on[] = "} L TO END MINIGAME";

static const char toggles_levitate_off[] = "{ L TO LEVITATE";
static const char toggles_levitate_on[] = "} L TO LEVITATE";

static const char toggles_ltotoggletb_off[] = "{ L TO TOGGLE TAG BARREL VOID";
static const char toggles_ltotoggletb_on[] = "} L TO TOGGLE TAG BARREL VOID";

static const char toggles_superspeed_off[] = "L TO SUPERSPEED:OFF";
static const char toggles_superspeed[20] = "L TO SUPERSPEED:1X";

static const char toggles_voiddisable_off[] = "{ DISABLE VOIDS";
static const char toggles_voiddisable_on[] = "} DISABLE VOIDS";

static const char* toggles_array[] = {
	toggles_sandstorm_unk,
	toggles_enemyspawn_off,
	toggles_minigamems_off,
	toggles_infhealth_off,
	toggles_ltocancelcs_off,
	toggles_ltoendminigame_off,
	toggles_levitate_off,
	toggles_superspeed,
	toggles_ltotoggletb_off,
	toggles_voiddisable_off,
	"TOGGLE TAG BARREL VOID",
	"TOGGLE VISIBILITY",
	"TURN OFF ALL CHEATS",
};

static const char* toggles_addresses[] = {
	(char*)&EnemySpawnOff,
	(char*)&MinigameTimersInMS,
	(char*)&InfiniteHealthCheatOn,
	(char*)&LToCancelCSOn,
	(char*)&LToEndGameOn,
	(char*)&LToLevitateOn,
	(char*)&LToToggleTBOn,
	(char*)&voidsDisabled,
};

static const char toggles_indexes[] = {
	1,
	2,
	3,
	4,
	5,
	6,
	8,
	9,
};

static const char* toggles_on[] = {
	toggles_enemyspawn_off,
	toggles_minigamems_on,
	toggles_infhealth_on,
	toggles_ltocancelcs_on,
	toggles_ltoendminigame_on,
	toggles_levitate_on,
	toggles_ltotoggletb_on,
	toggles_voiddisable_on,
};

static const char* toggles_off[] = {
	toggles_enemyspawn_on,
	toggles_minigamems_off,
	toggles_infhealth_off,
	toggles_ltocancelcs_off,
	toggles_ltoendminigame_off,
	toggles_levitate_off,
	toggles_ltotoggletb_off,
	toggles_voiddisable_off,
};

void openTogglesMenu(void) {
	if (CurrentMap == 0x26) {
		if (*(char *)SandstormAddress) {
			toggles_array[0] = toggles_sandstorm_on;
		} else {
			toggles_array[0] = toggles_sandstorm_off;
		}
	} else {
		toggles_array[0] = toggles_sandstorm_unk;
	}
	for (int i = 0; i < sizeof(toggles_indexes); i++) {
		if (*(char*)toggles_addresses[i]) {
			toggles_array[(int)toggles_indexes[i]] = toggles_on[i];
		} else {
			toggles_array[(int)toggles_indexes[i]] = toggles_off[i];
		}
	}
	dk_strFormat((char *)toggles_superspeed,"L TO SUPERSPEED:%dX",IsSuperspeedOn);
	if (IsSuperspeedOn == 1) {
		toggles_array[7] = toggles_superspeed_off;
	} else {
		toggles_array[7] = toggles_superspeed;
	}
	changeMenu(71);
}

void toggleCheat(void) {
	int pos = -1;
	int am_pos = ActiveMenu.positionIndex;
	for (int i = 0; i < sizeof(toggles_indexes); i++) {
		if (toggles_indexes[i] == am_pos) {
			pos = i;
		}
	}
	if (pos > -1) {
		*(char*)toggles_addresses[pos] = 1 ^ *(char*)toggles_addresses[pos];
	}
	openTogglesMenu();
}

void toggleVoidDisable(void) {
	voidsDisabled = 1 ^ voidsDisabled;
	if (voidsDisabled == 0) {
		if (Player) {
			Player->voiding = 0;
		}
	}
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
	MinigameTimersInMS = 1 ^ MinigameTimersInMS;
	changeTimer_button();
	openTogglesMenu();
}

void resetAllCheats(void) {
	InfiniteHealthCheatOn = 0;
	LToCancelCSOn = 0;
	LToEndGameOn = 0;
	LToLevitateOn = 0;
	LToToggleTBOn = 0;
	IsSuperspeedOn = 1;
	MinigameTimersInMS = 0;
	voidsDisabled = 0;
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
	(int)&toggleSandstorm,
	(int)&toggleSpawnPrevention,
	(int)&toggleMinigameTimers,
	(int)&toggleCheat,
	(int)&toggleCheat,
	(int)&toggleCheat,
	(int)&toggleCheat,
	(int)&toggleSuperspeed,
	(int)&toggleCheat,
	(int)&toggleVoidDisable,
	(int)&toggleTBVoid,
	(int)&toggleVisify,
	(int)&resetAllCheats,
};

const Screen toggles_struct = {
	.TextArray = (int*)toggles_array,
	.FunctionArray = toggles_functions,
	.ArrayItems = 13,
	.ParentScreen = 55,
	.ParentPosition = 6
};