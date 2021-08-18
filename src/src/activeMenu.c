#include "../include/common.h"

static const char returnLine[] = "RETURN";
static const char warp[] = "WARP TO MAP";
static const char flags[] = "SPECIAL FLAGS";
static const char saves[] = "SAVE STATES";
static const char watches[] = "WATCHES";
static const char ramview[] = "RAM VIEWER";
static const char timerSettings[] = "TIMER SETTINGS";
static const char fileStates[] = "FILE STATES";
static const char cheats[] = "CHEATS";
static const char settings[] = "SETTINGS";
static const char hackTitle[] = "DK64 PRACTICE ROM";
static const char hackVersion[] = "VERSION 1.4.1";
static const char forceClose[] = "EMERGENCY: ERROR 01";

static const char* main_array[] = {
	warp,
	flags,
	saves,
	watches,
	ramview,
	timerSettings,
	fileStates,
	cheats,
	settings
};

static const int main_functions[9];

static const Screen main_struct = {
	.TextArray = (const int*)main_array,
	.FunctionArray = main_functions,
	.ArrayItems = 9,
	.ParentScreen = 0,
	.ParentPosition = 0
};

static const Screen* menu_screens[] = {
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
};

void hideInputDisplay(void) {
	if (InputDisplayIndex > -1) {
		if (WatchActor[(int)InputDisplayIndex]) {
			if (ActiveMenu.isOpen) {
				WatchActor[(int)InputDisplayIndex]->opacity = 0;
			} else {
				WatchActor[(int)InputDisplayIndex]->opacity = 0xFF;
			}
		}
	}
}

void spawnMenu(int screenIndex) {
	TextOverlay* textOverlay;
	int x = 25;
	int y = 25;
	int style = 10;
	Screen* focused_screen = menu_screens[screenIndex];
	int* focused_text_array = (int*)focused_screen->TextArray;
	int array_count = focused_screen->ArrayItems;
	for (int i = 0; i < array_count; i++) {
		spawnTextOverlay(style,x,y,(char *)focused_text_array[i],0,0,2,0);
		textOverlay = (TextOverlay *)CurrentActorPointer;
		ActiveToolsMenu[i] = textOverlay;
		textOverlay->opacity = 0xFF;
		if (i == ActiveMenu.positionIndex) {
			textOverlay->red = 0xFF;
			textOverlay->green = 0xD7;
			textOverlay->blue = 0;
		}
		y += 10;
	}
	spawnTextOverlay(style,x,y,(char *)returnLine,0,0,2,0);
	textOverlay = (TextOverlay *)CurrentActorPointer;
	textOverlay->opacity = 0xFF;
	ActiveToolsMenu[array_count] = textOverlay;
	if (screenIndex == 0) {
		
		spawnTextOverlay(style,180,25,(char *)hackTitle,0,0,2,0);
		textOverlay = (TextOverlay *)CurrentActorPointer;
		textOverlay->opacity = 0xFF;
		HackTitle = textOverlay;
		spawnTextOverlay(style,217,35,(char *)hackVersion,0,0,2,0);
		textOverlay = (TextOverlay *)CurrentActorPointer;
		textOverlay->opacity = 0xFF;
		HackVersion = textOverlay;
	}
	ActiveMenu.isOpen = 1;
};

void clearMenu(void) {
	int* textOverlay;
	for (int i = 0; i < MaxMenuItems; i++) {
		textOverlay = (int *)ActiveToolsMenu[i];
		if (textOverlay) {
			deleteActor(textOverlay);
		}
		ActiveToolsMenu[i] = 0;
	}
	textOverlay = (int *)HackTitle;
	if (textOverlay) {
		deleteActor(textOverlay);
	}
	HackTitle = 0;
	textOverlay = (int *)HackVersion;
	if (textOverlay) {
		deleteActor(textOverlay);
	}
	HackVersion = 0;
	ActiveMenu.isOpen = 0;
};

