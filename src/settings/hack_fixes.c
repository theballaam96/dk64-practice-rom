#include "../../include/common.h"

static char* fixes_true[] = {
	"{ AUTO-LOAD SANDSTORM",
	"{ AUTO-LOAD GALLEON WATER",
	"{ AUTO-LOAD FUNGI NIGHTTIME",
	"{ AUTO-LOAD GIANT KOSHA TIMER",
	"} OBJECT CHANGE PARENT CHECKS"
};

static char* fixes_false[] = {
	"} AUTO-LOAD SANDSTORM",
	"} AUTO-LOAD GALLEON WATER",
	"} AUTO-LOAD FUNGI NIGHTTIME",
	"} AUTO-LOAD GIANT KOSHA TIMER",
	"{ OBJECT CHANGE PARENT CHECKS"
};

static char* fixes_array[] = {
	0,
	0,
	0,
	0,
	0,
};

void openFixesMenu(void) {
	for (int i = 0; i < sizeof(fixes_true)/4; i++) {
		if (scriptsNotAutoloading & (1 << i)) {
			fixes_array[i] = fixes_true[i];
		} else {
			fixes_array[i] = fixes_false[i];
		}
	}
	changeMenu(ACTIVEMENU_SCREEN_SETTINGS_FIXES);
}

void toggleObjectScriptLoads(void) {
	int shift = 1 << ActiveMenu.positionIndex;
	if (scriptsNotAutoloading & shift) {
		scriptsNotAutoloading &= (-1 - shift);
	} else {
		scriptsNotAutoloading |= shift;
	}
	saveSettings();
	openFixesMenu();
};

static const int fixes_functions[] = {
	(int)&toggleObjectScriptLoads,
	(int)&toggleObjectScriptLoads,
	(int)&toggleObjectScriptLoads,
	(int)&toggleObjectScriptLoads,
	(int)&toggleObjectScriptLoads,
};

const Screen fixes_struct = {
	.TextArray = (int*)fixes_array,
	.FunctionArray = fixes_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_SETTINGS_ROOT,
	.ParentPosition = 4
};