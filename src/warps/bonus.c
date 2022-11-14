#include "../../include/common.h"

static const char mapBonusBBBandit[] = "BATTY BARREL BANDIT";
static const char mapBonusBBother[] = "BEAVER BOTHER";
static const char mapBonusBBotherTower[] = "BEAVER BOTHER <TOWER>";
static const char mapBonusBBotherTree[] = "BEAVER BOTHER <TREE>";
static const char mapBonusBBBash[] = "BIG BUG BASH";
static const char mapBonusBBBarrage[] = "BUSY BARREL BARRAGE";
static const char mapBonusMMMaul[] = "MAD MAZE MAUL";
static const char mapBonusKrazyKK[] = "KRAZY KONG KLAMOUR";
static const char mapBonusKKosh[] = "KREMLING KOSH";
static const char mapBonusMMayhem[] = "MINECART MAYHEM";
static const char mapBonusPPPanic[] = "PERIL PATH PANIC";
static const char mapBonusSSeek[] = "SEARCHLIGHT SEEK";
static const char mapBonusSSSortie[] = "SPEEDY SWING SORTIE";
static const char mapBonusSSSalvage[] = "SPLISH SPLASH SALVAGE";
static const char mapBonusSSnatch[] = "STASH SNATCH";
static const char mapBonusSSnoop[] = "STEALTHY SNOOP";
static const char mapBonusTTTrouble[] = "TEETERING TURTLE TROUBLE";

static const char mapBonusMMMaulHard[] = "MAD MAZE MAUL <120 SECONDS>";
static const char mapBonusMMMaulInsane[] = "MAD MAZE MAUL <125 SECONDS>";
static const char mapBonusSSnatchNormal[] = "STASH SNATCH <16 COINS>";
static const char mapBonusSSnatchHard[] = "STASH SNATCH <4 COINS>";
static const char mapBonusSSnatchInsane[] = "STASH SNATCH <33 COINS>";
static const char mapBonusSSSortieHard[] = "SPEEDY SWING SORTIE <ZINGERS>";
static const char mapBonusSSSalvageHard[] = "SPLISH SPLASH SALVAGE <15 COINS>";
static const char mapBonusSSnoopEasy[] = "STEALTHY SNOOP <60 SECONDS>";
static const char mapBonusSSnoopHard[] = "STEALTHY SNOOP <90 SECONDS>";
static const char mapBonusPPPanicHard[] = "PERIL PATH PANIC <12 FAIRIES>";

void openBonusMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_ROOT);
}

void openBonusJapesMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_JAPES);
}

void openBonusAztecMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_AZTEC);
}

void openBonusFactoryMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_FACTORY);
}

void openBonusGalleonMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_GALLEON);
}

void openBonusFungiMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_FUNGI);
}

void openBonusCavesMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_CAVES);
}

void openBonusCastleMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_CASTLE);
}

void openBonusHelmMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_HELM);
}

void openBonusIslesMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_ISLES);
}

void openBonusSnideMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_SNIDE);
}

void openBonusUnusedMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_MAP_BONUS_UNUSED);
}

void initMapWarpLast(void) {
	setDataStates(0,0);
	warpToMap();
}

void initMapWarpFirst(void) {
	setDataStates(1,0);
	warpToMap();
	setDataStates(0,0);
}

static const char* bonusmain_mapwarp_array[] = {
	"JAPES BARRELS",
	"AZTEC BARRELS",
	"FACTORY BARRELS",
	"GALLEON BARRELS",
	"FUNGI BARRELS",
	"CAVES BARRELS",
	"CASTLE BARRELS",
	"HELM BARRELS",
	"ISLES BARRELS",
	"SNIDE MINIGAMES",
	"UNUSED MINIGAMES",
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
	(int)&openBonusIslesMenu,
	(int)&openBonusSnideMenu,
	(int)&openBonusUnusedMenu,
};

const Screen bonusmain_mapwarp_struct = {
	.TextArray = (int*)bonusmain_mapwarp_array,
	.FunctionArray = bonusmain_mapwarp_functions,
	.ArrayItems = 11,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_JAPES
};

static const char* bonusjapes_mapwarp_array[] = {
	mapBonusMMMaul,
	mapBonusMMayhem,
	mapBonusSSSortie,
	mapBonusSSSalvage,
};

static const int bonusjapes_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusjapes_mapwarp_struct = {
	.TextArray = (int*)bonusjapes_mapwarp_array,
	.FunctionArray = bonusjapes_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_AZTEC
};

static const char* bonusaztec_mapwarp_array[] = {
	mapBonusBBBash,
	mapBonusBBBarrage,
	mapBonusKKosh,
	mapBonusSSnoop,
	mapBonusTTTrouble,
};

static const int bonusaztec_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusaztec_mapwarp_struct = {
	.TextArray = (int*)bonusaztec_mapwarp_array,
	.FunctionArray = bonusaztec_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_FACTORY
};

static const char* bonusfactory_mapwarp_array[] = {
	mapBonusBBBandit,
	mapBonusBBother,
	mapBonusKrazyKK,
	mapBonusPPPanic,
	mapBonusSSnatch,	
};

