#include "../../include/common.h"

static char jetpac_level[] = "LEVEL SELECT";
static char jetpac_lvl0[] = "LEVEL 1";
static char jetpac_lvl1[] = "LEVEL 2";
static char jetpac_lvl2[] = "LEVEL 3";
static char jetpac_lvl3[] = "LEVEL 4";
static char jetpac_lvl4[] = "LEVEL 5";
static char jetpac_lvl5[] = "LEVEL 6";
static char jetpac_lvl6[] = "LEVEL 7";
static char jetpac_lvl7[] = "LEVEL 8";

static ActiveMenuData jetpacMenu;

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
				// start_rng = jetpacRNG;
				jetpacMenu.isOpen = 1;
			}
		}
	}
}

void changeJetpacScreen(int screenIndex) {
	jetpacMenu.screenIndex = screenIndex;
	jetpacMenu.positionIndex = 0;
}

static char* jetpac_array[] = {
	jetpac_level,
};

static const int jetpac_functions[] = {
	0,
};

static const Screen jetpac_struct = {
	.TextArray = (int*)jetpac_array,
	.FunctionArray = jetpac_functions,
	.ArrayItems = 1,
	.ParentScreen = 0,
	.ParentPosition = 0
};

const Screen* jetpac_screens[] = {
	&jetpac_struct,
};

void spawnJetpacMenu(void* dl) {
	int y = 0x28;
	const Screen* focused_screen = jetpac_screens[(int)jetpacMenu.screenIndex];
	int* focused_text_array = (int*)focused_screen->TextArray;
	int array_count = focused_screen->ArrayItems;
	if (jetpacMenu.positionIndex > array_count) {
		jetpacMenu.positionIndex = array_count;
	}
	int _position = jetpacMenu.positionIndex;
	if (jetpacMenu.isOpen) {
		for (int i = 0; i < array_count; i++) {
			if (_position == i) {
				setJetpacTextColor(0xFF,0xD7,0x00,0xFF);
			} else {
				setJetpacTextColor(0xFF,0xFF,0xFF,0xFF);
			}
			spawnJetpacText(dl,(char*)focused_text_array[i],0x38,y,0);
			y += 0xC;
		}
		if (jetpacMenu.positionIndex == array_count) {
			setJetpacTextColor(0xFF,0x45,0x00,0xFF);
		} else {
			setJetpacTextColor(0xFF,0xFF,0xFF,0xFF);
		}
		spawnJetpacText(dl,"RETURN",0x38,y,0);
	}
}