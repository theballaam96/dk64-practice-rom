#include "../../include/common.h"

void openAztecMainMenu(void) {
	changeMenu(5);
}

void openAztec5DTMenu(void) {
	changeMenu(6);
}

static const unsigned char aztec_destmap[] = {
	0x0, // Null for main map
	0xC5, // Dogadon 1
	0x49, // Crown
	0x29, // BBlast
	0xE, // Beetle Slide
	0x0, // Null for 5DTs
	0x14, // Llama Temple
	0x10 // Tiny Temple
};

static const unsigned char aztec_destexit[] = {
	0x0, // Null for main map
	0x0, // Dogadon 1
	0x0, // Crown
	0x0, // BBlast
	0x0, // Beetle Slide
	0x0, // Null for 5DTs
	0x0, // Llama Temple
	0x0 // Tiny Temple
};

const MapWarp map_aztec_struct = {
	.maps = aztec_destmap,
	.exits = aztec_destexit,
	.screen = 4
};

static const char* aztec_mapwarp_array[] = {
	"MAIN MAP",
	"DOGADON 1",
	"KRITTER KARNAGE",
	"BABOON BLAST COURSE",
	"BEETLE RACE",
	"FIVE DOOR TEMPLES",
	"LLAMA TEMPLE",
	"TINY TEMPLE"
};

static const int aztec_mapwarp_functions[] = {
	(int)&openAztecMainMenu,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&openAztec5DTMenu,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen aztec_mapwarp_struct = {
	.TextArray = (int*)aztec_mapwarp_array,
	.FunctionArray = aztec_mapwarp_functions,
	.ArrayItems = 8,
	.ParentScreen = 1,
	.ParentPosition = 1
};

static const unsigned char aztec_main_destmap[] = {
	0x26, // Portal
	0x26, // Totem
	0x26, // Oasis
	0x26, // Snake Road
};

static const unsigned char aztec_main_destexit[] = {
	0x00, // Portal
	0x12, // Totem
	0x08, // Oasis
	0x0A, // Snake Road
};

const MapWarp map_aztecmain_struct = {
	.maps = aztec_main_destmap,
	.exits = aztec_main_destexit,
	.screen = 5
};

static const char* aztecmain_mapwarp_array[] = {
	"FROM PORTAL",
	"FEED ME TOTEM",
	"OASIS",
	"SNAKE ROAD"
};

static const int aztecmain_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen aztecmain_mapwarp_struct = {
	.TextArray = (int*)aztecmain_mapwarp_array,
	.FunctionArray = aztecmain_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = 4,
	.ParentPosition = 0
};

static const unsigned char aztec_fivedt_destmap[] = {
	0x13, // DK
	0x15, // Diddy
	0x17, // Lanky
	0x16, // Tiny
	0x18 // Chunky
};

static const unsigned char aztec_fivedt_destexit[] = {
	0x0, // DK
	0x0, // Diddy
	0x0, // Lanky
	0x0, // Tiny
	0x0 // Chunky
};

const MapWarp map_aztecfivedt_struct = {
	.maps = aztec_fivedt_destmap,
	.exits = aztec_fivedt_destexit,
	.screen = 6
};

static const char* aztecfivedt_mapwarp_array[] = {
	"FIVE DOOR TEMPLE:DK",
	"FIVE DOOR TEMPLE:DIDDY",
	"FIVE DOOR TEMPLE:LANKY",
	"FIVE DOOR TEMPLE:TINY",
	"FIVE DOOR TEMPLE:CHUNKY"
};

static const int aztecfivedt_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen aztecfivedt_mapwarp_struct = {
	.TextArray = (int*)aztecfivedt_mapwarp_array,
	.FunctionArray = aztecfivedt_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = 4,
	.ParentPosition = 5
};

void openAztecMenu(void) {
	changeMenu(4);
}

