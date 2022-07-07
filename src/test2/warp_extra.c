#include "include/common.h"

static char warp_loadmapvars = 0;

typedef struct map_fromexit_data {
	/* 0x000 */ unsigned char dest_map;
	/* 0x001 */ unsigned char level_map;
	/* 0x002 */ unsigned char level_exit;
} map_fromexit_data;

typedef struct map_frompos_data {
	/* 0x000 */ unsigned char dest_map;
	/* 0x001 */ unsigned char level_map;
	/* 0x002 */ short x;
	/* 0x004 */ short y;
	/* 0x006 */ short z;
} map_frompos_data;

static char first_state = 0;
static char eightbit_state = 0;

static const map_fromexit_data bosses[7] = {
	{
		.dest_map = 0x8,
		.level_map = 0x7,
		.level_exit = 0xA,
	},
	{
		.dest_map = 0xC5,
		.level_map = 0x26,
		.level_exit = 12,
	},
	{
		.dest_map = 0x9A,
		.level_map = 0x1A,
		.level_exit = 0xB,
	},
	{
		.dest_map = 0x6F,
		.level_map = 0x1E,
		.level_exit = 20,
	},
	{
		.dest_map = 0x53,
		.level_map = 0x30,
		.level_exit = 24,	
	},
	{
		.dest_map = 0xC4,
		.level_map = 0x48,
		.level_exit = 24,
	},
	{
		.dest_map = 0xC7,
		.level_map = 0x57,
		.level_exit = 0x3,
	}

};

static const map_frompos_data crowns[10] = {
	{
		// Japes
		.dest_map = 0x35,
		.level_map = 0x7,
		.x = 1990,
		.y = 528,
		.z = 2087,
	},
	{
		// Aztec
		.dest_map = 0x49,
		.level_map = 0x10,
		.x = 1446,
		.y = 317,
		.z = 2331,
	},
	{
		// Factory
		.dest_map = 0x9B,
		.level_map = 0x1A,
		.x = 4119,
		.y = 1323,
		.z = 1165,
	},
	{
		// Galleon
		.dest_map = 0x9C,
		.level_map = 0x1E,
		.x = 3297,
		.y = 1679,
		.z = 2450,
	},
	{
		// Fungi
		.dest_map = 0x9F,
		.level_map = 0x30,
		.x = 1256,
		.y = 1087,
		.z = 1317,
	},
	{
		// Caves
		.dest_map = 0xA0,
		.level_map = 0x59,
		.x = 327,
		.y = 125,
		.z = 434,
	},
	{
		// Castle
		.dest_map = 0xA1,
		.level_map = 0xA8,
		.x = 503,
		.y = 10,
		.z = 581,
	},
	{
		// Helm
		.dest_map = 0xA2,
		.level_map = 0x11,
		.x = 1047,
		.y = 452,
		.z = 3391,
	},
	{
		// Snide's Room
		.dest_map = 0x9E,
		.level_map = 0xC3,
		.x = 361,
		.y = 7,
		.z = 278,
	},
	{
		// Fungi Lobby
		.dest_map = 0x9D,
		.level_map = 0xB2,
		.x = 291,
		.y = 30,
		.z = 637,
	}
};

