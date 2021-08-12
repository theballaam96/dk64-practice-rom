#include "../../include/common.h"

static const char mapJapesMain[] = "MAIN MAP";
static const char mapJapesDillo[] = "ARMY DILLO 1";
static const char mapJapesBBlast[] = "BABOON BLAST COURSE";
static const char mapJapesMinecart[] = "MINECART";
static const char mapJapesMountain[] = "MOUNTAIN";
static const char mapJapesPainting[] = "PAINTING ROOM";
static const char mapJapesShellhive[] = "SHELLHIVE";
static const char mapJapesUnderground[] = "UNDERGROUND";
static const char mapJapesPortal[] = "FROM PORTAL";
static const char mapJapesIntro[] = "FROM INTRO";
static const char mapJapesRiverLow[] = "LOWER RIVER";
static const char mapJapesRiverHigh[] = "UPPER RIVER";
static const char mapJapesStorm[] = "STORM AREA";
static const char mapJapesZinger[] = "ZINGER AREA";

void openJapesMainMenu(void) {
	changeMenu(3);
}

static const unsigned char japes_destmap[] = {
	0x0, // Null for main map
	0x8, // Dillo 1
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
	mapJapesMain,
	mapJapesDillo,
	mapJapesBBlast,
	mapJapesMinecart,
	mapJapesMountain,
	mapJapesPainting,
	mapJapesShellhive,
	mapJapesUnderground
};

static const int japes_mapwarp_functions[] = {
	(int)&openJapesMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen japes_mapwarp_struct = {
	.TextArray = (const int*)japes_mapwarp_array,
	.FunctionArray = japes_mapwarp_functions,
	.ArrayItems = 8,
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
	mapJapesPortal,
	mapJapesIntro,
	mapJapesRiverLow,
	mapJapesRiverHigh,
	mapJapesStorm,
	mapJapesZinger
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
	.TextArray = (const int*)japesmain_mapwarp_array,
	.FunctionArray = japesmain_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = 2,
	.ParentPosition = 0
};

void openJapesMenu(void) {
	changeMenu(2);
}
