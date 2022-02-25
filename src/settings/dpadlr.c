#include "../../include/common.h"

static char dpadlr_current_position[] = "CURRENT: POSITION SAVING";
static char dpadlr_current_frameadvance[] = "CURRENT: FRAME ADVANCE";
static char dpadlr_current_nothing[] = "CURRENT: NOTHING";

static char* current_dpadlr[] = {
	dpadlr_current_position,
	dpadlr_current_frameadvance,
	dpadlr_current_nothing,
};

static char* dpadlr_array[] = {
	dpadlr_current_position,
	"SET TO: POSITION SAVING",
	"SET TO: FRAME ADVANCE",
	"SET TO: NOTHING",
};

void openDPadLRMenu(void) {
	dpadlr_array[0] = current_dpadlr[(int)DisablePositionButtons];
	changeMenu(ACTIVEMENU_SCREEN_SETTINGS_DPADLR);
};

void changeDPadLRFunction(void) {
	DisablePositionButtons = ActiveMenu.positionIndex - 1;
	saveSettings();
	openDPadLRMenu();
};

static const int dpadlr_functions[] = {
	0,
	(int)&changeDPadLRFunction,
	(int)&changeDPadLRFunction,
	(int)&changeDPadLRFunction,
};

const Screen dpadlr_struct = {
	.TextArray = (int*)dpadlr_array,
	.FunctionArray = dpadlr_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_SETTINGS_ROOT,
	.ParentPosition = 0
};