static const map_frompos_data barrels[57] = {
	{
		.dest_map = 99,
		.level_map = 7,
		.x = 1838,
		.y = 384,
		.z = 2441,
	},
	{
		.dest_map = 77,
		.level_map = 7,
		.x = 2272,
		.y = 700,
		.z = 3181,
	},
	{
		.dest_map = 68,
		.level_map = 7,
		.x = 2782,
		.y = 320,
		.z = 507,
	},
	{
		.dest_map = 96,
		.level_map = 7,
		.x = 2486,
		.y = 316,
		.z = 224,
	},
	{
		.dest_map = 201,
		.level_map = 17,
		.x = 473,
		.y = 268,
		.z = 2620,
	},
	{
		.dest_map = 165,
		.level_map = 17,
		.x = 280,
		.y = 268,
		.z = 2838,
	},
	{
		.dest_map = 202,
		.level_map = 17,
		.x = 1989,
		.y = 105,
		.z = 3531,
	},
	{
		.dest_map = 3,
		.level_map = 17,
		.x = 1988,
		.y = 105,
		.z = 3242,
	},
	{
		.dest_map = 212,
		.level_map = 17,
		.x = 280,
		.y = -71,
		.z = 3941,
	},
	{
		.dest_map = 35,
		.level_map = 17,
		.x = 480,
		.y = -71,
		.z = 4149,
	},
	{
		.dest_map = 50,
		.level_map = 17,
		.x = 118,
		.y = 26,
		.z = 3245,
	},
	{
		.dest_map = 210,
		.level_map = 17,
		.x = 112,
		.y = 26,
		.z = 3545,
	},
	{
		.dest_map = 209,
		.level_map = 17,
		.x = 1609,
		.y = -11,
		.z = 2619,
	},
	{
		.dest_map = 211,
		.level_map = 17,
		.x = 1819,
		.y = -11,
		.z = 2826,
	},
	{
		.dest_map = 18,
		.level_map = 20,
		.x = 2216,
		.y = 560,
		.z = 2420,
	},
	{
		.dest_map = 102,
		.level_map = 23,
		.x = 154,
		.y = 164,
		.z = 912,
	},
	{
		.dest_map = 10,
		.level_map = 24,
		.x = 100,
		.y = 210,
		.z = 2108,
	},
	{
		.dest_map = 104,
		.level_map = 26,
		.x = 1174,
		.y = 166,
		.z = 841,
	},
	{
		.dest_map = 144,
		.level_map = 26,
		.x = 2416,
		.y = 1629,
		.z = 1297,
	},
	{
		.dest_map = 74,
		.level_map = 26,
		.x = 1267,
		.y = 1152,
		.z = 1819,
	},
	{
		.dest_map = 32,
		.level_map = 26,
		.x = 2749,
		.y = 1185,
		.z = 1130,
	},
	{
		.dest_map = 101,
		.level_map = 26,
		.x = 259,
		.y = 896,
		.z = 1443,
	},
	{
		.dest_map = 103,
		.level_map = 30,
		.x = 1599,
		.y = 2105,
		.z = 531,
	},
	{
		.dest_map = 65,
		.level_map = 30,
		.x = 2127,
		.y = 2051,
		.z = 840,
	},
	{
		.dest_map = 146,
		.level_map = 34,
		.x = 2850,
		.y = 1870,
		.z = 1821,
	},
	{
		.dest_map = 78,
		.level_map = 38,
		.x = 4243,
		.y = 169,
		.z = 2407,
	},
	{
		.dest_map = 126,
		.level_map = 38,
		.x = 2722,
		.y = 180,
		.z = 4752,
	},
	{
		.dest_map = 133,
		.level_map = 43,
		.x = 1336,
		.y = 69,
		.z = 1159,
	},
	{
		.dest_map = 121,
		.level_map = 43,
		.x = 1175,
		.y = 96,
		.z = 1281,
	},
	{
		.dest_map = 141,
		.level_map = 46,
		.x = 1078,
		.y = 75,
		.z = 560,
	},
	{
		.dest_map = 115,
		.level_map = 47,
		.x = 968,
		.y = 81,
		.z = 708,
	},
	{
		.dest_map = 79,
		.level_map = 48,
		.x = 1269, // 1281
		.y = 620, // 597
		.z = 3902, // 3841
	},
	{
		.dest_map = 118,
		.level_map = 48,
		.x = 909,
		.y = 1620,
		.z = 1021,
	},
	{
		.dest_map = 129,
		.level_map = 59,
		.x = 324,
		.y = 180,
		.z = 586,
	},
	{
		.dest_map = 142,
		.level_map = 63,
		.x = 274,
		.y = 40,
		.z = 316,
	},
	{
		.dest_map = 134,
		.level_map = 64,
		.x = 350,
		.y = 436,
		.z = 217,
	},
	{
		.dest_map = 142,
		.level_map = 72,
		.x = 452,
		.y = 222,
		.z = 2480,
	},
	{
		.dest_map = 69,
		.level_map = 72,
		.x = 3032,
		.y = 362,
		.z = 1369,
	},
	{
		.dest_map = 150,
		.level_map = 87,
		.x = 1557,
		.y = 2075,
		.z = 1322,
	},
	{
		.dest_map = 130,
		.level_map = 88,
		.x = 556,
		.y = 229,
		.z = 839,
	},
	{
		.dest_map = 139,
		.level_map = 90,
		.x = 294,
		.y = 56,
		.z = 337,
	},
	{
		.dest_map = 136,
		.level_map = 105,
		.x = 403,
		.y = 701,
		.z = 403,
	},
	{
		.dest_map = 140,
		.level_map = 112,
		.x = 732,
		.y = 213,
		.z = 2756,
	},
	{
		.dest_map = 119,
		.level_map = 151,
		.x = 1126,
		.y = 245,
		.z = 851,
	},
	{
		.dest_map = 116,
		.level_map = 163,
		.x = 543,
		.y = 148,
		.z = 186,
	},
	{
		.dest_map = 136,
		.level_map = 164,
		.x = 1806,
		.y = 380,
		.z = 324,
	},
	{
		.dest_map = 117,
		.level_map = 170,
		.x = 686,
		.y = 250,
		.z = 657,
	},
	{
		.dest_map = 149,
		.level_map = 173,
		.x = 497,
		.y = -32,
		.z = 388,
	},
	{
		.dest_map = 180,
		.level_map = 176,
		.x = 720,
		.y = 114,
		.z = 730,
	},
	{
		.dest_map = 177,
		.level_map = 176,
		.x = 821,
		.y = 114,
		.z = 821,
	},
	{
		.dest_map = 181,
		.level_map = 176,
		.x = 841,
		.y = 114,
		.z = 607,
	},
	{
		.dest_map = 182,
		.level_map = 176,
		.x = 941,
		.y = 114,
		.z = 732,
	},
	{
		.dest_map = 148,
		.level_map = 179,
		.x = 371,
		.y = 131,
		.z = 757,
	},
	{
		.dest_map = 131,
		.level_map = 186,
		.x = 735,
		.y = 1104,
		.z = 1813,
	},
	{
		.dest_map = 145,
		.level_map = 188,
		.x = 1269,
		.y = 665,
		.z = 1298,
	},
	{
		.dest_map = 140,
		.level_map = 193,
		.x = 577,
		.y = 296,
		.z = 672,
	},
	{
		.dest_map = 122,
		.level_map = 195,
		.x = 573,
		.y = 140,
		.z = 224,
	}
};

