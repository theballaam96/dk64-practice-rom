#include "../include/common.h"

static const char flag_diddyhelpme_set[] = "DIDDY HELP ME CUTSCENE: WATCHED";
static const char flag_diddyhelpme_clear[] = "DIDDY HELP ME CUTSCENE: NOT WATCHED";

static const char flag_llamacutscene_set[] = "LLAMA CUTSCENE: WATCHED";
static const char flag_llamacutscene_clear[] = "LLAMA CUTSCENE: NOT WATCHED";

static const char flag_giantkoshacutscene_set[] = "GIANT KOSHA CUTSCENE: WATCHED";
static const char flag_giantkoshacutscene_clear[] = "GIANT KOSHA CUTSCENE: NOT WATCHED";

static const short cutscene_flags[] = {
	FLAG_CUTSCENE_DIDDYHELPME,
	FLAG_CUTSCENE_LLAMA,
	FLAG_CUTSCENE_KOSHA
};
static const char cutscene_flag_types[] = {0,0,0};

void openFlagsCutsceneMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_CUTSCENE);
}

static const char* flagmenu_cutscene_array[] = {
	flag_diddyhelpme_clear,
	flag_llamacutscene_clear,
	flag_giantkoshacutscene_clear,
};

static const int flagmenu_cutscene_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_cutscene_struct = {
	.TextArray = (int*)flagmenu_cutscene_array,
	.FunctionArray = flagmenu_cutscene_functions,
	.ArrayItems = 3,
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT ,
	.ParentPosition = 6
};

static const char* flag_diddyhelpme_array[] = {
	flag_diddyhelpme_clear,
	flag_diddyhelpme_set,
};

static const char* flag_llamacutscene_array[] = {
	flag_llamacutscene_clear,
	flag_llamacutscene_set,
};

static const char* flag_giantkoshacutscene_array[] = {
	flag_giantkoshacutscene_clear,
	flag_giantkoshacutscene_set,
};

static const int* flagcutscene_array[] =  {
	(int *)flag_diddyhelpme_array,
	(int *)flag_llamacutscene_array,
	(int *)flag_giantkoshacutscene_array,
};

const flagMenuData flagmenu_cutscenemenu = {
	.flagArray = cutscene_flags,
	.flagTypeArray = cutscene_flag_types,
	.flagText = (const int*)flagcutscene_array,
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_CUTSCENE,
	.flagCount = 3,
};