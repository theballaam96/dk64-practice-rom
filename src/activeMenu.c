#include "../include/common.h"

static const char* main_array[] = {
	"WARP TO MAP",
	"FLAGS",
	"SAVE STATES",
	"WATCHES",
	"DEBUG",
	"TIMER SETTINGS",
	"FILE STATES",
	"CHEATS",
	"SETTINGS"
};

static const int main_functions[9];

static const Screen main_struct = {
	.TextArray = (int*)main_array,
	.FunctionArray = main_functions,
	.ArrayItems = 9,
	.ParentScreen = 0,
	.ParentPosition = 0
};

const Screen* menu_screens[] = {
	&main_struct,
	&maps_container_struct,
	&japes_mapwarp_struct,
	&japesmain_mapwarp_struct,
	&aztec_mapwarp_struct,
	&aztecmain_mapwarp_struct,
	&aztecfivedt_mapwarp_struct,
	&factory_mapwarp_struct,
	&factorymain_mapwarp_struct,
	&galleon_mapwarp_struct,
	&galleonmain_mapwarp_struct,
	&galleonships_mapwarp_struct,
	&watch_struct,
	&fungi_mapwarp_struct,
	&fungimain_mapwarp_struct,
	&fungigmush_mapwarp_struct,
	&fungimills_mapwarp_struct,
	&caves_mapwarp_struct,
	&cavesmain_mapwarp_struct,
	&caves5dc_mapwarp_struct,
	&caves5di_mapwarp_struct,
	&castle_mapwarp_struct,
	&castlemain_mapwarp_struct,
	&castlecrypt_mapwarp_struct,
	&castletunnel_mapwarp_struct,
	&castleoutside_mapwarp_struct,
	&castlerooms_mapwarp_struct,
	&isles_mapwarp_struct,
	&islesmain_mapwarp_struct,
	&isleslobbies_mapwarp_struct,
	&helmrool_mapwarp_struct,
	&state_struct,
	&changestate_struct,
	&timersettings_struct,
	&ramview_struct,
	&filestates_main_struct,
	&filestates_nle_struct,
	&filestates_101main_struct,
	&filestates_general_struct,
	&filestates_101org_struct,
	&filestates_101jfm_struct,
	&filestates_101ffm_struct,
	&viewstate_struct,
	&flagmain_struct,
	&flagmenu_kongs_struct,
	&flagmenu_keysin_struct,
	&flagmenu_keyshave_struct,
	&flagmenu_levelintros_struct,
	&flagmenu_leveltns_struct,
	&flagmenu_levelboss_struct,
	&flagmenu_cutscene_struct,
	&flagmenu_modifier_struct,
	&flagmenu_ftt_struct,
	&flagmenu_misc_struct,
	&flagcustom_struct,
	&cheats_struct,
	&gamemode_struct,
	&settings_struct,
	&kongcolors_struct,
	&quadrant_struct,
	&dpadlr_struct,
	&dpadd_struct,
	&transform_struct,
	&moveset_struct,
	&cranky_struct,
	&funky_struct,
	&candy_struct,
	&flagmenu_tbarrels_struct,
	&vanilla_struct,
	&hack_struct,
	&other_mapwarp_struct,
	&toggles_struct,
	&snagcheats_struct,
	&gamemode_gameplay_struct,
	&gamemode_cutscenes_struct,
	&gamemode_unused_struct,
	&debug_struct,
	&actor_struct,
	&detailsscreen_struct,
	&watch_player_struct,
	&watch_timers_struct,
	&watch_sysenv_struct,
	&watch_snag_struct,
	&watch_assist_struct,
	&heap_struct,
	&flaglog_struct,
	&instruction_struct,
	&testinfo_struct,
	&forcespawn_struct,
	&filestates_glitchless_struct,
	&bonusmain_mapwarp_struct,
	&bonusjapes_mapwarp_struct,
	&bonusaztec_mapwarp_struct,
	&bonusfactory_mapwarp_struct,
	&bonusgalleon_mapwarp_struct,
	&bonusfungi_mapwarp_struct,
	&bonuscaves_mapwarp_struct,
	&bonuscastle_mapwarp_struct,
	&bonushelm_mapwarp_struct,
	&bonusisles_mapwarp_struct,
	&collisionmenu_struct,
	&floormenu_struct,
	&bports_struct,
	&watch_fake_struct,
	&state_settings_struct,
	&tricktoggles_struct,
};

void spawnMenu(int screenIndex) {
	ActiveMenu.screenIndex = screenIndex;
	const Screen* focused_screen = menu_screens[screenIndex];
	int array_count = focused_screen->ArrayItems;
	if (ActiveMenu.positionIndex >= array_count) {
		ActiveMenu.positionIndex = array_count - 1;
	}
	ActiveMenu.isOpen = 1;
};

int* displayMenu(int* dl) {
	if (ActiveMenu.isOpen) {
		int x = 25;
		int y = 25;
		int red = 0xFF;
		int green = 0xFF;
		int blue = 0xFF;
		const Screen* focused_screen = menu_screens[(int)ActiveMenu.screenIndex];
		int* focused_text_array = (int*)focused_screen->TextArray;
		int array_count = focused_screen->ArrayItems;
		int background = 1;
		for (int i = 0; i < array_count; i++) {
			red = 0xFF;
			green = 0xFF;
			blue = 0xFF;
			if (i == ActiveMenu.positionIndex) {
				red = 0xFF;
				green = 0xD7;
				blue = 0;
			}
			dl = drawPixelTextContainer(dl, x, y, (char *)focused_text_array[i], red, green, blue, 0xFF,background);
			y += 13;
		}
		if (ActiveMenu.positionIndex == array_count) {
			red = 0xFF;
			green = 0x45;
			blue = 0;
		} else {
			red = 0xFF;
			green = 0xFF;
			blue = 0xFF;
		}
		int check_char = ((char*)focused_text_array[array_count - 1])[0];
		if ((check_char == 0x7B) || (check_char == 0x7D)) {
			y += 6;
		}
		dl = drawPixelTextContainer(dl, x, y, "RETURN", red, green, blue, 0xFF,background);
	}
	return dl;
}

