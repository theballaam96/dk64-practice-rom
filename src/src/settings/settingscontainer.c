#include "../../include/common.h"

static const char settings_dpadlr[] = "D-Pad L&R Function";
static const char settings_dpadd[] = "D-Pad Down Function";
static const char settings_vanillavars[] = "Vanilla Variables";
static const char settings_hackvars[] = "Hack Variables";
static const char settings_kongmenu[] = "Change Kong Colors";
static const char settings_changeinputquadrant[] = "Change Input Display Quadrant";
static const char settings_runsticktest[] = "Run Stick Assessment Test";
static const char settings_resetdefaults[] = "Reset to Default";

static const char* settings_array[] = {
	settings_dpadlr,
	settings_dpadd,
	settings_vanillavars,
	settings_hackvars,
	settings_kongmenu,
	settings_changeinputquadrant,
	settings_runsticktest,
	settings_resetdefaults
};

void openSettingsMainMenu(void) {
	changeMenu(57);
}

void resetSettingsHandler(void) {
	resetSettings();
	playSFX(UhOh);
	openSettingsMainMenu();
};

static const int settings_functions[] = {
	(int)&openDPadLRMenu,
	(int)&openDPadDMenu,
	(int)&openVanillaVarsMenu,
	(int)&openHackVarsMenu,
	(int)&openKongColorsMenu,
	(int)&openInputQuadrantMenu,
	(int)&startTest,
	(int)&resetSettingsHandler,
};

const Screen settings_struct = {
	.TextArray = (int*)settings_array,
	.FunctionArray = settings_functions,
	.ArrayItems = 8,
	.ParentScreen = 0,
	.ParentPosition = 8
};