#include "../../include/common.h"

static const char toggles_moonkick_off[] = "{ AUTO-MOONKICK";
static const char toggles_moonkick_on[] = "} AUTO-MOONKICK";

static const char toggles_phase_off[] = "{ D-UP TO AUTO-PHASE";
static const char toggles_phase_on[] = "} D-UP TO AUTO-PHASE";

static const char toggles_moontail_off[] = "{ AUTO-MOONTAIL";
static const char toggles_moontail_on[] = "} AUTO-MOONTAIL";

static const char toggles_startail_off[] = "{ AUTO-STARTAIL";
static const char toggles_startail_on[] = "} AUTO-STARTAIL";

static char AutoMoontailOn = 0;
static char AutoStartailOn = 0;

static const char* tricktoggles_array[] = {
	toggles_moonkick_off,
	toggles_phase_off,
	toggles_moontail_off,
	toggles_startail_off,
};

static const char tricktoggles_access[] = {
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU,
	ACCESS_US | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU,
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU,
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU,
};

static const char* tricktoggles_on[] = {
	toggles_moonkick_on,
	toggles_phase_on,
	toggles_moontail_on,
	toggles_startail_on,
};

static const char* tricktoggles_off[] = {
	toggles_moonkick_off,
	toggles_phase_off,
	toggles_moontail_off,
	toggles_startail_off,
};

static const char* tricktoggles_addresses[] = {
	(char*)&AutoMoonkickOn,
	(char*)&AutoPhaseStateOn,
	(char*)&AutoMoontailOn,
	(char*)&AutoStartailOn,
};

void writeYSpeedComponents(float velocity, float accel) {
	if (Player) {
		Player->yVelocity = velocity - accel;
		Player->yAccel = accel;
	}
}

void DiddyMoonMoves(void) {
	int moon_index = 0;
	if (Character == 1) {
		if (Player) {
			if (Player->control_state == 0x26) {
				if (Player->control_state_progress == 0) {
					if ((Player->touching_object == 1) && (AutoStartailOn)) {
						int* m2location = (int*)ObjectModel2Pointer;
						int pad_index = convertSubIDToIndex(Player->standing_on_index);
						if (pad_index > -1) {
							ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,pad_index);
							if (_object->object_type == 0xD4) {
								moon_index = 2;
							}
						}
					}
					if (Player->grounded_bitfield & 1) {
						if ((moon_index == 0) && (AutoMoontailOn)) {
							moon_index = 1;
						}
					}
				}
			}
		}
		if (moon_index == 1) {
			// Moontail
			writeYSpeedComponents(248.89f,-17.78f);
		} else if (moon_index == 2) {
			// Startail
			writeYSpeedComponents(309.33f,-10.67f);
		}
	}
}

void openTrickToggleMenu(void) {
	for (int i = 0; i < (sizeof(tricktoggles_addresses)/4); i++) {
		if (*(char*)tricktoggles_addresses[i]) {
			tricktoggles_array[i] = tricktoggles_on[i];
		} else {
			tricktoggles_array[i] = tricktoggles_off[i];
		}
	}
	changeMenu(ACTIVEMENU_SCREEN_CHEATS_TRICKS);
}

void toggleTrick(void) {
	int idx = ActiveMenu.positionIndex;
	*(char*)tricktoggles_addresses[idx] = 1 ^ *(char*)tricktoggles_addresses[idx];
	openTrickToggleMenu();
}

static const int tricktoggles_functions[] = {
	(int)&toggleTrick,
	(int)&toggleTrick,
	(int)&toggleTrick,
	(int)&toggleTrick,
};

const Screen tricktoggles_struct = {
	.TextArray = (int*)tricktoggles_array,
	.FunctionArray = tricktoggles_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_CHEATS_ROOT,
	.ParentPosition = 5,
	.hasAccessArray = 1,
	.AccessArray = tricktoggles_access
};