void setDataStates(int state, int eightbit) {
	first_state = state;
	eightbit_state = eightbit;
}

void handleMapWarping(int map, int exit, int levelIndex, load_modes load_mode) {
	// Fixes some minor bugs with the following map categories
		// Crowns
		// Barrel Minigames
		// Arcade
		// Jetpac
		// Shops
		// T&S
	int boss_index = -1;
	int crown_index = -1;
	int barrel_index = -1;
	warp_loadmapvars = 0;
	for (int i = 0; i < 7; i++) {
		if (bosses[i].dest_map == map) {
			boss_index = i;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (crowns[i].dest_map == map) {
			crown_index = i;
		}
	}
	for (int i = 0; i < 57; i++) {
		if (barrels[i].dest_map == map) {
			if (first_state == 0) {
				barrel_index = i;
			} else if (barrel_index == -1) {
				barrel_index = i;
			}
		}
	}
	if (load_mode == MAPWARP) {
		if (eightbit_state == 1) { // Arcade
			setFlag(FLAG_STORY_ARCADE,1,2);
			initiateTransition_0(map,exit,0xA,0x2);
			parentData[0].in_submap |= 2;
			parentData[0].transition_properties_bitfield = 3;
			parentData[0].positions.xPos = 1862.0f;
			parentData[0].positions.yPos = 1107.0f;
			parentData[0].positions.zPos = 1305.0f;
			parentData[0].map = 0x1A;
			parentData[0].exit = 0;
		} else if (eightbit_state == 2) { // Jetpac
			setFlag(FLAG_STORY_JETPAC,1,2);
			initiateTransition_0(map,exit,0xA,0x2);
			parentData[0].in_submap |= 2;
			parentData[0].transition_properties_bitfield = 2;
			parentData[0].map = 0x57;
			parentData[0].exit = 0x12;
		} else if (eightbit_state == 3) {
			setFlag(FLAG_STORY_ARCADE,0,2);
			initiateTransition(map,exit);
		} else if (eightbit_state == 4) {
			setFlag(FLAG_STORY_JETPAC,0,2);
			initiateTransition(map,exit);
		} else {
			if ((boss_index > -1)) {
				initiateTransition_0(map,exit,0xA,0x2);
				parentData[0].in_submap |= 2;
				parentData[0].transition_properties_bitfield = 2;
				parentData[0].map = bosses[boss_index].level_map;
				parentData[0].exit = bosses[boss_index].level_exit;
			} else if (crown_index > -1) {
				initiateTransition_0(map,exit,0xA,0x2);
				parentData[0].in_submap |= 2;
				parentData[0].transition_properties_bitfield = 3;
				parentData[0].positions.xPos = crowns[crown_index].x;
				parentData[0].positions.yPos = crowns[crown_index].y;
				parentData[0].positions.zPos = crowns[crown_index].z;
				parentData[0].map = crowns[crown_index].level_map;
				parentData[0].exit = 0;
			} else if (barrel_index > -1) {
				initiateTransition_0(map,exit,0,2);
				parentData[0].in_submap |= 2;
				parentData[0].transition_properties_bitfield = 3;
				parentData[0].positions.xPos = barrels[barrel_index].x;
				parentData[0].positions.yPos = barrels[barrel_index].y - 40;
				parentData[0].positions.zPos = barrels[barrel_index].z;
				parentData[0].map = barrels[barrel_index].level_map;
				parentData[0].exit = 0;
			} else {
				initiateTransition(map,exit);
				warp_loadmapvars |= 1;
			}
		}
		eightbit_state = 0;
	} else if (load_mode == SAVESTATE) {
		if (barrel_index > -1) {
			initiateTransition_0(map,exit,0,2);
		} else {
			initiateTransition_0(map,exit,0xA,0x2);
		}
	}
}

void loadMapVars_0(void) {

	if ((ObjectModel2Timer == 20) && (TransitionSpeed < 0) && (warp_loadmapvars & 1)) {
		// if (IsAutowalking) {
		// 	if ((AutowalkPointer) && isRDRAM(AutowalkPointer)) {
		// 		AutowalkPointer->xPos = (short)Player->xPos;
		// 		AutowalkPointer->zPos = (short)Player->zPos;
		// 	}
		// }
		warp_loadmapvars &= 0xFE;
	}
}