#include "../include/common.h"

static const char* maps_container_array[] = {
	"JUNGLE JAPES",
	"ANGRY AZTEC",
	"FRANTIC FACTORY",
	"GLOOMY GALLEON",
	"FUNGI FOREST",
	"CRYSTAL CAVES",
	"CREEPY CASTLE",
	"HIDEOUT HELM AND K. ROOL",
	"DK ISLES",
	"MISCELLANEOUS",
	"BONUS BARRELS"
};

const Screen maps_container_struct = {
	.TextArray = (int*)maps_container_array,
	.FunctionArray = maps_container_functions,
	.ArrayItems = 11,
	.ParentScreen = 0,
	.ParentPosition = 0
};

void initWarpMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_ROOT);
}

void warpToMap(void) {
	resetMap();
	for (int i = 0; i < WarpScreens; i++) {
		int _screen = ActiveMenu.screenIndex;
		int check_screen = warping_struct[i]->screen;
		if (_screen == check_screen) {
			TimerData.Timer = 0;
			TimerData.Mode = 0;
			setFlag(FLAG_KROOL_INTRO_TINY,1,2);
			setFlag(FLAG_KROOL_INTRO_DK,1,2);
			setFlag(FLAG_KROOL_TOE_1,0,2);
			setFlag(FLAG_KROOL_TOE_2,0,2);
			setFlag(FLAG_KROOL_TOE_3,0,2);
			setFlag(FLAG_KROOL_TOE_4,0,2);
			setFlag(FLAG_KROOL_CUTSCENE_GORILLAGONE,0,2);
			setPermFlag(FLAG_FTT_BLOCKER);
			int _map = warping_struct[i]->maps[(int)ActiveMenu.positionIndex];
			int _exit = warping_struct[i]->exits[(int)ActiveMenu.positionIndex];
			if ((_map > 0xCA) && (_map < 0xD0)) {
				Character = _map - 0xCB;
				if (_map != 0xCD) {
					setFlag(FLAG_KROOL_RESET_TINY,1,2);
				}
			}
			CutsceneFadeActive = 0; // Prevent wrong cutscene crashes
			handleMapWarping(_map, _exit, 0, MAPWARP);
		}
	}
}