void toggleMenu(void) {
	if ((TBVoidByte & 2) == 0) {
		if (IsPauseMenuOpen == 0) {
			if (CurrentMap != 0x50) {
				if ((ControllerInput.Buttons & R_Button) && (NewlyPressedControllerInput.Buttons & L_Button)) {
					ActiveMenu.screenIndex = 0;
					ActiveMenu.positionIndex = 0;
					if (ActiveMenu.isOpen == 0) {
						spawnMenu(0);
					} else {
						clearMenu();
						ClosingMenu = 1;
					}
				}
			}
		}
	}
};

void moveSlot(void) {
	TextOverlay* textOverlay;
	unsigned char _red;
	unsigned char _green;
	unsigned char _blue;
	if (ActiveMenu.isOpen) {
		if ((TBVoidByte & 2) == 0) {
			if (IsPauseMenuOpen == 0) {
				if ((ControllerInput.Buttons & L_Button) == 0) {
					int screenIndex = ActiveMenu.screenIndex;
					Screen* focused_screen = menu_screens[screenIndex];
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
					for (int i = 0; i < cap; i++) {
						textOverlay = (TextOverlay *)(int *)ActiveToolsMenu[i];
						_red = 0xFF;
						_green = 0xFF;
						_blue = 0xFF;
						if (textOverlay) {
							if (_position == i) {
								if (_position == (cap - 1)) {
									_red = 0xFF;
									_green = 0x45;
									_blue = 0;
								} else {
									_red = 0xFF;
									_green = 0xD7;
									_blue = 0;
								}
							}
						};
						textOverlay->red = _red;
						textOverlay->green = _green;
						textOverlay->blue = _blue;
					}
				}
			}
		}
	}
};

void closeMenuOnTransition(void) {
	if (ActiveMenu.isOpen) {
		if ((TransitionSpeed > 0) || (CutsceneActive == 6)) {
			clearMenu();
		}
	}
}

void emergencyClose(void) {
	TextOverlay* textOverlay;
	if (NewMenu_ErrorStart) {
		int _time = FrameReal - NewMenu_ErrorStart;
		if (_time >= ErrorLength) {
			textOverlay = ActiveTools_Error;
			deleteActor((void *)textOverlay);
			NewMenu_ErrorStart = 0;
		}
	} else {
		if (LoadedActorCount >= 60) {
			if (ActiveMenu.isOpen) {
				NewMenu_ErrorStart = FrameReal;
				spawnTextOverlay(10,100,200,(char *)forceClose,0,0,2,0);
				textOverlay = (TextOverlay *)CurrentActorPointer;
				textOverlay->opacity = 0xFF;
				textOverlay->red = 0xFF;
				textOverlay->green = 0;
				textOverlay->blue = 0;
				ActiveTools_Error = textOverlay;
			}
		}
	}
}

void previousScreen(void) {
	int screenIndex = ActiveMenu.screenIndex;
	clearMenu();
	if (screenIndex == 0) {
		ClosingMenu = 1;
	} else {
		Screen* focused_screen = menu_screens[screenIndex];
		int newScreen = focused_screen->ParentScreen;
		int newPosition = focused_screen->ParentPosition;
		ActiveMenu.screenIndex = newScreen;
		ActiveMenu.positionIndex = newPosition;
		spawnMenu(newScreen);
	}
}

void confirmOptionBackground(void) {
	Screen* focused_screen = menu_screens[(int)ActiveMenu.screenIndex];
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
		if ((TBVoidByte & 2) == 0) {
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
					// Take into account custom flag screen
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

void changeMenu(int newScreenIndex) {
	clearMenu();
	if (ActiveMenu.screenIndex != newScreenIndex) {
		ActiveMenu.positionIndex = 0;
		ActiveMenu.screenIndex = newScreenIndex;
	}
	spawnMenu(newScreenIndex);
}

void endClose() {
	ClosingMenu = 0;
}

static const int main_functions[] = {
	(int)&initWarpMenu,
	0,
	(int)&openStateMenu,
	(int)&openWatchMenu,
	(int)&initRamViewerTab,
	(int)&openTimerSettingsMenu,
	(int)&openFileStateMainMenu,
	0,
	0
};