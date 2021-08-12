#include "../../include/common.h"

static const char mapJapes[] = "JUNGLE JAPES";
static const char mapAztec[] = "ANGRY AZTEC";
static const char mapFactory[] = "FRANTIC FACTORY";
static const char mapGalleon[] = "GLOOMY GALLEON";
static const char mapFungi[] = "FUNGI FOREST";
static const char mapCaves[] = "CRYSTAL CAVES";
static const char mapCastle[] = "CREEPY CASTLE";
static const char mapHelmKRool[] = "HIDEOUT HELM AND K. ROOL";
static const char mapIsles[] = "DK ISLES";

static const char* maps_container_array[] = {
	mapJapes,
	mapAztec,
	mapFactory,
	mapGalleon,
	mapFungi,
	mapCaves,
	mapCastle,
	mapHelmKRool,
	mapIsles
};

const Screen maps_container_struct = {
	.TextArray = (const int*)maps_container_array,
	.FunctionArray = maps_container_functions,
	.ArrayItems = 9,
	.ParentScreen = 0,
	.ParentPosition = 0
};

void initWarpMenu(void) {
	changeMenu(1);
}

void warpToMap(void) {
	if (InBadMap != 0) {
		playSFX(Wrong);
	} else {
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
				initiateTransition(_map,_exit);
				if ((_map > 0xCA) && (_map < 0xD0)) {
					Character = _map - 0xCB;
					if (_map != 0xCD) {
						setFlag(92,1,2);
					}
				}
			}
		}
	}
}