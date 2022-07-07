#include "../include/common.h"

void openCavesMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_CAVESMAIN);
}

void openCaves5DCMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_CAVES5DC);
}

void openCaves5DIMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_CAVES5DI);
}

static const unsigned char caves_destmap[] = {
	0x0, // Null for main map
	0xC4, // Dillo 2
	0xA0, // Crown
	0xBA, // BBlast
	0x52, // Beetle Race
	0x0, // Null for 5DCs
	0x0, // Null for 5DIs
	0x62, // Ice Castle
	0x59, // Rotating Room
	0x5E // Sprint Cabin
};

static const unsigned char caves_destexit[] = {
	0x0, // Null for main map
	0x0, // Dillo 2
	0x0, // Crown
	0x0, // BBlast
	0x0, // Beetle Race
	0x0, // Null for 5DCs
	0x0, // Null for 5DIs
	0x0, // Ice Castle
	0x0, // Rotating Room
	0x0 // Sprint Cabin
};

const MapWarp map_caves_struct = {
	.maps = caves_destmap,
	.exits = caves_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_CAVES
};

static const char* caves_mapwarp_array[] = {
	"MAIN MAP",
	"ARMY DILLO 2",
	"PLINTH PANIC",
	"BABOON BLAST COURSE",
	"BEETLE RACE",
	"FIVE DOOR CABINS",
	"FIVE DOOR IGLOOS",
	"ICE CASTLE",
	"ROTATING ROOM",
	"SPRINT CABIN"
};

static const int caves_mapwarp_functions[] = {
	(int)&openCavesMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&openCaves5DCMenu,
	(int)&openCaves5DIMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen caves_mapwarp_struct = {
	.TextArray = (int*)caves_mapwarp_array,
	.FunctionArray = caves_mapwarp_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
	.ParentPosition = 5
};

static const unsigned char caves_main_destmap[] = {
	0x48, // Portal
	0x48, // Cabins Area
	0x48, // Giant Boulder
	0x48, // Ice Castle Area
	0x48, // Igloos Area
	0x48 // Waterfall
};

static const unsigned char caves_main_destexit[] = {
	0x00, // Portal
	0x09, // Cabins Area
	0x1A, // Giant Boulder
	0x06, // Ice Castle Area
	0x0B, // Igloos Area
	0x14 // Waterfall
};

const MapWarp map_cavesmain_struct = {
	.maps = caves_main_destmap,
	.exits = caves_main_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_CAVESMAIN
};

static const char* cavesmain_mapwarp_array[] = {
	"FROM PORTAL",
	"CABINS AREA",
	"GIANT BOULDER ROOM",
	"ICE CASTLE AREA",
	"IGLOOS AREA",
	"WATERFALL"
};

static const int cavesmain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen cavesmain_mapwarp_struct = {
	.TextArray = (int*)cavesmain_mapwarp_array,
	.FunctionArray = cavesmain_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_CAVES,
	.ParentPosition = 0
};

static const unsigned char caves_5dc_destmap[] = {
	0x5B, // 5DC DK
	0xC8, // 5DC Diddy Candles
	0x5C, // 5DC Diddy Enemies
	0x5D, // 5DC Tiny
	0x5A // 5DC Chunky
};

static const unsigned char caves_5dc_destexit[] = {
	0x0, // 5DC DK
	0x0, // 5DC Diddy Candles
	0x0, // 5DC Diddy Enemies
	0x0, // 5DC Tiny
	0x0 // 5DC Chunky
};

const MapWarp map_caves5dc_struct = {
	.maps = caves_5dc_destmap,
	.exits = caves_5dc_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_CAVES5DC
};

static const char* caves5dc_mapwarp_array[] = {
	"FIVE DOOR CABIN:DK",
	"FIVE DOOR CABIN:DIDDY CANDLES",
	"FIVE DOOR CABIN:DIDDY ENEMIES",
	"FIVE DOOR CABIN:TINY",
	"FIVE DOOR CABIN:CHUNKY"
};

static const int caves5dc_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen caves5dc_mapwarp_struct = {
	.TextArray = (int*)caves5dc_mapwarp_array,
	.FunctionArray = caves5dc_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_CAVES,
	.ParentPosition = 5
};


static const unsigned char caves_5di_destmap[] = {
	0x56, // DK
	0x64, // Diddy
	0x55, // Lanky
	0x54, // Tiny
	0x5F, // Chunky
};

static const unsigned char caves_5di_destexit[] = {
	0x0, // DK
	0x0, // Diddy
	0x0, // Lanky
	0x0, // Tiny
	0x0, // Chunky
};

const MapWarp map_caves5di_struct = {
	.maps = caves_5di_destmap,
	.exits = caves_5di_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_CAVES5DI
};

static const char* caves5di_mapwarp_array[] = {
	"FIVE DOOR IGLOO:DK",
	"FIVE DOOR IGLOO:DIDDY",
	"FIVE DOOR IGLOO:LANKY",
	"FIVE DOOR IGLOO:TINY",
	"FIVE DOOR IGLOO:CHUNKY"
};

static const int caves5di_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen caves5di_mapwarp_struct = {
	.TextArray = (int*)caves5di_mapwarp_array,
	.FunctionArray = caves5di_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_CAVES,
	.ParentPosition = 6
};

void openCavesMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_CAVES);
}

