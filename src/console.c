#include "../include/common.h"

static char spawned_menu = 0;
static char menu_slot = 0;

static const char* console_text_list[] = {
	"THIS IS THE FIRST TIME YOU'VE BOOTED UP THE ROM",
	"PLEASE SELECT YOUR CONSOLE",
	"NINTENDO 64",
	"WII U VIRTUAL CONSOLE",
	"EMULATOR",
	"YOU CAN CHANGE THIS IN THE SETTINGS MENU LATER",
};
static const short console_x[] = {25,100,160,125,167,25};
static const short console_y[] = {55,68,101,114,127,160};

int* spawnConsoleMenu(int* dl) {
	if ((spawned_menu == 0) && (ObjectModel2Timer == 5)) {
		preventSongPlaying = 0;
		playSFX(173);
		spawned_menu = 1;
	}
	for (int i = 0; i < 6; i++) {
		int red = 0xFF;
		int green = 0xFF;
		int blue = 0xFF;
		if ((i > 1) && (i < 5)) {
			if (menu_slot == (i - 2)) {
				green = 0xD7;
				blue = 0;
			}
		}
		dl = drawTextContainer(dl, 6, console_x[i], console_y[i] + 100, (char *)console_text_list[i], red, green, blue, 0xFF, 0);
	}
	return dl;	
}

void controlConsoleMenu(void) {
	if (spawned_menu) {
		if (NewlyPressedControllerInput.Buttons & D_Up) {
			if (menu_slot > 0) {
				menu_slot -= 1;
				playSFX(64);
			}
		} else if (NewlyPressedControllerInput.Buttons & D_Down) {
			if (menu_slot < 2) {
				menu_slot += 1;
				playSFX(64);
			}
		} else if (NewlyPressedControllerInput.Buttons & A_Button) {
			assignedConsole = 1 + menu_slot;
			saveSettings();
			playSFX(69);
			initiateTransitionFade(0x50,0,5);
			spawned_menu = 0;
		}
	}
}