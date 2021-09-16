#include "../../include/common.h"

static const unsigned char minigame_list[] = {
	0x68, // BBother Easy
	0x88, // BBother Normal
	0x89, // BBother Hard
	0x0B, // SSnoop Normal No Logo
	0x41, // SSnoop Normal
	0x7E, // SSnoop V Easy
	0x7F, // SSnoop Easy
	0x80, // SSnoop Hard
	0x63, // SSSortie Easy
	0x86, // SSSortie Normal
	0x87, // SSSortie Hard
	0x60, // SSSalvage Normal
	0x84, // SSSalvage Hard
	0x85, // SSSalvage Easy
	0x23, // DK BBlast
	0xD4, // DK Rambi
	0xA5, // Diddy Kremling
	0xC9, // Diddy Rocketbarrel
	0x03, // Lanky Maze
	0xCA, // Lanky Zinger
	0x32, // Tiny Bounce
	0xD2, // Tiny Floor is lava
	0xD1, // Chunky ? Box
	0xD3, // Chunky Gun
	0x4E, // BBBarrage Easy
	0x4F, // BBBarrage Normal
	0x83, // BBBarrage Hard
	0x42, // MMMaul Hard
	0x44, // MMMaul Easy
	0x45, // MMMaul Normal
	0x7C, // MMMaul Insane
	0x43, // SSnatch Normal
	0x4A, // SSnatch Easy
	0x4B, // SSnatch Hard
	0x7D, // SSnatch Insane
	0x90, // PPPanic V Easy
	0x91, // PPPanic Easy
	0x92, // PPPanic Normal
	0x93, // PPPanic Hard
	0x65, // KrazyKK Easy
	0x8D, // KrazyKK Normal
	0x8E, // KrazyKK Hard
	0x8F, // KrazyKK Insane
	0x20, // BBBandit V Easy
	0x79, // BBBandit Easy
	0x7A, // BBBandit Normal
	0x7B, // BBBandit Hard
	0x66, // BBBash V Easy
	0x94, // BBBash Easy
	0x95, // BBBash Normal
	0x96, // BBBash Hard
	0x0A, // KKosh V Easy
	0x73, // KKosh Easy
	0x74, // KKosh Normal
	0x75, // KKosh Hard
	0x67, // SSeek V Easy
	0x8A, // SSeek Easy
	0x8B, // SSeek Normal
	0x8C, // SSeek Hard
	0xB1, // Dive Barrel
	0xB4, // Orange Barrel
	0xB5, // Barrel Barrel
	0xB6, // Vine Barrel
	0x4D, // MMayhem Easy
	0x81, // MMayhem Normal
	0x82, // MMayhem Hard
	0x12, // TTTrouble V Easy
	0x76, // TTTrouble Easy
	0x77, // TTTrouble Normal
	0x78, // TTTrouble Hard
};

void changeTimer_button(void) {
	for (int i = 0; i < sizeof(minigame_list); i++) {
		if (CurrentMap == minigame_list[i]) {
			for (int j = 0; j < LoadedActorCount; j++) {
				if (LoadedActorArray[j].actor->actorType == 176) { // Timer Object
					timerActor* _timer = (timerActor*)LoadedActorArray[j].actor;
					if (MinigameTimersInMS) {
						_timer->type = 0xB;
					} else {
						_timer->type = 6;
					}
				}
			}
		}
	}
}

void changeTimer_spawnTimer(void) {
	if (ConvertTimerCountdown > 1) {
		ConvertTimerCountdown -= 1;
	} else {
		if ((ConvertTimerCountdown == 1) && (CutsceneActive == 0)) {
			ConvertTimerCountdown -= 1;
			changeTimer_button();
		}
	}
	// for (int i = 0; i < sizeof(minigame_list); i++) {
	// 	if (CurrentMap == minigame_list[i]) {
	// 		timerActor* _timer = (timerActor*)CurrentActorPointer;
	// 		if (MinigameTimersInMS) {
	// 			_timer->type = 0xB;
	// 			_timer->test = (_timer->test - 1) & 0xFF;
	// 		} else {
	// 			_timer->type = 6;
	// 		}
	// 		TestVariable = (int)CurrentActorPointer;
	// 	}
	// }
}