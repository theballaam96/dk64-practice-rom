#include "../include/common.h"

static const char maps_spawner[] = {
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
	0 // Null terminator
};

static const char maps_pppanic[] = {
	0x90, // PPPanic V Easy
	0x91, // PPPanic Easy
	0x92, // PPPanic Normal
	0x93, // PPPanic Hard
	0 // Null terminator
};

static const char maps_krazykk[] = {
	0x65, // KrazyKK Easy
	0x8D, // KrazyKK Normal
	0x8E, // KrazyKK Hard
	0x8F, // KrazyKK Insane
	0
};

static const char maps_bbbandit[] = {
	0x20, // BBBandit V Easy
	0x79, // BBBandit Easy
	0x7A, // BBBandit Normal
	0x7B, // BBBandit Hard
	0
};

static const char maps_bbbash[] = {
	0x66, // BBBash V Easy
	0x94, // BBBash Easy
	0x95, // BBBash Normal
	0x96, // BBBash Hard
	0
};

static const char maps_kkosh[] = {
	0x0A, // KKosh V Easy
	0x73, // KKosh Easy
	0x74, // KKosh Normal
	0x75, // KKosh Hard
	0
};

static const char maps_sseek[] = {
	0x67, // SSeek V Easy
	0x8A, // SSeek Easy
	0x8B, // SSeek Normal
	0x8C, // SSeek Hard
	0
};

static const char maps_tbarrels[] = {
	0xB1, // Dive Barrel
	0xB4, // Orange Barrel
	0xB5, // Barrel Barrel
	0xB6, // Vine Barrel
	0
};

static const char maps_timer[] = {
	0x4D, // MMayhem Easy
	0x81, // MMayhem Normal
	0x82, // MMayhem Hard
	0x12, // TTTrouble V Easy
	0x76, // TTTrouble Easy
	0x77, // TTTrouble Normal
	0x78, // TTTrouble Hard
	0
};

void endMinigame(void) {
	// Needs finishing
};

void LToEndMinigame(void) {
	if (LToEndGameOn) {
		if (ActiveMenu.isOpen == 0) {
			if (ClosingMenu == 0) {
				if (NewlyPressedControllerInput.Buttons & L_Button) {
					endMinigame();
				}
			}
		}
	}
};

void ToggleEndMinigameWithL(void) {
	// Needs finishing
};