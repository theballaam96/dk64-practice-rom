#include "../../include/common.h"

static char colors_dk_1[] = "DK: BLUE";
static char colors_dk_2[] = "DK: GREEN";
static char colors_dk_3[] = "DK: PURPLE";

static char colors_di_1[] = "DIDDY: DARK BLUE";
static char colors_di_2[] = "DIDDY: YELLOW";
static char colors_di_3[] = "DIDDY: LIGHT BLUE";

static char colors_la_1[] = "LANKY: GREEN";
static char colors_la_2[] = "LANKY: PURPLE";
static char colors_la_3[] = "LANKY: RED";

static char colors_ti_1[] = "TINY: GREEN";
static char colors_ti_2[] = "TINY: PURPLE";
static char colors_ti_3[] = "TINY: RED";

static char colors_ch_1[] = "CHUNKY: RED";
static char colors_ch_2[] = "CHUNKY: PURPLE AND BLUE";
static char colors_ch_3[] = "CHUNKY: GREEN AND PURPLE";

static char* kongcolors_array[] = {
	colors_dk_1,
	colors_di_1,
	colors_la_1,
	colors_ti_1,
	colors_ch_1,
};

static char* kongcolors_dk[] = {
	colors_dk_1,
	colors_dk_2,
	colors_dk_3,
};

static char* kongcolors_di[] = {
	colors_di_1,
	colors_di_2,
	colors_di_3,
};

static char* kongcolors_la[] = {
	colors_la_1,
	colors_la_2,
	colors_la_3,
};

static char* kongcolors_ti[] = {
	colors_ti_1,
	colors_ti_2,
	colors_ti_3,
};

static char* kongcolors_ch[] = {
	colors_ch_1,
	colors_ch_2,
	colors_ch_3,
};

void openKongColorsMenu(void) {
	kongcolors_array[0] = kongcolors_dk[(int)kongcolors[0] - 1];
	kongcolors_array[1] = kongcolors_di[(int)kongcolors[1] - 1];
	kongcolors_array[2] = kongcolors_la[(int)kongcolors[2] - 1];
	kongcolors_array[3] = kongcolors_ti[(int)kongcolors[3] - 1];
	kongcolors_array[4] = kongcolors_ch[(int)kongcolors[4] - 1];
	changeMenu(58);
};

void changeKongColor(void) {
	int _color = kongcolors[(int)ActiveMenu.positionIndex];
	if (_color > 2) {
		_color = 0;
	};
	kongcolors[(int)ActiveMenu.positionIndex] = _color + 1;
	saveSettings();
	openKongColorsMenu();
};

static const int kongcolors_functions[] = {
	(int)&changeKongColor,
	(int)&changeKongColor,
	(int)&changeKongColor,
	(int)&changeKongColor,
	(int)&changeKongColor,
};

const Screen kongcolors_struct = {
	.TextArray = (int*)kongcolors_array,
	.FunctionArray = kongcolors_functions,
	.ArrayItems = 5,
	.ParentScreen = 57,
	.ParentPosition = 4
};