#include "../../include/common.h"

static const char* settings_array[] = {
	"D-PAD L AND R FUNCTION",
	"D-PAD DOWN FUNCTION",
	"VANILLA VARIABLES",
	"HACK VARIABLES",
	"FIXES",
	"CHANGE KONG COLORS",
	"CHANGE INPUT DISPLAY QUADRANT",
	"RUN STICK ASSESSMENT TEST",
	"RESET TO DEFAULT"
};

void openSettingsMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_SETTINGS_ROOT);
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
	(int)&openFixesMenu,
	(int)&openKongColorsMenu,
	(int)&openInputQuadrantMenu,
	(int)&startTest,
	(int)&resetSettingsHandler,
};

const Screen settings_struct = {
	.TextArray = (int*)settings_array,
	.FunctionArray = settings_functions,
	.ArrayItems = 9,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 9
};