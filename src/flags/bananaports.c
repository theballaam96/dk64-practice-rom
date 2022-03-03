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

static const short warpflags_japes[] = {
	FLAG_WARP_JAPES_W1_PORTAL,
	FLAG_WARP_JAPES_W1_FAR,
	FLAG_WARP_JAPES_W2_HIGH,
	FLAG_WARP_JAPES_W2_LOW,
	FLAG_WARP_JAPES_W3_RIGHT,
	FLAG_WARP_JAPES_W3_LEFT,
	FLAG_WARP_JAPES_W4_CLOSE,
	FLAG_WARP_JAPES_W4_CRANKY,
	FLAG_WARP_JAPES_W5_SHELLHIVE,
	FLAG_WARP_JAPES_W5_TOP,
};
static const short warpflags_aztec[] = {
	FLAG_WARP_AZTEC_W1_PORTAL,
	FLAG_WARP_AZTEC_W1_CANDY,
	FLAG_WARP_AZTEC_W2_TEMPLE,
	FLAG_WARP_AZTEC_W2_TOTEM,
	FLAG_WARP_AZTEC_W3_CRANKY,
	FLAG_WARP_AZTEC_W3_TOTEM,
	FLAG_WARP_AZTEC_W4_TOTEM,
	FLAG_WARP_AZTEC_W4_FUNKY,
	FLAG_WARP_AZTEC_W5_TOTEM,
	FLAG_WARP_AZTEC_W5_SNOOP,
	FLAG_WARP_LLAMA_W1_HIGH,
	FLAG_WARP_LLAMA_W1_LOW,
	FLAG_WARP_LLAMA_W2_FAR,
	FLAG_WARP_LLAMA_W2_LOW,
};
static const short warpflags_factory[] = {
	FLAG_WARP_FACTORY_W1_FOYER,
	FLAG_WARP_FACTORY_W1_STORAGE,
	FLAG_WARP_FACTORY_W2_FOYER,
	FLAG_WARP_FACTORY_W2_RND,
	FLAG_WARP_FACTORY_W3_FOYER,
	FLAG_WARP_FACTORY_W3_SNIDE,
	FLAG_WARP_FACTORY_W4_TOP,
	FLAG_WARP_FACTORY_W4_BOTTOM,
	FLAG_WARP_FACTORY_W5_FUNKY,
	FLAG_WARP_FACTORY_W5_ARCADE,
};
static const short warpflags_galleon[] = {
	FLAG_WARP_GALLEON_W1_LIGHTHOUSE,
	FLAG_WARP_GALLEON_W1_CRANKY,
	FLAG_WARP_GALLEON_W2_2DS,
	FLAG_WARP_GALLEON_W2_CRANKY,
	FLAG_WARP_GALLEON_W3_SNIDE,
	FLAG_WARP_GALLEON_W3_CRANKY,
	FLAG_WARP_GALLEON_W4_SEAL,
	FLAG_WARP_GALLEON_W4_TOWER,
	FLAG_WARP_GALLEON_W5_5DS,
	FLAG_WARP_GALLEON_W5_LIGHTHOUSE,
};
static const short warpflags_fungi[] = {
	FLAG_WARP_FUNGI_W1_MILL,
	FLAG_WARP_FUNGI_W1_CLOCK,
	FLAG_WARP_FUNGI_W2_CLOCK,
	FLAG_WARP_FUNGI_W2_FUNKY,
	FLAG_WARP_FUNGI_W3_CLOCK,
	FLAG_WARP_FUNGI_W3_MUSH,
	FLAG_WARP_FUNGI_W4_CLOCK,
	FLAG_WARP_FUNGI_W4_OWL,
	FLAG_WARP_FUNGI_W5_LOW,
	FLAG_WARP_FUNGI_W5_HIGH,
};
static const short warpflags_caves[] = {
	FLAG_WARP_CAVES_W1_5DI,
	FLAG_WARP_CAVES_W1_PORTAL,
	FLAG_WARP_CAVES_W2_PORTAL,
	FLAG_WARP_CAVES_W2_FAR,
	FLAG_WARP_CAVES_W3_5DI,
	FLAG_WARP_CAVES_W3_CAVERN,
	FLAG_WARP_CAVES_W4_FAR,
	FLAG_WARP_CAVES_W4_5DI,
	FLAG_WARP_CAVES_W5_5DC,
	FLAG_WARP_CAVES_W5_PILLAR,
};
static const short warpflags_castle[] = {
	FLAG_WARP_CASTLE_W1_HUB,
	FLAG_WARP_CASTLE_W1_FAR,
	FLAG_WARP_CASTLE_W2_HUB,
	FLAG_WARP_CASTLE_W2_HIGH,
	FLAG_WARP_CASTLE_W3_HUB,
	FLAG_WARP_CASTLE_W3_HIGH,
	FLAG_WARP_CASTLE_W4_HUB,
	FLAG_WARP_CASTLE_W4_HIGH,
	FLAG_WARP_CASTLE_W5_HUB,
	FLAG_WARP_CASTLE_W5_HIGH,
	FLAG_WARP_CRYPT_W1_CLOSE,
	FLAG_WARP_CRYPT_W1_FAR,
	FLAG_WARP_CRYPT_W2_CLOSE,
	FLAG_WARP_CRYPT_W2_FAR,
	FLAG_WARP_CRYPT_W3_CLOSE,
	FLAG_WARP_CRYPT_W3_FAR,
};
static const short warpflags_helm[] = {
	FLAG_WARP_HELM_W1_NEAR,
	FLAG_WARP_HELM_W1_FAR
};
static const short warpflags_isles[] = {
	FLAG_WARP_ISLES_W1_RING,
	FLAG_WARP_ISLES_W1_FAR,
	FLAG_WARP_ISLES_W2_RING,
	FLAG_WARP_ISLES_W2_FAR,
	FLAG_WARP_ISLES_W3_RING,
	FLAG_WARP_ISLES_W3_FAR,
	FLAG_WARP_ISLES_W4_RING,
	FLAG_WARP_ISLES_W4_HIGH,
	FLAG_WARP_ISLES_W5_RING,
	FLAG_WARP_ISLES_W5_FAR,
	FLAG_WARP_LOBBY_W1_NEAR,
	FLAG_WARP_LOBBY_W1_FAR,
};

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
	changeMenu(ACTIVEMENU_SCREEN_FLAG_BANANAPORTS);
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
	.ParentScreen = ACTIVEMENU_SCREEN_FLAG_ROOT,
	.ParentPosition = 9
};