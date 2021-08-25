#include "../../include/common.h"

static const char flag_dive_set[] = "DIVE BARREL: COMPLETE";
static const char flag_dive_clear[] = "DIVE BARREL: INCOMPLETE";

static const char flag_orange_set[] = "ORANGE BARREL: COMPLETE";
static const char flag_orange_clear[] = "ORANGE BARREL: INCOMPLETE";

static const char flag_barrel_set[] = "BARREL BARREL: COMPLETE";
static const char flag_barrel_clear[] = "BARREL BARREL: INCOMPLETE";

static const char flag_vine_set[] = "VINE BARREL: COMPLETE";
static const char flag_vine_clear[] = "VINE BARREL: INCOMPLETE";

static const short tbarrel_flags[] = {0x0182,0x0184,0x0185,0x0183};
static const char tbarrel_flag_types[] = {0,0,0,0};

void openFlagsTBarrelMenu(void) {
	openFlagSubmenu(67);
}

void tbarrelSetFlag(void) {
	toggleFlag();
	char _bool = 1;
	for (int i = 0; i < 4; i++) {
		_bool = checkFlag(0x182 + i,0) & _bool;
	}
	setFlag(0x187,_bool,0);
}

static const char* flagmenu_tbarrels_array[] = {
	flag_dive_clear,
	flag_orange_clear,
	flag_barrel_clear,
	flag_vine_clear,
};

static const int flagmenu_tbarrels_functions[] = {
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
};

const Screen flagmenu_tbarrels_struct = {
	.TextArray = (int*)flagmenu_tbarrels_array,
	.FunctionArray = flagmenu_tbarrels_functions,
	.ArrayItems = 4,
	.ParentScreen = 63,
	.ParentPosition = 5
};

static const char* flag_dive_array[] = {
	flag_dive_clear,
	flag_dive_set,
};

static const char* flag_orange_array[] = {
	flag_orange_clear,
	flag_orange_set,
};

static const char* flag_barrel_array[] = {
	flag_barrel_clear,
	flag_barrel_set,
};

static const char* flag_vine_array[] = {
	flag_vine_clear,
	flag_vine_set,
};

static const int* flagtbarrel_array[] =  {
	(int *)flag_dive_array,
	(int *)flag_orange_array,
	(int *)flag_barrel_array,
	(int *)flag_vine_array,
};

const flagMenuData flagmenu_tbarrelmenu = {
	.flagArray = tbarrel_flags,
	.flagTypeArray = tbarrel_flag_types,
	.flagText = (const int*)flagtbarrel_array,
	.screenIndex = 67,
	.flagCount = 4,
};