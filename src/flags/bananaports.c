#include "../../include/common.h"

#define LEVEL_COUNT 9

static const char bports_japes_tagged[] = "} JAPES WARPS";
static const char bports_aztec_tagged[] = "} AZTEC WARPS";
static const char bports_factory_tagged[] = "} FACTORY WARPS";
static const char bports_galleon_tagged[] = "} GALLEON WARPS";
static const char bports_fungi_tagged[] = "} FUNGI WARPS";
static const char bports_caves_tagged[] = "} CAVES WARPS";
static const char bports_castle_tagged[] = "} CASTLE WARPS";
static const char bports_helm_tagged[] = "} HELM WARPS";
static const char bports_isles_tagged[] = "} ISLES WARPS";
static const char bports_all_tagged[] = "} ALL WARPS";

static const char bports_japes_clear[] = "{ JAPES WARPS";
static const char bports_aztec_clear[] = "{ AZTEC WARPS";
static const char bports_factory_clear[] = "{ FACTORY WARPS";
static const char bports_galleon_clear[] = "{ GALLEON WARPS";
static const char bports_fungi_clear[] = "{ FUNGI WARPS";
static const char bports_caves_clear[] = "{ CAVES WARPS";
static const char bports_castle_clear[] = "{ CASTLE WARPS";
static const char bports_helm_clear[] = "{ HELM WARPS";
static const char bports_isles_clear[] = "{ ISLES WARPS";
static const char bports_all_clear[] = "{ ALL WARPS";

static char level_warps[LEVEL_COUNT] = {};
static char all_tagged = 0;

static const short warpflags_japes[] = {0x20,0x21,0x23,0x22,0x25,0x24,0x28,0x29,0x26,0x27};
static const short warpflags_aztec[] = {0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x3E,0x59,0x58,0x5B,0x5A};
static const short warpflags_factory[] = {0x8D,0x8E,0x8F,0x90,0x91,0x92,0x94,0x93,0x96,0x95};
static const short warpflags_galleon[] = {0xB2,0xB1,0xAC,0xAB,0xAE,0xAD,0xAF,0xA3,0xA9,0xAA};
static const short warpflags_fungi[] = {0xEE,0xED,0xEF,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6};
static const short warpflags_caves[] = {0x11C,0x11B,0x11D,0x11E,0x123,0x127,0x120,0x11F,0x121,0x122};
static const short warpflags_castle[] = {0x147,0x148,0x149,0x14A,0x14B,0x14C,0x14D,0x14E,0x14F,0x150,0x151,0x152,0x153,0x154,0x155,0x156};
static const short warpflags_helm[] = {0x305,0x306};
static const short warpflags_isles[] = {0x1B1,0x1B2,0x1B3,0x1B4,0x1B5,0x1B6,0x1B7,0x1B8,0x1BA,0x1B9,0x1A1,0x1A2};

static const short* warpflags_list[LEVEL_COUNT] = {
	warpflags_japes,
	warpflags_aztec,
	warpflags_factory,
	warpflags_galleon,
	warpflags_fungi,
	warpflags_caves,
	warpflags_castle,
	warpflags_helm,
	warpflags_isles,
};

static const char warpflags_count[LEVEL_COUNT] = {
	10,14,10,10,10,10,16,2,12
};

static const char* bports_tagged[] = {
	bports_japes_tagged,
	bports_aztec_tagged,
	bports_factory_tagged,
	bports_galleon_tagged,
	bports_fungi_tagged,
	bports_caves_tagged,
	bports_castle_tagged,
	bports_helm_tagged,
	bports_isles_tagged,
	bports_all_tagged,
};

static const char* bports_clear[] = {
	bports_japes_clear,
	bports_aztec_clear,
	bports_factory_clear,
	bports_galleon_clear,
	bports_fungi_clear,
	bports_caves_clear,
	bports_castle_clear,
	bports_helm_clear,
	bports_isles_clear,
	bports_all_clear,
};

static const char* bports_array[] = {
	bports_japes_clear,
	bports_aztec_clear,
	bports_factory_clear,
	bports_galleon_clear,
	bports_fungi_clear,
	bports_caves_clear,
	bports_castle_clear,
	bports_helm_clear,
	bports_isles_clear,
	bports_all_clear,
};

void openBPortsMenu(void) {
	int all_set = 1;
	int level_set = 1;
	for (int i = 0; i < LEVEL_COUNT; i++) {
		int count = warpflags_count[i];
		level_set = 1;
		for (int j = 0; j < count; j++) {
			int warp_set = checkFlag(warpflags_list[i][j],0);
			level_set &= warp_set;
			all_set &= warp_set;
		}
		level_warps[i] = level_set;
		if (level_warps[i]) {
			bports_array[i] = bports_tagged[i];
		} else {
			bports_array[i] = bports_clear[i];
		}
	}
	all_tagged = all_set;
	if (all_tagged) {
		bports_array[9] = bports_tagged[9];
	} else {
		bports_array[9] = bports_clear[9];
	}
	changeMenu(102);
}

void toggleWarpLevel(int idx, int use_all_set) {
	int count = warpflags_count[idx];
	int dest = 1 ^ level_warps[idx];
	if (use_all_set) {
		dest = 1 ^ all_tagged;
	}
	for (int i = 0; i < count; i++) {
		setFlag(warpflags_list[idx][i],dest,0);
	}
}

void toggleLevelWarps(void) {
	int pos = ActiveMenu.positionIndex;
	toggleWarpLevel(pos,0);
	openBPortsMenu();
}

void toggleAllWarps(void) {
	for (int i = 0; i < LEVEL_COUNT; i++) {
		toggleWarpLevel(i,1);
	}
	openBPortsMenu();
}

static const int bports_functions[] = {
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleLevelWarps,
	(int)&toggleAllWarps,
};

const Screen bports_struct = {
	.TextArray = (int*)bports_array,
	.FunctionArray = bports_functions,
	.ArrayItems = 10,
	.ParentScreen = 43,
	.ParentPosition = 9
};