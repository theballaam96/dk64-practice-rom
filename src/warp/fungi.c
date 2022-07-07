#include "../include/common.h"

void openFungiMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_FUNGIMAIN);
}

void openFungiGMushMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_FUNGIMUSH);
}

void openFungiMillsMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_FUNGIMILL);
}

static const unsigned char fungi_destmap[] = {
	0x0, // Null for main map
	0x53, // Dogadon 2
	0x9F, // Crown
	0x34, // Anthill
	0xBC, // BBlast
	0x3B, // Barn
	0x38, // Dark Attic
	0x0, // Null for GMush
	0x3A, // Lanky Attic
	0x0, // Null for Mills
	0x37, // Minecart
	0x39 // Winch Room
};

static const unsigned char fungi_destexit[] = {
	0x0, // Null for main map
	0x0, // Dogadon 2
	0x0, // Crown
	0x0, // Anthill
	0x0, // BBlast
	0x0, // Barn
	0x0, // Dark Attic
	0x0, // Null for GMush
	0x0, // Lanky Attic
	0x0, // Null for Mills
	0x0, // Minecart
	0x0 // Winch Room
};

const MapWarp map_fungi_struct = {
	.maps = fungi_destmap,
	.exits = fungi_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_FUNGI
};

static const char* fungi_mapwarp_array[] = {
	"MAIN MAP",
	"DOGADON 2",
	"KAMIKAZE KREMLINGS",
	"ANTHILL",
	"BABOON BLAST COURSE",
	"BARN",
	"DARK ATTIC",
	"GIANT MUSHROOM",
	"LANKYS ATTIC",
	"MILLS",
	"MINECART",
	"WINCH ROOM"
};

static const int fungi_mapwarp_functions[] = {
	(int)&openFungiMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&openFungiGMushMenu,
	(int)&warpToMap,
	(int)&openFungiMillsMenu,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen fungi_mapwarp_struct = {
	.TextArray = (int*)fungi_mapwarp_array,
	.FunctionArray = fungi_mapwarp_functions,
	.ArrayItems = 12,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
	.ParentPosition = 4
};

static const unsigned char fungi_main_destmap[] = {
	0x30, // Portal
	0x30, // Apple
	0x30, // Mill
	0x30, // Mushroom
	0x30, // Owl
	0x30, // Top of GMush 
};

static const unsigned char fungi_main_destexit[] = {
	0x00, // Portal
	0x12, // Apple
	0x06, // Mill
	0x08, // Mushroom
	0x17, // Owl
	0x18, // Top of GMush
};

const MapWarp map_fungimain_struct = {
	.maps = fungi_main_destmap,
	.exits = fungi_main_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_FUNGIMAIN
};

static const char* fungimain_mapwarp_array[] = {
	"FROM PORTAL",
	"APPLE SIDE",
	"MILL SIDE",
	"MUSHROOM SIDE",
	"OWL TREE",
	"TOP OF MUSHROOM"
};

static const int fungimain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen fungimain_mapwarp_struct = {
	.TextArray = (int*)fungimain_mapwarp_array,
	.FunctionArray = fungimain_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_FUNGI,
	.ParentPosition = 0
};

static const unsigned char fungi_gmush_destmap[] = {
	0x40, // Mush Bottom
	0x40, // Mush Middle
	0x40, // Mush Top
	0x46, // Mush Dark
	0x3F, // Mush Light
	0x47, // Mush Face
};

static const unsigned char fungi_gmush_destexit[] = {
	0x0, // Mush Bottom
	0x1, // Mush Middle
	0x4, // Mush Top
	0x0, // Mush Dark
	0x0, // Mush Light
	0x0, // Mush Face
};

const MapWarp map_fungigmush_struct = {
	.maps = fungi_gmush_destmap,
	.exits = fungi_gmush_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_FUNGIMUSH
};

static const char* fungigmush_mapwarp_array[] = {
	"GIANT MUSHROOM:BOTTOM",
	"GIANT MUSHROOM:MIDDLE",
	"GIANT MUSHROOM:TOP",
	"MUSHROOM TOP:DARK ROOM",
	"MUSHROOM TOP:LIGHT ROOM",
	"MUSHROOM TOP:FACE PUZZLE"
};

static const int fungigmush_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen fungigmush_mapwarp_struct = {
	.TextArray = (int*)fungigmush_mapwarp_array,
	.FunctionArray = fungigmush_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_FUNGI,
	.ParentPosition = 7
};


static const unsigned char fungi_mills_destmap[] = {
	0x3D, // Mill Front
	0x3E, // Mill Rear
	0x3C, // Spider Boss
};

static const unsigned char fungi_mills_destexit[] = {
	0x0, // Mill Front
	0x0, // Mill Rear
	0x0, // Spider Boss
};

const MapWarp map_fungimills_struct = {
	.maps = fungi_mills_destmap,
	.exits = fungi_mills_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_FUNGIMILL
};

static const char* fungimills_mapwarp_array[] = {
	"MILL:FRONT",
	"MILL:REAR",
	"MILL:SPIDER BOSS"
};

static const int fungimills_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen fungimills_mapwarp_struct = {
	.TextArray = (int*)fungimills_mapwarp_array,
	.FunctionArray = fungimills_mapwarp_functions,
	.ArrayItems = 3,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_FUNGI,
	.ParentPosition = 9
};

void openFungiMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_FUNGI);
}

