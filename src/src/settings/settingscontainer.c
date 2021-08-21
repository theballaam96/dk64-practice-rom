#include "../../include/common.h"

static const char settings_dpadlr[] = "D-PAD LR FUNCTION";
static const char settings_dpadd[] = "D-PAD DOWN FUNCTION";
static const char settings_screenratio_43[] = "SCREEN RATIO: 4:3";
static const char settings_cameramode_free[] = "CHIMPY CAM: FREE";
static const char settings_quickstartup_on[] = "QUICK STARTUP: ON";
static const char settings_storyskip_on[] = "FORCED STORY SKIP: ON";
static const char settings_pausevolume_normal[] = "PAUSE VOLUME: NORMAL";
static const char settings_dpadmenu_on[] = "D-PAD TO NAVIGATE MENU: ON";
static const char settings_kongmenu[] = "CHANGE KONG COLORS";
static const char settings_saveprompts_off[] = "SAVE NOTIFICATIONS: OFF";
static const char settings_precision[16] = "PRECISION: 2";
static const char settings_resetdefaults[] = "RESET TO DEFAULT";

void openSettingsMainMenu(void) {
	changeMenu(57);
}

static const char* settings_array[] = {
	settings_dpadlr,
	settings_dpadd,
	settings_screenratio_43,
	settings_cameramode_free,
	settings_quickstartup_on,
	settings_storyskip_on,
	settings_pausevolume_normal,
	settings_dpadmenu_on,
	settings_kongmenu,
	settings_saveprompts_off,
	settings_precision,
	settings_resetdefaults
};

static const int settings_functions[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(int)&openKongColorsMenu,
	0,
	0,
	0,
};

const Screen settings_struct = {
	.TextArray = (int*)settings_array,
	.FunctionArray = settings_functions,
	.ArrayItems = 12,
	.ParentScreen = 0,
	.ParentPosition = 8
};