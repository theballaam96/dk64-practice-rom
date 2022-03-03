#include "../../include/common.h"

static const char flag_dk_set[] = "DK: FREED";
static const char flag_dk_clear[] = "DK: LOCKED";

static const char flag_diddy_set[] = "DIDDY: FREED";
static const char flag_diddy_clear[] = "DIDDY: LOCKED";

static const char flag_lanky_set[] = "LANKY: FREED";
static const char flag_lanky_clear[] = "LANKY: LOCKED";

static const char flag_tiny_set[] = "TINY: FREED";
static const char flag_tiny_clear[] = "TINY: LOCKED";

static const char flag_chunky_set[] = "CHUNKY: FREED";
static const char flag_chunky_clear[] = "CHUNKY: LOCKED";

static const short kong_flags[] = {
	FLAG_KONG_DK,
	FLAG_KONG_DIDDY,
	FLAG_KONG_LANKY,
	FLAG_KONG_TINY,
	FLAG_KONG_CHUNKY
};
static const char kong_flag_types[] = {0,0,0,0,0};

void openFlagsKongMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_KONGS);
}

static const char* flagmenu_kongs_array[] = {
	flag_dk_clear,
	flag_diddy_clear,
	flag_lanky_clear,
	flag_tiny_clear,
	flag_chunky_clear,
};

static const int flagmenu_kongs_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_kongs_struct = {
	.TextArray = (int*)flagmenu_kongs_array,
	.FunctionArray = flagmenu_kongs_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
	.ParentPosition = 0
};

static const char* flag_dk_array[] = {
	flag_dk_clear,
	flag_dk_set,
};

static const char* flag_diddy_array[] = {
	flag_diddy_clear,
	flag_diddy_set,
};

static const char* flag_lanky_array[] = {
	flag_lanky_clear,
	flag_lanky_set,
};

static const char* flag_tiny_array[] = {
	flag_tiny_clear,
	flag_tiny_set,
};

static const char* flag_chunky_array[] = {
	flag_chunky_clear,
	flag_chunky_set,
};

static const int* flagkong_array[] =  {
	(int *)flag_dk_array,
	(int *)flag_diddy_array,
	(int *)flag_lanky_array,
	(int *)flag_tiny_array,
	(int *)flag_chunky_array,
};

const flagMenuData flagmenu_kongmenu = {
	.flagArray = kong_flags,
	.flagTypeArray = kong_flag_types,
	.flagText = (const int*)flagkong_array,
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_KONGS,
	.flagCount = 5,
};