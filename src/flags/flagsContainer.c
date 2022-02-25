#include "../../include/common.h"

void openFlagsMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FLAG_ROOT);
}

void openFlagSubmenu(int screenIndex) {
	short _flag_index;
	char _flag_type;
	int _flag_state;
	int* _flag_text_struct;
	int* _flag_text;
	for (int i = 0; i < flagMenuScreenCount; i++) {
		if (flag_menus[i]->screenIndex == screenIndex) {
			for (int j = 0; j < flag_menus[i]->flagCount; j++) {
				_flag_index = flag_menus[i]->flagArray[j];
				_flag_type = flag_menus[i]->flagTypeArray[j];
				_flag_state = checkFlag(_flag_index,_flag_type);
				_flag_text_struct = (int *)flag_menus[i]->flagText[j];
				_flag_text = (int *)_flag_text_struct[_flag_state];
				menu_screens[screenIndex]->TextArray[j] = (int)(int *)_flag_text;
			}
		}
	}
	changeMenu(screenIndex);
};

void toggleFlag(void) {
	short _flag_index;
	char _flag_type;
	int _flag_state;
	for (int i = 0; i < flagMenuScreenCount; i++) {
		if (flag_menus[i]->screenIndex == ActiveMenu.screenIndex) {
			_flag_index = flag_menus[i]->flagArray[(int)ActiveMenu.positionIndex];
			_flag_type = flag_menus[i]->flagTypeArray[(int)ActiveMenu.positionIndex];
			_flag_state = checkFlag(_flag_index,_flag_type);
			_flag_state = 1 ^ _flag_state;
			setFlag(_flag_index,_flag_state,_flag_type);
		}
	}
	openFlagSubmenu(ActiveMenu.screenIndex);
}

static const char* flagmain_array[] = {
	"KONGS FREED",
	"KEYS TURNED IN",
	"KEYS IN POSSESSION",
	"LEVEL INTROS",
	"LEVEL TROFF AND SCOFF",
	"LEVEL BOSS INTROS",
	"CUTSCENES",
	"LEVEL MODIFIERS",
	"FIRST TIME TEXTS",
	"BANANAPORTS",
	"MISCELLANEOUS",
	"CUSTOM",
};

const Screen flagmain_struct = {
	.TextArray = (int*)flagmain_array,
	.FunctionArray = flagmain_functions,
	.ArrayItems = 12,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 1
};