static const int bonusfactory_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusfactory_mapwarp_struct = {
	.TextArray = (int*)bonusfactory_mapwarp_array,
	.FunctionArray = bonusfactory_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_GALLEON
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
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusgalleon_mapwarp_struct = {
	.TextArray = (int*)bonusgalleon_mapwarp_array,
	.FunctionArray = bonusgalleon_mapwarp_functions,
	.ArrayItems = 7,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_FUNGI
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
	(int)&initMapWarpLast,
	(int)&initMapWarpFirst,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusfungi_mapwarp_struct = {
	.TextArray = (int*)bonusfungi_mapwarp_array,
	.FunctionArray = bonusfungi_mapwarp_functions,
	.ArrayItems = 6,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_CAVES
};

static const char* bonuscaves_mapwarp_array[] = {
	mapBonusBBBarrage,
	mapBonusKrazyKK,
	mapBonusMMMaul,
	mapBonusSSeek,
};

static const int bonuscaves_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonuscaves_mapwarp_struct = {
	.TextArray = (int*)bonuscaves_mapwarp_array,
	.FunctionArray = bonuscaves_mapwarp_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_CASTLE
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
	(int)&initMapWarpFirst,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpFirst,
	(int)&initMapWarpLast,
};

const Screen bonuscastle_mapwarp_struct = {
	.TextArray = (int*)bonuscastle_mapwarp_array,
	.FunctionArray = bonuscastle_mapwarp_functions,
	.ArrayItems = 7,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_HELM
};

static const char* bonushelm_mapwarp_array[] = {
	"DK RAMBI GAME",
	"DK TARGET GAME",
	"DIDDY KREMLING GAME",
	"DIDDY ROCKETBARREL GAME",
	"LANKY MAZE GAME",
	"LANKY SHOOTING GAME",
	"TINY MUSHROOM GAME",
	"TINY PTT GAME",
	"CHUNKY HIDDEN KREMLING GAME",
	"CHUNKY SHOOTING GAME",
};

static const int bonushelm_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonushelm_mapwarp_struct = {
	.TextArray = (int*)bonushelm_mapwarp_array,
	.FunctionArray = bonushelm_mapwarp_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
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
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_ISLES
};

static const char* bonusisles_mapwarp_array[] = {
	mapBonusBBBandit,
	mapBonusBBBash,
	mapBonusKKosh,
	mapBonusPPPanic,
	mapBonusSSeek,
};

static const int bonusisles_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusisles_mapwarp_struct = {
	.TextArray = (int*)bonusisles_mapwarp_array,
	.FunctionArray = bonusisles_mapwarp_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
	.ParentPosition = 8
};

///////////
// SNIDE //
///////////

static const unsigned char bonussnide_destmap[] = {
	117, // KKosh
	123, // Batty BB
	137, // BBother
	138, // SSeek
	143, // Krazy KK
	146, // PPPanic
	150, // BBBash
	120, // TTTrouble
};

static const unsigned char bonussnide_destexit[] = {
	0, // KKosh
	0, // Batty BB
	0, // BBother
	0, // SSeek
	0, // Krazy KK
	0, // PPPanic
	0, // BBBash
	0, // TTTrouble
};

const MapWarp map_bonussnide_struct = {
	.maps = bonussnide_destmap,
	.exits = bonussnide_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_SNIDE
};

static const char* bonussnide_mapwarp_array[] = {
	mapBonusKKosh,
	mapBonusBBBandit,
	mapBonusBBother,
	mapBonusSSeek,
	mapBonusKrazyKK,
	mapBonusPPPanic,
	mapBonusBBBash,
	mapBonusTTTrouble,
};

static const int bonussnide_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonussnide_mapwarp_struct = {
	.TextArray = (int*)bonussnide_mapwarp_array,
	.FunctionArray = bonussnide_mapwarp_functions,
	.ArrayItems = 8,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
	.ParentPosition = 9
};

////////////
// UNUSED //
////////////

static const unsigned char bonusunused_destmap[] = {
	66, // MMMaul (Hard)
	124, // MMMaul (Insane)
	147, // PPPanic (Hard)
	135, // SSSortie (Hard)
	132, // SSSalvage (Hard)
	67, // SSnatch (Normal)
	75, // SSnatch (Hard)
	125, // SSnatch (Insane)
	127, // SSnoop (Easy)
	128, // SSnoop (Hard)
};

static const unsigned char bonusunused_destexit[] = {
	0, // MMMaul (Hard)
	0, // MMMaul (Insane)
	0, // PPPanic (Hard)
	0, // SSSortie (Hard)
	0, // SSSalvage (Hard)
	0, // SSnatch (Normal)
	0, // SSnatch (Hard)
	0, // SSnatch (Insane)
	0, // SSnoop (Easy)
	0, // SSnoop (Hard)
};

const MapWarp map_bonusunused_struct = {
	.maps = bonusunused_destmap,
	.exits = bonusunused_destexit,
	.screen = ACTIVEMENU_SCREEN_MAP_BONUS_UNUSED
};

static const char* bonusunused_mapwarp_array[] = {
	mapBonusMMMaulHard,
	mapBonusMMMaulInsane,
	mapBonusPPPanicHard,
	mapBonusSSSortieHard,
	mapBonusSSSalvageHard,
	mapBonusSSnatchNormal,
	mapBonusSSnatchHard,
	mapBonusSSnatchInsane,
	mapBonusSSnoopEasy,
	mapBonusSSnoopHard,
};

static const int bonusunused_mapwarp_functions[] = {
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
	(int)&initMapWarpLast,
};

const Screen bonusunused_mapwarp_struct = {
	.TextArray = (int*)bonusunused_mapwarp_array,
	.FunctionArray = bonusunused_mapwarp_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_MAP_BONUS_ROOT,
	.ParentPosition = 10
};