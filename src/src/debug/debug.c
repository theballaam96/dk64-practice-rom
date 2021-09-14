#include "../../include/common.h"

static const char debug_actors[] = "Actors";
static const char debug_memory[] = "Memory";

void openDebugMenu(void) {
	changeMenu(76);
}

void openRAMViewer(void) {
	defineRAMViewerParameters((int*)0x80000000,(int*)0x80800000);
	startRamViewerDisplay();
}

static const char* debug_array[] = {
	debug_actors,
	debug_memory,
};

static const int debug_functions[] = {
	(int)&openActorMenu,
	(int)&openRAMViewer,
};

const Screen debug_struct = {
	.TextArray = (int*)debug_array,
	.FunctionArray = debug_functions,
	.ArrayItems = 2,
	.ParentScreen = 0,
	.ParentPosition = 4
};