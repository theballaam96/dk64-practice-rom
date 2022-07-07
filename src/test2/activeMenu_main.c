#include "include/common.h"
#define MAX_ELEMENTS 13

static const char* main_array[] = {
	"WARP TO MAP",
	"FLAGS",
	"SAVE STATES",
	"WATCHES",
	"COLLISION",
	"DEBUG",
	"TIMER SETTINGS",
	"FILE STATES",
	"CHEATS",
	"SETTINGS"
};

static const int main_functions[10];
static const char main_access[] = {
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Warp
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Flags
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Save States
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Watches
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Collision
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Debug
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Timer Settings
	ACCESS_US | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // File States
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Cheats
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Settings
};

const Screen main_struct = {
	.TextArray = (int*)main_array,
	.FunctionArray = main_functions,
	.ArrayItems = 10,
	.ParentScreen = 0,
	.ParentPosition = 0,
	.hasAccessArray = 1,
	.AccessArray = main_access
};

int isValidSpotInternal(int position, int screenIndex) {
	const Screen* focused_screen = menu_screens[screenIndex];
	int hasAccessArray = focused_screen->hasAccessArray;
	int ret_ver = 1;
	int ret_console = 1;
	if (hasAccessArray) {
		char* focused_access_array = (char*)focused_screen->AccessArray;
		ret_ver = (focused_access_array[position] & (1 << ROM_VERSION)) != 0;
		if (assignedConsole != NONE) {
			ret_console = (focused_access_array[position] & (8 << ((int)(assignedConsole) - 1))) != 0;
		}
	}
	return ret_ver & ret_console;
}

int isValidSpot(int position) {
	return isValidSpotInternal(position,ActiveMenu.screenIndex);
}

int getScreenItemCount(int screenIndex) {
	const Screen* focused_screen = menu_screens[screenIndex];
	int count = focused_screen->ArrayItems;
	int item_count = 0;
	for (int i = 0; i < count; i++) {
		item_count += isValidSpotInternal(i,screenIndex);
	}
	return item_count;
}

void skipEmptyOptions(int direction) {
	int pos = ActiveMenu.positionIndex;
	int startPos = pos;
	int total = ActiveMenu.totalItems;
	const Screen* focused_screen = menu_screens[(int)ActiveMenu.screenIndex];
	int hasAccessArray = focused_screen->hasAccessArray;
	if ((hasAccessArray) && (direction != 0) && (pos >= 0) && (pos < total)) {
		if (!isValidSpot(pos)) {
			int pass = 1;
			while(pass) {
				pos += direction;
				if ((pos < 0) || (pos > (total - 1))) {
					pos = total;
					pass = 0;
					break;
				}
				if (pos == startPos) {
					pos = total;
					pass = 0;
					break;
				} else if (isValidSpot(pos)) {
					pass = 0;
					break;
				}
			}
		}
	}
	ActiveMenu.positionIndex = pos;
}

void spawnMenu(int screenIndex) {
	ActiveMenu.screenIndex = screenIndex;
	int array_count = getScreenItemCount(screenIndex);
	const Screen* focused_screen = menu_screens[screenIndex];
	ActiveMenu.totalItems = focused_screen->ArrayItems;
	if (array_count > MAX_ELEMENTS) {
		array_count = MAX_ELEMENTS;
		ActiveMenu.hasScroll = 1;
	} else {
		ActiveMenu.hasScroll = 0;
	}
	if (ActiveMenu.positionIndex >= ActiveMenu.totalItems) {
		ActiveMenu.positionIndex = ActiveMenu.totalItems - 1;
	}
	skipEmptyOptions(1);
	if (ActiveMenu.positionIndex > array_count) {
		ActiveMenu.startIndex = (ActiveMenu.positionIndex - MAX_ELEMENTS) + 1;
	}
	if (!ActiveMenu.hasScroll) {
		ActiveMenu.startIndex = 0;
	}
	ActiveMenu.isOpen = 1;
};

int* displayScrollBar(int* dl) {
	if (ActiveMenu.hasScroll) {
		int line_shade = 10;
		int box_shade = 20;
		int left = 62;
		int thickness = 15;
		int pad = 5;
		int top = 100;
		int height = 700;
		float box_height = height * MAX_ELEMENTS;
		box_height /= ActiveMenu.totalItems;
		int box_graduation_limit = height - box_height;
		float box_top = ActiveMenu.startIndex * box_graduation_limit;
		box_top /= (ActiveMenu.totalItems - MAX_ELEMENTS);
		box_top += top;
		dl = drawScreenRect(dl, left, top, left + thickness, top + height, line_shade, line_shade, line_shade, 1);
		dl = drawScreenRect(dl, left - pad, box_top - pad, left + thickness + pad, box_top + box_height + pad, box_shade, box_shade, box_shade, 1);
	}
	return dl;
}

