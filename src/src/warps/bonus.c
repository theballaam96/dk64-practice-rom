#include "../../include/common.h"

static const char mapBonusBBBandit[] = "Batty Barrel Bandit";
static const char mapBonusBBother[] = "Beaver Bother";
static const char mapBonusBBotherTower[] = "Beaver Bother (Tower)";
static const char mapBonusBBotherTree[] = "Beaver Bother (Tree)";
static const char mapBonusBBBash[] = "Big Bug Bash";
static const char mapBonusBBBarrage[] = "Busy Barrel Barrage";
static const char mapBonusMMMaul[] = "Mad Maze Maul";
static const char mapBonusKrazyKK[] = "Krazy Kong Klamour";
static const char mapBonusKKosh[] = "Kremling Kosh";
static const char mapBonusMMayhem[] = "Minecart Mayhem";
static const char mapBonusPPPanic[] = "Peril Path Panic";
static const char mapBonusSSeek[] = "Searchlight Seek";
static const char mapBonusSSSortie[] = "Speedy Swing Sortie";
static const char mapBonusSSSalvage[] = "Splish Splash Salvage";
static const char mapBonusSSnatch[] = "Stash Snatch";
static const char mapBonusSSnoop[] = "Stealthy Snoop";
static const char mapBonusTTTrouble[] = "Teetering Turtle Trouble";

static const char mapBonusDKTarget[] = "DK Target Game";
static const char mapBonusDKRambi[] = "DK Rambi Game";
static const char mapBonusDiddyKremling[] = "Diddy Kremling Game";
static const char mapBonusDiddyRocketbarrel[] = "Diddy Rocketbarrel Game";
static const char mapBonusLankyMaze[] = "Lanky Maze Game";
static const char mapBonusLankyShooting[] = "Lanky Shooting Game";
static const char mapBonusTinyPTT[] = "Tiny PTT Game";
static const char mapBonusTinyMushroom[] = "Tiny Mushroom Game";
static const char mapBonusChunkyHiddenKremling[] = "Chunky Hidden Kremling Game";
static const char mapBonusChunkyShooting[] = "Chunky Shooting Game";

static const char mapBonusJapes[] = "Japes Barrels";
static const char mapBonusAztec[] = "Aztec Barrels";
static const char mapBonusFactory[] = "Factory Barrels";
static const char mapBonusGalleon[] = "Galleon Barrels";
static const char mapBonusFungi[] = "Fungi Barrels";
static const char mapBonusCaves[] = "Caves Barrels";
static const char mapBonusCastle[] = "Castle Barrels";
static const char mapBonusHelm[] = "Helm Barrels";
static const char mapBonusIsles[] = "Isles Barrels";


void openBonusMainMenu(void) {
	changeMenu(90);
}

void openBonusJapesMenu(void) {
	changeMenu(91);
}

void openBonusAztecMenu(void) {
	changeMenu(92);
}

void openBonusFactoryMenu(void) {
	changeMenu(93);
}

void openBonusGalleonMenu(void) {
	changeMenu(94);
}

void openBonusFungiMenu(void) {
	changeMenu(95);
}

void openBonusCavesMenu(void) {
	changeMenu(96);
}

void openBonusCastleMenu(void) {
	changeMenu(97);
}

void openBonusHelmMenu(void) {
	changeMenu(98);
}

void openBonusIslesMenu(void) {
	changeMenu(99);
}

static const char* bonusmain_mapwarp_array[] = {
	mapBonusJapes,
	mapBonusAztec,
	mapBonusFactory,
	mapBonusGalleon,
	mapBonusFungi,
	mapBonusCaves,
	mapBonusCastle,
	mapBonusHelm,
	mapBonusIsles,
};

static const int bonusmain_mapwarp_functions[] = {
	(int)&openBonusJapesMenu,
	(int)&openBonusAztecMenu,
	(int)&openBonusFactoryMenu,
	(int)&openBonusGalleonMenu,
	(int)&openBonusFungiMenu,
	(int)&openBonusCavesMenu,
	(int)&openBonusCastleMenu,
	(int)&openBonusHelmMenu,
	(int)&openBonusIslesMenu
};

const Screen bonusmain_mapwarp_struct = {
	.TextArray = (int*)bonusmain_mapwarp_array,
	.FunctionArray = bonusmain_mapwarp_functions,
	.ArrayItems = 9,
	.ParentScreen = 1,
	.ParentPosition = 10
};

///////////
// JAPES //
///////////

static const unsigned char bonusjapes_destmap[] = {
	68, // Mad Maze Maul
	77, // Minecart Mayhem
	99, // Speedy Swing Sortie
	96, // Splish Splash Salvage
};

static const unsigned char bonusjapes_destexit[] = {
	0, // Mad Maze Maul
	0, // Minecart Mayhem
	0, // Speedy Swing Sortie
	0, // Splish Splash Salvage
};

const MapWarp map_bonusjapes_struct = {
	.maps = bonusjapes_destmap,
	.exits = bonusjapes_destexit,
	.screen = 91
};

