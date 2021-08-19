#include "../include/common.h"

void initHack(void) {
	if ((Gamemode == 0) && (LoadedHooks == 0)) {
		Precision = 2;
		InputDisplayIndex = -1;
		// if (StoredSettings.hasSavedData) {
		// 	for (int i = 0; i < 5; i++) {
		// 		kongcolors[i] = StoredSettings.kongColors[i];
		// 	}
		// }
		LoadedHooks = 1;
	}
}