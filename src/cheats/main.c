#include "../include/common.h"

static const char cheats_instantskew[] = "ACQUIRE REGULAR SKEW";
static const char cheats_instantskew_inverse[] = "ACQUIRE CANNON SKEW";
//static const char cheats_killboss[] = "KILL BOSS";

static const char* cheats_array[] = {
	"MOVESET AND INVENTORY",
	"CHANGE GAMEMODE",
	"CANCEL CUTSCENE",
	cheats_instantskew,
	"SPAWN SNAG CHEATS",
	"AUTO-TRICKS",
	"TOGGLES",
	"INFINITES",
	"UNDO LAST FLAG WRITE",
	"GAIN CONTROL",
	"FORCE END MINIGAME",
	"TRANSFORM",
	"HELM TIMER CONTROL",
};

void openCheatsMenu(void) {
	if (Player) {
		if (Player->skew_angle == 0xC00) {
			cheats_array[3] = cheats_instantskew_inverse;
		} else {
			cheats_array[3] = cheats_instantskew;
		}
	}
	changeMenu(ACTIVEMENU_SCREEN_CHEATS_ROOT);
}

void undoLastFlagWrite(void) {
	if (UndoFlag.flag_stored) {
		setFlag(UndoFlag.encoded_flag,1 ^ UndoFlag.output, UndoFlag.flag_type);
		playSFX(Splat);
	}
}

void openHelmControl(void) {
	changeMenu(ACTIVEMENU_SCREEN_CHEATS_HELMTIMER);
}

static const int cheats_functions[] = {
	(int)&openMovesetInventoryMenu,
	(int)&openGamemodeMenu,
	(int)&cancelCutscene,
	(int)&alterSkewAngle,
	(int)&openSnagMenu,
	(int)&openTrickToggleMenu,
	(int)&openTogglesMenu,
	(int)&openInfinitesMenu,
	(int)&undoLastFlagWrite,
	(int)&gainControl,
	(int)&endMinigame,
	(int)&openTransformMenu,
	(int)&openHelmControl,
};

const Screen cheats_struct = {
	.TextArray = (int*)cheats_array,
	.FunctionArray = cheats_functions,
	.ArrayItems = 13,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 8
};