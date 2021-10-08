#include "../../include/common.h"

static char arcade_map[10] = "MAP SELECT";
static char arcade_map0[] = "25M";
static char arcade_map1[] = "50M";
static char arcade_map2[] = "75M";
static char arcade_map3[] = "100M";
static char arcade_diff[20] = "LEVEL SELECT";
static char arcade_levitate[] = "LEVITATE JUMPMAN";
static char arcade_restocklives[] = "RESTOCK LIVES";
static char arcade_savestate[] = "SAVE STATE";
static char arcade_loadstate[] = "LOAD STATE";
static char arcade_lvl0[] = "LEVEL 1";
static char arcade_lvl1[] = "LEVEL 2";
static char arcade_lvl2[] = "LEVEL 3";
static char arcade_lvl3[] = "LEVEL 4";
static char arcade_lvl4[] = "LEVEL 5";
static char arcade_lvl5[] = "LEVEL 6";
static char arcade_lvl6[] = "LEVEL 7";
static char arcade_lvl7[] = "LEVEL 8";
static char arcade_lvl8[] = "LEVEL 9";

static arcadeObjectBase arcadeObjectsState = {};
static arcadeMoveFloorBase arcadeFloorState = {};
static arcadeObject jumpmanObj = {};
static arcadeSavestate arcadeState = {};
static char waiting_for_reload = 0;
static int start_level_timer = 0;
static int start_global_timer = 0;
static int start_bonus_timer = 0;
static int start_rng = 0;

void toggleArcadeMenu(void) {
	if (ControllerInput.Buttons & R_Button) {
		if (NewlyPressedControllerInput.Buttons & L_Button) {
			if (arcadeMenu.isOpen) {
				arcadeMenu.isOpen = 0;
			} else {
				arcadeMenu.screenIndex = 0;
				arcadeMenu.positionIndex = 0;
				start_level_timer = arcadeLevelTimer;
				start_global_timer = arcadeGlobalTimer;
				start_bonus_timer = arcadeBonusTimer;
				start_rng = arcadeRNG;
				arcadeMenu.isOpen = 1;
			}
		}
	}
}

void warpToArcadeMap(void) {
	arcadeMap = (arcadeMap & 0xFC) + arcadeMenu.positionIndex;
	wipeMemory(&arcadeObjBase,0xA00);
	waiting_for_reload = 0;
	arcadeMode = 2;
	arcadeLevelTimer = 0xA1; // Instant Load
}

void setArcadeDifficulty(void) {
	arcadeLevel = arcadeMenu.positionIndex + 1;
	arcadeMap = (arcadeMap & 3) + (arcadeLevel << 2); 
	playSFX(ArcadeGrunt);
}

void changeArcadeScreen(int screenIndex) {
	arcadeMenu.screenIndex = screenIndex;
	arcadeMenu.positionIndex = 0;
}

void arcadeLevitate(void) {
	int jump_index = arcadeGetObjIndexOfType(13);
	if (jump_index > -1) {
		arcadeObjBase[jump_index].y -= 1;
	}
}

void arcadeRestock(void) {
	arcadeLives = 2;
	arcadeLivesVisual = 2;
}

void openArcadeMapScreen(void) {
	changeArcadeScreen(1);
}

void openArcadeLvlScreen(void) {
	changeArcadeScreen(2);
}

void saveArcadeState(void) {
	int dk100_index = arcadeGetObjIndexOfType(23);
	int end_cutscene = 0;
	if (dk100_index > -1) {
		if (arcadeObjBase[dk100_index].movement == 8) {
			end_cutscene = 1;
		}
	}
	if ((arcadeMode == 5) && (end_cutscene == 0)) {
		arcadeState.map = arcadeMap;
		arcadeState.level = arcadeLevel;
		arcadeState.mode = arcadeMode;
		arcadeState.RNG = start_rng;
		arcadeState.base = (arcadeObjectBase*)&arcadeObjectsState;
		arcadeState.floors = (arcadeMoveFloorBase*)&arcadeFloorState;
		arcadeState.level_timer = start_level_timer;
		arcadeState.global_timer = start_global_timer;
		arcadeState.current_score = arcadeCurrentScore;
		arcadeState.high_score = arcadeHighScore;
		arcadeState.bonus_timer = start_bonus_timer;
		arcadeState.lives = arcadeLives;
		arcadeState.song = arcadeSong;
		arcadeState.hammer_timer = arcadeHammerTimer;
		arcadeState.rivet_bitfield = arcadeRivetBitfield;
		arcadeState.stored = 1;
		dk_memcpy(&arcadeObjectsState,arcadeObjBase,0xA00);
		dk_memcpy(&arcadeFloorState,&arcadeMovableFloor,0x48);
		// for (int i = 0; i < 0x50; i++) {
		// 	arcadeObjectsState.object[i].image_data_pointer = 0;
		// }
		playSFX(ArcadeSpring);
	} else {
		playSFX(ArcadeFalling);
	}
}

