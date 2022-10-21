#include "../include/common.h"

static char spawned_menu = 0;
static char menu_slot = 0;
static char has_loaded = 0;
static char has_blockered = 0;

#if ROM_VERSION == 2
	#define FIRST_LINE "WELCOME TO THE PRACTICE ROM <JP>"
	#define LAST_LINE "THIS CAN BE CHANGED LATER"
#else
	#define FIRST_LINE "THIS IS THE FIRST TIME YOU'VE BOOTED UP THE ROM"
	#define LAST_LINE "YOU CAN CHANGE THIS IN THE SETTINGS MENU LATER"
#endif

static const char* console_text_list[] = {
	FIRST_LINE,
	"PLEASE SELECT YOUR CONSOLE",
	"NINTENDO 64",
	"WII U VIRTUAL CONSOLE",
	"EMULATOR",
	LAST_LINE,
};
static const short console_x[] = {25,100,160,125,167,25};
static const short console_y[] = {55,68,101,114,127,160};
static const short console_x_jp[] = {30,55,108,75,120,60};

static unsigned char snake_x[10] = {40,39,38,37,36,0,0,0,0,0};
static unsigned char snake_y[10] = {45,45,45,45,45,0,0,0,0,0};
static unsigned char fruit_x = 42;
static unsigned char fruit_y = 45;
static unsigned char snake_size = 5;
static int snake_direction = 0; // Right, bottom, left, top

#define SNAKE_SQUARE_SIZE 8

void updateSnake(void) {
	int rng = getRNGLower31() & 7;
	int target_direction = 0;
	if (snake_y[0] < fruit_y) {
		target_direction = 1;
	} else if (snake_y[0] > fruit_y) {
		target_direction = 3;
	} else if (snake_x[0] > fruit_x) {
		target_direction = 2;
	}
	int target_diff = target_direction - snake_direction;
	if ((target_direction == 0) && (snake_direction == 3)) {
		target_diff = 1;
	} else if ((target_direction == 3) && (snake_direction == 0)) {
		target_diff = -1;
	}
	int direction_change = 0;
	if (target_diff < -1) {
		direction_change = -1;
	} else if (target_diff > 1) {
		direction_change = 1;
	} else {
		direction_change = target_diff;
	}
	snake_direction += direction_change;
	if (snake_direction < 0) {
		snake_direction += 4;
	} else if (snake_direction > 3) {
		snake_direction -= 4;
	}
	int diff_x = 0;
	int diff_y = 0;
	if (snake_direction == 0) {
		// Right
		diff_x = 1;
	} else if (snake_direction == 1) {
		// Bottom
		diff_y = 1;
	} else if (snake_direction == 2) {
		// Left
		diff_x = -1;
	} else {
		// Top
		diff_y = -1;
	}
	for (int i = 9; i >= 0; i--) {
		snake_x[i+1] = snake_x[i];
		snake_y[i+1] = snake_y[i]; 
	}
	snake_x[0] += diff_x;
	snake_y[0] += diff_y;
	if (snake_y[0] > 50) {
		snake_y[0] = 10;
	} else if (snake_y[0] < 10) {
		snake_y[0] = 50;
	}
	if (snake_x[0] > 90) {
		snake_x[0] = 35;
	} else if (snake_x[0] < 35) {
		snake_x[0] = 90;
	}
	int dead = 0;
	int grow = 0;
	for (int i = 0; i < snake_size; i++) {
		if (i > 0) {
			if ((snake_x[0] == snake_x[i]) && (snake_y[0] == snake_y[i])) {
				dead = 1;
			}
		}
		if ((fruit_x == snake_x[i]) && (fruit_y == snake_y[i])) {
			grow = 1;
		}
	}
	if (dead) {
		snake_size = 5;
		for (int i = 0; i < 10; i++) {
			snake_x[i] = 40 - i;
			snake_y[i] = 45;
		}
	} else if (grow) {
		snake_size += 1;
		fruit_x = (getRNGLower31() & 31) + 35;
		fruit_y = (getRNGLower31() & 31) + 14;
	}
}

int* drawSnake(int* dl) {
	updateSnake();
	for (int i = 0; i < snake_size; i++) {
		int left = snake_x[i]*SNAKE_SQUARE_SIZE;
		int top = snake_y[i]*SNAKE_SQUARE_SIZE;
		dl = drawScreenRect(dl, left, top, left+SNAKE_SQUARE_SIZE,top+SNAKE_SQUARE_SIZE,0,0x1F,0,0xFF);
	}
	int fruit_left = fruit_x * SNAKE_SQUARE_SIZE;
	int fruit_top = fruit_y * SNAKE_SQUARE_SIZE;
	dl = drawScreenRect(dl, fruit_left - SNAKE_SQUARE_SIZE, fruit_top - SNAKE_SQUARE_SIZE, fruit_left+SNAKE_SQUARE_SIZE,fruit_top+SNAKE_SQUARE_SIZE,0x1F,0,0,0xFF);
	return dl;
}

int* spawnConsoleMenu(int* dl) {
	if ((spawned_menu == 0) && (ObjectModel2Timer == 5)) {
		preventSongPlaying = 0;
		spawned_menu = 1;
		has_blockered = 0;
		snake_size = 5;
	}
	int loaded = *(char*)(0x807F01A6);
	if ((loaded) || (ObjectModel2Timer > 800)) {
		if (has_loaded == 0) {
			has_loaded = 1;
			loadSettings();
			if (assignedConsole == NONE) {
				has_loaded = 2;
			} else {
				initiateTransitionFade(0x50, 0, 5);
			}
		}
	}
	if (has_loaded == 2) {
		if (!has_blockered) {
			playSFX(173);
			has_blockered = 1;
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
			if (ROM_VERSION < 2) {
				dl = drawTextContainer(dl, 6, console_x[i], console_y[i] + 100, (char *)console_text_list[i], red, green, blue, 0xFF, 0);
			} else {
				dl = drawPixelTextContainer(dl, console_x_jp[i], console_y[i], (char *)console_text_list[i], red, green, blue, 0xFF,0);
			}
		}
	} else {
		if (has_loaded == 0) {
			dl = drawPixelTextContainer(dl, 85, 130, "LOADING PRACTICE ROM", 0xFF, 0xFF, 0xFF, 0xFF, 1);
			dl = drawPixelTextContainer(dl, 110, 150, "PLEASE WAIT", 0xFF, 0xFF, 0xFF, 0xFF, 1);
		} else {
			dl = drawPixelTextContainer(dl, 87, 130, "LOADED PRACTICE ROM", 0xFF, 0xFF, 0xFF, 0xFF, 1);
		}
		dl = drawSnake(dl);
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
			int gfb_start = (int)getFlagBlockAddress(1);
			*(int*)(gfb_start) = -1;
			*(int*)(gfb_start + 4) = -1;
			for (int i = 0; i < 0x40; i++) {
				setFlag(i, 1, 1);
			}
			saveSettings();
			playSFX(69);
			initiateTransitionFade(0x50,0,5);
			spawned_menu = 0;
		}
	}
}