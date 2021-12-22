#include "../../include/common.h"

static const char cheats_instantskew[] = "ACQUIRE REGULAR SKEW";
static const char cheats_instantskew_inverse[] = "ACQUIRE CANNON SKEW";
//static const char cheats_killboss[] = "KILL BOSS";
	
static const short warp_flags[] = {
	0x20,0x21,0x23,0x22,0x25,0x24,0x28,0x29,0x26,0x27 // Japes
	,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x3E // Aztec Main
	,0x59,0x58,0x5B,0x5A // Aztec LLama
	,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x94,0x93,0x96,0x95 // Factory
	,0xB2,0xB1,0xAC,0xAB,0xAE,0xAD,0xAF,0xA3,0xA9,0xAA // Galleon
	,0xEE,0xED,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6 // Fungi
	,0x11C,0x11B,0x11D,0x11E,0x123,0x127,0x120,0x11F,0x121,0x122 // Caves
	,0x147,0x148,0x149,0x14A,0x14B,0x14C,0x14D,0x14E,0x14F,0x150 // Castle Main
	,0x151,0x152,0x153,0x154,0x155,0x156 // Castle Crypt
	,0x305,0x306 // Helm
	,0x1B1,0x1B2,0x1B3,0x1B4,0x1B5,0x1B6,0x1B7,0x1B8,0x1BA,0x1B9 // Isles Main
	,0x1A1,0x1A2 // Isles Helm Lobby
};

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
	"TAG ALL WARPS",
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

void tagAllWarps(void) {
	for (int i = 0; i < 94; i++) {
		setFlag(warp_flags[i],1,0);
	}
	playSFX(TakeWarp);
};

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
	(int)&tagAllWarps,
	(int)&openTransformMenu,
};

const Screen cheats_struct = {
	.TextArray = (int*)cheats_array,
	.FunctionArray = cheats_functions,
	.ArrayItems = 11,
	.ParentScreen = 0,
	.ParentPosition = 7
};