#include "../../include/common.h"

static char vanilla_screenratio_43[] = "Screen Ratio: Normal";
static char vanilla_screenratio_169[] = "Screen Ratio: Widescreen";

static char vanilla_chimpycam_free[] = "Chimpy Cam: Free";
static char vanilla_chimpycam_follow[] = "Chimpy Cam: Follow";

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
	changeMenu(68);
};

void toggleScreenRatio(void) {
	ScreenRatio = 1 - ScreenRatio;
	openVanillaVarsMenu();
}

void toggleChimpyCam(void) {
	ChimpyCam = 1 - ChimpyCam;
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
	.ParentScreen = 57,
	.ParentPosition = 2
};