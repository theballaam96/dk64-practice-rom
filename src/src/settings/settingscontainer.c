#include "../../include/common.h"

static const char settings_dpadlr[] = "D-PAD LR FUNCTION";
static const char settings_dpadd[] = "D-PAD DOWN FUNCTION";
static const char settings_vanillavars[] = "VANILLA VARIABLES";
static const char settings_hackvars[] = "HACK VARIABLES";
static const char settings_kongmenu[] = "CHANGE KONG COLORS";
static const char settings_changeinputquadrant[] = "CHANGE INPUT DISPLAY QUADRANT";
static const char settings_resetdefaults[] = "RESET TO DEFAULT";

static const char* settings_array[] = {
	settings_dpadlr,
	settings_dpadd,
	settings_vanillavars,
	settings_hackvars,
	settings_kongmenu,
	settings_changeinputquadrant,
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
	(int)&resetSettingsHandler,
};

const Screen settings_struct = {
	.TextArray = (int*)settings_array,
	.FunctionArray = settings_functions,
	.ArrayItems = 7,
	.ParentScreen = 0,
	.ParentPosition = 8
};