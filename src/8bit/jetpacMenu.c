#include "../../include/common.h"

#define JETPAC_TIMER_DISABLED 0
#define JETPAC_TIMER_PREPARING 1
#define JETPAC_TIMER_RUNNING 2
#define JETPAC_TIMER_FINISH 3

static ActiveMenuData jetpacMenu;
static int start_rng = 0;
static char level_load = 0;
static char rarewaretimerenabled = 0;
static char rarewaretimer_off[] = "{ 5000 POINT TIMER";
static char rarewaretimer_on[] = "} 5000 POINT TIMER";
static unsigned int rareware_timer = 0;

static const int jetman_colors[] = {
	0xFFFFFF, // White
	0xFF0000, // Red
	0x00FF7F, // Green
	0x6495ED, // Blue
	0xFFA500, // Yellow
	0x8B008B, // Purple
	0x008B8B, // Cyan
};

void toggleJetpacMenu(void) {
	if (ControllerInput.Buttons & R_Button) {
		if (NewlyPressedControllerInput.Buttons & L_Button) {
			if (jetpacMenu.isOpen) {
				jetpacMenu.isOpen = 0;
			} else {
				jetpacMenu.screenIndex = 0;
				jetpacMenu.positionIndex = 0;
				// start_level_timer = jetpacLevelTimer;
				// start_global_timer = jetpacGlobalTimer;
				// start_bonus_timer = jetpacBonusTimer;
				start_rng = RNG;
				jetpacMenu.isOpen = 1;
			}
		}
	}
}

void changeJetpacScreen(int screenIndex) {
	jetpacMenu.screenIndex = screenIndex;
	jetpacMenu.positionIndex = 0;
}

void openJetpacLevelMenu(void) {
	changeJetpacScreen(1);
}

void restockJetpacLives(void) {
	for (int i = 0; i < 2; i++) {
		competitors[i].lives = 3;
	}
}

void setJetpacLevel(void) {
	int jetpac_level = jetpacMenu.positionIndex;
	placeJetpacFloor();
	resetJetpacVars();
	for (int i = 0; i < 2; i++) {
		competitors[i].level = jetpac_level - 1;
	}
	int old_level = competitors[jetpacPlayerIndex].level;
	competitor_struct* focused_competitor = (competitor_struct*)&competitors[jetpacPlayerIndex];
	if (old_level < 0) {
		competitors[jetpacPlayerIndex].lives -= 1;
	}
	competitors[jetpacPlayerIndex].level += 1;
	spawnJetpacItem(focused_competitor);
	resetJetpacMap(focused_competitor);
	focused_competitor->unk_010 = 1;
	focused_competitor->unk_114 = 0;
	changeJetpacMode(2);
}

void resetJetpacScore(void) {
	startJetpacGame();
	jetpacTimerState = JETPAC_TIMER_DISABLED;
	rareware_timer = 0;
}

static char* jetpac_array[] = {
	"LEVEL SELECT",
	"RESTOCK LIVES",
	"RESET JETPAC",
	rarewaretimer_off,
};

void openBaseJetpacMenu(void) {
	if (rarewaretimerenabled) {
		jetpac_array[3] = rarewaretimer_on;
	} else {
		jetpac_array[3] = rarewaretimer_off;
	}
	changeJetpacScreen(0);
}

void toggleRWTimer(void) {
	int old_position = jetpacMenu.positionIndex;
	rarewaretimerenabled = 1 ^ rarewaretimerenabled;
	openBaseJetpacMenu();
	jetpacMenu.positionIndex = old_position;
}

static const int jetpac_functions[] = {
	(int)&openJetpacLevelMenu,
	(int)&restockJetpacLives,
	(int)&resetJetpacScore,
	(int)&toggleRWTimer,
};

static const Screen jetpac_struct = {
	.TextArray = (int*)jetpac_array,
	.FunctionArray = jetpac_functions,
	.ArrayItems = 4,
	.ParentScreen = 0,
	.ParentPosition = 0
};

