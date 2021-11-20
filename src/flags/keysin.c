#include "../../include/common.h"

static const char flag_key0_set[] = "Japes: Open";
static const char flag_key0_clear[] = "Japes: Not Open";

static const char flag_key1_set[] = "Key 1: Turned";
static const char flag_key1_clear[] = "Key 1: Not Turned";

static const char flag_key2_set[] = "Key 2: Turned";
static const char flag_key2_clear[] = "Key 2: Not Turned";

static const char flag_key3_set[] = "Key 3: Turned";
static const char flag_key3_clear[] = "Key 3: Not Turned";

static const char flag_key4_set[] = "Key 4: Turned";
static const char flag_key4_clear[] = "Key 4: Not Turned";

static const char flag_key5_set[] = "Key 5: Turned";
static const char flag_key5_clear[] = "Key 5: Not Turned";

static const char flag_key6_set[] = "Key 6: Turned";
static const char flag_key6_clear[] = "Key 6: Not Turned";

static const char flag_key7_set[] = "Key 7: Turned";
static const char flag_key7_clear[] = "Key 7: Not Turned";

static const char flag_key8_set[] = "Key 8: Turned";
static const char flag_key8_clear[] = "Key 8: Not Turned";

static const short keysin_flags[] = {0x01BB,0x01BC,0x01BD,0x01BE,0x01BF,0x01C0,0x01C1,0x01C2,0x01C3};
static const char keysin_flag_types[] = {0,0,0,0,0,0,0,0,0};

void openFlagsKeysinMenu(void) {
	openFlagSubmenu(45);
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
	.ParentScreen = 43,
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
	.screenIndex = 45,
	.flagCount = 9,
};