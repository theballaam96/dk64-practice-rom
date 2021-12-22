#include "../../include/common.h"

static const char flag_key1have_set[] = "KEY 1: OBTAINED";
static const char flag_key1have_clear[] = "KEY 1: NOT OBTAINED";

static const char flag_key2have_set[] = "KEY 2: OBTAINED";
static const char flag_key2have_clear[] = "KEY 2: NOT OBTAINED";

static const char flag_key3have_set[] = "KEY 3: OBTAINED";
static const char flag_key3have_clear[] = "KEY 3: NOT OBTAINED";

static const char flag_key4have_set[] = "KEY 4: OBTAINED";
static const char flag_key4have_clear[] = "KEY 4: NOT OBTAINED";

static const char flag_key5have_set[] = "KEY 5: OBTAINED";
static const char flag_key5have_clear[] = "KEY 5: NOT OBTAINED";

static const char flag_key6have_set[] = "KEY 6: OBTAINED";
static const char flag_key6have_clear[] = "KEY 6: NOT OBTAINED";

static const char flag_key7have_set[] = "KEY 7: OBTAINED";
static const char flag_key7have_clear[] = "KEY 7: NOT OBTAINED";

static const char flag_key8have_set[] = "KEY 8: OBTAINED";
static const char flag_key8have_clear[] = "KEY 8: NOT OBTAINED";

static const short keyshave_flags[] = {0x001A,0x004A,0x008A,0x00A8,0x00EC,0x0124,0x013D,0x017C};
static const char keyshave_flag_types[] = {0,0,0,0,0,0,0,0};

void openFlagsKeyshaveMenu(void) {
	openFlagSubmenu(46);
}

static const char* flagmenu_keyshave_array[] = {
	flag_key1have_clear,
	flag_key2have_clear,
	flag_key3have_clear,
	flag_key4have_clear,
	flag_key5have_clear,
	flag_key6have_clear,
	flag_key7have_clear,
	flag_key8have_clear,
};

static const int flagmenu_keyshave_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_keyshave_struct = {
	.TextArray = (int*)flagmenu_keyshave_array,
	.FunctionArray = flagmenu_keyshave_functions,
	.ArrayItems = 8,
	.ParentScreen = 43,
	.ParentPosition = 2
};

static const char* flag_key1have_array[] = {
	flag_key1have_clear,
	flag_key1have_set,
};

static const char* flag_key2have_array[] = {
	flag_key2have_clear,
	flag_key2have_set,
};

static const char* flag_key3have_array[] = {
	flag_key3have_clear,
	flag_key3have_set,
};

static const char* flag_key4have_array[] = {
	flag_key4have_clear,
	flag_key4have_set,
};

static const char* flag_key5have_array[] = {
	flag_key5have_clear,
	flag_key5have_set,
};

static const char* flag_key6have_array[] = {
	flag_key6have_clear,
	flag_key6have_set,
};

static const char* flag_key7have_array[] = {
	flag_key7have_clear,
	flag_key7have_set,
};

static const char* flag_key8have_array[] = {
	flag_key8have_clear,
	flag_key8have_set,
};

static const int* flagkeyshave_array[] =  {
	(int *)flag_key1have_array,
	(int *)flag_key2have_array,
	(int *)flag_key3have_array,
	(int *)flag_key4have_array,
	(int *)flag_key5have_array,
	(int *)flag_key6have_array,
	(int *)flag_key7have_array,
	(int *)flag_key8have_array,
};

const flagMenuData flagmenu_keyshavemenu = {
	.flagArray = keyshave_flags,
	.flagTypeArray = keyshave_flag_types,
	.flagText = (const int*)flagkeyshave_array,
	.screenIndex = 46,
	.flagCount = 8,
};