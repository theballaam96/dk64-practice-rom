#include "../../include/common.h"

static const char mapIslesMain[] = "OVERWORLD";
static const char mapIslesBFI[] = "INSIDE BANANA FAIRY ISLAND";
static const char mapIslesKLumsy[] = "K. LUMSY";
static const char mapIslesLobbies[] = "LOBBIES";
static const char mapIslesSnides[] = "SNIDE'S ROOM";
static const char mapIslesTrainingGrounds[] = "TRAINING GROUNDS";
static const char mapIslesTreehouse[] = "TREEHOUSE";

static const char mapIslesEscape[] = "ESCAPE";
static const char mapIslesBFIArea[] = "BANANA FAIRY ISLAND AREA";
static const char mapIslesKrocIsle[] = "KROC ISLE";
static const char mapIslesOutsideKRool[] = "OUTSIDE K. ROOL";
static const char mapIslesTopOfIsles[] = "TOP OF DK ISLES";

static const char mapIslesLobbyJapes[] = "JUNGLE JAPES LOBBY";
static const char mapIslesLobbyAztec[] = "ANGRY AZTEC LOBBY";
static const char mapIslesLobbyFactory[] = "FRANTIC FACTORY LOBBY";
static const char mapIslesLobbyGalleon[] = "GLOOMY GALLEON LOBBY";
static const char mapIslesLobbyFungi[] = "FUNGI FOREST LOBBY";
static const char mapIslesLobbyCaves[] = "CRYSTAL CAVES LOBBY";
static const char mapIslesLobbyCastle[] = "CREEPY CASTLE LOBBY";
static const char mapIslesLobbyHelm[] = "HIDEOUT HELM LOBBY";

void openIslesMainMenu(void) {
	changeMenu(28);
}

void openIslesLobbyMenu(void) {
	changeMenu(29);
}

static const unsigned char isles_destmap[] = {
	0x0, // Null for overworld
	0xBD, // Inside BFI
	0x61, // K Lumsy
	0x0, // Null for Lobbies
	0xC3, // Snide's Room
	0xB0, // Training Grounds
	0xAB // Treehouse
};

static const unsigned char isles_destexit[] = {
	0x0, // Null for overworld
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
	.screen = 27
};

static const char* isles_mapwarp_array[] = {
	mapIslesMain,
	mapIslesBFI,
	mapIslesKLumsy,
	mapIslesLobbies,
	mapIslesSnides,
	mapIslesTrainingGrounds,
	mapIslesTreehouse
};

static const int isles_mapwarp_functions[] = {
	(int)&openIslesMainMenu,
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
	.ArrayItems = 7,
	.ParentScreen = 1,
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
	.screen = 28
};

static const char* islesmain_mapwarp_array[] = {
	mapIslesEscape,
	mapIslesBFIArea,
	mapIslesKrocIsle,
	mapIslesOutsideKRool,
	mapIslesTopOfIsles
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
	.ParentScreen = 27,
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
	.screen = 29
};

static const char* isleslobbies_mapwarp_array[] = {
	mapIslesLobbyJapes,
	mapIslesLobbyAztec,
	mapIslesLobbyFactory,
	mapIslesLobbyGalleon,
	mapIslesLobbyFungi,
	mapIslesLobbyCaves,
	mapIslesLobbyCastle,
	mapIslesLobbyHelm
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
	.ParentScreen = 27,
	.ParentPosition = 3
};

void openIslesMenu(void) {
	changeMenu(27);
}

