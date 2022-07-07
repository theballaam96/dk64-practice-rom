#include "../include/common.h"

static const char flag_diddy_set[] = "DIDDY FTT: WATCHED";
static const char flag_diddy_clear[] = "DIDDY FTT: NOT WATCHED";

static const char flag_lanky_set[] = "LANKY FTT: WATCHED";
static const char flag_lanky_clear[] = "LANKY FTT: NOT WATCHED";

static const char flag_tiny_set[] = "TINY FTT: WATCHED";
static const char flag_tiny_clear[] = "TINY FTT: NOT WATCHED";

static const char flag_chunky_set[] = "CHUNKY FTT: WATCHED";
static const char flag_chunky_clear[] = "CHUNKY FTT: NOT WATCHED";

static const char flag_blocker_set[] = "B LOCKER FTT: WATCHED";
static const char flag_blocker_clear[] = "B LOCKER FTT: NOT WATCHED";

static const char flag_bananaport_set[] = "BANANAPORT FTT: WATCHED";
static const char flag_bananaport_clear[] = "BANANAPORT FTT: NOT WATCHED";

static const char flag_crownpad_set[] = "CROWN PAD FTT: WATCHED";
static const char flag_crownpad_clear[] = "CROWN PAD FTT: NOT WATCHED";

static const char flag_strongkong_set[] = "STRONG KONG FTT: WATCHED";
static const char flag_strongkong_clear[] = "STRONG KONG FTT: NOT WATCHED";

static const char flag_orangstandsprint_set[] = "OSTAND SPRINT FTT: WATCHED";
static const char flag_orangstandsprint_clear[] = "OSTAND SPRINT FTT: NOT WATCHED";

static const char flag_minimonkey_set[] = "MINI MONKEY FTT: WATCHED";
static const char flag_minimonkey_clear[] = "MINI MONKEY FTT: NOT WATCHED";

static const char flag_hunkychunky_set[] = "HUNKY CHUNKY FTT: WATCHED";
static const char flag_hunkychunky_clear[] = "HUNKY CHUNKY FTT: NOT WATCHED";

static const short ftt_flags[] = {
	FLAG_FTT_DIDDY,
	FLAG_FTT_LANKY,
	FLAG_FTT_TINY,
	FLAG_FTT_CHUNKY,
	FLAG_FTT_BLOCKER,
	FLAG_FTT_BANANAPORT,
	FLAG_FTT_CROWNPAD,
	FLAG_FTT_STRONGKONG,
	FLAG_FTT_ORANGSPRINT,
	FLAG_FTT_MINIMONKEY,
	FLAG_FTT_HUNKYCHUNKY
};
static const char ftt_flag_types[] = {0,0,0,0,0,0,0,0,0,0,0};

void openFlagsFTTMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_FTT);
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

void toggleKongFTT(void) {
	int am_pos = ActiveMenu.positionIndex;
	if (checkFlag(ftt_flags[am_pos],0)) {
		for (int i = 0; i < 0xE; i++) {
			MovesBase[am_pos + 1].gb_count[i] = 0;
		}
	}
	toggleFlag();
}

static const int flagmenu_ftt_functions[] = {
	(int)&toggleKongFTT,
	(int)&toggleKongFTT,
	(int)&toggleKongFTT,
	(int)&toggleKongFTT,
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
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
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
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_FTT,
	.flagCount = 11,
};