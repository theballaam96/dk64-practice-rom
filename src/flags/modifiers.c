#include "../../include/common.h"

static const char flag_prodroom_set[] = "PRODUCTION ROOM: ON";
static const char flag_prodroom_clear[] = "PRODUCTION ROOM: OFF";

static const char flag_galleonwater_set[] = "GALLEON WATER LEVEL: RAISED";
static const char flag_galleonwater_clear[] = "GALLEON WATER LEVEL: LOWERED";

static const char flag_galleonship_set[] = "GALLEON SHIP: SPAWNED";
static const char flag_galleonship_clear[] = "GALLEON SHIP: NOT SPAWNED";

static const char flag_funginighttime_set[] = "FUNGI TIME OF DAY: NIGHT";
static const char flag_funginighttime_clear[] = "FUNGI TIME OF DAY: DAY";

static const char flag_koshadead_set[] = "GIANT KOSHA: DEAD";
static const char flag_koshadead_clear[] = "GIANT KOSHA: ALIVE";

static const char flag_bom_set[] = "BLAST O MATIC: OFF";
static const char flag_bom_clear[] = "BLAST O MATIC: ON";

static const short modifier_flags[] = {
	FLAG_MODIFIER_PRODROOM,
	FLAG_MODIFIER_GALLEONWATER,
	FLAG_MODIFIER_GALLEONSHIP,
	FLAG_MODIFIER_FUNGINIGHT,
	FLAG_MODIFIER_KOSHADEAD,
	FLAG_MODIFIER_HELMBOM
};
static const char modifier_flag_types[] = {0,0,0,0,0,0};

void openFlagsModifierMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_MODIFIER);
}

static const char* flagmenu_modifier_array[] = {
	flag_prodroom_clear,
	flag_galleonwater_clear,
	flag_galleonship_clear,
	flag_funginighttime_clear,
	flag_koshadead_clear,
	flag_bom_clear,
};

static const int flagmenu_modifier_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_modifier_struct = {
	.TextArray = (int*)flagmenu_modifier_array,
	.FunctionArray = flagmenu_modifier_functions,
	.ArrayItems = 6,
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
	.ParentPosition = 7
};

static const char* flag_prodroom_array[] = {
	flag_prodroom_clear,
	flag_prodroom_set,
};

static const char* flag_galleonwater_array[] = {
	flag_galleonwater_clear,
	flag_galleonwater_set,
};

static const char* flag_galleonship_array[] = {
	flag_galleonship_clear,
	flag_galleonship_set,
};

static const char* flag_funginighttime_array[] = {
	flag_funginighttime_clear,
	flag_funginighttime_set,
};

static const char* flag_koshadead_array[] = {
	flag_koshadead_clear,
	flag_koshadead_set,
};

static const char* flag_bom_array[] = {
	flag_bom_clear,
	flag_bom_set,
};

static const int* flagmodifier_array[] =  {
	(int *)flag_prodroom_array,
	(int *)flag_galleonwater_array,
	(int *)flag_galleonship_array,
	(int *)flag_funginighttime_array,
	(int *)flag_koshadead_array,
	(int *)flag_bom_array,
};

const flagMenuData flagmenu_modifiermenu = {
	.flagArray = modifier_flags,
	.flagTypeArray = modifier_flag_types,
	.flagText = (const int*)flagmodifier_array,
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_MODIFIER,
	.flagCount = 6,
};