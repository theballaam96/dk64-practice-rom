#include "../../include/common.h"

static char dpadlr_current_position[] = "Current: Position Saving";
static char dpadlr_current_frameadvance[] = "Current: Frame Advance";
static char dpadlr_current_nothing[] = "Current: Nothing";

static char dpadlr_position[] = "Set to: Position Saving";
static char dpadlr_frameadvance[] = "Set to: Frame Advance";
static char dpadlr_nothing[] = "Set to: Nothing";

static char* current_dpadlr[] = {
	dpadlr_current_position,
	dpadlr_current_frameadvance,
	dpadlr_current_nothing,
};

static char* dpadlr_array[] = {
	dpadlr_current_position,
	dpadlr_position,
	dpadlr_frameadvance,
	dpadlr_nothing,
};

void openDPadLRMenu(void) {
	dpadlr_array[0] = current_dpadlr[(int)DisablePositionButtons];
	changeMenu(60);
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
	.ParentScreen = 57,
	.ParentPosition = 0
};