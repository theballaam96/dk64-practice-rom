#include "../../include/common.h"

static char instruction_up[] = "Hold up";
static char instruction_right[] = "Hold right";
static char instruction_down[] = "Hold down";
static char instruction_left[] = "Hold left";

static char information_up[30] = "UR: Overall: 100%. DK64: 100%";
static char information_right[30] = "UR: Overall: 100%. DK64: 100%";
static char information_down[30] = "UR: Overall: 100%. DK64: 100%";
static char information_left[30] = "UR: Overall: 100%. DK64: 100%";

static const char header_up[] = "U";
static const char header_right[] = "R";
static const char header_down[] = "D";
static const char header_left[] = "L";

static stickTestData data_u = {};
static stickTestData data_r = {};
static stickTestData data_d = {};
static stickTestData data_l = {};

static stickTestData* stick_data[] = {
	&data_u,
	&data_r,
	&data_d,
	&data_l,
};

static const char* info_headers[] = {
	header_up,
	header_right,
	header_down,
	header_left,
};

static char instruction_timer = 0;
static char instruction_stage = 0;
static float test_initial_x = 0;
static float test_initial_y = 0;
static float test_initial_z = 0;

static char* instruction_list[] = {
	instruction_up,
	instruction_right,
	instruction_down,
	instruction_left,
};

static char* instruction_array[] = {
	instruction_up,
};

static char* testinfo_array[] = {
	information_up,
	information_right,
	information_down,
	information_left,
};

void startTest(void) {
	instruction_array[0] = instruction_list[0];
	instruction_timer = 100;
	instruction_stage = 0;
	if (Player) {
		test_initial_x = Player->xPos;
		test_initial_y = Player->yPos;
		test_initial_z = Player->zPos;
	}
	changeMenu(86);
};

int clampRatio(int input_ratio) {
	if (input_ratio > 100) {
		return 100;
	} else if (input_ratio < 0) {
		return 0;
	}
	return input_ratio;
}

void showTestResults(void) {
	int ratio_max = 0;
	int ratio_threshold = 0;
	for (int i = 0; i < 4; i++) {
		// UR: Overall: 100%. DK64: 100%
		ratio_max = clampRatio(100 * ((float)(stick_data[i]->mag_max) / 127));
		ratio_threshold = clampRatio(100 * ((float)(stick_data[i]->mag_threshold) / 80));
		dk_strFormat(
			testinfo_array[i],
			"%s: Overall: %d%%. DK64: %d%%",
			info_headers[i],
			ratio_max,
			ratio_threshold
		);
	};
	changeMenu(87);
}

void runTest(void) {
	int _stage = 0;
	int _max_mag = 0;
	int _threshold_mag = 0;
	if (ActiveMenu.isOpen) {
		if (ActiveMenu.screenIndex == 86) {
			if (instruction_stage < 4) {
				if (Player) {
					Player->xPos = test_initial_x;
					Player->yPos = test_initial_y;
					Player->zPos = test_initial_z;
					Player->touching_object = 0;
					Player->collision_queue_pointer = 0;
				}
				if (instruction_timer > 1) {
					instruction_timer -= 1;
				} else if (instruction_timer == 1) {
					instruction_timer -= 1;
					_stage = (int)instruction_stage;
					_max_mag = (int)(float)dk_sqrt((ControllerInput.stickX * ControllerInput.stickX) + (ControllerInput.stickY * ControllerInput.stickY));
					_threshold_mag = (int)(float)dk_sqrt((stickX_magnitude * stickX_magnitude) + (stickY_magnitude * stickY_magnitude));
					stick_data[_stage]->mag_max = _max_mag;
					stick_data[_stage]->mag_threshold = _threshold_mag;
					instruction_stage += 1;
					if (instruction_stage < 4) {
						instruction_timer = 100;
						instruction_array[0] = instruction_list[(int)instruction_stage];
						changeMenu(86);
					} else {
						showTestResults();
					}
				}
			}
		}
	}
}

static const int instruction_functions[] = {
	0,
};

const Screen instruction_struct = {
	.TextArray = (int*)instruction_array,
	.FunctionArray = instruction_functions,
	.ArrayItems = 1,
	.ParentScreen = 57,
	.ParentPosition = 6
};

static const int testinfo_functions[] = {
	0,
	0,
	0,
	0,
};

const Screen testinfo_struct = {
	.TextArray = (int*)testinfo_array,
	.FunctionArray = testinfo_functions,
	.ArrayItems = 4,
	.ParentScreen = 57,
	.ParentPosition = 6
};