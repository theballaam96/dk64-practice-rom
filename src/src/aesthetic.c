#include "../include/common.h"

void colorMenuSky(void) {
	MenuSkyTopRGB.red = 0;
	MenuSkyTopRGB.green = 0;
	MenuSkyTopRGB.blue = 0xFF;
	MenuSkyRGB.red = 0;
	MenuSkyRGB.green = 0;
	MenuSkyRGB.blue = 0;
};

char kongcolors[5] = {1,2,2,2,1};

void colorKong(void) {
	prepKongColoring();
	// DK = 1 (Blue)
	// Diddy = 2 (Yellow Cap)
	// Lanky = 2 (Purple Straps)
	// Tiny = 2 (Purple)
	// Chunky = 1 (Red)
	if (Character < 5) {
		PlayerOneColor = (int)kongcolors[(int)Character];
	} else {
		PlayerOneColor = 0;
	}
}

void startupSkip(void) {
	char _skip = 0;
	char _map = 0x4C;
	char _mode = 2; 
	if (DisableStartupSkip == 0) {
		_map = 0x50;
		_mode = 5;
		if (Gamemode == 1) {
			_skip = 1;
		}
	}
	BetaNinRWSkip = _skip;
	LogosDestMap = _map;
	LogosDestMode = _mode;
}