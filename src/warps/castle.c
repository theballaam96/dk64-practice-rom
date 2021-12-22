#include "../../include/common.h"

void openCastleMainMenu(void) {
	changeMenu(22);
}

void openCastleCryptMenu(void) {
	changeMenu(23);
}

void openCastleDungeonTunnelMenu(void) {
	changeMenu(24);
}

void openCastleOutsideBuildingsMenu(void) {
	changeMenu(25);
}

void openCastleRoomsMenu(void) {
	changeMenu(26);
}

static const unsigned char castle_destmap[] = {
	0x00, // Null for main map
	0xC7, // King Kut Out
	0xA1, // Crown
	0xBB, // BBlast
	0xB9, // Car Race
	0x00, // Null for Crypts
	0xA3, // Dungeon
	0x00, // Null for Tunnel
	0x00, // Null for Outside Buildings
	0x00 // Null for Rooms
};

static const unsigned char castle_destexit[] = {
	0x00, // Null for main map
	0x00, // King Kut Out
	0x00, // Crown
	0x00, // BBlast
	0x00, // Car Race
	0x00, // Null for Crypts
	0x00, // Dungeon
	0x00, // Null for Tunnel
	0x00, // Null for Outside Buildings
	0x00 // Null for Rooms
};

const MapWarp map_castle_struct = {
	.maps = castle_destmap,
	.exits = castle_destexit,
	.screen = 21
};

static const char* castle_mapwarp_array[] = {
	"MAIN MAP",
	"KING KUT OUT",
	"PINNACLE PALAVER",
	"BABOON BLAST COURSE",
	"CAR RACE",
	"CRYPT",
	"DUNGEON",
	"DUNGEON TUNNEL",
	"OUTSIDE BUILDINGS",
	"ROOMS"
};

static const int castle_mapwarp_functions[] = {
	(int)&openCastleMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&openCastleCryptMenu,
	(int)&warpToMap,
	(int)&openCastleDungeonTunnelMenu,
	(int)&openCastleOutsideBuildingsMenu,
	(int)&openCastleRoomsMenu
};

const Screen castle_mapwarp_struct = {
	.TextArray = (int*)castle_mapwarp_array,
	.FunctionArray = castle_mapwarp_functions,
	.ArrayItems = 10,
	.ParentScreen = 1,
	.ParentPosition = 6
};

static const unsigned char castle_main_destmap[] = {
	0x57, // Portal
	0x57, // Intro
	0x57, // Top of Castle
	0x57, // Warp 2
	0x57, // Warp 4
};

static const unsigned char castle_main_destexit[] = {
	0x00, // Portal
	0x15, // Intro
	0x0E, // Top of Castle
	0x03, // Warp 2
	0x0A, // Warp 4
};

const MapWarp map_castlemain_struct = {
	.maps = castle_main_destmap,
	.exits = castle_main_destexit,
	.screen = 22
};

static const char* castlemain_mapwarp_array[] = {
	"FROM PORTAL",
	"INTRO",
	"TOP OF CASTLE",
	"WARP 2",
	"WARP 4"
};

static const int castlemain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen castlemain_mapwarp_struct = {
	.TextArray = (int*)castlemain_mapwarp_array,
	.FunctionArray = castlemain_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = 21,
	.ParentPosition = 0
};

static const unsigned char castle_crypt_destmap[] = {
	0x70, // Crypt DDC
	0x6C, // Crypt LT
	0xB7, // Crypt Hub
	0x6A // Crypt Minecart
};

static const unsigned char castle_crypt_destexit[] = {
	0x0, // Crypt DDC
	0x0, // Crypt LT
	0x0, // Crypt Hub
	0x0 // Crypt Minecart
};

const MapWarp map_castlecrypt_struct = {
	.maps = castle_crypt_destmap,
	.exits = castle_crypt_destexit,
	.screen = 23
};

static const char* castlecrypt_mapwarp_array[] = {
	"CRYPT:DK DIDDY CHUNKY",
	"CRYPT:LANKY TINY",
	"CRYPT:HUB",
	"CRYPT:MINECART"
};

static const int castlecrypt_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen castlecrypt_mapwarp_struct = {
	.TextArray = (int*)castlecrypt_mapwarp_array,
	.FunctionArray = castlecrypt_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = 21,
	.ParentPosition = 5
};


static const unsigned char castle_tunnel_destmap[] = {
	0x97, // Tunnel Near
	0x97, // Tunnel Rear
};

static const unsigned char castle_tunnel_destexit[] = {
	0x0, // Tunnel Near
	0x2, // Tunnel Rear
};

const MapWarp map_castletunnel_struct = {
	.maps = castle_tunnel_destmap,
	.exits = castle_tunnel_destexit,
	.screen = 24
};

static const char* castletunnel_mapwarp_array[] = {
	"DUNGEON TUNNEL:NEAR",
	"DUNGEON TUNNEL:FAR",
};

static const int castletunnel_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen castletunnel_mapwarp_struct = {
	.TextArray = (int*)castletunnel_mapwarp_array,
	.FunctionArray = castletunnel_mapwarp_functions,
	.ArrayItems = 2,
	.ParentScreen = 21,
	.ParentPosition = 7
};

static const unsigned char castle_outside_destmap[] = {
	0xA8, // Greenhouse
	0xA6, // Shed
	0xA4, // Tree
	0xA7 // Trash Can
};

static const unsigned char castle_outside_destexit[] = {
	0x0, // Greenhouse
	0x0, // Shed
	0x0, // Tree
	0x0 // Trash Can
};

const MapWarp map_castleoutside_struct = {
	.maps = castle_outside_destmap,
	.exits = castle_outside_destexit,
	.screen = 25
};

static const char* castleoutside_mapwarp_array[] = {
	"GREENHOUSE",
	"SHED",
	"TREE",
	"TRASH CAN"
};

static const int castleoutside_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen castleoutside_mapwarp_struct = {
	.TextArray = (int*)castleoutside_mapwarp_array,
	.FunctionArray = castleoutside_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = 21,
	.ParentPosition = 8
};

static const unsigned char castle_rooms_destmap[] = {
	0x58, // Ballroom
	0x72, // Library
	0x71, // Museum
	0x69 // Wind Tower
};

static const unsigned char castle_rooms_destexit[] = {
	0x0, // Ballroom
	0x1, // Library
	0x0, // Museum
	0x0 // Wind Tower
};

const MapWarp map_castlerooms_struct = {
	.maps = castle_rooms_destmap,
	.exits = castle_rooms_destexit,
	.screen = 26
};

static const char* castlerooms_mapwarp_array[] = {
	"BALLROOM",
	"LIBRARY",
	"MUSEUM",
	"WIND TOWER"
};

static const int castlerooms_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen castlerooms_mapwarp_struct = {
	.TextArray = (int*)castlerooms_mapwarp_array,
	.FunctionArray = castlerooms_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = 21,
	.ParentPosition = 9
};

void openCastleMenu(void) {
	changeMenu(21);
}

