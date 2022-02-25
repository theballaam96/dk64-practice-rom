#include "../../include/common.h"

void openFactoryMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_FACTORYMAIN);
}

static const unsigned char factory_destmap[] = {
	0x00, // Null for main map
	0x9A, // Mad Jack
	0x9B, // Crown
	0x6E, // BBlast
	0x1B, // Car Race
	0x24, // Crusher Room
	0x1D // Power Shed
};

static const unsigned char factory_destexit[] = {
	0x0, // Null for main map
	0x0, // Mad Jack
	0x0, // Crown
	0x0, // BBlast
	0x0, // Car Race
	0x0, // Crusher Room
	0x0 // Power Shed
};

const MapWarp map_factory_struct = {
	.maps = factory_destmap,
	.exits = factory_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_FACTORY
};

static const char* factory_mapwarp_array[] = {
	"MAIN MAP",
	"MAD JACK",
	"ARENA AMBUSH",
	"BABOON BLAST COURSE",
	"CAR RACE",
	"CRUSHER ROOM",
	"POWER SHED"
};

static const int factory_mapwarp_functions[] = {
	(int)&openFactoryMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen factory_mapwarp_struct = {
	.TextArray = (int*)factory_mapwarp_array,
	.FunctionArray = factory_mapwarp_functions,
	.ArrayItems = 7,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
	.ParentPosition = 2
};

static const unsigned char factory_main_destmap[] = {
	0x1A, // Portal
	0x1A, // Arcade Room
	0x1A, // Block Tower
	0x1A, // Candy Area
	0x1A, // Funky Room
	0x1A, // Production Room
	0x1A, // R&D
	0x1A, // Snide's Room
	0x1A, // Storage Room
};

static const unsigned char factory_main_destexit[] = {
	0x00, // Portal
	0x0A, // Arcade Room
	0x09, // Block Tower
	0x11, // Candy Area
	0x06, // Funky Room
	0x0C, // Production Room
	0x0B, // R&D
	0x05, // Snide's Room
	0x04, // Storage Room
};

const MapWarp map_factorymain_struct = {
	.maps = factory_main_destmap,
	.exits = factory_main_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_FACTORYMAIN
};

static const char* factorymain_mapwarp_array[] = {
	"FROM PORTAL",
	"ARCADE ROOM",
	"BLOCK TOWER",
	"CANDY AREA",
	"FUNKY ROOM",
	"PRODUCTION ROOM",
	"RESEARCH AND DEVELOPMENT",
	"SNIDES ROOM",
	"STORAGE ROOM"
};

static const int factorymain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen factorymain_mapwarp_struct = {
	.TextArray = (int*)factorymain_mapwarp_array,
	.FunctionArray = factorymain_mapwarp_functions,
	.ArrayItems = 9,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_FACTORY,
	.ParentPosition = 0
};

void openFactoryMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_FACTORY);
}

