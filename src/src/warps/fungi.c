#include "../../include/common.h"

static const char mapFungiMain[] = "MAIN MAP";
static const char mapFungiDogadon[] = "DOGADON 2";
static const char mapFungiAnthill[] = "ANTHILL";
static const char mapFungiBBlast[] = "BABOON BLAST COURSE";
static const char mapFungiBarn[] = "BARN";
static const char mapFungiDarkAttic[] = "DARK ATTIC";
static const char mapFungiGiantMush[] = "GIANT MUSHROOM";
static const char mapFungiLankyAttic[] = "LANKY'S ATTIC";
static const char mapFungiMills[] = "MILLS";
static const char mapFungiMinecart[] = "MINECART";
static const char mapFungiWinch[] = "WINCH ROOM";

static const char mapFungiPortal[] = "FROM PORTAL";
static const char mapFungiAppleSide[] = "APPLE SIDE";
static const char mapFungiMillSide[] = "MILL SIDE";
static const char mapFungiMushroomSide[] = "MUSHROOM SIDE";
static const char mapFungiOwlSide[] = "OWL TREE";
static const char mapFungiTopOfMushroom[] = "TOP OF MUSHROOM";

static const char mapFungiGMushBottom[] = "GIANT MUSHROOM: BOTTOM";
static const char mapFungiGMushMiddle[] = "GIANT MUSHROOM: MIDDLE";
static const char mapFungiGMushTop[] = "GIANT MUSHROOM: TOP";
static const char mapFungiGMushDark[] = "MUSHROOM TOP: DARK ROOM";
static const char mapFungiGMushLight[] = "MUSHROOM TOP: LIGHT ROOM";
static const char mapFungiGMushFace[] = "MUSHROOM TOP: FACE PUZZLE";

static const char mapFungiMillFront[] = "MILL: FRONT";
static const char mapFungiMillRear[] = "MILL: REAR";
static const char mapFungiMillSpider[] = "MILL: SPIDER BOSS";

void openFungiMainMenu(void) {
	changeMenu(14);
}

void openFungiGMushMenu(void) {
	changeMenu(15);
}

void openFungiMillsMenu(void) {
	changeMenu(16);
}

static const unsigned char fungi_destmap[] = {
	0x0, // Null for main map
	0x53, // Dogadon 2
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
	.screen = 13
};

static const char* fungi_mapwarp_array[] = {
	mapFungiMain,
	mapFungiDogadon,
	mapFungiAnthill,
	mapFungiBBlast,
	mapFungiBarn,
	mapFungiDarkAttic,
	mapFungiGiantMush,
	mapFungiLankyAttic,
	mapFungiMills,
	mapFungiMinecart,
	mapFungiWinch
};

static const int fungi_mapwarp_functions[] = {
	(int)&openFungiMainMenu,
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
	.TextArray = (const int*)fungi_mapwarp_array,
	.FunctionArray = fungi_mapwarp_functions,
	.ArrayItems = 11,
	.ParentScreen = 1,
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
	.screen = 14
};

static const char* fungimain_mapwarp_array[] = {
	mapFungiPortal,
	mapFungiAppleSide,
	mapFungiMillSide,
	mapFungiMushroomSide,
	mapFungiOwlSide,
	mapFungiTopOfMushroom
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
	.TextArray = (const int*)fungimain_mapwarp_array,
	.FunctionArray = fungimain_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = 13,
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
	.screen = 15
};

static const char* fungigmush_mapwarp_array[] = {
	mapFungiGMushBottom,
	mapFungiGMushMiddle,
	mapFungiGMushTop,
	mapFungiGMushDark,
	mapFungiGMushLight,
	mapFungiGMushFace
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
	.TextArray = (const int*)fungigmush_mapwarp_array,
	.FunctionArray = fungigmush_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = 13,
	.ParentPosition = 6
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
	.screen = 16
};

static const char* fungimills_mapwarp_array[] = {
	mapFungiMillFront,
	mapFungiMillRear,
	mapFungiMillSpider
};

static const int fungimills_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen fungimills_mapwarp_struct = {
	.TextArray = (const int*)fungimills_mapwarp_array,
	.FunctionArray = fungimills_mapwarp_functions,
	.ArrayItems = 3,
	.ParentScreen = 13,
	.ParentPosition = 8
};

void openFungiMenu(void) {
	changeMenu(13);
}

