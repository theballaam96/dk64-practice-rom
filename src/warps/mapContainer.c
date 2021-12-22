#include "../../include/common.h"

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
	changeMenu(1);
}

void warpToMap(void) {
	resetMap();
	for (int i = 0; i < WarpScreens; i++) {
		int _screen = ActiveMenu.screenIndex;
		int check_screen = warping_struct[i]->screen;
		if (_screen == check_screen) {
			TimerData.Timer = 0;
			TimerData.Mode = 0;
			TempFlagBlock[0xA] = TempFlagBlock[0xA] & 0xE1;
			TempFlagBlock[0xB] = (TempFlagBlock[0xB] | 0x21) & 0x7F;
			setPermFlag(0x17E);
			int _map = warping_struct[i]->maps[(int)ActiveMenu.positionIndex];
			int _exit = warping_struct[i]->exits[(int)ActiveMenu.positionIndex];
			if ((_map > 0xCA) && (_map < 0xD0)) {
				Character = _map - 0xCB;
				if (_map != 0xCD) {
					setFlag(92,1,2);
				}
			}
			CutsceneFadeActive = 0; // Prevent wrong cutscene crashes
			handleMapWarping(_map, _exit, 0, MAPWARP);
		}
	}
}