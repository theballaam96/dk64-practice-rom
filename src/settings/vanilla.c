#include "../include/common.h"

static char vanilla_screenratio_43[] = "SCREEN RATIO:NORMAL";
static char vanilla_screenratio_169[] = "SCREEN RATIO:WIDESCREEN";

static char vanilla_chimpycam_free[] = "CHIMPY CAM:FREE";
static char vanilla_chimpycam_follow[] = "CHIMPY CAM:FOLLOW";

static char* vanilla_array[] = {
	vanilla_screenratio_43,
	vanilla_chimpycam_free,
};

void openVanillaVarsMenu(void) {
	if (ScreenRatio) {
		vanilla_array[0] = vanilla_screenratio_169;
	} else {
		vanilla_array[0] = vanilla_screenratio_43;
	}
	if (ChimpyCam) {
		vanilla_array[1] = vanilla_chimpycam_follow;
	} else {
		vanilla_array[1] = vanilla_chimpycam_free;
	}
	changeMenu(ACTIVEMENU_SCREEN_SETTINGS_VANILLA);
};

void toggleScreenRatio(void) {
	ScreenRatio = 1 ^ ScreenRatio;
	openVanillaVarsMenu();
}

void toggleChimpyCam(void) {
	ChimpyCam = 1 ^ ChimpyCam;
	openVanillaVarsMenu();
}

static const int vanilla_functions[] = {
	(int)&toggleScreenRatio,
	(int)&toggleChimpyCam,
};

const Screen vanilla_struct = {
	.TextArray = (int*)vanilla_array,
	.FunctionArray = vanilla_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_SETTINGS_ROOT,
	.ParentPosition = 2
};