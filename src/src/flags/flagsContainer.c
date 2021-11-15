#include "../../include/common.h"

static const char flag_kongs[] = "Kongs Freed";
static const char flag_keysin[] = "Keys Turned In";
static const char flag_keyshave[] = "Keys in Possession";
static const char flag_levelIntros[] = "Level Intros";
static const char flag_levenTnS[] = "Level Troff & Scoff";
static const char flag_levelBoss[] = "Level Boss Intros";
static const char flag_cutscenes[] = "Cutscenes";
static const char flag_modifiers[] = "Level Modifiers";
static const char flag_misc[] = "Miscellaneous";
static const char flag_ftt[] = "First Time Texts";
static const char flag_custom[] = "Custom";

void openFlagsMainMenu(void) {
	changeMenu(43);
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
			_flag_state = 1 - _flag_state;
			setFlag(_flag_index,_flag_state,_flag_type);
		}
	}
	openFlagSubmenu(ActiveMenu.screenIndex);
}

static const char* flagmain_array[] = {
	flag_kongs,
	flag_keysin,
	flag_keyshave,
	flag_levelIntros,
	flag_levenTnS,
	flag_levelBoss,
	flag_cutscenes,
	flag_modifiers,
	flag_ftt,
	flag_misc,
	flag_custom,
};

const Screen flagmain_struct = {
	.TextArray = (int*)flagmain_array,
	.FunctionArray = flagmain_functions,
	.ArrayItems = 11,
	.ParentScreen = 0,
	.ParentPosition = 1
};