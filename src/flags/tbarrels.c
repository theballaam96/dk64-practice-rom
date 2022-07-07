#include "../include/common.h"

static const char flag_dive_set[] = "DIVE BARREL: COMPLETE";
static const char flag_dive_clear[] = "DIVE BARREL: INCOMPLETE";

static const char flag_orange_set[] = "ORANGE BARREL: COMPLETE";
static const char flag_orange_clear[] = "ORANGE BARREL: INCOMPLETE";

static const char flag_barrel_set[] = "BARREL BARREL: COMPLETE";
static const char flag_barrel_clear[] = "BARREL BARREL: INCOMPLETE";

static const char flag_vine_set[] = "VINE BARREL: COMPLETE";
static const char flag_vine_clear[] = "VINE BARREL: INCOMPLETE";

static const char flag_tbarrelsspawned_set[] = "TRAINING BARRELS: SPAWNED";
static const char flag_tbarrelsspawned_clear[] = "TRAINING BARRELS: NOT SPAWNED";

static const short tbarrel_flags[] = {
	FLAG_TBARREL_DIVE,
	FLAG_TBARREL_ORANGE,
	FLAG_TBARREL_BARREL,
	FLAG_TBARREL_VINE,
	FLAG_TBARREL_SPAWNED
};
static const char tbarrel_flag_types[] = {0,0,0,0,0};

void openFlagsTBarrelMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_MOVES_TBARRELS);
}

void tbarrelSetFlag(void) {
	toggleFlag();
	char _bool = 1;
	for (int i = 0; i < 4; i++) {
		_bool = checkFlag(FLAG_TBARREL_DIVE + i,0) & _bool;
	}
	setFlag(FLAG_TBARREL_COMPLETE,_bool,0);
	TestVariable = 1; // Not sure why, but this prevents a crash
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
	.ParentScreen = ACTIVEMENU_SCREEN_MOVES_ROOT,
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
	.screenIndex = ACTIVEMENU_SCREEN_MOVES_TBARRELS,
	.flagCount = 5,
};