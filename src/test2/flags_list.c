#include "../include/common.h"

const flagMenuData* flag_menus[] = {
	&flagmenu_kongmenu,
	&flagmenu_keysinmenu,
	&flagmenu_keyshavemenu,
	&flagmenu_levelintrosmenu,
	&flagmenu_leveltnsmenu,
	&flagmenu_levelbossmenu,
	&flagmenu_cutscenemenu,
	&flagmenu_modifiermenu,
	&flagmenu_fttmenu,
	&flagmenu_miscmenu,
	&flagmenu_tbarrelmenu,
};

const int flagmain_functions[] = {
	(int)&openFlagsKongMenu,
	(int)&openFlagsKeysinMenu,
	(int)&openFlagsKeyshaveMenu,
	(int)&openFlagsLevelintrosMenu,
	(int)&openFlagsLeveltnsMenu,
	(int)&openFlagsLevelbossMenu,
	(int)&openFlagsCutsceneMenu,
	(int)&openFlagsModifierMenu,
	(int)&openFlagsFTTMenu,
	(int)&openBPortsMenu,
	(int)&openFlagsMiscMenu,
	(int)&openFlagsCustomMenu,
};