void loadArcadeState(void) {
	if (arcadeState.stored) {
		arcadeMap = arcadeState.map;
		arcadeLevel = arcadeState.level;
		arcadeMap = (arcadeMap & 0xFC) + arcadeState.map;
		arcadeMode = 2;
		arcadeLevelTimer = 0xA1;
		arcadeLives = arcadeState.lives;
		arcadeLivesVisual = arcadeState.lives;
		arcadeCurrentScore = arcadeState.current_score;
		arcadeHighScore = arcadeState.high_score;
		waiting_for_reload = 1;
	} else {
		playSFX(ArcadeFalling);
	}
}

void finishLoadingArcadeState(void) {
	if ((waiting_for_reload) && (arcadeLevelTimer < 0xA0)) {
		if (arcadeLevelTimer == 0) {
			dk_memcpy(arcadeObjBase,&arcadeObjectsState,0xA00);
			dk_memcpy(&arcadeMovableFloor,&arcadeFloorState,0x48);
			arcadeObjBase[(int)arcadeJumpmanIndex].movement = 0;
			arcadeLevelTimer = 0x38;
		}
		if (arcadeObjBase[(int)arcadeJumpmanIndex].movement != 0) {
			if (arcadeState.level_timer > 0x3C) {
				arcadeLevelTimer = arcadeState.level_timer;
			} else {
				dk_memcpy(&jumpmanObj,&arcadeObjBase[(int)arcadeJumpmanIndex],0x20);
			}
			arcadeGlobalTimer = arcadeState.global_timer;
			arcadeBonusTimer = arcadeState.bonus_timer;
			arcadeRNG = arcadeState.RNG;
			arcadeMode = arcadeState.mode;
			arcadeHammerTimer = arcadeState.hammer_timer;
			arcadeRivetBitfield = arcadeState.rivet_bitfield;
			setArcadeSong(arcadeState.song);
			dk_memcpy(arcadeObjBase,&arcadeObjectsState,0xA00);
			dk_memcpy(&arcadeMovableFloor,&arcadeFloorState,0x48);
			if (arcadeState.level_timer < 0x3D) {
				dk_memcpy(&arcadeObjBase[(int)arcadeJumpmanIndex],&jumpmanObj,0x20);
			}
			waiting_for_reload = 0;
		}
	}
}

static char* arcade_array[] = {
	arcade_map,
	arcade_diff,
	arcade_levitate,
	arcade_restocklives,
	arcade_savestate,
	arcade_loadstate
};

static const int arcade_functions[] = {
	(int)&openArcadeMapScreen,
	(int)&openArcadeLvlScreen,
	(int)&arcadeLevitate,
	(int)&arcadeRestock,
	(int)&saveArcadeState,
	(int)&loadArcadeState,
};

static const Screen arcade_struct = {
	.TextArray = (int*)arcade_array,
	.FunctionArray = arcade_functions,
	.ArrayItems = 6,
	.ParentScreen = 0,
	.ParentPosition = 0
};

static char* arcademap_array[] = {
	arcade_map0,
	arcade_map1,
	arcade_map2,
	arcade_map3
};

static const int arcademap_functions[] = {
	(int)&warpToArcadeMap,
	(int)&warpToArcadeMap,
	(int)&warpToArcadeMap,
	(int)&warpToArcadeMap
};

static const Screen arcademap_struct = {
	.TextArray = (int*)arcademap_array,
	.FunctionArray = arcademap_functions,
	.ArrayItems = 4,
	.ParentScreen = 0,
	.ParentPosition = 0
};

static char* arcadelvl_array[] = {
	arcade_lvl0,
	arcade_lvl1,
	arcade_lvl2,
	arcade_lvl3,
	arcade_lvl4,
	arcade_lvl5,
	arcade_lvl6,
	arcade_lvl7,
	arcade_lvl8
};

