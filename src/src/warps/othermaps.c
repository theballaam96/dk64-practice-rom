#include "../../include/common.h"

static const char mapArcade[] = "Arcade (Mystery Menu)";
static const char mapJetpac[] = "Jetpac (Mystery Menu)";

static const unsigned char other_destmap[] = {
	0x2, // Arcade
	0x9, // Jetpac
};

static const unsigned char other_destexit[] = {
	0x0, // Arcade
	0x0, // Jetpac
};

const MapWarp map_other_struct = {
	.maps = other_destmap,
	.exits = other_destexit,
	.screen = 70
};

static const char* other_mapwarp_array[] = {
	mapArcade,
	mapJetpac
};

static const int other_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen other_mapwarp_struct = {
	.TextArray = (int*)other_mapwarp_array,
	.FunctionArray = other_mapwarp_functions,
	.ArrayItems = 2,
	.ParentScreen = 1,
	.ParentPosition = 9
};

void openOtherMapsMenu(void) {
	changeMenu(70);
};

