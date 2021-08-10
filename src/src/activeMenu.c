#include "../include/common.h"

static const char returnLine[] = "RETURN";
static const char warp[] = "WARP TO MAP";
static const char flags[] = "SPECIAL FLAGS";
static const char saves[] = "SAVE STATES";
static const char watches[] = "WATCHES";
static const char timerSettings[] = "TIMER SETTINGS";
static const char fileStates[] = "FILE STATES";
static const char cheats[] = "CHEATS";
static const char settings[] = "SETTINGS";

static const char* main_array[] = {
	warp,
	flags,
	saves,
	watches,
	timerSettings,
	fileStates,
	cheats,
	settings,
	returnLine
};

static const int main_functions[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

static const Screen main_struct = {
	.TextArray = (const int*)main_array,
	.FunctionArray = main_functions,
	.ArrayItems = 9,
	.ParentScreen = 0,
	.ParentPosition = 0
};

static const Screen* menu_screens[] = {
	&main_struct
};

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
	textOverlay = HackTitle;
	if (textOverlay) {
		deleteActor(textOverlay);
	}
	HackTitle = 0;
	textOverlay = HackVersion;
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
						ActiveMenu.isOpen = 1;
					} else {
						clearMenu();
						ActiveMenu.isOpen = 0;
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
					int cap = focused_screen->ArrayItems;
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