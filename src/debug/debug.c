#include "../../include/common.h"

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
	"ACTORS",
	"MEMORY",
	"ANALYZE HEAP",
	"FLAG LOG",
	"SPAWN ACTORS",
	"CORRUPT",
	"COLLISION VIEW",
};

static const int debug_functions[] = {
	(int)&openActorMenu,
	(int)&openRAMViewer,
	(int)&openHeapMenu,
	(int)&openFlagLogMenu,
	(int)&openForceSpawnActorMenu,
	(int)&corruptGame,
	(int)&openCollisionMenu,
};

const Screen debug_struct = {
	.TextArray = (int*)debug_array,
	.FunctionArray = debug_functions,
	.ArrayItems = 7,
	.ParentScreen = 0,
	.ParentPosition = 4
};