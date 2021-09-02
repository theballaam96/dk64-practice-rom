#include "../../include/common.h"

static const char debug_actors[] = "Actors";
static const char debug_memory[] = "Memory (WIP)";

void openDebugMenu(void) {
	changeMenu(76);
}

static const char* debug_array[] = {
	debug_actors,
	debug_memory,
};

static const int debug_functions[] = {
	(int)&openActorMenu,
	(int)&initRamViewerTab,
};

const Screen debug_struct = {
	.TextArray = (int*)debug_array,
	.FunctionArray = debug_functions,
	.ArrayItems = 2,
	.ParentScreen = 0,
	.ParentPosition = 1
};