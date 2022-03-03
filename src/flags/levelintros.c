#include "../../include/common.h"

static const char flag_japesintro_set[] = "JAPES INTRO: WATCHED";
static const char flag_japesintro_clear[] = "JAPES INTRO: NOT WATCHED";

static const char flag_aztecintro_set[] = "AZTEC INTRO: WATCHED";
static const char flag_aztecintro_clear[] = "AZTEC INTRO: NOT WATCHED";

static const char flag_factoryintro_set[] = "FACTORY INTRO: WATCHED";
static const char flag_factoryintro_clear[] = "FACTORY INTRO: NOT WATCHED";

static const char flag_galleonintro_set[] = "GALLEON INTRO: WATCHED";
static const char flag_galleonintro_clear[] = "GALLEON INTRO: NOT WATCHED";

static const char flag_fungiintro_set[] = "FUNGI INTRO: WATCHED";
static const char flag_fungiintro_clear[] = "FUNGI INTRO: NOT WATCHED";

static const char flag_cavesintro_set[] = "CAVES INTRO: WATCHED";
static const char flag_cavesintro_clear[] = "CAVES INTRO: NOT WATCHED";

static const char flag_castleintro_set[] = "CASTLE INTRO: WATCHED";
static const char flag_castleintro_clear[] = "CASTLE INTRO: NOT WATCHED";

static const short levelintros_flags[] = {
	FLAG_INTRO_JAPES,
	FLAG_INTRO_AZTEC,
	FLAG_INTRO_FACTORY,
	FLAG_INTRO_GALLEON,
	FLAG_INTRO_FUNGI,
	FLAG_INTRO_CAVES,
	FLAG_INTRO_CASTLE,
};
static const char levelintros_flag_types[] = {0,0,0,0,0,0,0};

void openFlagsLevelintrosMenu(void) {
	openFlagSubmenu(ACTIVEMENU_SCREEN_FLAG_LEVELINTROS);
}

static const char* flagmenu_levelintros_array[] = {
	flag_japesintro_clear,
	flag_aztecintro_clear,
	flag_factoryintro_clear,
	flag_galleonintro_clear,
	flag_fungiintro_clear,
	flag_cavesintro_clear,
	flag_castleintro_clear,
};

static const int flagmenu_levelintros_functions[] = {
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
	(int)&toggleFlag,
};

const Screen flagmenu_levelintros_struct = {
	.TextArray = (int*)flagmenu_levelintros_array,
	.FunctionArray = flagmenu_levelintros_functions,
	.ArrayItems = 7,
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
	.ParentPosition = 3
};

static const char* flag_japesintro_array[] = {
	flag_japesintro_clear,
	flag_japesintro_set,
};

static const char* flag_aztecintro_array[] = {
	flag_aztecintro_clear,
	flag_aztecintro_set,
};

static const char* flag_factoryintro_array[] = {
	flag_factoryintro_clear,
	flag_factoryintro_set,
};

static const char* flag_galleonintro_array[] = {
	flag_galleonintro_clear,
	flag_galleonintro_set,
};

static const char* flag_fungiintro_array[] = {
	flag_fungiintro_clear,
	flag_fungiintro_set,
};

static const char* flag_cavesintro_array[] = {
	flag_cavesintro_clear,
	flag_cavesintro_set,
};

static const char* flag_castleintro_array[] = {
	flag_castleintro_clear,
	flag_castleintro_set,
};

static const int* flaglevelintros_array[] =  {
	(int *)flag_japesintro_array,
	(int *)flag_aztecintro_array,
	(int *)flag_factoryintro_array,
	(int *)flag_galleonintro_array,
	(int *)flag_fungiintro_array,
	(int *)flag_cavesintro_array,
	(int *)flag_castleintro_array,
};

const flagMenuData flagmenu_levelintrosmenu = {
	.flagArray = levelintros_flags,
	.flagTypeArray = levelintros_flag_types,
	.flagText = (const int*)flaglevelintros_array,
	.screenIndex = ACTIVEMENU_SCREEN_FLAG_LEVELINTROS,
	.flagCount = 7,
};