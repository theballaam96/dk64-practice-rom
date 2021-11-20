#include "../../include/common.h"

static const char flag_japesboss_set[] = "Army Dillo 1 Intro: Watched";
static const char flag_japesboss_clear[] = "Army Dillo 1 Intro: Not Watched";

static const char flag_aztecboss_set[] = "Dogadon 1 Intro: Watched";
static const char flag_aztecboss_clear[] = "Dogadon 1 Intro: Not Watched";

static const char flag_factoryboss_set[] = "Mad Jack Intro: Watched";
static const char flag_factoryboss_clear[] = "Mad Jack Intro: Not Watched";

static const char flag_galleonboss_set[] = "Pufftoss Intro: Watched";
static const char flag_galleonboss_clear[] = "Pufftoss Intro: Not Watched";

static const char flag_fungiboss_set[] = "Dogadon 2 Intro: Watched";
static const char flag_fungiboss_clear[] = "Dogadon 2 Intro: Not Watched";

static const char flag_cavesboss_set[] = "Army Dillo 2 Intro: Watched";
static const char flag_cavesboss_clear[] = "Army Dillo 2 Intro: Not Watched";

static const char flag_castleboss_set[] = "King Kut Out Intro: Watched";
static const char flag_castleboss_clear[] = "King Kut Out Intro: Not Watched";

static const short levelboss_flags[] = {0x0068,0x0067,0x006A,0x006B,0x0069,0x006D,0x006C};
static const char levelboss_flag_types[] = {2,2,2,2,2,2,2};

void openFlagsLevelbossMenu(void) {
	openFlagSubmenu(49);
}

static const char* flagmenu_levelboss_array[] = {
	flag_japesboss_clear,
	flag_aztecboss_clear,
	flag_factoryboss_clear,
	flag_galleonboss_clear,
	flag_fungiboss_clear,
	flag_cavesboss_clear,
	flag_castleboss_clear,
};

static const int flagmenu_levelboss_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_levelboss_struct = {
	.TextArray = (int*)flagmenu_levelboss_array,
	.FunctionArray = flagmenu_levelboss_functions,
	.ArrayItems = 7,
	.ParentScreen = 43,
	.ParentPosition = 5
};

static const char* flag_japesboss_array[] = {
	flag_japesboss_clear,
	flag_japesboss_set,
};

static const char* flag_aztecboss_array[] = {
	flag_aztecboss_clear,
	flag_aztecboss_set,
};

static const char* flag_factoryboss_array[] = {
	flag_factoryboss_clear,
	flag_factoryboss_set,
};

static const char* flag_galleonboss_array[] = {
	flag_galleonboss_clear,
	flag_galleonboss_set,
};

static const char* flag_fungiboss_array[] = {
	flag_fungiboss_clear,
	flag_fungiboss_set,
};

static const char* flag_cavesboss_array[] = {
	flag_cavesboss_clear,
	flag_cavesboss_set,
};

static const char* flag_castleboss_array[] = {
	flag_castleboss_clear,
	flag_castleboss_set,
};

static const int* flaglevelboss_array[] =  {
	(int *)flag_japesboss_array,
	(int *)flag_aztecboss_array,
	(int *)flag_factoryboss_array,
	(int *)flag_galleonboss_array,
	(int *)flag_fungiboss_array,
	(int *)flag_cavesboss_array,
	(int *)flag_castleboss_array,
};

const flagMenuData flagmenu_levelbossmenu = {
	.flagArray = levelboss_flags,
	.flagTypeArray = levelboss_flag_types,
	.flagText = (const int*)flaglevelboss_array,
	.screenIndex = 49,
	.flagCount = 7,
};