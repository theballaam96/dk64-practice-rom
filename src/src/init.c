#include "../include/common.h"

void initHack(void) {
	if ((LoadedHooks == 0) && (CurrentMap == 0x28) && (TransitionSpeed > 0)) {
		InputDisplayIndex = -1;
		IsSuperspeedOn = 1;
		DebugInfoOn = 1;
		*(int*)(0x80731F78) = 0;
		*(int*)(0x80728670) = 0x240447B8; // Increases the malloc for character spawners
		*(char*)(0x80745D20) = 113; // NFR Title Screen Song
		colorMenuSky();
		for (int i = 0; i < WatchCount; i++) {
			ViewedSnagWatches[i] = -1;
		}
		loadExtraHooks();
		if (StoredSettings.hasSavedData == 0) {
			*(int *)(0x807ED558) = -1;
			*(int *)(0x807ED55C) = -1;
			SaveToGlobal();
		}
		if (StoredSettings.console > 0) {
			DestMap = 0x50;
		}
		loadSettings();
		LoadedHooks = 1;
	}
}