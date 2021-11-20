#include "../../include/common.h"

static const char flag_diddy_set[] = "Diddy FTT: Watched";
static const char flag_diddy_clear[] = "Diddy FTT: Not Watched";

static const char flag_lanky_set[] = "Lanky FTT: Watched";
static const char flag_lanky_clear[] = "Lanky FTT: Not Watched";

static const char flag_tiny_set[] = "Tiny FTT: Watched";
static const char flag_tiny_clear[] = "Tiny FTT: Not Watched";

static const char flag_chunky_set[] = "Chunky FTT: Watched";
static const char flag_chunky_clear[] = "Chunky FTT: Not Watched";

static const char flag_blocker_set[] = "B. Locker FTT: Watched";
static const char flag_blocker_clear[] = "B. Locker FTT: Not Watched";

static const char flag_bananaport_set[] = "Bananaport FTT: Watched";
static const char flag_bananaport_clear[] = "Bananaport FTT: Not Watched";

static const char flag_crownpad_set[] = "Crown Pad FTT: Watched";
static const char flag_crownpad_clear[] = "Crown Pad FTT: Not Watched";

static const char flag_strongkong_set[] = "Strong Kong FTT: Watched";
static const char flag_strongkong_clear[] = "Strong Kong FTT: Not Watched";

static const char flag_orangstandsprint_set[] = "OStand Sprint FTT: Watched";
static const char flag_orangstandsprint_clear[] = "OStand Sprint FTT: Not Watched";

static const char flag_minimonkey_set[] = "Mini Monkey FTT: Watched";
static const char flag_minimonkey_clear[] = "Mini Monkey FTT: Not Watched";

static const char flag_hunkychunky_set[] = "Hunky Chunky FTT: Watched";
static const char flag_hunkychunky_clear[] = "Hunky Chunky FTT: Not Watched";

static const short ftt_flags[] = {0x016F,0x0170,0x0171,0x0172,0x017E,0x0163,0x0166,0x016B,0x016A,0x0168,0x0169};
static const char ftt_flag_types[] = {0,0,0,0,0,0,0,0,0,0,0};

void openFlagsFTTMenu(void) {
	openFlagSubmenu(52);
}

static const char* flagmenu_ftt_array[] = {
	flag_diddy_clear,
	flag_lanky_clear,
	flag_tiny_clear,
	flag_chunky_clear,
	flag_blocker_clear,
	flag_bananaport_clear,
	flag_crownpad_clear,
	flag_strongkong_clear,
	flag_orangstandsprint_clear,
	flag_minimonkey_clear,
	flag_hunkychunky_clear,
};

static const int flagmenu_ftt_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_ftt_struct = {
	.TextArray = (int*)flagmenu_ftt_array,
	.FunctionArray = flagmenu_ftt_functions,
	.ArrayItems = 11,
	.ParentScreen = 43,
	.ParentPosition = 8
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

static const char* flag_blocker_array[] = {
	flag_blocker_clear,
	flag_blocker_set,
};

static const char* flag_bananaport_array[] = {
	flag_bananaport_clear,
	flag_bananaport_set,
};

static const char* flag_crownpad_array[] = {
	flag_crownpad_clear,
	flag_crownpad_set,
};

static const char* flag_strongkong_array[] = {
	flag_strongkong_clear,
	flag_strongkong_set,
};

static const char* flag_orangstandsprint_array[] = {
	flag_orangstandsprint_clear,
	flag_orangstandsprint_set,
};

static const char* flag_minimonkey_array[] = {
	flag_minimonkey_clear,
	flag_minimonkey_set,
};

static const char* flag_hunkychunky_array[] = {
	flag_hunkychunky_clear,
	flag_hunkychunky_set,
};

static const int* flagftt_array[] =  {
	(int *)flag_diddy_array,
	(int *)flag_lanky_array,
	(int *)flag_tiny_array,
	(int *)flag_chunky_array,
	(int *)flag_blocker_array,
	(int *)flag_bananaport_array,
	(int *)flag_crownpad_array,
	(int *)flag_strongkong_array,
	(int *)flag_orangstandsprint_array,
	(int *)flag_minimonkey_array,
	(int *)flag_hunkychunky_array,
};

const flagMenuData flagmenu_fttmenu = {
	.flagArray = ftt_flags,
	.flagTypeArray = ftt_flag_types,
	.flagText = (const int*)flagftt_array,
	.screenIndex = 52,
	.flagCount = 11,
};