#include "../../include/common.h"

const snagTableInfo snag_data[] = {
	{0x00070052}, // Diddy Mountain
	{0x00070048}, // Free Diddy
	{0x00260026}, // Free Llama
	{0x002600A3}, // Gong Tower
	{0x00260023}, // Vase
	{0x002600EB}, // Vulture Race
	{0x0010007E}, // Tiny Temple
	{0x001A0108}, // Arcade R1
	{0x001A0029}, // Chunky Prod
	{0x001A007C}, // Chunky R&D
	{0x001A0082}, // Dartboard
	{0x001A002C}, // Diddy Prod
	{0x001A0060}, // Diddy R&D
	{0x001A0078}, // Free Chunky
	{0x001A007E}, // Numbers Game
	{0x001A003E}, // Piano Game
	{0x001D0002}, // Power Shed
	{0x001E0032}, // Cannon Game
	{0x001E000E}, // Chests
	{0x001E002D}, // Diddy Ship
	{0x001E006B}, // Enguarde Chest
	{0x001E002E}, // Free Seal
	{0x0031002F}, // Lighthouse
	{0x0033000F}, // Mech Fish
	{0x002D000E}, // Mermaid
	{0x0030003E}, // Apple GB
	{0x00300039}, // Fungi BBlast GB
	{0x0030002B}, // Mill GB
	{0x00300057}, // Rabbit Race
	{0x00400003}, // Mush Cannons
	{0x003A0002}, // Lanky Attic
	{0x00340000}, // Anthill
	{0x003D000D}, // Kegs GB
	{0x00470002}, // Fungi Face Puzzle
	{0x00480032}, // Caves BBlast GB
	{0x0048003E}, // Caves GGone
	{0x005C0001}, // Diddy Enemies 5DC
	{0x00640001}, // Diddy 5DI
	{0x00620010}, // Ice Tomato
	{0x005E0001}, // Sprint Cabin
	{0x005F0000}, // Chunky 5DI
	{0x00A3000F}, // DK Dungeon
	{0x00700008}, // Diddy Crypt
	{0x00A80001}, // Greenhouse GB
	{0x00A70004}, // Trash Can
	{0x00A60006}, // Shed
	{0x00220004}, // Japes Rock
	{0x00220056}, // Big X
	{0x0011005D}, // DK Helm Medal
	{0x00110061}, // Diddy Helm Medal
	{0x0011005F}, // Lanky Helm Medal
	{0x00110060}, // Tiny Helm Medal
	{0x0011005E}, // Chunky Helm Medal
};

static char snagmenu_collect0[20] = "";
static char snagmenu_collect1[20] = "";
static char snagmenu_collect2[20] = "";
static char snagmenu_collect3[20] = "";
static char snagmenu_collect4[20] = "";
static char snagmenu_collect5[20] = "";
static char snagmenu_collect6[20] = "";
static char snagmenu_collect7[20] = "";
static char snagmenu_collect8[20] = "";
static char snagmenu_collect9[20] = "";
static char snagmenu_collect10[20] = "";
static char snagmenu_collect11[20] = "";
static char snagmenu_collect12[20] = "";

static char snagwatch_name0[16] = "";
static char snagwatch_name1[16] = "";
static char snagwatch_name2[16] = "";
static char snagwatch_name3[16] = "";

static char* watch_snag_array[] = {
	snagmenu_collect0,
	snagmenu_collect1,
	snagmenu_collect2,
	snagmenu_collect3,
	snagmenu_collect4,
	snagmenu_collect5,
	snagmenu_collect6,
	snagmenu_collect7,
	snagmenu_collect8,
	snagmenu_collect9,
	snagmenu_collect10,
	snagmenu_collect11,
	snagmenu_collect12,
};

char* snagwatch_names_array[] = {
	snagwatch_name0,
	snagwatch_name1,
	snagwatch_name2,
	snagwatch_name3,
};

static const int watch_snag_functions[13];

Screen watch_snag_struct = {
	.TextArray = (int*)watch_snag_array,
	.FunctionArray = watch_snag_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 3
};