static const int arcadelvl_functions[] = {
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty,
	(int)&setArcadeDifficulty
};

static const Screen arcadelvl_struct = {
	.TextArray = (int*)arcadelvl_array,
	.FunctionArray = arcadelvl_functions,
	.ArrayItems = 9,
	.ParentScreen = 0,
	.ParentPosition = 1
};

const Screen* arcade_screens[] = {
	&arcade_struct,
	&arcademap_struct,
	&arcadelvl_struct
};

void spawnArcadeMenu(void* write_location) {
	int y = 0x28;
	const Screen* focused_screen = arcade_screens[(int)arcadeMenu.screenIndex];
	int* focused_text_array = (int*)focused_screen->TextArray;
	int array_count = focused_screen->ArrayItems;
	if (arcadeMenu.positionIndex > array_count) {
		arcadeMenu.positionIndex = array_count;
	}
	int _position = arcadeMenu.positionIndex;
	if (arcadeMenu.isOpen) {
		for (int i = 0; i < array_count; i++) {
			if (_position == i) {
				setArcadeTextColor(0xFF,0xD7,0x00,0xFF);
			} else {
				setArcadeTextColor(0xFF,0xFF,0xFF,0xFF);
			}
			setArcadeTextXY(0x38,y);
			spawnArcadeText(write_location,(char*)focused_text_array[i]);
			y += 0xC;
		}
		if (arcadeMenu.positionIndex == array_count) {
			setArcadeTextColor(0xFF,0x45,0x00,0xFF);
		} else {
			setArcadeTextColor(0xFF,0xFF,0xFF,0xFF);
		}
		setArcadeTextXY(0x38,y);
		spawnArcadeText(write_location,"RETURN");
	}
}

void closeArcadeMenu(void) {
	const Screen* focused_screen = arcade_screens[(int)arcadeMenu.screenIndex];
	if (arcadeMenu.screenIndex == 0) {
		arcadeMenu.isOpen = 0;
	} else {
		arcadeMenu.screenIndex = focused_screen->ParentScreen;
		arcadeMenu.positionIndex = focused_screen->ParentPosition;
	}
}

void returnArcade(void) {
	const Screen* focused_screen = arcade_screens[(int)arcadeMenu.screenIndex];
	int* focused_function_array = (int *)focused_screen->FunctionArray;
	int cap = focused_screen->ArrayItems;
	if (arcadeMenu.positionIndex == cap) {
		closeArcadeMenu();
	} else {
		int _code = focused_function_array[(int)arcadeMenu.positionIndex];
		if (_code) {
			callFunc((int *)_code);
		}
	}
}


void controlArcadeMenuActions(void) {
	const Screen* focused_screen = arcade_screens[(int)arcadeMenu.screenIndex];
	int cap = focused_screen->ArrayItems;
	int _position = arcadeMenu.positionIndex;
	if  (arcadeMenu.isOpen) {
		if ((_position > 0) && (NewlyPressedControllerInput.Buttons & D_Up)) {
			arcadeMenu.positionIndex -= 1;
		} else if ((_position == 0) && (NewlyPressedControllerInput.Buttons & D_Up)) {
			arcadeMenu.positionIndex = cap;
		} else if ((_position < cap) && (NewlyPressedControllerInput.Buttons & D_Down)) {
			arcadeMenu.positionIndex += 1;
		} else if ((_position == cap) && (NewlyPressedControllerInput.Buttons & D_Down)) {
			arcadeMenu.positionIndex = 0;
		} else if (((ControllerInput.Buttons & L_Button) || ((ControllerInput.Buttons & D_Right) && (MenuShortcutButtonsOff == 0))) && (arcadeMenu.positionIndex == 2) && (arcadeMenu.screenIndex == 0) && ((ControllerInput.Buttons & R_Button) == 0)) {
			returnArcade();
		} else if (((NewlyPressedControllerInput.Buttons & L_Button) || ((NewlyPressedControllerInput.Buttons & D_Right) && (MenuShortcutButtonsOff == 0))) && ((ControllerInput.Buttons & R_Button) == 0)) {
			returnArcade();
		} else if ((NewlyPressedControllerInput.Buttons & D_Left) && ((ControllerInput.Buttons & R_Button) == 0) && (MenuShortcutButtonsOff == 0)) {
			closeArcadeMenu();
		}
	}
}