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
	int _char = Character;
	if (ROM_VERSION == 0) {
		prepKongColoring();
	}
	// DK = 1 (Blue)
	// Diddy = 2 (Yellow Cap)
	// Lanky = 2 (Purple Straps)
	// Tiny = 2 (Purple)
	// Chunky = 1 (Red)
	if (Character < 5) {
		PlayerOneColor = (int)kongcolors[_char];
	} else {
		PlayerOneColor = 0;
	}
}

void startupSkip(void) {
	char _skip = 0;
	char _map = 0x4C;
	char _mode = 2; 
	if (DisableStartupSkip == 0) {
		if (assignedConsole == 0) {
			_map = 0x51;
		} else {
			_map = 0x50;
		}
		_mode = 5;
		if (Gamemode == 1) {
			_skip = 1;
		}
	}
	BetaNinRWSkip = _skip;
	LogosDestMap = _map;
	LogosDestMode = _mode;
}

void setKRoolRound(void) {
	if (KRoolRoundSetting == 0) {
		// Random
		if (((CutsceneActive == 6) && (CurrentMap == 0x50)) || (TransitionSpeed > 0)) {
			StoredRound = (RNG & 0xF) + 1;
			if (StoredRound > 11) {
				StoredRound = 1;
			} else {
				if (StoredRound < 1) {
					StoredRound = 11;
				}
			}
		}
		KRoolRound = StoredRound;
	} else {
		// Forced Sequential
		if ((CurrentMap > 0xCA) && (CurrentMap < 0xD0)) {
			KRoolRound = CurrentMap - 0xCA;
		}
	}
}