#include "../../include/common.h"

static const char flag_japestns_set[] = "JAPES TROFF 'N' SCOFF: CLEARED";
static const char flag_japestns_clear[] = "JAPES TROFF 'N' SCOFF: SPAWNED";

static const char flag_aztectns_set[] = "AZTEC TROFF 'N' SCOFF: CLEARED";
static const char flag_aztectns_clear[] = "AZTEC TROFF 'N' SCOFF: SPAWNED";

static const char flag_factorytns_set[] = "FACTORY TROFF 'N' SCOFF: CLEARED";
static const char flag_factorytns_clear[] = "FACTORY TROFF 'N' SCOFF: SPAWNED";

static const char flag_galleontns_set[] = "GALLEON TROFF 'N' SCOFF: CLEARED";
static const char flag_galleontns_clear[] = "GALLEON TROFF 'N' SCOFF: SPAWNED";

static const char flag_fungitns_set[] = "FUNGI TROFF 'N' SCOFF: CLEARED";
static const char flag_fungitns_clear[] = "FUNGI TROFF 'N' SCOFF: SPAWNED";

static const char flag_cavestns_set[] = "CAVES TROFF 'N' SCOFF: CLEARED";
static const char flag_cavestns_clear[] = "CAVES TROFF 'N' SCOFF: SPAWNED";

static const char flag_castletns_set[] = "CASTLE TROFF 'N' SCOFF: CLEARED";
static const char flag_castletns_clear[] = "CASTLE TROFF 'N' SCOFF: SPAWNED";

static const short leveltns_flags[] = {0x002E,0x006C,0x0098,0x00CB,0x0102,0x012E,0x0160};
static const char leveltns_flag_types[] = {0,0,0,0,0,0,0};

void openFlagsLeveltnsMenu(void) {
	openFlagSubmenu(48);
}

static const char* flagmenu_leveltns_array[] = {
	flag_japestns_clear,
	flag_aztectns_clear,
	flag_factorytns_clear,
	flag_galleontns_clear,
	flag_fungitns_clear,
	flag_cavestns_clear,
	flag_castletns_clear,
};

static const int flagmenu_leveltns_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_leveltns_struct = {
	.TextArray = (int*)flagmenu_leveltns_array,
	.FunctionArray = flagmenu_leveltns_functions,
	.ArrayItems = 7,
	.ParentScreen = 43,
	.ParentPosition = 4
};

static const char* flag_japestns_array[] = {
	flag_japestns_clear,
	flag_japestns_set,
};

static const char* flag_aztectns_array[] = {
	flag_aztectns_clear,
	flag_aztectns_set,
};

static const char* flag_factorytns_array[] = {
	flag_factorytns_clear,
	flag_factorytns_set,
};

static const char* flag_galleontns_array[] = {
	flag_galleontns_clear,
	flag_galleontns_set,
};

static const char* flag_fungitns_array[] = {
	flag_fungitns_clear,
	flag_fungitns_set,
};

static const char* flag_cavestns_array[] = {
	flag_cavestns_clear,
	flag_cavestns_set,
};

static const char* flag_castletns_array[] = {
	flag_castletns_clear,
	flag_castletns_set,
};

static const int* flagleveltns_array[] =  {
	(int *)flag_japestns_array,
	(int *)flag_aztectns_array,
	(int *)flag_factorytns_array,
	(int *)flag_galleontns_array,
	(int *)flag_fungitns_array,
	(int *)flag_cavestns_array,
	(int *)flag_castletns_array,
};

const flagMenuData flagmenu_leveltnsmenu = {
	.flagArray = leveltns_flags,
	.flagTypeArray = leveltns_flag_types,
	.flagText = (const int*)flagleveltns_array,
	.screenIndex = 48,
	.flagCount = 7,
};