static const char* bonusjapes_mapwarp_array[] = {
	mapBonusMMMaul,
	mapBonusMMayhem,
	mapBonusSSSortie,
	mapBonusSSSalvage,
};

static const int bonusjapes_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonusjapes_mapwarp_struct = {
	.TextArray = (int*)bonusjapes_mapwarp_array,
	.FunctionArray = bonusjapes_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = 90,
	.ParentPosition = 0
};

///////////
// AZTEC //
///////////

static const unsigned char bonusaztec_destmap[] = {
	102, // Big Bug Bash
	78, // Busy Barrel Barrage
	10, // Kremling Kosh
	126, // Stealthy Snoop
	18, // Teetering Turtle Trouble
};

static const unsigned char bonusaztec_destexit[] = {
	0, // Big Bug Bash
	0, // Busy Barrel Barrage
	0, // Kremling Kosh
	0, // Stealthy Snoop
	0, // Teetering Turtle Trouble
};

const MapWarp map_bonusaztec_struct = {
	.maps = bonusaztec_destmap,
	.exits = bonusaztec_destexit,
	.screen = 92
};

static const char* bonusaztec_mapwarp_array[] = {
	mapBonusBBBash,
	mapBonusBBBarrage,
	mapBonusKKosh,
	mapBonusSSnoop,
	mapBonusTTTrouble,
};

static const int bonusaztec_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonusaztec_mapwarp_struct = {
	.TextArray = (int*)bonusaztec_mapwarp_array,
	.FunctionArray = bonusaztec_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = 90,
	.ParentPosition = 1
};

/////////////
// FACTORY //
/////////////

static const unsigned char bonusfactory_destmap[] = {
	32, // Batty Barrel Bandit
	104, // Beaver Bother
	101, // Krazy Kong Klamour
	144, // Peril Path Panic
	74, // Stash Snatch
};

static const unsigned char bonusfactory_destexit[] = {
	0, // Batty Barrel Bandit
	0, // Beaver Bother
	0, // Krazy Kong Klamour
	0, // Peril Path Panic
	0, // Stash Snatch
};

const MapWarp map_bonusfactory_struct = {
	.maps = bonusfactory_destmap,
	.exits = bonusfactory_destexit,
	.screen = 93
};

static const char* bonusfactory_mapwarp_array[] = {
	mapBonusBBBandit,
	mapBonusBBother,
	mapBonusKrazyKK,
	mapBonusPPPanic,
	mapBonusSSnatch,	
};

static const int bonusfactory_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonusfactory_mapwarp_struct = {
	.TextArray = (int*)bonusfactory_mapwarp_array,
	.FunctionArray = bonusfactory_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = 90,
	.ParentPosition = 2
};

/////////////
// GALLEON //
/////////////

static const unsigned char bonusgalleon_destmap[] = {
	121, // Batty BB
	148, // BBBash
	141, // Krazy KK
	115, // KKosh
	103, // SSeek
	133, // SSSalvage
	65, // SSnoop
};

static const unsigned char bonusgalleon_destexit[] = {
	0, // Batty BB
	0, // BBBash
	0, // Krazy KK
	0, // KKosh
	0, // SSeek
	0, // SSSalvage
	0, // SSnoop
};

const MapWarp map_bonusgalleon_struct = {
	.maps = bonusgalleon_destmap,
	.exits = bonusgalleon_destexit,
	.screen = 94
};

static const char* bonusgalleon_mapwarp_array[] = {
	mapBonusBBBandit,
	mapBonusBBBash,
	mapBonusKrazyKK,
	mapBonusKKosh,
	mapBonusSSeek,
	mapBonusSSSalvage,
	mapBonusSSnoop,	
};

static const int bonusgalleon_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonusgalleon_mapwarp_struct = {
	.TextArray = (int*)bonusgalleon_mapwarp_array,
	.FunctionArray = bonusgalleon_mapwarp_functions,
	.ArrayItems = 7,
	.ParentScreen = 90,
	.ParentPosition = 3
};

///////////
// FUNGI //
///////////

static const unsigned char bonusfungi_destmap[] = {
	79, // BBBarrage
	142, // Krazy KK
	129, // MMayhem
	145, // PPPanic
	134, // SSSortie
	118, // TTTrouble
};

static const unsigned char bonusfungi_destexit[] = {
	0, // BBBarrage
	0, // Krazy KK
	0, // MMayhem
	0, // PPPanic
	0, // SSSortie
	0, // TTTrouble
};

const MapWarp map_bonusfungi_struct = {
	.maps = bonusfungi_destmap,
	.exits = bonusfungi_destexit,
	.screen = 95
};

static const char* bonusfungi_mapwarp_array[] = {
	mapBonusBBBarrage,
	mapBonusKrazyKK,
	mapBonusMMayhem,
	mapBonusPPPanic,
	mapBonusSSSortie,
	mapBonusTTTrouble,
};

static const int bonusfungi_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonusfungi_mapwarp_struct = {
	.TextArray = (int*)bonusfungi_mapwarp_array,
	.FunctionArray = bonusfungi_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = 90,
	.ParentPosition = 4
};

