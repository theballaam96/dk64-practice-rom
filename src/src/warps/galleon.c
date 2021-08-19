#include "../../include/common.h"

static const char mapGalleonMain[] = "MAIN MAP";
static const char mapGalleonPufftoss[] = "PUFFTOSS";
static const char mapGalleonBBlast[] = "BABOON BLAST COURSE";
static const char mapGalleonSeasick[] = "K. ROOL'S SHIP";
static const char mapGalleonLighthouse[] = "LIGHTHOUSE";
static const char mapGalleonMermaid[] = "MERMAID PALACE";
static const char mapGalleonMechFish[] = "MECHANICAL FISH";
static const char mapGalleonSeal[] = "SEAL RACE";
static const char mapGalleonShipwrecks[] = "SHIPWRECKS";
static const char mapGalleonSubmarine[] = "SUBMARINE";
static const char mapGalleonTreasureChest[] = "TREASURE CHEST";

static const char mapGalleonPortal[] = "FROM PORTAL";
static const char mapGalleonCranky[] = "CRANKY AREA";
static const char mapGalleonLighthouseArea[] = "LIGHTHOUSE SIDE";
static const char mapGalleonShipwreckSide[] = "SHIPWRECK SIDE";

static const char mapGalleon5DSDK[] = "FIVE DOOR SHIP: DK";
static const char mapGalleon5DSDiddy[] = "FIVE DOOR SHIP: DIDDY";
static const char mapGalleon5DSLanky[] = "FIVE DOOR SHIP: LANKY";
static const char mapGalleon5DSTiny[] = "FIVE DOOR SHIP: TINY";
static const char mapGalleon5DSChunky[] = "FIVE DOOR SHIP: CHUNKY";
static const char mapGalleon2DSLanky[] = "TWO DOOR SHIP: LANKY";
static const char mapGalleon2DSTiny[] = "TWO DOOR SHIP: TINY";

void openGalleonMainMenu(void) {
	changeMenu(10);
}

void openGalleonShipsMenu(void) {
	changeMenu(11);
}

static const unsigned char galleon_destmap[] = {
	0x0, // Null for main map
	0x6F, // Pufftoss
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
	.screen = 9
};

static const char* galleon_mapwarp_array[] = {
	mapGalleonMain,
	mapGalleonPufftoss,
	mapGalleonBBlast,
	mapGalleonSeasick,
	mapGalleonLighthouse,
	mapGalleonMermaid,
	mapGalleonMechFish,
	mapGalleonSeal,
	mapGalleonShipwrecks,
	mapGalleonSubmarine,
	mapGalleonTreasureChest
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
	(int)&openGalleonShipsMenu,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen galleon_mapwarp_struct = {
	.TextArray = (int*)galleon_mapwarp_array,
	.FunctionArray = galleon_mapwarp_functions,
	.ArrayItems = 11,
	.ParentScreen = 1,
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
	.screen = 10
};

static const char* galleonmain_mapwarp_array[] = {
	mapGalleonPortal,
	mapGalleonCranky,
	mapGalleonLighthouseArea,
	mapGalleonShipwreckSide
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
	.ParentScreen = 9,
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
	.screen = 11
};

static const char* galleonships_mapwarp_array[] = {
	mapGalleon5DSDK,
	mapGalleon5DSDiddy,
	mapGalleon5DSLanky,
	mapGalleon5DSTiny,
	mapGalleon5DSChunky,
	mapGalleon2DSLanky,
	mapGalleon2DSTiny
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
	.ParentScreen = 9,
	.ParentPosition = 8
};

void openGalleonMenu(void) {
	changeMenu(9);
}

