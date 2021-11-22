#include "../include/common.h"

void initHack(void) {
	if ((LoadedHooks == 0) && (CurrentMap == 0x28) && (TransitionSpeed > 0)) {
		InputDisplayIndex = -1;
		IsSuperspeedOn = 1;
		DebugInfoOn = 1;
		debugColumnLoop = 0; // Debug 1 Column
		characterSpawnerMalloc = 0x240447B8; // Increases the malloc for character spawners
		nfrTitleScreenSong = 113; // NFR Title Screen Song
		// int* file_size;
		// *(int*)(&file_size) = 0x180;
		// copyFromROM(0x2021600,(int*)0x807546D0,&file_size,0,0,0,0);
		//textData[0].kerning_char = -2;
		textData[0].kerning_anim = 5;
		// Style 6 Mtx
		int base_mtx = 3;
		style6Mtx[0x0] = base_mtx;
		style6Mtx[0x5] = base_mtx;
		style6Mtx[0xF] = base_mtx + 1;
		colorMenuSky();
		for (int i = 0; i < WatchCount; i++) {
			ViewedSnagWatches[i] = -1;
		}
		loadExtraHooks();
		if (StoredSettings.hasSavedData == 0) {
			globalFlags[0] = -1;
			globalFlags[1] = -1;
			SaveToGlobal();
		}
		if (StoredSettings.console > 0) {
			DestMap = 0x50;
		}
		*(int*)(0x807FFF50) = 631;
		*(int*)(0x807FFF54) = 487;
		*(float*)(0x807FFF58) = 5.19f;
		*(float*)(0x807FFF5C) = 5.19f;
		loadSettings();
		LoadedHooks = 1;
	}
}