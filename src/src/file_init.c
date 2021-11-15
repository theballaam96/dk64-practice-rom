#include "../include/common.h"

void fileInit(void) {
	if (FileInitQOLOff == 0) {
		if ((CutsceneActive == 6) && (CurrentMap == 0x50)) {
			char _filestarted = checkFlag(378,0);
			if (_filestarted == 0) {
				setFlag(378,1,0); // Waterfall Cutscene
				setFlag(390,1,0); // Escape Cutscene
				setFlag(367,1,0); // Diddy FTT
				setFlag(368,1,0); // Lanky FTT
				setFlag(369,1,0); // Tiny FTT
				setFlag(370,1,0); // Chunky FTT
			}
		}
	}
}