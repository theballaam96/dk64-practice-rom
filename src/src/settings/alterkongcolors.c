#include "../../include/common.h"

static char colors_dk_1[] = "DK: Blue";
static char colors_dk_2[] = "DK: Green";
static char colors_dk_3[] = "DK: Purple";

static char colors_di_1[] = "Diddy: Dark Blue";
static char colors_di_2[] = "Diddy: Yellow";
static char colors_di_3[] = "Diddy: Light Blue";

static char colors_la_1[] = "Lanky: Green";
static char colors_la_2[] = "Lanky: Purple";
static char colors_la_3[] = "Lanky: Red";

static char colors_ti_1[] = "Tiny: Green";
static char colors_ti_2[] = "Tiny: Purple";
static char colors_ti_3[] = "Tiny: Red";

static char colors_ch_1[] = "Chunky: Red";
static char colors_ch_2[] = "Chunky: Purple & Blue";
static char colors_ch_3[] = "Chunky: Green & Purple";

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