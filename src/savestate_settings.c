#include "../include/common.h"

static char void_grace_on[] = "} VOID GRACE PERIOD";
static char void_grace_off[] = "{ VOID GRACE PERIOD";

static char* state_settings_array[] = {
	void_grace_on,
};

void openStateSettingsMenu(void) {
	if (savestateSettingsBitfield & 1) {
		state_settings_array[0] = void_grace_off;
	} else {
		state_settings_array[0] = void_grace_on;
	}
	changeMenu(104);
}

void toggleStateSettingOption(void) {
	int bit = 1 << ActiveMenu.positionIndex;
	if (savestateSettingsBitfield & bit) {
		savestateSettingsBitfield &= (0xFF - bit);
	} else {
		savestateSettingsBitfield |= bit;
	}
	saveSettings();
	openStateSettingsMenu();
}

static const int state_settings_functions[] = {
	(int)&toggleStateSettingOption,
};

const Screen state_settings_struct = {
	.TextArray = (int*)state_settings_array,
	.FunctionArray = state_settings_functions,
	.ArrayItems = 1,
	.ParentScreen = 31,
	.ParentPosition = 5
};