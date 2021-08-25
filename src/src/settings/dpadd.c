#include "../../include/common.h"

static char dpadd_current_taganywhere[] = "CURRENT: TAG ANYWHERE";
static char dpadd_current_nothing[] = "CURRENT: NOTHING";

static char dpadd_taganywhere[] = "SET TO TAG ANYWHERE";
static char dpadd_nothing[] = "SET TO NOTHING";

static char* current_dpadd[] = {
	dpadd_current_taganywhere,
	dpadd_current_nothing,
};

static char* dpadd_array[] = {
	dpadd_current_taganywhere,
	dpadd_taganywhere,
	dpadd_nothing,
};

void openDPadDMenu(void) {
	dpadd_array[0] = current_dpadd[(int)DisableTagAnywhere];
	changeMenu(61);
};

void changeDPadDFunction(void) {
	DisableTagAnywhere = ActiveMenu.positionIndex - 1;
	saveSettings();
	openDPadDMenu();
};

static const int dpadd_functions[] = {
	0,
	(int)&changeDPadDFunction,
	(int)&changeDPadDFunction,
};

const Screen dpadd_struct = {
	.TextArray = (int*)dpadd_array,
	.FunctionArray = dpadd_functions,
	.ArrayItems = 3,
	.ParentScreen = 57,
	.ParentPosition = 1
};