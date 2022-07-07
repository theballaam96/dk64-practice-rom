#include "../include/common.h"

void openIslesMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_ISLESMAIN);
}

void openIslesLobbyMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_ISLESLOBBIES);
}

static const unsigned char isles_destmap[] = {
	0x0, // Null for overworld
	0x9E, // Crown 1
	0x9D, // Crown 2
	0xBD, // Inside BFI
	0x61, // K Lumsy
	0x0, // Null for Lobbies
	0xC3, // Snide's Room
	0xB0, // Training Grounds
	0xAB // Treehouse
};

static const unsigned char isles_destexit[] = {
	0x0, // Null for overworld
	0x0, // Crown 1
	0x0, // Crown 2
	0x0, // Inside BFI
	0x0, // K Lumsy
	0x0, // Null for Lobbies
	0x0, // Snide's Room
	0x1, // Training Grounds
	0x2 // Treehouse
};

const MapWarp map_isles_struct = {
	.maps = isles_destmap,
	.exits = isles_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_ISLES
};

static const char* isles_mapwarp_array[] = {
	"OVERWORLD",
	"BISH BASH BRAWL",
	"FOREST FRACAS",
	"INSIDE BANANA FAIRY ISLAND",
	"K.LUMSY",
	"LOBBIES",
	"SNIDES ROOM",
	"TRAINING GROUNDS",
	"TREEHOUSE"
};

static const int isles_mapwarp_functions[] = {
	(int)&openIslesMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&openIslesLobbyMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen isles_mapwarp_struct = {
	.TextArray = (int*)isles_mapwarp_array,
	.FunctionArray = isles_mapwarp_functions,
	.ArrayItems = 9,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
	.ParentPosition = 8
};

static const unsigned char isles_main_destmap[] = {
	0x22, // Escape
	0x22, // Outside BFI
	0x22, // Kroc Isles
	0x22, // Outside K Rool
	0x22 // Top of Isles
};

static const unsigned char isles_main_destexit[] = {
	0x0, // Escape
	0x8, // Outside BFI
	0x4, // Kroc Isles
	0xC, // Outside K Rool
	0x6 // Top of Isles
};

const MapWarp map_islesmain_struct = {
	.maps = isles_main_destmap,
	.exits = isles_main_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_ISLESMAIN
};

static const char* islesmain_mapwarp_array[] = {
	"ESCAPE",
	"BANANA FAIRY ISLAND AREA",
	"KROC ISLE",
	"OUTSIDE K ROOL",
	"TOP OF DK ISLES"
};

static const int islesmain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen islesmain_mapwarp_struct = {
	.TextArray = (int*)islesmain_mapwarp_array,
	.FunctionArray = islesmain_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ISLES,
	.ParentPosition = 0
};

static const unsigned char isles_lobbies_destmap[] = {
	0xA9, // Japes
	0xAD, // Aztec
	0xAF, // Factory
	0xAE, // Galleon
	0xB2, // Fungi
	0xC2, // Caves
	0xC1, // Castle
	0xAA // Helm
};

static const unsigned char isles_lobbies_destexit[] = {
	0x0, // Japes
	0x0, // Aztec
	0x0, // Factory
	0x0, // Galleon
	0x0, // Fungi
	0x0, // Caves
	0x0, // Castle
	0x0 // Helm
};

const MapWarp map_isleslobbies_struct = {
	.maps = isles_lobbies_destmap,
	.exits = isles_lobbies_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_ISLESLOBBIES
};

static const char* isleslobbies_mapwarp_array[] = {
	"JUNGLE JAPES LOBBY",
	"ANGRY AZTEC LOBBY",
	"FRANTIC FACTORY LOBBY",
	"GLOOMY GALLEON LOBBY",
	"FUNGI FOREST LOBBY",
	"CRYSTAL CAVES LOBBY",
	"CREEPY CASTLE LOBBY",
	"HIDEOUT HELM LOBBY"
};

static const int isleslobbies_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen isleslobbies_mapwarp_struct = {
	.TextArray = (int*)isleslobbies_mapwarp_array,
	.FunctionArray = isleslobbies_mapwarp_functions,
	.ArrayItems = 8,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ISLES,
	.ParentPosition = 5
};

void openIslesMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_ISLES);
}