void clearMenu(void) {
	ActiveMenu.isOpen = 0;
};

void wipeText(void) {
	if (ActorNamesTable) {
		dk_free(ActorNamesTable);
		ActorNamesTable = 0;
	}
	if (SnagNamesTable) {
		dk_free(SnagNamesTable);
		SnagNamesTable = 0;
	}
	if (SnagCapitalsTable) {
		dk_free(SnagCapitalsTable);
		SnagCapitalsTable = 0;
	}
}

void closeMenu(void) {
	clearMenu();
	wipeText();
	hideRacePosition(1);
	ClosingMenu = 1;
}

void toggleMenu(void) {
	if (((TBVoidByte & 2) == 0) || (ArtificialPauseOn)) {
		if (IsPauseMenuOpen == 0) {
			if (CurrentMap != 0x50) {
				if ((ControllerInput.Buttons & R_Button) && (NewlyPressedControllerInput.Buttons & L_Button)) {
					ActiveMenu.screenIndex = 0;
					ActiveMenu.positionIndex = 0;
					if (ActiveMenu.isOpen == 0) {
						spawnMenu(0);
						closeRamViewerDisplay();
						wipeText();
					} else {
						closeMenu();
					}
				}
			}
		}
	}
};

void moveSlot(void) {
	if (ActiveMenu.isOpen) {
		if (((TBVoidByte & 2) == 0) || (ArtificialPauseOn)) {
			if (IsPauseMenuOpen == 0) {
				if ((ControllerInput.Buttons & L_Button) == 0) {
					int screenIndex = ActiveMenu.screenIndex;
					const Screen* focused_screen = menu_screens[screenIndex];
					int cap = focused_screen->ArrayItems + 1;
					int _position = ActiveMenu.positionIndex;
					if (NewlyPressedControllerInput.Buttons & D_Up) {
						if (_position == 0) {
							_position = cap - 1;
						} else {
							_position -= 1;
						}
					} else {
						if (NewlyPressedControllerInput.Buttons & D_Down) {
							_position += 1;
							if (_position == cap) {
								_position = 0;
							}
						}
					}
					ActiveMenu.positionIndex = _position;
				}
			}
		}
	}
};

void closeMenuOnTransition(void) {
	if ((TransitionSpeed > 0) || (CutsceneActive == 6)) {
		if (ActiveMenu.isOpen) {
			clearMenu();
		}
		wipeText();
	}
}

void previousScreen(void) {
	int screenIndex = ActiveMenu.screenIndex;
	clearMenu();
	if (screenIndex == 0) {
		ClosingMenu = 1;
		wipeText();
	} else {
		const Screen* focused_screen = menu_screens[screenIndex];
		int newScreen = focused_screen->ParentScreen;
		int newPosition = focused_screen->ParentPosition;
		ActiveMenu.screenIndex = newScreen;
		ActiveMenu.positionIndex = newPosition;
		spawnMenu(newScreen);
	}
}

void confirmOptionBackground(void) {
	const Screen* focused_screen = menu_screens[(int)ActiveMenu.screenIndex];
	int* focused_function_array = (int *)focused_screen->FunctionArray;
	int cap = focused_screen->ArrayItems;
	if (ActiveMenu.positionIndex == cap) {
		previousScreen();
	} else {
		int _code = focused_function_array[(int)ActiveMenu.positionIndex];
		if (_code) {
			callFunc((int *)_code);
		}
	}
}

void confirmOption(void) {
	if (ActiveMenu.isOpen) {
		if (((TBVoidByte & 2) == 0) || (ArtificialPauseOn)) {
			if (IsPauseMenuOpen == 0) {
				if (NewlyPressedControllerInput.Buttons & L_Button) {
					if ((ControllerInput.Buttons & R_Button) == 0) {
						confirmOptionBackground();
					}
				}
			}
		}
	}
}

void menuShortcutButtons(void) {
	if (MenuShortcutButtonsOff == 0) {
		short _buttons = NewlyPressedControllerInput.Buttons;
		if ((_buttons & L_Button) == 0) {
			if (ActiveMenu.isOpen) {
				if (ClosingMenu == 0) {
					if ((ActiveMenu.screenIndex != 54) && (ActiveMenu.screenIndex != 88)) {
						if (_buttons & D_Left) {
							previousScreen();
						} else {
							if (_buttons & D_Right) {
								confirmOptionBackground();
							}
						}
					}
				}
			}
		}
	}
}

void changeMenu(int newScreenIndex) {
	clearMenu();
	if (ActiveMenu.screenIndex != newScreenIndex) {
		ActiveMenu.positionIndex = 0;
		ActiveMenu.screenIndex = newScreenIndex;
	}
	spawnMenu(newScreenIndex);
}

static const int main_functions[] = {
	(int)&initWarpMenu,
	(int)&openFlagsMainMenu,
	(int)&openStateMenu,
	(int)&openWatchMenu,
	(int)&openDebugMenu,
	(int)&openTimerSettingsMenu,
	(int)&openFileStateMainMenu,
	(int)&openCheatsMenu,
	(int)&openSettingsMainMenu,
};