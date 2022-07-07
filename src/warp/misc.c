#include "../include/common.h"

void warpToStoryArcade(void) {
	setDataStates(0,1);
	warpToMap();
}

void warpToStoryJetpac(void) {
	setDataStates(0,2);
	warpToMap();
}

void warpToMenuArcade(void) {
	setDataStates(0,3);
	warpToMap();
}

void warpToMenuJetpac(void) {
	setDataStates(0,4);
	warpToMap();
}

static const unsigned char other_destmap[] = {
	0x2, // Arcade
	0x9, // Jetpac
	0x2, // Story Arcade
	0x9, // Story Jetpac
};

static const unsigned char other_destexit[] = {
	0x0, // Arcade
	0x0, // Jetpac
	0x0, // Story Arcade
	0x0, // Story Jetpac
};

const MapWarp map_other_struct = {
	.maps = other_destmap,
	.exits = other_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_OTHER
};

static const char* other_mapwarp_array[] = {
	"ARCADE <MYSTERY MENU>",
	"JETPAC <MYSTERY MENU>",
	"ARCADE <STORY MODE>",
	"JETPAC <STORY MODE>",
};

static const int other_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToStoryArcade,
	(int)&warpToStoryJetpac,
};

const Screen other_mapwarp_struct = {
	.TextArray = (int*)other_mapwarp_array,
	.FunctionArray = other_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
	.ParentPosition = 9
};

void openOtherMapsMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_OTHER);
};

