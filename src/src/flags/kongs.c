#include "../../include/common.h"

static const char flag_dk_set[] = "DK: Freed";
static const char flag_dk_clear[] = "DK: Locked";

static const char flag_diddy_set[] = "Diddy: Freed";
static const char flag_diddy_clear[] = "Diddy: Locked";

static const char flag_lanky_set[] = "Lanky: Freed";
static const char flag_lanky_clear[] = "Lanky: Locked";

static const char flag_tiny_set[] = "Tiny: Freed";
static const char flag_tiny_clear[] = "Tiny: Locked";

static const char flag_chunky_set[] = "Chunky: Freed";
static const char flag_chunky_clear[] = "Chunky: Locked";

static const short kong_flags[] = {0x0181,0x0006,0x0046,0x0042,0x0075};
static const char kong_flag_types[] = {0,0,0,0,0};

void openFlagsKongMenu(void) {
	openFlagSubmenu(44);
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
	.ParentScreen = 43,
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
	.screenIndex = 44,
	.flagCount = 5,
};