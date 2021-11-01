#include "../include/common.h"

static char warp_loadmapvars = 0;

void handleMapWarping(int map, int levelIndex) {
	// Fixes some minor bugs with the following map categories
		// Bosses
		// Crowns
		// Barrel Minigames
		// Arcade
		// Jetpac
		// Shops
		// T&S
	// switch(map) {
	// 	case 2:
	// 		//setFlag(0x63,1,2);
	// 		break;
	// 	case 9:
	// 		//setFlag(0x61,1,2);
	// 	break;
	// }
	warp_loadmapvars = 1;
}

void loadMapVars_0(void) {
	if ((ObjectModel2Timer == 20) && (TransitionSpeed < 0) && (warp_loadmapvars)) {
		if (IsAutowalking) {
			if ((AutowalkPointer) && isRDRAM(AutowalkPointer)) {
				AutowalkPointer->xPos = (short)Player->xPos;
				AutowalkPointer->zPos = (short)Player->zPos;
			}
		}
		warp_loadmapvars = 0;
	}
}