#include "../../include/common.h"

static const char mapCavesMain[] = "Main Map";
static const char mapCavesDillo[] = "Army Dillo 2";
static const char mapCavesBBlast[] = "Baboon Blast Course";
static const char mapCavesBeetleRace[] = "Beetle Race";
static const char mapCaves5DCs[] = "Five Door Cabins";
static const char mapCaves5DIs[] = "Five Door Igloos";
static const char mapCavesIceCastle[] = "Ice Castle";
static const char mapCavesRotatingRoom[] = "Rotating Room";
static const char mapCavesSprintCabin[] = "Sprint Cabin";

static const char mapCavesPortal[] = "From Portal";
static const char mapCavesCabinsArea[] = "Cabins Area";
static const char mapCavesGiantBoulder[] = "Giant Boulder Room";
static const char mapCavesIceCastleArea[] = "Ice Castle Area";
static const char mapCavesIglooArea[] = "Igloos Area";
static const char mapCavesWaterfall[] = "Waterfall";

static const char mapCaves5DCDK[] = "Five Door Cabin: DK";
static const char mapCaves5DCDiddyCandle[] = "Five Door Cabin: Diddy Candles";
static const char mapCaves5DCDiddyEnemy[] = "Five Door Cabin: Diddy Enemies";
static const char mapCaves5DCTiny[] = "Five Door Cabin: Tiny";
static const char mapCaves5DCChunky[] = "Five Door Cabin: Chunky";

static const char mapCaves5DIDK[] = "Five Door Igloo: DK";
static const char mapCaves5DIDiddy[] = "Five Door Igloo: Diddy";
static const char mapCaves5DILanky[] = "Five Door Igloo: Lanky";
static const char mapCaves5DITiny[] = "Five Door Igloo: Tiny";
static const char mapCaves5DIChunky[] = "Five Door Igloo: Chunky";

static const char mapCavesCrown[] = "Plinth Panic";

void openCavesMainMenu(void) {
	changeMenu(18);
}

void openCaves5DCMenu(void) {
	changeMenu(19);
}

void openCaves5DIMenu(void) {
	changeMenu(20);
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
	.screen = 17
};

static const char* caves_mapwarp_array[] = {
	mapCavesMain,
	mapCavesDillo,
	mapCavesCrown,
	mapCavesBBlast,
	mapCavesBeetleRace,
	mapCaves5DCs,
	mapCaves5DIs,
	mapCavesIceCastle,
	mapCavesRotatingRoom,
	mapCavesSprintCabin
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
	.ParentScreen = 1,
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
	.screen = 18
};

static const char* cavesmain_mapwarp_array[] = {
	mapCavesPortal,
	mapCavesCabinsArea,
	mapCavesGiantBoulder,
	mapCavesIceCastleArea,
	mapCavesIglooArea,
	mapCavesWaterfall
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
	.ParentScreen = 17,
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
	.screen = 19
};

static const char* caves5dc_mapwarp_array[] = {
	mapCaves5DCDK,
	mapCaves5DCDiddyCandle,
	mapCaves5DCDiddyEnemy,
	mapCaves5DCTiny,
	mapCaves5DCChunky
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
	.ParentScreen = 17,
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
	.screen = 20
};

static const char* caves5di_mapwarp_array[] = {
	mapCaves5DIDK,
	mapCaves5DIDiddy,
	mapCaves5DILanky,
	mapCaves5DITiny,
	mapCaves5DIChunky
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
	.ParentScreen = 17,
	.ParentPosition = 6
};

void openCavesMenu(void) {
	changeMenu(17);
}