static char* jetpac_level_array[] = {
	"LEVEL 1",
	"LEVEL 2",
	"LEVEL 3",
	"LEVEL 4",
	"LEVEL 5",
	"LEVEL 6",
	"LEVEL 7",
	"LEVEL 8",
};

static const int jetpac_level_functions[] = {
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
	(int)&setJetpacLevel,
};

static const Screen jetpac_level_struct = {
	.TextArray = (int*)jetpac_level_array,
	.FunctionArray = jetpac_level_functions,
	.ArrayItems = 8,
	.ParentScreen = 0,
	.ParentPosition = 0
};

const Screen* jetpac_screens[] = {
	&jetpac_struct,
	&jetpac_level_struct,
};

void controlJetpacTimer(void) {
	if (rarewaretimerenabled) {
		if ((jetpacTimerState > JETPAC_TIMER_FINISH) || (jetpacTimerState < JETPAC_TIMER_DISABLED)) {
			jetpacTimerState = JETPAC_TIMER_DISABLED;
		}
		switch(jetpacTimerState) {
			case JETPAC_TIMER_DISABLED:
				jetpacTimerState = JETPAC_TIMER_PREPARING;
				break;
			case JETPAC_TIMER_PREPARING:
				rareware_timer = 0;
				if ((jetpacLevelStartTimer == 179) && (jetpacMode == 2) && (competitors[0].lives_consumed == 0) && (competitors[0].score == 0)) {
					jetpacTimerState = JETPAC_TIMER_RUNNING;
				}
				break;
			case JETPAC_TIMER_RUNNING:
				if ((!jetpacPaused) && (jetpacMode != 3)) {
					rareware_timer += 1;
				}
				break;
			case JETPAC_TIMER_FINISH:
				if (jetpacMode == 0) {
					jetpacTimerState = JETPAC_TIMER_PREPARING;
					rareware_timer = 0;
				}
			break;
		}
		if (jetpacMode == 0) {
			jetpacTimerState = 0;
		}
	}
}

void updateJetmanColor(void) {
	int color_index = jetmanColorIndex;
	if (color_index > 0) {
		jetpacObjectBase[4].red = (jetman_colors[color_index] >> 16) & 0xFF;
		jetpacObjectBase[4].green = (jetman_colors[color_index] >> 8) & 0xFF;
		jetpacObjectBase[4].blue = jetman_colors[color_index] & 0xFF;
	}
}

#define JETPAC_TEXT_X 0x28
static char rareware_timer_text[20] = "";
static char rareware_timer_secs[10] = "";

void spawnJetpacMenu(void* dl) {
	int y = 0x30;
	const Screen* focused_screen = jetpac_screens[(int)jetpacMenu.screenIndex];
	int* focused_text_array = (int*)focused_screen->TextArray;
	int array_count = focused_screen->ArrayItems;
	if (jetpacMenu.positionIndex > array_count) {
		jetpacMenu.positionIndex = array_count;
	}
	int _position = jetpacMenu.positionIndex;
	// int red = 0;
	// int green = 0;
	// int blue = 0;
	jetpacPaused = 0;
	updateJetmanColor();
	if (jetpacMenu.isOpen) {
		jetpacPaused = 1;
		if (level_load) {
			jetpacLevelStartTimer = 179;
			level_load = 0;
		}
		for (int i = 0; i < array_count; i++) {
			if (_position == i) {
				setJetpacTextColor(0xFF,0xD7,0x00,0xFF);
				// red = 0xFF;
				// green = 0xD7;
				// blue = 0x00;
			} else {
				setJetpacTextColor(0xFF,0xFF,0xFF,0xFF);
				// red = 0xFF;
				// green = 0xFF;
				// blue = 0xFF;
			}
			// drawJetpacPixelFont(dl, (char*)focused_text_array[i], JETPAC_TEXT_X, y, red, green, blue, 0xFF);
			spawnJetpacText(dl,(char*)focused_text_array[i],JETPAC_TEXT_X,y,0);
			y += 0xC;
		}
		if (jetpacMenu.positionIndex == array_count) {
			// red = 0xFF;
			// green = 0x45;
			// blue = 0x00;
			setJetpacTextColor(0xFF,0x45,0x00,0xFF);
		} else {
			// red = 0xFF;
			// green = 0xFF;
			// blue = 0xFF;
			setJetpacTextColor(0xFF,0xFF,0xFF,0xFF);
		}
		// drawJetpacPixelFont(dl, "RETURN", JETPAC_TEXT_X, y, red, green, blue, 0xFF);
		spawnJetpacText(dl,"RETURN",JETPAC_TEXT_X,y,0);
	} else if (rarewaretimerenabled && (jetpacMode != 0)) {
		controlJetpacTimer();
		setJetpacTextColor(0xFF,0xFF,0xFF,0xFF);
		float rareware_timer_seconds = (rareware_timer % 3600);
		int rareware_timer_mins = rareware_timer / 3600;
		rareware_timer_seconds /= 60;
		if (rareware_timer_seconds < 10) {
			dk_strFormat((char*)rareware_timer_secs,"0%f",rareware_timer_seconds);
		} else {
			dk_strFormat((char*)rareware_timer_secs,"%f",rareware_timer_seconds);
		}
		rareware_timer_secs[5] = 0;
		dk_strFormat((char *)rareware_timer_text,"TIMER: %d:%s",rareware_timer_mins,rareware_timer_secs);
		spawnJetpacText(dl,rareware_timer_text,JETPAC_TEXT_X,200,0);
	}
}

