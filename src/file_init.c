#include "../include/common.h"

void fileInit(void) {
	if (FileInitQOLOff == 0) {
		if ((CutsceneActive == 6) && (CurrentMap == 0x50)) {
			char _filestarted = checkFlag(FLAG_WATERFALL,0);
			if (_filestarted == 0) {
				setFlag(FLAG_WATERFALL,1,0); // Waterfall Cutscene
				setFlag(FLAG_ESCAPE,1,0); // Escape Cutscene
				setFlag(FLAG_FTT_DIDDY,1,0); // Diddy FTT
				setFlag(FLAG_FTT_LANKY,1,0); // Lanky FTT
				setFlag(FLAG_FTT_TINY,1,0); // Tiny FTT
				setFlag(FLAG_FTT_CHUNKY,1,0); // Chunky FTT
			}
		}
	} else {
		if ((CutsceneActive == 6) && (CurrentMap == 0x50)) {
			if (!checkFlag(FLAG_ESCAPE, 0) && (DestMap == 0x22)) {
				DestMap = 0xB0;
				DestExit = 1;
			}
		}
	}
}