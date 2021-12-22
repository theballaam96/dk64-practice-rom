#include "../../include/common.h"

static const unsigned char helmrool_destmap[] = {
	0x11, // Helm Entrance
	0x11, // Helm BoM Room
	0x11, // Helm Navigation Room
	0xA2, // Helm Crown
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
	0x0, // Helm Crown
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
	"HELM:ENTRANCE",
	"HELM:BOM ROOM",
	"HELM:NAVIGATION",
	"SHOCKWAVE SHOWDOWN",
	"K.ROOL:DK PHASE",
	"K.ROOL:DIDDY PHASE",
	"K.ROOL:LANKY PHASE",
	"K.ROOL:TINY PHASE",
	"K.ROOL:CHUNKY PHASE"
};

static const int helmrool_mapwarp_functions[] = {
	(int)&warpToMap,
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
	.TextArray = (int*)helmrool_mapwarp_array,
	.FunctionArray = helmrool_mapwarp_functions,
	.ArrayItems = 9,
	.ParentScreen = 1,
	.ParentPosition = 7
};

void openHelmRoolMenu(void) {
	changeMenu(30);
}

