#include "../include/common.h"

void handleMapWarping(int map, int levelIndex) {
	// Fixes some minor bugs with the following map categories
		// Bosses
		// Crowns
		// Barrel Minigames
		// Arcade
		// Jetpac
		// Shops
		// T&S
	switch(map) {
		case 2:
			//setFlag(0x63,1,2);
			break;
		case 9:
			//setFlag(0x61,1,2);
		break;
	}
}