void closeJetpacMenu(void) {
	const Screen* focused_screen = jetpac_screens[(int)jetpacMenu.screenIndex];
	if (jetpacMenu.screenIndex == 0) {
		jetpacMenu.isOpen = 0;
	} else {
		jetpacMenu.screenIndex = focused_screen->ParentScreen;
		jetpacMenu.positionIndex = focused_screen->ParentPosition;
	}
}

void returnJetpac(void) {
	const Screen* focused_screen = jetpac_screens[(int)jetpacMenu.screenIndex];
	int* focused_function_array = (int *)focused_screen->FunctionArray;
	int cap = focused_screen->ArrayItems;
	if (jetpacMenu.positionIndex == cap) {
		closeJetpacMenu();
	} else {
		int _code = focused_function_array[(int)jetpacMenu.positionIndex];
		if (_code) {
			callFunc((int *)_code);
		}
	}
}


void controlJetpacMenuActions(void) {
	const Screen* focused_screen = jetpac_screens[(int)jetpacMenu.screenIndex];
	int cap = focused_screen->ArrayItems;
	int _position = jetpacMenu.positionIndex;
	if  (jetpacMenu.isOpen) {
		if ((_position > 0) && (NewlyPressedControllerInput.Buttons & D_Up)) {
			jetpacMenu.positionIndex -= 1;
		} else if ((_position == 0) && (NewlyPressedControllerInput.Buttons & D_Up)) {
			jetpacMenu.positionIndex = cap;
		} else if ((_position < cap) && (NewlyPressedControllerInput.Buttons & D_Down)) {
			jetpacMenu.positionIndex += 1;
		} else if ((_position == cap) && (NewlyPressedControllerInput.Buttons & D_Down)) {
			jetpacMenu.positionIndex = 0;
		} else if (((ControllerInput.Buttons & L_Button) || ((ControllerInput.Buttons & D_Right) && (MenuShortcutButtonsOff == 0))) && (jetpacMenu.positionIndex == 2) && (jetpacMenu.screenIndex == 0) && ((ControllerInput.Buttons & R_Button) == 0)) {
			returnJetpac();
		} else if (((NewlyPressedControllerInput.Buttons & L_Button) || ((NewlyPressedControllerInput.Buttons & D_Right) && (MenuShortcutButtonsOff == 0))) && ((ControllerInput.Buttons & R_Button) == 0)) {
			returnJetpac();
		} else if ((NewlyPressedControllerInput.Buttons & D_Left) && ((ControllerInput.Buttons & R_Button) == 0) && (MenuShortcutButtonsOff == 0)) {
			closeJetpacMenu();
		}
	}
}