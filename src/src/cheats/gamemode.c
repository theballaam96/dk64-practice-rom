#include "../../include/common.h"

static const char gamemodes_00[] = "Nintendo Logo";
static const char gamemodes_01[] = "Opening Cutscene";
static const char gamemodes_02[] = "DK Rap";
static const char gamemodes_03[] = "DK TV";
static const char gamemodes_04[] = "Gamemode 4";
static const char gamemodes_05[] = "Main Menu";
static const char gamemodes_06[] = "Adventure & Kong Battle";
static const char gamemodes_07[] = "Loading Game Over";
static const char gamemodes_08[] = "Gamemode 8";
static const char gamemodes_09[] = "Game Over";
static const char gamemodes_10[] = "End Sequence (Adventure)";
static const char gamemodes_11[] = "DK Theatre";
static const char gamemodes_12[] = "DK Bonus & Bosses";
static const char gamemodes_13[] = "Snide's Bonus Minigames";
static const char gamemodes_14[] = "End Sequence (DK Theatre)";

static const char gamemodes_gameplay[] = "Gameplay Gamemodes";
static const char gamemodes_cutscenes[] = "Cutscene Gamemodes";
static const char gamemodes_unused[] = "Unused Gamemodes";

static const char gamemodes_gameplay_list[] = {5,6,12,13};
static const char gamemodes_cutscenes_list[] = {0,1,2,3,7,9,10,11,14};
static const char gamemodes_unused_list[] = {4,8};

void openGamemodeMenu(void) {
	changeMenu(56);
}

void openGamemodeGameplayMenu(void) {
	changeMenu(73);
}

void openGamemodeCutscenesMenu(void) {
	changeMenu(74);
}

void openGamemodeUnusedMenu(void) {
	changeMenu(75);
}

void changeGamemode(void) {
	char new_mode = 6;
	switch (ActiveMenu.screenIndex) {
		case 73:
			new_mode = gamemodes_gameplay_list[(int)ActiveMenu.positionIndex];
			break;
		case 74:
			new_mode = gamemodes_cutscenes_list[(int)ActiveMenu.positionIndex];
			break;
		case 75:
			new_mode = gamemodes_unused_list[(int)ActiveMenu.positionIndex];
		break;
	}
	Gamemode = new_mode;
	Mode = new_mode;
	playSFX(CameraPull);
}

static const char* gamemode_array[] = {
	gamemodes_gameplay,
	gamemodes_cutscenes,
	gamemodes_unused,
};

static const int gamemode_functions[] = {
	(int)&openGamemodeGameplayMenu,
	(int)&openGamemodeCutscenesMenu,
	(int)&openGamemodeUnusedMenu,
};

const Screen gamemode_struct = {
	.TextArray = (int*)gamemode_array,
	.FunctionArray = gamemode_functions,
	.ArrayItems = 3,
	.ParentScreen = 55,
	.ParentPosition = 1
};

static const char* gamemode_gameplay_array[] = {
	gamemodes_05,
	gamemodes_06,
	gamemodes_12,
	gamemodes_13,
};

static const int gamemode_gameplay_functions[] = {
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
};

const Screen gamemode_gameplay_struct = {
	.TextArray = (int*)gamemode_gameplay_array,
	.FunctionArray = gamemode_gameplay_functions,
	.ArrayItems = 4,
	.ParentScreen = 56,
	.ParentPosition = 0
};

static const char* gamemode_cutscenes_array[] = {
	gamemodes_00,
	gamemodes_01,
	gamemodes_02,
	gamemodes_03,
	gamemodes_07,
	gamemodes_09,
	gamemodes_10,
	gamemodes_11,
	gamemodes_14,
};

static const int gamemode_cutscenes_functions[] = {
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
};

const Screen gamemode_cutscenes_struct = {
	.TextArray = (int*)gamemode_cutscenes_array,
	.FunctionArray = gamemode_cutscenes_functions,
	.ArrayItems = 9,
	.ParentScreen = 56,
	.ParentPosition = 1
};

static const char* gamemode_unused_array[] = {
	gamemodes_04,
	gamemodes_08,
};

static const int gamemode_unused_functions[] = {
	(int)&changeGamemode,
	(int)&changeGamemode,
};

const Screen gamemode_unused_struct = {
	.TextArray = (int*)gamemode_unused_array,
	.FunctionArray = gamemode_unused_functions,
	.ArrayItems = 2,
	.ParentScreen = 56,
	.ParentPosition = 2
};