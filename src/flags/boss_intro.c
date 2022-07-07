#include "../include/common.h"

static const char flag_japesboss_set[] = "ARMY DILLO 1 INTRO: WATCHED";
static const char flag_japesboss_clear[] = "ARMY DILLO 1 INTRO: NOT WATCHED";

static const char flag_aztecboss_set[] = "DOGADON 1 INTRO: WATCHED";
static const char flag_aztecboss_clear[] = "DOGADON 1 INTRO: NOT WATCHED";

static const char flag_factoryboss_set[] = "MAD JACK INTRO: WATCHED";
static const char flag_factoryboss_clear[] = "MAD JACK INTRO: NOT WATCHED";

static const char flag_galleonboss_set[] = "PUFFTOSS INTRO: WATCHED";
static const char flag_galleonboss_clear[] = "PUFFTOSS INTRO: NOT WATCHED";

static const char flag_fungiboss_set[] = "DOGADON 2 INTRO: WATCHED";
static const char flag_fungiboss_clear[] = "DOGADON 2 INTRO: NOT WATCHED";

static const char flag_cavesboss_set[] = "ARMY DILLO 2 INTRO: WATCHED";
static const char flag_cavesboss_clear[] = "ARMY DILLO 2 INTRO: NOT WATCHED";

static const char flag_castleboss_set[] = "KING KUT OUT INTRO: WATCHED";
static const char flag_castleboss_clear[] = "KING KUT OUT INTRO: NOT WATCHED";

static const short levelboss_flags[] = {
	FLAG_INTRO_ARMYDILLO1,
	FLAG_INTRO_DOGADON1,
	FLAG_INTRO_MADJACK,
	FLAG_INTRO_PUFFTOSS,
	FLAG_INTRO_DOGADON2,
	FLAG_INTRO_ARMYDILLO2,
	FLAG_INTRO_KINGKUTOUT
};
static const char levelboss_flag_types[] = {2,2,2,2,2,2,2};

void openFlagsLevelbossMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_BOSSINTRO);
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
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
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
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_BOSSINTRO,
	.flagCount = 7,
};