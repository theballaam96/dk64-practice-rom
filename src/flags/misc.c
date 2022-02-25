#include "../../include/common.h"

static const char flag_arcader1_set[] = "ARCADE ROUND 1: BEATEN";
static const char flag_arcader1_clear[] = "ARCADE ROUND 1: NOT BEATEN";

static const char flag_rabbitr1_set[] = "RABBIT RACE ROUND 1: BEATEN";
static const char flag_rabbitr1_clear[] = "RABBIT RACE ROUND 1: NOT BEATEN";

static const short misc_flags[] = {0x0082,0x00F8};
static const char misc_flag_types[] = {0,0};

void openFlagsMiscMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_MISC);
}

static const char* flagmenu_misc_array[] = {
	flag_arcader1_clear,
	flag_rabbitr1_clear,
};

static const int flagmenu_misc_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_misc_struct = {
	.TextArray = (int*)flagmenu_misc_array,
	.FunctionArray = flagmenu_misc_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
	.ParentPosition = 10
};

static const char* flag_arcader1_array[] = {
	flag_arcader1_clear,
	flag_arcader1_set,
};

static const char* flag_rabbitr1_array[] = {
	flag_rabbitr1_clear,
	flag_rabbitr1_set,
};

static const int* flagmisc_array[] =  {
	(int *)flag_arcader1_array,
	(int *)flag_rabbitr1_array,
};

const flagMenuData flagmenu_miscmenu = {
	.flagArray = misc_flags,
	.flagTypeArray = misc_flag_types,
	.flagText = (const int*)flagmisc_array,
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_MISC,
	.flagCount = 2,
};