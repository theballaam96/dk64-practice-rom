#include "../../include/common.h"

static const unsigned int snag_data[] = {
	0x00070052, // Diddy Mountain
	0x00070048, // Free Diddy
	0x00260026, // Free Llama
	0x002600A3, // Gong Tower
	0x00260023, // Vase
	0x002600EB, // Vulture Race
	0x0010007E, // Tiny Temple
	0x001A0108, // Arcade R1
	0x001A0029, // Chunky Prod
	0x001A007C, // Chunky R&D
	0x001A0082, // Dartboard
	0x001A002C, // Diddy Prod
	0x001A0060, // Diddy R&D
	0x001A0078, // Free Chunky
	0x001A007E, // Numbers Game
	0x001A003E, // Piano Game
	0x001D0002, // Power Shed
	0x001E0032, // Cannon Game
	0x001E000E, // Chests
	0x001E002D, // Diddy Ship
	0x001E006B, // Enguarde Chest
	0x001E002E, // Free Seal
	0x0031002F, // Lighthouse
	0x0033000F, // Mech Fish
	0x002D000E, // Mermaid
	0x0030003E, // Apple GB
	0x00300039, // Fungi BBlast GB
	0x0030002B, // Mill GB
	0x00300057, // Rabbit Race
	0x00400003, // Mush Cannons
	0x003A0002, // Lanky Attic
	0x00340000, // Anthill
	0x003D000D, // Kegs GB
	0x00470002, // Fungi Face Puzzle
	0x00480032, // Caves BBlast GB
	0x0048003E, // Caves GGone
	0x005C0001, // Diddy Enemies 5DC
	0x00640001, // Diddy 5DI
	0x00620010, // Ice Tomato
	0x005E0001, // Sprint Cabin
	0x005F0000, // Chunky 5DI
	0x00A3000F, // DK Dungeon
	0x00700008, // Diddy Crypt
	0x00A80001, // Greenhouse GB
	0x00A70004, // Trash Can
	0x00A60006, // Shed
	0x00220004, // Japes Rock
	0x00220056, // Big X
	0x0011005D, // DK Helm Medal
	0x00110061, // Diddy Helm Medal
	0x0011005F, // Lanky Helm Medal
	0x00110060, // Tiny Helm Medal
	0x0011005E, // Chunky Helm Medal
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
};

static const int watch_snag_functions[9];

Screen watch_snag_struct = {
	.TextArray = (int*)watch_snag_array,
	.FunctionArray = watch_snag_functions,
	.ArrayItems = 4,
	.ParentScreen = 0,
	.ParentPosition = 3
};

void openWatchSnagMenu(void) {
	unsigned char _map;
	char snag_counter = 0;
	for (int i = 0; i < (sizeof(snag_data) / 4); i++) {
		_map = (snag_data[i]>>16) & 0xFF;
		if (CurrentMap == _map) {
			// Listing is in map
			//dk_strFormat((char *)watch_snag_array[snag_counter],"%2d: 0x%4X: %d",i + startingActorIndex,actorAddr, actorType);
		}
	}
	changeMenu(82);
}

void toggleSnagWatch(void) {

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
};