///////////
// CAVES //
///////////

static const unsigned char bonuscaves_destmap[] = {
	131, // BBBarrage
	142, // Krazy KK
	69, // MMMaul
	139, // SSeek
};

static const unsigned char bonuscaves_destexit[] = {
	0, // BBBarrage
	0, // Krazy KK
	0, // MMMaul
	0, // SSeek
};

const MapWarp map_bonuscaves_struct = {
	.maps = bonuscaves_destmap,
	.exits = bonuscaves_destexit,
	.screen = 96
};

static const char* bonuscaves_mapwarp_array[] = {
	mapBonusBBBarrage,
	mapBonusKrazyKK,
	mapBonusMMMaul,
	mapBonusSSeek,
};

static const int bonuscaves_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonuscaves_mapwarp_struct = {
	.TextArray = (int*)bonuscaves_mapwarp_array,
	.FunctionArray = bonuscaves_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = 90,
	.ParentPosition = 5
};

////////////
// CASTLE //
////////////

static const unsigned char bonuscastle_destmap[] = {
	136, // BBother (Tower)
	136, // BBother (Tree)
	150, // BBBash
	116, // KKosh
	130, // MMayhem
	140, // SSeek
	119, // TTTrouble
};

static const unsigned char bonuscastle_destexit[] = {
	0, // BBother (Tower)
	0, // BBother (Tree)
	0, // BBBash
	0, // KKosh
	0, // MMayhem
	0, // SSeek
	0, // TTTrouble
};

const MapWarp map_bonuscastle_struct = {
	.maps = bonuscastle_destmap,
	.exits = bonuscastle_destexit,
	.screen = 97
};

static const char* bonuscastle_mapwarp_array[] = {
	mapBonusBBotherTower,
	mapBonusBBotherTree,
	mapBonusBBBash,
	mapBonusKKosh,
	mapBonusMMayhem,
	mapBonusSSeek,
	mapBonusTTTrouble,
};

static const int bonuscastle_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonuscastle_mapwarp_struct = {
	.TextArray = (int*)bonuscastle_mapwarp_array,
	.FunctionArray = bonuscastle_mapwarp_functions,
	.ArrayItems = 7,
	.ParentScreen = 90,
	.ParentPosition = 6
};

//////////
// HELM //
//////////

static const unsigned char bonushelm_destmap[] = {
	212, // DK Rambi
	35, // DK Target
	165, // Diddy Kremling
	201, // Diddy RBarrel
	3, // Lanky Maze
	202, // Lanky Shoot
	50, // Tiny Mush
	210, // Tiny PTT
	209, // Chunky Hidden
	211, // Chunky Shoot
};

static const unsigned char bonushelm_destexit[] = {
	0, // DK Rambi
	0, // DK Target
	0, // Diddy Kremling
	0, // Diddy RBarrel
	0, // Lanky Maze
	0, // Lanky Shoot
	0, // Tiny Mush
	0, // Tiny PTT
	0, // Chunky Hidden
	0, // Chunky Shoot
};

const MapWarp map_bonushelm_struct = {
	.maps = bonushelm_destmap,
	.exits = bonushelm_destexit,
	.screen = 98
};

static const char* bonushelm_mapwarp_array[] = {
	mapBonusDKRambi,
	mapBonusDKTarget,
	mapBonusDiddyKremling,
	mapBonusDiddyRocketbarrel,
	mapBonusLankyMaze,
	mapBonusLankyShooting,
	mapBonusTinyMushroom,
	mapBonusTinyPTT,
	mapBonusChunkyHiddenKremling,
	mapBonusChunkyShooting,
};

static const int bonushelm_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonushelm_mapwarp_struct = {
	.TextArray = (int*)bonushelm_mapwarp_array,
	.FunctionArray = bonushelm_mapwarp_functions,
	.ArrayItems = 10,
	.ParentScreen = 90,
	.ParentPosition = 7
};

///////////
// ISLES //
///////////

static const unsigned char bonusisles_destmap[] = {
	122, // BBBandit
	149, // BBBash
	117, // KKosh
	146, // PPPanic
	140, // SSeek
};

static const unsigned char bonusisles_destexit[] = {
	0, // BBBandit
	0, // BBBash
	0, // KKosh
	0, // PPPanic
	0, // SSeek
};

const MapWarp map_bonusisles_struct = {
	.maps = bonusisles_destmap,
	.exits = bonusisles_destexit,
	.screen = 99
};

static const char* bonusisles_mapwarp_array[] = {
	mapBonusBBBandit,
	mapBonusBBBash,
	mapBonusKKosh,
	mapBonusPPPanic,
	mapBonusSSeek,
};

static const int bonusisles_mapwarp_functions[] = {
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
	(int)&warpToMap,
};

const Screen bonusisles_mapwarp_struct = {
	.TextArray = (int*)bonusisles_mapwarp_array,
	.FunctionArray = bonusisles_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = 90,
	.ParentPosition = 8
};