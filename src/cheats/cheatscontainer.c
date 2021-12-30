#include "../../include/common.h"

static const char cheats_instantskew[] = "ACQUIRE REGULAR SKEW";
static const char cheats_instantskew_inverse[] = "ACQUIRE CANNON SKEW";
//static const char cheats_killboss[] = "KILL BOSS";

static const char* cheats_array[] = {
	"MOVESET AND INVENTORY",
	"CHANGE GAMEMODE",
	"CANCEL CUTSCENE",
	cheats_instantskew,
	"SPAWN SNAG CHEATS",
	"TOGGLES",
	"UNDO LAST FLAG WRITE",
	"GAIN CONTROL",
	"FORCE END MINIGAME",
	"TRANSFORM",
};

void openCheatsMenu(void) {
	if (Player) {
		if (Player->skew_angle == 0xC00) {
			cheats_array[3] = cheats_instantskew_inverse;
		} else {
			cheats_array[3] = cheats_instantskew;
		}
	}
	changeMenu(55);
}

void undoLastFlagWrite(void) {
	if (UndoFlag.flag_stored) {
		setFlag(UndoFlag.encoded_flag,1 ^ UndoFlag.output, UndoFlag.flag_type);
		playSFX(Splat);
	}
}

static const int cheats_functions[] = {
	(int)&openMovesetInventoryMenu,
	(int)&openGamemodeMenu,
	(int)&cancelCutscene,
	(int)&alterSkewAngle,
	(int)&openSnagMenu,
	(int)&openTogglesMenu,
	(int)&undoLastFlagWrite,
	(int)&gainControl,
	(int)&endMinigame,
	(int)&openTransformMenu,
};

const Screen cheats_struct = {
	.TextArray = (int*)cheats_array,
	.FunctionArray = cheats_functions,
	.ArrayItems = 10,
	.ParentScreen = 0,
	.ParentPosition = 7
};