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
static const float console_y[] = {55,68,101,114,127,160};

static TextOverlay* text_actors[6];

void spawnConsoleMenu(void) {
	TextOverlay* textOverlay;
	if ((spawned_menu == 0) && (ObjectModel2Timer == 5)) {
		preventSongPlaying = 0;
		playSFX(173);
		for (int i = 0; i < 6; i++) {
			spawnTextOverlay(0,25,console_y[i],(char *)console_text_list[i],0,0,2,0);
			textOverlay = (TextOverlay *)CurrentActorPointer;
			text_actors[i] = textOverlay;
			textOverlay->opacity = 0xFF;
		}
		spawned_menu = 1;
	}	
}

void controlConsoleMenu(void) {
	if (spawned_menu) {
		for (int i = 0; i < 3; i++) {
			if (menu_slot == i) {
				text_actors[2+i]->red = 0xFF;
				text_actors[2+i]->green = 0xD7;
				text_actors[2+i]->blue = 0;
			} else {
				text_actors[2+i]->red = 0xFF;
				text_actors[2+i]->green = 0xFF;
				text_actors[2+i]->blue = 0xFF;
			}
		}
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