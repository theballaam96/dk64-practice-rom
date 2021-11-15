#include "../../include/common.h"

static const char flag_prodroom_set[] = "Production Room: On";
static const char flag_prodroom_clear[] = "Production Room: Off";

static const char flag_galleonwater_set[] = "Galleon Water Level: Raised";
static const char flag_galleonwater_clear[] = "Galleon Water Level: Lowered";

static const char flag_galleonship_set[] = "Galleon Ship: Spawned";
static const char flag_galleonship_clear[] = "Galleon Ship: Not Spawned";

static const char flag_funginighttime_set[] = "Fungi Time of Day: Night";
static const char flag_funginighttime_clear[] = "Fungi Time of Day: Day";

static const char flag_koshadead_set[] = "Giant Kosha: Dead";
static const char flag_koshadead_clear[] = "Giant Kosha: Alive";

static const char flag_bom_set[] = "Blast-o-Matic: Off";
static const char flag_bom_clear[] = "Blast-o-Matic: On";

static const short modifier_flags[] = {0x006F,0x00A0,0x009C,0x00CE,0x012C,0x0302};
static const char modifier_flag_types[] = {0,0,0,0,0,0};

void openFlagsModifierMenu(void) {
	openFlagSubmenu(51);
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
	.ParentScreen = 43,
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
	.screenIndex = 51,
	.flagCount = 6,
};