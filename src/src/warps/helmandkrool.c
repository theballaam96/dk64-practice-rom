#include "../../include/common.h"

static const char mapHelmEntrance[] = "HELM: ENTRACE";
static const char mapHelmBoMRoom[] = "HELM: BOM ROOM";
static const char mapHelmNavigationRoom[] = "HELM: NAVIGATION ROOM";
static const char mapRoolDK[] = "K. ROOL: DK PHASE";
static const char mapRoolDiddy[] = "K. ROOL: DIDDY PHASE";
static const char mapRoolLanky[] = "K. ROOL: LANKY PHASE";
static const char mapRoolTiny[] = "K. ROOL: TINY PHASE";
static const char mapRoolChunky[] = "K. ROOL: CHUNKY PHASE";

static const unsigned char helmrool_destmap[] = {
	0x11, // Helm Entrance
	0x11, // Helm BoM Room
	0x11, // Helm Navigation Room
	0xCB, // DK Phase
	0xCC, // Diddy Phase
	0xCD, // Lanky Phase
	0xCE, // Tiny Phase
	0xCF // Chunky Phase
};

static const unsigned char helmrool_destexit[] = {
	0x0, // Helm Entrance
	0x3, // Helm BoM Room
	0x4, // Helm Navigation Room
	0x0, // DK Phase
	0x0, // Diddy Phase
	0x0, // Lanky Phase
	0x0, // Tiny Phase
	0x0 // Chunky Phase
};

const MapWarp map_helmrool_struct = {
	.maps = helmrool_destmap,
	.exits = helmrool_destexit,
	.screen = 30
};

static const char* helmrool_mapwarp_array[] = {
	mapHelmEntrance,
	mapHelmBoMRoom,
	mapHelmNavigationRoom,
	mapRoolDK,
	mapRoolDiddy,
	mapRoolLanky,
	mapRoolTiny,
	mapRoolChunky
};

static const int helmrool_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap
};

const Screen helmrool_mapwarp_struct = {
	.TextArray = (const int*)helmrool_mapwarp_array,
	.FunctionArray = helmrool_mapwarp_functions,
	.ArrayItems = 8,
	.ParentScreen = 1,
	.ParentPosition = 7
};

void openHelmRoolMenu(void) {
	changeMenu(30);
}

