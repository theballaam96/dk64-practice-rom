#include "../../../include/common.h"

static const char cranky_slam0[] = "SLAM:NONE";
static const char cranky_slam1[] = "SLAM:REGULAR";
static const char cranky_slam2[] = "SLAM:SUPER";
static const char cranky_slam3[] = "SLAM:SUPER DUPER";

static const char cranky_dk0[] = "DK:NONE";
static const char cranky_dk1[] = "DK:BBLAST";
static const char cranky_dk2[] = "DK:BBLAST AND STRONG KONG";
static const char cranky_dk3[] = "DK:ALL";

static const char cranky_di0[] = "DIDDY:NONE";
static const char cranky_di1[] = "DIDDY:CCHARGE";
static const char cranky_di2[] = "DIDDY:CCHARGE AND ROCKETBARREL";
static const char cranky_di3[] = "DIDDY:ALL";

static const char cranky_la0[] = "LANKY:NONE";
static const char cranky_la1[] = "LANKY:OSTAND";
static const char cranky_la2[] = "LANKY:OSTAND AND BBALLOON";
static const char cranky_la3[] = "LANKY:ALL";

static const char cranky_ti0[] = "TINY:NONE";
static const char cranky_ti1[] = "TINY:MMONKEY";
static const char cranky_ti2[] = "TINY:MMONKEY AND PTT";
static const char cranky_ti3[] = "TINY:ALL";

static const char cranky_ch0[] = "CHUNKY:NONE";
static const char cranky_ch1[] = "CHUNKY:HUNKY CHUNKY";
static const char cranky_ch2[] = "CHUNKY:HUNKY CHUNKY AND PPUNCH";
static const char cranky_ch3[] = "CHUNKY:ALL";

static const char cranky_ssflag_on[] = "SIMIAN SLAM PURCHASED:TRUE";
static const char cranky_ssflag_off[] = "SIMIAN SLAM PURCHASED:FALSE";

static const char* cranky_array[] = {
	cranky_slam0,
	cranky_dk0,
	cranky_di0,
	cranky_la0,
	cranky_ti0,
	cranky_ch0,
	cranky_ssflag_off,
};

static const char* cranky_list_slam[] = {
	cranky_slam0,
	cranky_slam1,
	cranky_slam2,
	cranky_slam3,
};

static const char* cranky_list_dk[] = {
	cranky_dk0,
	cranky_dk1,
	cranky_dk2,
	cranky_dk3,
};

static const char* cranky_list_di[] = {
	cranky_di0,
	cranky_di1,
	cranky_di2,
	cranky_di3,
};

static const char* cranky_list_la[] = {
	cranky_la0,
	cranky_la1,
	cranky_la2,
	cranky_la3,
};

static const char* cranky_list_ti[] = {
	cranky_ti0,
	cranky_ti1,
	cranky_ti2,
	cranky_ti3,
};

static const char* cranky_list_ch[] = {
	cranky_ch0,
	cranky_ch1,
	cranky_ch2,
	cranky_ch3,
};

static const int* cranky_list_kong[] = {
	(int*)cranky_list_dk,
	(int*)cranky_list_di,
	(int*)cranky_list_la,
	(int*)cranky_list_ti,
	(int*)cranky_list_ch,
};

void openCrankyMenu(void) {
	cranky_array[0] = cranky_list_slam[(int)MovesBase[0].simian_slam];
	for (int i = 0; i < 5; i++) {
		cranky_array[i + 1] = (char*)cranky_list_kong[i][(int)MovesBase[i].special_moves];
	}
	char _flag = checkFlag(0x180,0);
	if (_flag) {
		cranky_array[6] = cranky_ssflag_on;
	} else {
		cranky_array[6] = cranky_ssflag_off;
	}
	changeMenu(64);
};

void toggleSlamFlag(void) {
	char _flag = checkFlag(0x180,0);
	setFlag(0x180,1 ^ _flag,0);
	openCrankyMenu();
}

void toggleSlam(void) {
	char _base = MovesBase[0].simian_slam + 1;
	if (_base > 3) {
		_base = 0;
	}
	for (int i = 0; i < 5; i++) {
		MovesBase[i].simian_slam = _base;
	}
	openCrankyMenu();
};

void toggleKongMove(void) {
	char _base = MovesBase[(int)ActiveMenu.positionIndex - 1].special_moves + 1;
	if (_base > 3) {
		_base = 0;
	};
	MovesBase[(int)ActiveMenu.positionIndex - 1].special_moves = _base;
	openCrankyMenu();
};

static const int cranky_functions[] = {
	(int)&toggleSlam,
	(int)&toggleKongMove,
	(int)&toggleKongMove,
	(int)&toggleKongMove,
	(int)&toggleKongMove,
	(int)&toggleKongMove,
	(int)&toggleSlamFlag,
};

const Screen cranky_struct = {
	.TextArray = (int*)cranky_array,
	.FunctionArray = cranky_functions,
	.ArrayItems = 7,
	.ParentScreen = 63,
	.ParentPosition = 2
};