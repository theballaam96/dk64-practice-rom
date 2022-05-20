#include "../../include/common.h"

static char voidmap_off[20] = "";
static char voidmap_on[20] = "";
static char voidmap_wiiu[] = "VOID BOUNDARIES";
static char voidmap_other[] = "VOID MAP";

void openRAMViewer(void) {
	if (assignedConsole != WIIU) {
		defineRAMViewerParameters((int*)0x80000000,(int*)0x80800000,0);
		startRamViewerDisplay();
	} else {
		playSFX(Wrong);
	}
}

void openMemoryScreen(void) {
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_MEMORYROOT);
}

static const char debug_access[] = {
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Actor List
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_EMU, // Memory
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Analyze Heap
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Flag Log
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Spawn Actors
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Void Map
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Corrupt
	0, // Collision View
};

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
	if (assignedConsole != WIIU) {
		dk_strFormat(voidmap_off,"{ %s",voidmap_other);
		dk_strFormat(voidmap_on,"} %s",voidmap_other);
	} else {
		dk_strFormat(voidmap_off,"{ %s",voidmap_wiiu);
		dk_strFormat(voidmap_on,"} %s",voidmap_wiiu);
	}
	if (voidMapOn) {
		debug_array[5] = voidmap_on;
	} else {
		debug_array[5] = voidmap_off;
	}
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_ROOT);
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
	(int)&openMemoryScreen,
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
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 5,
	.hasAccessArray = 1,
	.AccessArray = debug_access
};

static char* memory_array[] = {
	"OPEN MEMORY VIEWER",
	"MANAGE FROZEN VALUES",
};

static const int memory_functions[] = {
	(int)&openRAMViewer,
	(int)&openFreezeScreen,
};

const Screen memory_struct = {
	.TextArray = (int*)memory_array,
	.FunctionArray = memory_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_DEBUG_ROOT,
	.ParentPosition = 1,
};