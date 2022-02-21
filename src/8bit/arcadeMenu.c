#include "../../include/common.h"

static arcadeObjectBase arcadeObjectsState = {};
static arcadeMoveFloorBase arcadeFloorState = {};
static arcadeObject jumpmanObj = {};
static arcadeSavestate arcadeState = {};
static char waiting_for_reload = 0;
static int start_level_timer = 0;
static int start_global_timer = 0;
static int start_bonus_timer = 0;
static int start_rng = 0;
static char maptimerenabled = 0;
static char maptimer_off[] = "{ MAP TIMER";
static char maptimer_on[] = "} MAP TIMER";
static unsigned int maptimervalue = 0;

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
		arcadeObjBase[jump_index].jump_init_y = arcadeObjBase[jump_index].y;
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
	"MAP SELECT",
	"LEVEL SELECT",
	"LEVITATE JUMPMAN",
	"RESTOCK LIVES",
	maptimer_off,
	"SAVE STATE",
	"LOAD STATE"
};

void openBaseArcadeMenu(void) {
	if (maptimerenabled) {
		arcade_array[4] = maptimer_on;
	} else {
		arcade_array[4] = maptimer_off;
	}
	changeArcadeScreen(0);
}

void controlArcadeTimer(void) {
	if (maptimerenabled) {
		if (arcadeMode == 2) {
			maptimervalue = 0;
		} else if (arcadeMode == 5) {
			int pause_value = 3;
			if ((arcadeMap & 3) == 3) {
				pause_value = 2;
			}
			if (arcadeLevelTimer > 0x3C) {
				if (arcadePause != pause_value) {
					maptimervalue = arcadeLevelTimer - 0x3C;
				} else {
					if ((arcadeMap & 3) == 1) { // 50m
						for (int i = 0; i < 0x50; i++) {
							if (arcadeObjBase[i].type == 25) {
								maptimervalue = arcadeLevelTimer - 0x3C;
							}
						}
					}
				}
			}

		}
	}
}

void toggleArcadeTimer(void) {
	int old_position = arcadeMenu.positionIndex;
	maptimerenabled = 1 ^ maptimerenabled;
	openBaseArcadeMenu();
	arcadeMenu.positionIndex = old_position;
}


static const int arcade_functions[] = {
	(int)&openArcadeMapScreen,
	(int)&openArcadeLvlScreen,
	(int)&arcadeLevitate,
	(int)&arcadeRestock,
	(int)&toggleArcadeTimer,
	(int)&saveArcadeState,
	(int)&loadArcadeState,
};

static const Screen arcade_struct = {
	.TextArray = (int*)arcade_array,
	.FunctionArray = arcade_functions,
	.ArrayItems = 7,
	.ParentScreen = 0,
	.ParentPosition = 0
};

static char* arcademap_array[] = {
	"25M",
	"50M",
	"75M",
	"100M"
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
	"LEVEL 1",
	"LEVEL 2",
	"LEVEL 3",
	"LEVEL 4",
	"LEVEL 5",
	"LEVEL 6",
	"LEVEL 7",
	"LEVEL 8",
	"LEVEL 9"
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

static char arcade_timer_secs[10] = "";
static char arcade_timer_text[20] = "";

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
	} else if (maptimerenabled) {
		int x = 0x38;
		int y = 224;
		controlArcadeTimer();
		setArcadeTextXY(x-1,y+1);
		setArcadeTextColor(0,0,0,0xFF);
		float arcade_timer_seconds = (maptimervalue % 3600);
		int arcade_timer_mins = maptimervalue / 3600;
		arcade_timer_seconds /= 60;
		if (arcade_timer_seconds < 10) {
			dk_strFormat((char*)arcade_timer_secs,"0%f",arcade_timer_seconds);
		} else {
			dk_strFormat((char*)arcade_timer_secs,"%f",arcade_timer_seconds);
		}
		arcade_timer_secs[5] = 0;
		dk_strFormat((char *)arcade_timer_text,"TIMER: %d:%s",arcade_timer_mins,arcade_timer_secs);
		spawnArcadeText(write_location,arcade_timer_text);
		setArcadeTextXY(x,y);
		setArcadeTextColor(0xFF,0xFF,0xFF,0xFF);
		spawnArcadeText(write_location,arcade_timer_text);
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