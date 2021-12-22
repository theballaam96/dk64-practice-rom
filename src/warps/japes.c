#include "../../include/common.h"

void openJapesMainMenu(void) {
	changeMenu(3);
}

static const unsigned char japes_destmap[] = {
	0x0, // Null for main map
	0x8, // Dillo 1
	0x35, // Crown
	0x25, // BBlast
	0x6, // Minecart
	0x4, // Mountain
	0xD, // Painting Room
	0xC, // Shellhive
	0x21 // Underground
};

static const unsigned char japes_destexit[] = {
	0x0, // Null for main map
	0x0, // Dillo 1
	0x0, // Crown
	0x0, // BBlast
	0x0, // Minecart
	0x0, // Mountain
	0x0, // Painting Room
	0x0, // Shellhive
	0x0 // Underground
};

const MapWarp map_japes_struct = {
	.maps = japes_destmap,
	.exits = japes_destexit,
	.screen = 2
};

static const char* japes_mapwarp_array[] = {
	"MAIN MAP",
	"ARMY DILLO 1",
	"BEAVER BRAWL",
	"BABOON BLAST COURSE",
	"MINECART",
	"MOUNTAIN",
	"PAINTING ROOM",
	"SHELLHIVE",
	"UNDERGROUND"
};

static const int japes_mapwarp_functions[] = {
	(int)&openJapesMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen japes_mapwarp_struct = {
	.TextArray = (int*)japes_mapwarp_array,
	.FunctionArray = japes_mapwarp_functions,
	.ArrayItems = 9,
	.ParentScreen = 1,
	.ParentPosition = 0
};

static const unsigned char japes_main_destmap[] = {
	0x7, // Portal
	0x7, // Intro
	0x7, // River Low
	0x7, // River High
	0x7, // Storm area
	0x7, // Zinger area
};

static const unsigned char japes_main_destexit[] = {
	0x0F, // Portal
	0x00, // Intro
	0x10, // River Low
	0x02, // River High
	0x03, // Storm area
	0x01, // Zinger area
};

const MapWarp map_japesmain_struct = {
	.maps = japes_main_destmap,
	.exits = japes_main_destexit,
	.screen = 3
};

static const char* japesmain_mapwarp_array[] = {
	"FROM PORTAL",
	"FROM INTRO",
	"LOWER RIVER",
	"UPPER RIVER",
	"STORM AREA",
	"ZINGER AREA"
};

static const int japesmain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen japesmain_mapwarp_struct = {
	.TextArray = (int*)japesmain_mapwarp_array,
	.FunctionArray = japesmain_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = 2,
	.ParentPosition = 0
};

void openJapesMenu(void) {
	changeMenu(2);
}

