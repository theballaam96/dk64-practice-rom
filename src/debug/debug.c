#include "../../include/common.h"

static char voidmap_off[] = "{ VOID MAP";
static char voidmap_on[] = "} VOID MAP";

void openRAMViewer(void) {
	if (assignedConsole != WIIU) {
		defineRAMViewerParameters((int*)0x80000000,(int*)0x80800000,0);
		startRamViewerDisplay();
	} else {
		playSFX(Wrong);
	}
}

static char* debug_array[] = {
	"ACTORS",
	"MEMORY",
	"ANALYZE HEAP",
	"FLAG LOG",
	"SPAWN ACTORS",
	voidmap_off,
	"CORRUPT",
	"COLLISION VIEW",
};

void openDebugMenu(void) {
	if (voidMapOn) {
		debug_array[5] = voidmap_on;
	} else {
		debug_array[5] = voidmap_off;
	}
	changeMenu(76);
}

void toggleVoidMap(void) {
	voidMapOn = 1 ^ voidMapOn;
	if ((voidMapOn) && (voidPointer == 0)) {
		preload_map_voids();
	}
	openDebugMenu();
}

static const int debug_functions[] = {
	(int)&openActorMenu,
	(int)&openRAMViewer,
	(int)&openHeapMenu,
	(int)&openFlagLogMenu,
	(int)&openForceSpawnActorMenu,
	(int)&toggleVoidMap,
	(int)&corruptGame,
	(int)&openCollisionMenu,
};

const Screen debug_struct = {
	.TextArray = (int*)debug_array,
	.FunctionArray = debug_functions,
	.ArrayItems = 7, // 8
	.ParentScreen = 0,
	.ParentPosition = 4
};