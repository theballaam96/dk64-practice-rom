#include "../../include/common.h"

static const char cheats_altermoveset[] = "ALTER MOVESET";
static const char cheats_coins[] = "GIVE COINS";
static const char cheats_restockinventory[] = "RESTOCK INVENTORY";
static const char cheats_changegamemode[] = "CHANGE GAMEMODE";
static const char cheats_cancelcs[] = "CANCEL CUTSCENE";
static const char cheats_instantskew[] = "INSTANT SKEW: SKEW";
static const char cheats_instantskew_inverse[] = "INSTANT SKEW: INVERSE SKEW";
static const char cheats_snagcheats[] = "SPAWN SNAG CHEATS";
static const char cheats_toggles[] = "TOGGLES";
static const char cheats_undoflag[] = "UNDO FLAG WRITE";
static const char cheats_gaincontrol[] = "GAIN CONTROL";
static const char cheats_endminigame[] = "FORCE END MINIGAME";
static const char cheats_tagallwarps[] = "TAG ALL WARPS";
static const char cheats_corrupt[] = "CORRUPT";
static const char cheats_turnoffall[] = "TURN OFF ALL CHEATS";

static const char* cheats_array[] = {
	cheats_altermoveset,
	cheats_coins,
	cheats_restockinventory,
	cheats_changegamemode,
	cheats_cancelcs,
	cheats_instantskew,
	cheats_snagcheats,
	cheats_toggles,
	cheats_undoflag,
	cheats_gaincontrol,
	cheats_endminigame,
	cheats_tagallwarps,
	cheats_corrupt,
	cheats_turnoffall,
};

void openCheatsMenu(void) {
	if (Player) {
		if (Player->skew_angle == 0xC00) {
			cheats_array[5] = cheats_instantskew_inverse;
		} else {
			cheats_array[5] = cheats_instantskew;
		}
	}
	changeMenu(55);
}

static const int cheats_functions[] = {
	0,
	0,
	0,
	(int)&openGamemodeMenu,
	(int)&cancelCutscene,
	(int)&alterSkewAngle,
	0,
	0,
	0,
	(int)&gainControl,
	0,
	0,
	(int)&corruptGame,
	0,
};

const Screen cheats_struct = {
	.TextArray = (int*)cheats_array,
	.FunctionArray = cheats_functions,
	.ArrayItems = 14,
	.ParentScreen = 0,
	.ParentPosition = 7
};