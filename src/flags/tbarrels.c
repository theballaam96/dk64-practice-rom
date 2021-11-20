#include "../../include/common.h"

static const char flag_dive_set[] = "Dive Barrel: Complete";
static const char flag_dive_clear[] = "Dive Barrel: Incomplete";

static const char flag_orange_set[] = "Orange Barrel: Complete";
static const char flag_orange_clear[] = "Orange Barrel: Incomplete";

static const char flag_barrel_set[] = "Barrel Barrel: Complete";
static const char flag_barrel_clear[] = "Barrel Barrel: Incomplete";

static const char flag_vine_set[] = "Vine Barrel: Complete";
static const char flag_vine_clear[] = "Vine Barrel: Incomplete";

static const char flag_tbarrelsspawned_set[] = "Training Barrels: Spawned";
static const char flag_tbarrelsspawned_clear[] = "Training Barrels: Not Spawned";

static const short tbarrel_flags[] = {0x0182,0x0184,0x0185,0x0183,0x017F};
static const char tbarrel_flag_types[] = {0,0,0,0,0};

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
	flag_tbarrelsspawned_clear,
};

static const int flagmenu_tbarrels_functions[] = {
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
	(int)&tbarrelSetFlag,
};

const Screen flagmenu_tbarrels_struct = {
	.TextArray = (int*)flagmenu_tbarrels_array,
	.FunctionArray = flagmenu_tbarrels_functions,
	.ArrayItems = 5,
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

static const char* flag_tbarrelsspawned_array[] = {
	flag_tbarrelsspawned_clear,
	flag_tbarrelsspawned_set,
};

static const int* flagtbarrel_array[] =  {
	(int *)flag_dive_array,
	(int *)flag_orange_array,
	(int *)flag_barrel_array,
	(int *)flag_vine_array,
	(int *)flag_tbarrelsspawned_array,
};

const flagMenuData flagmenu_tbarrelmenu = {
	.flagArray = tbarrel_flags,
	.flagTypeArray = tbarrel_flag_types,
	.flagText = (const int*)flagtbarrel_array,
	.screenIndex = 67,
	.flagCount = 5,
};