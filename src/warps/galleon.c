#include "../../include/common.h"

void openGalleonMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_GALLEONMAIN);
}

void openGalleonShipsMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_GALLEONSHIPS);
}

static const unsigned char galleon_destmap[] = {
	0x0, // Null for main map
	0x6F, // Pufftoss
	0x9C, // Crown
	0x36, // BBlast
	0x1F, // Seasick Ship
	0x31, // Lighthouse
	0x2D, // Mermaid Palace
	0x33, // Mech Fish
	0x27, // Seal Race
	0x0, // Null for Shipwrecks
	0xB3, // Submarine
	0x2C // Treasure Chest
};

static const unsigned char galleon_destexit[] = {
	0x0, // Null for main map
	0x0, // Pufftoss
	0x0, // Crown
	0x0, // BBlast
	0x0, // Seasick Ship
	0x0, // Lighthouse
	0x0, // Mermaid Palace
	0x0, // Mech Fish
	0x0, // Seal Race
	0x0, // Null for Shipwrecks
	0x0, // Submarine
	0x0 // Treasure Chest
};

const MapWarp map_galleon_struct = {
	.maps = galleon_destmap,
	.exits = galleon_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_GALLEON
};

static const char* galleon_mapwarp_array[] = {
	"MAIN MAP",
	"PUFFTOSS",
	"MORE KRITTER KARNAGE",
	"BABOON BLAST COURSE",
	"K.ROOL^S SHIP",
	"LIGHTHOUSE",
	"MERMAID PALACE",
	"MECHANICAL FISH",
	"SEAL RACE",
	"SHIPWRECKS",
	"SUBMARINE",
	"TREASURE CHEST"
};

static const int galleon_mapwarp_functions[] = {
	(int)&openGalleonMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&openGalleonShipsMenu,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen galleon_mapwarp_struct = {
	.TextArray = (int*)galleon_mapwarp_array,
	.FunctionArray = galleon_mapwarp_functions,
	.ArrayItems = 12,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
	.ParentPosition = 3
};

static const unsigned char galleon_main_destmap[] = {
	0x1E, // Portal
	0x1E, // Cranky Area
	0x1E, // Lighthouse Side
	0x1E, // Shipwreck Side
};

static const unsigned char galleon_main_destexit[] = {
	0x0, // Portal
	0xD, // Cranky Area
	0xB, // Lighthouse Side
	0x7, // Shipwreck Side
};

const MapWarp map_galleonmain_struct = {
	.maps = galleon_main_destmap,
	.exits = galleon_main_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_GALLEONMAIN
};

static const char* galleonmain_mapwarp_array[] = {
	"FROM PORTAL",
	"CRANKY AREA",
	"LIGHTHOUSE SIDE",
	"SHIPWRECK SIDE"
};

static const int galleonmain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen galleonmain_mapwarp_struct = {
	.TextArray = (int*)galleonmain_mapwarp_array,
	.FunctionArray = galleonmain_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_GALLEON,
	.ParentPosition = 0
};

static const unsigned char galleon_ships_destmap[] = {
	0x2E, // 5DS DK
	0x2B, // 5DS Diddy
	0x2B, // 5DS Lanky
	0x2E, // 5DS Tiny
	0x2B, // 5DS Chunky
	0x2F, // 2DS Lanky
	0x2F // 2DS Tiny
};

static const unsigned char galleon_ships_destexit[] = {
	0x0, // 5DS DK
	0x0, // 5DS Diddy
	0x2, // 5DS Lanky
	0x1, // 5DS Tiny
	0x1, // 5DS Chunky
	0x1, // 2DS Lanky
	0x0 // 2DS Tiny
};

const MapWarp map_galleonships_struct = {
	.maps = galleon_ships_destmap,
	.exits = galleon_ships_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_GALLEONSHIPS
};

static const char* galleonships_mapwarp_array[] = {
	"FIVE DOOR SHIP:DK",
	"FIVE DOOR SHIP:DIDDY",
	"FIVE DOOR SHIP:LANKY",
	"FIVE DOOR SHIP:TINY",
	"FIVE DOOR SHIP:CHUNKY",
	"TWO DOOR SHIP:LANKY",
	"TWO DOOR SHIP:TINY"
};

static const int galleonships_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen galleonships_mapwarp_struct = {
	.TextArray = (int*)galleonships_mapwarp_array,
	.FunctionArray = galleonships_mapwarp_functions,
	.ArrayItems = 7,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_GALLEON,
	.ParentPosition = 9
};

void openGalleonMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_GALLEON);
}