int* displayMenu(int* dl) {
	if (ActiveMenu.isOpen) {
		int x = 25;
		int y = 25;
		int red = 0xFF;
		int green = 0xFF;
		int blue = 0xFF;
		const Screen* focused_screen = menu_screens[(int)ActiveMenu.screenIndex];
		int* focused_text_array = (int*)focused_screen->TextArray;
		int array_count = getScreenItemCount(ActiveMenu.screenIndex);
		if (array_count > MAX_ELEMENTS) {
			array_count = MAX_ELEMENTS;
		}
		int background = 1;
		int relative_pos = ActiveMenu.positionIndex - ActiveMenu.startIndex;
		int i = 0;
		int j = 0;
		while (i < array_count) {
			red = 0xFF;
			green = 0xFF;
			blue = 0xFF;
			if (j == relative_pos) {
				red = 0xFF;
				green = 0xD7;
				blue = 0;
			}
			if (isValidSpot(j + ActiveMenu.startIndex)) {
				dl = drawPixelTextContainer(dl, x, y, (char *)focused_text_array[j + ActiveMenu.startIndex], red, green, blue, 0xFF,background);
				y += 13;
				i += 1;
			}
			j += 1;
			if ((j + ActiveMenu.startIndex) > ActiveMenu.totalItems) {
				break;
			}
		}
		if (ActiveMenu.positionIndex == ActiveMenu.totalItems) {
			red = 0xFF;
			green = 0x45;
			blue = 0;
		} else {
			red = 0xFF;
			green = 0xFF;
			blue = 0xFF;
		}
		int check_char = ((char*)focused_text_array[ActiveMenu.totalItems - 1])[0];
		if ((check_char == 0x7B) || (check_char == 0x7D)) {
			y += 6;
		}
		dl = drawPixelTextContainer(dl, x, y, "RETURN", red, green, blue, 0xFF,background);
		dl = displayScrollBar(dl);
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
					ActiveMenu.hasScroll = 0;
					ActiveMenu.startIndex = 0;
					if (ActiveMenu.isOpen == 0) {
						spawnMenu(ACTIVEMENU_SCREEN_ROOT);
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
					int rel_pos = ActiveMenu.positionIndex - ActiveMenu.startIndex;
					if (NewlyPressedControllerInput.Buttons & D_Up) {
						_position = ActiveMenu.positionIndex;
						rel_pos = ActiveMenu.positionIndex - ActiveMenu.startIndex;
						if (ActiveMenu.hasScroll) {
							if ((rel_pos == 0) && (ActiveMenu.startIndex > 0)) {
								ActiveMenu.startIndex -= 1;
							}
						}
						if (_position == 0) {
							_position = cap - 1;
							if (ActiveMenu.hasScroll) {
								ActiveMenu.startIndex = _position - MAX_ELEMENTS;
							}
						} else {
							_position -= 1;
						}
						ActiveMenu.positionIndex = _position;
						skipEmptyOptions(-1);
						if (ActiveMenu.hasScroll) {
							ActiveMenu.startIndex += (ActiveMenu.positionIndex - _position);
							if (ActiveMenu.startIndex < 0) {
								ActiveMenu.startIndex = 0;
							} else if (ActiveMenu.startIndex > (ActiveMenu.totalItems - MAX_ELEMENTS)) {
								ActiveMenu.startIndex = ActiveMenu.totalItems - MAX_ELEMENTS;
							}
						}
					} else if (NewlyPressedControllerInput.Buttons & D_Down) {
						_position = ActiveMenu.positionIndex;
						rel_pos = ActiveMenu.positionIndex - ActiveMenu.startIndex;
						if (ActiveMenu.hasScroll) {
							if ((rel_pos == (MAX_ELEMENTS - 1)) && (ActiveMenu.startIndex < (ActiveMenu.totalItems - MAX_ELEMENTS))) {
								ActiveMenu.startIndex += 1;
							}
						}
						_position += 1;
						if (_position == cap) {
							_position = 0;
							if (ActiveMenu.hasScroll) {
								ActiveMenu.startIndex = 0;
							}
						}
						ActiveMenu.positionIndex = _position;
						skipEmptyOptions(1);
					}
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
	if (screenIndex == ACTIVEMENU_SCREEN_ROOT) {
		ClosingMenu = 1;
		wipeText();
	} else {
		const Screen* focused_screen = menu_screens[screenIndex];
		int newScreen = focused_screen->ParentScreen;
		int newPosition = focused_screen->ParentPosition;
		ActiveMenu.screenIndex = newScreen;
		ActiveMenu.positionIndex = newPosition;
		ActiveMenu.startIndex = 0;
		ActiveMenu.hasScroll = 0;
		spawnMenu(newScreen);
	}
}

void confirmOptionBackground(void) {
	const Screen* focused_screen = menu_screens[(int)ActiveMenu.screenIndex];
	int* focused_function_array = (int *)focused_screen->FunctionArray;
	int cap = ActiveMenu.totalItems;
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
					if ((ActiveMenu.screenIndex != ACTIVEMENU_SCREEN_FLAG_CUSTOM) && (ActiveMenu.screenIndex != ACTIVEMENU_SCREEN_DEBUG_SPAWNACTOR)) {
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
		ActiveMenu.startIndex = 0;
		ActiveMenu.hasScroll = 0;
	}
	spawnMenu(newScreenIndex);
}

static const int main_functions[] = {
	(int)&initWarpMenu,
	(int)&openFlagsMainMenu,
	(int)&openStateMenu,
	(int)&openWatchMenu,
	(int)&openCollisionRootMenu,
	(int)&openDebugMenu,
	(int)&openTimerSettingsMenu,
	(int)&openFileStateMainMenu,
	(int)&openCheatsMenu,
	(int)&openSettingsMainMenu,
};