#include "../../include/common.h"

static const char debug_actors[] = "Actors";
static const char debug_memory[] = "Memory";
static const char debug_heap[] = "Analyze Heap";
static const char debug_flag[] = "Flag Log";
static const char debug_spawnactor[] = "Spawn Actors";
static const char debug_corrupt[] = "Corrupt";

void openDebugMenu(void) {
	changeMenu(76);
}

void openRAMViewer(void) {
	if (assignedConsole != WIIU) {
		defineRAMViewerParameters((int*)0x80000000,(int*)0x80800000,0);
		startRamViewerDisplay();
	} else {
		playSFX(Wrong);
	}
}

static const char* debug_array[] = {
	debug_actors,
	debug_memory,
	debug_heap,
	debug_flag,
	debug_spawnactor,
	debug_corrupt,
};

static const int debug_functions[] = {
	(int)&openActorMenu,
	(int)&openRAMViewer,
	(int)&openHeapMenu,
	(int)&openFlagLogMenu,
	(int)&openForceSpawnActorMenu,
	(int)&corruptGame,
};

const Screen debug_struct = {
	.TextArray = (int*)debug_array,
	.FunctionArray = debug_functions,
	.ArrayItems = 6,
	.ParentScreen = 0,
	.ParentPosition = 4
};