void openWatchSnagMenu(void) {
	unsigned int _map;
	int snag_counter = 0;
	int* file_size;
	if (SnagNamesTable == 0) {
		actorNames* copy_space = dk_malloc(0x350);
		SnagNamesTable = copy_space;
		*(int*)(&file_size) = 0x350;
		copyFromROM(0x2021800,copy_space,&file_size,0,0,0,0);
	}
	if (SnagCapitalsTable == 0) {
		actorNames* copy_space = dk_malloc(0x350);
		SnagCapitalsTable = copy_space;
		*(int*)(&file_size) = 0x350;
		copyFromROM(0x2021C00,copy_space,&file_size,0,0,0,0);
	}
	for (int i = 0; i < (sizeof(snag_data) / 4); i++) {
		_map = snag_data[i].map;
		if (CurrentMap == _map) {
			int snag_viewed = 0;
			for (int j = 0; j < WatchCount; j++) {
				if (ViewedSnagWatches[j] == i) {
					snag_viewed = 1;
				}
			}
			if (snag_viewed) {
				dk_strFormat((char *)watch_snag_array[snag_counter++],"} %s",SnagCapitalsTable->actor_name[i]);
			} else {
				dk_strFormat((char *)watch_snag_array[snag_counter++],"{ %s",SnagCapitalsTable->actor_name[i]);
			}
		}
	}
	for (int i = 0; i < WatchCount; i++) {
		if (ViewedSnagWatches[i] > -1) {
			if (snag_data[(int)ViewedSnagWatches[i]].map != CurrentMap) {
				dk_strFormat((char *)watch_snag_array[snag_counter++],"} %s",SnagCapitalsTable->actor_name[(int)ViewedSnagWatches[i]]);
			}
		}
	}
	if (snag_counter == 0) {
		dk_strFormat((char *)watch_snag_array[0],"NO SNAG COLLECTABLES");
		snag_counter = 1;
	}
	watch_snag_struct.ArrayItems = snag_counter;
	changeMenu(ACTIVEMENU_SCREEN_WATCH_SNAG);
}

void toggleSnagWatch(void) {
	int i = 0;
	int index_already_spawned = 0;
	unsigned int list_index = 0;
	unsigned int _map;
	unsigned int map_snag_index = 0;
	int native_cap = 0;
	int watched_count = 0;
	for (int i = 0; i < (sizeof(snag_data) / 4); i++) {
		_map = snag_data[i].map;
		if (CurrentMap == _map) {
			native_cap++;
		}
	}
	for (int i = 0; i < WatchCount; i++) {
		if (ViewedSnagWatches[i] > -1) {
			watched_count++;
		}
	}
	if ((native_cap > 0) || (watched_count > 0)) {
		if (ActiveMenu.positionIndex < native_cap) {
			for (int i = 0; i < (sizeof(snag_data)/4);i++) {
				_map = snag_data[i].map;
				if (CurrentMap == _map) {
					if (map_snag_index++ == ActiveMenu.positionIndex) {
						list_index = i;
					}
				}
			}
		} else {
			int extra_count = 0;
			for (int i = 0; i < WatchCount; i++) {
				if (ViewedSnagWatches[i] > -1) {
					if (snag_data[(int)ViewedSnagWatches[i]].map != CurrentMap) {
						if (extra_count++ == (ActiveMenu.positionIndex - native_cap)) {
							list_index = ViewedSnagWatches[i];
						}
					}
				}
			}
		}
		i = 0;
		while (i < WatchCount) {
			if (ViewedSnagWatches[i] == list_index) {
				index_already_spawned = 1;
				break;
			}
			i++;
		}
		if (index_already_spawned) {
			WatchIndex[i] = 0;
			ViewedSnagWatches[i] = -1;
		} else {
			i = 0;
			checkWatchCapacity();
			while (i < WatchCount) {
				if (WatchIndex[i] == 0) {
					WatchIndex[i] = 15;
					ViewedSnagWatches[i] = list_index;
					dk_strFormat((char *)snagwatch_names_array[i],"%s",SnagCapitalsTable->actor_name[list_index]);
					colorWatch(0xFF,0xFF,0xFF,i);
					break;
				};
				i++;
			}
		}
		openWatchSnagMenu();
	} else {
		playSFX(Burp);
	}
}

static const int watch_snag_functions[] = {
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
	(int)&toggleSnagWatch,
};