#include "../include/common.h"

void initHack(void) {
	
	if ((LoadedHooks == 0) && (CurrentMap == 0x50)) {
		Precision = 2;
		InputDisplayIndex = -1;
		loadSettings();
		// if (StoredSettings.hasSavedData) {
		// 	for (int i = 0; i < 5; i++) {
		// 		kongcolors[i] = StoredSettings.kongColors[i];
		// 	}
		// }
		LoadedHooks = 1;
	}
}