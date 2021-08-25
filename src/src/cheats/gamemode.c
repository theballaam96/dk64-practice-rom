#include "../../include/common.h"

static const char gamemodes_00[] = "NINTENDO LOGO";
static const char gamemodes_01[] = "OPENING CUTSCENE";
static const char gamemodes_02[] = "DK RAP";
static const char gamemodes_03[] = "DK TV";
static const char gamemodes_04[] = "GAMEMODE 4";
static const char gamemodes_05[] = "MAIN MENU";
static const char gamemodes_06[] = "ADVENTURE MODE AND KONG BATTLE";
static const char gamemodes_07[] = "LOADING GAME OVER";
static const char gamemodes_08[] = "GAMEMODE 8";
static const char gamemodes_09[] = "GAME OVER";
static const char gamemodes_10[] = "END SEQUENCE (ADVENTURE)";
static const char gamemodes_11[] = "DK THEATRE";
static const char gamemodes_12[] = "DK BONUS AND BOSSES";
static const char gamemodes_13[] = "SNIDE'S BONUS MINIGAMES";
static const char gamemodes_14[] = "END SEQUENCE (DK THEATRE)";

void openGamemodeMenu(void) {
	changeMenu(56);
}

void changeGamemode(void) {
	Gamemode = ActiveMenu.positionIndex;
	Mode = ActiveMenu.positionIndex;
	playSFX(CameraPull);
}

static const char* gamemode_array[] = {
	gamemodes_00,
	gamemodes_01,
	gamemodes_02,
	gamemodes_03,
	gamemodes_04,
	gamemodes_05,
	gamemodes_06,
	gamemodes_07,
	gamemodes_08,
	gamemodes_09,
	gamemodes_10,
	gamemodes_11,
	gamemodes_12,
	gamemodes_13,
	gamemodes_14,
};

static const int gamemode_functions[] = {
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
	(int)&changeGamemode,
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

const Screen gamemode_struct = {
	.TextArray = (int*)gamemode_array,
	.FunctionArray = gamemode_functions,
	.ArrayItems = 15,
	.ParentScreen = 55,
	.ParentPosition = 1
};