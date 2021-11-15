#include "../../include/common.h"

static const char flag_japesintro_set[] = "Jaoes Intro: Watched";
static const char flag_japesintro_clear[] = "Jaoes Intro: Not Watched";

static const char flag_aztecintro_set[] = "Aztec Intro: Watched";
static const char flag_aztecintro_clear[] = "Aztec Intro: Not Watched";

static const char flag_factoryintro_set[] = "Factory Intro: Watched";
static const char flag_factoryintro_clear[] = "Factory Intro: Not Watched";

static const char flag_galleonintro_set[] = "Galleon Intro: Watched";
static const char flag_galleonintro_clear[] = "Galleon Intro: Not Watched";

static const char flag_fungiintro_set[] = "Fungi Intro: Watched";
static const char flag_fungiintro_clear[] = "Fungi Intro: Not Watched";

static const char flag_cavesintro_set[] = "Caves Intro: Watched";
static const char flag_cavesintro_clear[] = "Caves Intro: Not Watched";

static const char flag_castleintro_set[] = "Castle Intro: Watched";
static const char flag_castleintro_clear[] = "Castle Intro: Not Watched";

static const short levelintros_flags[] = {0x001B,0x005F,0x008C,0x00C2,0x0101,0x011A,0x015D};
static const char levelintros_flag_types[] = {0,0,0,0,0,0,0};

void openFlagsLevelintrosMenu(void) {
	openFlagSubmenu(47);
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
	.ParentScreen = 43,
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
	.screenIndex = 47,
	.flagCount = 7,
};