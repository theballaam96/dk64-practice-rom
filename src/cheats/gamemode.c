#include "../../include/common.h"

void openGamemodeMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_CHEATS_GAMEMODE_ROOT);
}

void changeGamemode(void) {
	int new_mode = ActiveMenu.positionIndex;
	Gamemode = new_mode;
	Mode = new_mode;
	playSFX(CameraPull);
}

static const char* gamemode_array[] = {
	"NINTENDO LOGO",
	"OPENING CUTSCENE",
	"DK RAP",
	"DK TV",
	"GAMEMODE 4",
	"MAIN MENU",
	"ADVENTURE # KONG BATTLE",
	"LOADING GAME OVER",
	"GAMEMODE 8",
	"GAME OVER",
	"END SEQUENCE <ADVENTURE>",
	"DK THEATRE",
	"DK BONUS # BOSSES",
	"SNIDE^S BONUS GAMES",
	"END SEQUENCE <DK THEATRE>"
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
	.ParentScreen = ACTIVEMENU_SCREEN_CHEATS_ROOT,
	.ParentPosition = 1
};