#include "../include/common.h"

static char boot_speedup_done = 0;

void bootSpeedup(void) {
	if (!boot_speedup_done) {
		boot_speedup_done = 1;
		int balloon_patch_count = 0;
		for (int j = 0; j < 8; j++) {
			coloredBananaCounts[j] = 0;
		}
		for (int i = 0; i < 221; i++) {
			balloonPatchCounts[i] = balloon_patch_count;
			int* setup = getMapData(9,i,1,1);
			char* modeltwo_setup = 0;
			char* actor_setup = 0;
			if (setup) {
				int world = getWorld(i,1);
				getModel2AndActorInfo(setup,(int**)&modeltwo_setup,(int**)&actor_setup);
				int model2_count = *(int*)(modeltwo_setup);
				int actor_count = *(int*)(actor_setup);
				char* focused_actor = (char*)(actor_setup + 4);
				char* focused_model2 = (char*)(modeltwo_setup + 4);
				if (actor_count > 0) {
					for (int j = 0; j < actor_count; j++) {
						balloon_patch_count += isBalloonOrPatch(*(short*)((int)focused_actor + 0x32) + 0x10);
						focused_actor += 0x38;
					}
				}
				if (model2_count > 0) {
					for (int j = 0; j < model2_count; j++) {
						coloredBananaCounts[world] += isSingleOrBunch(*(unsigned short*)(focused_model2 + 0x28));
						focused_model2 += 0x30;
					}
				}
				enableComplexFree();
				complexFreeWrapper(setup);
			}
		}
	}
}

void initHack(int source) {
	if (LoadedHooks == 0) {
		if (((CurrentMap == 0x28) && (TransitionSpeed > 0)) || (source == 1)) {
			InputDisplayIndex = -1;
			IsSuperspeedOn = 1;
			DebugInfoOn = 1;
			debugColumnLoop = 0; // Debug 1 Column
			characterSpawnerMalloc = 0x240447B8; // Increases the malloc for character spawners
			displayListCap = 0x24040002; // Expand Display List Cap
			nfrTitleScreenSong = 113; // NFR Title Screen Song
			// Style 6 Mtx
			int base_mtx = 75;
			style6Mtx[0x0] = base_mtx;
			style6Mtx[0x5] = base_mtx;
			style6Mtx[0xF] = 100;
			base_mtx = 12;
			style2Mtx[0x0] = base_mtx;
			style2Mtx[0x5] = base_mtx;
			style2Mtx[0xF] = 10;
			colorMenuSky();
			if (ROM_VERSION == 0) {
				*(char*)(0x8074D8D5) = 2; // Change Actor 1 to 3D Model
				*(short*)(0x8074DB48) = 20; // Change paad size to 0x30
				*(int*)(0x8074C0A4) = (int)&collisionCode;
			}
			for (int i = 0; i < WatchCount; i++) {
				ViewedSnagWatches[i] = -1;
			}
			loadExtraHooks();
			if (StoredSettings.console == 0) {
				int gfb_start = (int)getFlagBlockAddress(1);
				*(int*)(gfb_start) = -1;
				*(int*)(gfb_start + 4) = -1;
				SaveToGlobal();
			}
			if (StoredSettings.console > 0) {
				DestMap = 0x50;
			}
			loadSettings();
			LoadedHooks = 1;
		}
	}
}

void quickInit(void) {
	initHack(1);
	initiateTransition(0x50,0);
	Gamemode = 5;
	Mode = 5;
}