#include "../include/common.h"

static const char flag_key0_set[] = "JAPES: OPEN";
static const char flag_key0_clear[] = "JAPES: NOT OPEN";

static const char flag_key1_set[] = "KEY 1: TURNED";
static const char flag_key1_clear[] = "KEY 1: NOT TURNED";

static const char flag_key2_set[] = "KEY 2: TURNED";
static const char flag_key2_clear[] = "KEY 2: NOT TURNED";

static const char flag_key3_set[] = "KEY 3: TURNED";
static const char flag_key3_clear[] = "KEY 3: NOT TURNED";

static const char flag_key4_set[] = "KEY 4: TURNED";
static const char flag_key4_clear[] = "KEY 4: NOT TURNED";

static const char flag_key5_set[] = "KEY 5: TURNED";
static const char flag_key5_clear[] = "KEY 5: NOT TURNED";

static const char flag_key6_set[] = "KEY 6: TURNED";
static const char flag_key6_clear[] = "KEY 6: NOT TURNED";

static const char flag_key7_set[] = "KEY 7: TURNED";
static const char flag_key7_clear[] = "KEY 7: NOT TURNED";

static const char flag_key8_set[] = "KEY 8: TURNED";
static const char flag_key8_clear[] = "KEY 8: NOT TURNED";

static const short keysin_flags[] = {
	FLAG_KEYIN_JAPES,
	FLAG_KEYIN_KEY1,
	FLAG_KEYIN_KEY2,
	FLAG_KEYIN_KEY3,
	FLAG_KEYIN_KEY4,
	FLAG_KEYIN_KEY5,
	FLAG_KEYIN_KEY6,
	FLAG_KEYIN_KEY7,
	FLAG_KEYIN_KEY8
};
static const char keysin_flag_types[] = {0,0,0,0,0,0,0,0,0};

void openFlagsKeysinMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_KEYSIN);
}

static const char* flagmenu_keysin_array[] = {
	flag_key0_clear,
	flag_key1_clear,
	flag_key2_clear,
	flag_key3_clear,
	flag_key4_clear,
	flag_key5_clear,
	flag_key6_clear,
	flag_key7_clear,
	flag_key8_clear,
};

static const int flagmenu_keysin_functions[] = {
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

const Screen flagmenu_keysin_struct = {
	.TextArray = (int*)flagmenu_keysin_array,
	.FunctionArray = flagmenu_keysin_functions,
	.ArrayItems = 9,
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
	.ParentPosition = 1
};

static const char* flag_key0_array[] = {
	flag_key0_clear,
	flag_key0_set,
};

static const char* flag_key1_array[] = {
	flag_key1_clear,
	flag_key1_set,
};

static const char* flag_key2_array[] = {
	flag_key2_clear,
	flag_key2_set,
};

static const char* flag_key3_array[] = {
	flag_key3_clear,
	flag_key3_set,
};

static const char* flag_key4_array[] = {
	flag_key4_clear,
	flag_key4_set,
};

static const char* flag_key5_array[] = {
	flag_key5_clear,
	flag_key5_set,
};

static const char* flag_key6_array[] = {
	flag_key6_clear,
	flag_key6_set,
};

static const char* flag_key7_array[] = {
	flag_key7_clear,
	flag_key7_set,
};

static const char* flag_key8_array[] = {
	flag_key8_clear,
	flag_key8_set,
};

static const int* flagkeysin_array[] =  {
	(int *)flag_key0_array,
	(int *)flag_key1_array,
	(int *)flag_key2_array,
	(int *)flag_key3_array,
	(int *)flag_key4_array,
	(int *)flag_key5_array,
	(int *)flag_key6_array,
	(int *)flag_key7_array,
	(int *)flag_key8_array,
};

const flagMenuData flagmenu_keysinmenu = {
	.flagArray = keysin_flags,
	.flagTypeArray = keysin_flag_types,
	.flagText = (const int*)flagkeysin_array,
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_KEYSIN,
	.flagCount = 9,
};