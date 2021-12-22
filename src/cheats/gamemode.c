#include "../../include/common.h"

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
	"GAMEPLAY GAMEMODES",
	"CUTSCENE GAMEMODES",
	"UNUSED GAMEMODES",
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
	"MAIN MENU",
	"ADVENTURE AND KONG BATTLE",
	"DK BONUS AND BOSSES",
	"SNIDE BONUS MINIGAMES",
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
	"NINTENDO LOGO",
	"OPENING CUTSCENE",
	"DK RAP",
	"DK TV",
	"LOADING GAME OVER",
	"GAME OVER",
	"END SEQUENCE <ADVENTURE>",
	"DK THEATRE",
	"END SEQUENCE <DK THEATRE>",
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
	"GAMEMODE 4",
	"GAMEMODE 8",
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