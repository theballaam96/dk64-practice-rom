#include "../../../include/common.h"

static const char funky_ammobelt[16] = "AMMO BELT:0";

static const char funky_dk0[] = "DK:NO GUN";
static const char funky_dk1[] = "DK:COCONUT GUN";

static const char funky_di0[] = "DIDDY:NO GUN";
static const char funky_di1[] = "DIDDY:PEANUT POPGUNS";

static const char funky_la0[] = "LANKY:NO GUN";
static const char funky_la1[] = "LANKY:GRAPE SHOOTER";

static const char funky_ti0[] = "TINY:NO GUN";
static const char funky_ti1[] = "TINY:FEATHER BOW";

static const char funky_ch0[] = "CHUNKY:NO GUN";
static const char funky_ch1[] = "CHUNKY:PINEAPPLE LAUNCHER";

static const char funky_ha0[] = "HOMING AMMO:DISABLED";
static const char funky_ha1[] = "HOMING AMMO:ENABLED";

static const char funky_ss0[] = "SNIPER SCOPE:DISABLED";
static const char funky_ss1[] = "SNIPER SCOPE:ENABLED";

static const char* funky_array[] = {
	funky_dk0,
	funky_di0,
	funky_la0,
	funky_ti0,
	funky_ch0,
	funky_ammobelt,
	funky_ha0,
	funky_ss0,
};

static const char* funky_list_dk[] = {
	funky_dk0,
	funky_dk1,
};

static const char* funky_list_di[] = {
	funky_di0,
	funky_di1,
};

static const char* funky_list_la[] = {
	funky_la0,
	funky_la1,
};

static const char* funky_list_ti[] = {
	funky_ti0,
	funky_ti1,
};

static const char* funky_list_ch[] = {
	funky_ch0,
	funky_ch1,
};

static const int* funky_list_kong[] = {
	(int*)funky_list_dk,
	(int*)funky_list_di,
	(int*)funky_list_la,
	(int*)funky_list_ti,
	(int*)funky_list_ch,
};

void openFunkyMenu(void) {
	dk_strFormat((char *)funky_ammobelt,"AMMO BELT:%d",MovesBase[0].ammo_belt);
	if (MovesBase[0].weapon_bitfield & 2) {
		funky_array[6] = funky_ha1;
	} else {
		funky_array[6] = funky_ha0;
	}
	if (MovesBase[0].weapon_bitfield & 4) {
		funky_array[7] = funky_ss1;
	} else {
		funky_array[7] = funky_ss0;
	}
	for (int i = 0; i < 5; i++) {
		funky_array[i] = (char*)funky_list_kong[i][(int)MovesBase[i].weapon_bitfield & 1];
	}
	changeMenu(ACTIVEMENU_SCREEN_MOVES_FUNKY);
};

void toggleAmmoBelt(void) {
	char _base = MovesBase[0].ammo_belt + 1;
	if (_base > 2) {
		_base = 0;
	}
	for (int i = 0; i < 5; i++) {
		MovesBase[i].ammo_belt = _base;
	}
	openFunkyMenu();
};

void toggleGun(void) {
	char _base = MovesBase[(int)ActiveMenu.positionIndex].weapon_bitfield & 1;
	if (_base) {
		MovesBase[(int)ActiveMenu.positionIndex].weapon_bitfield = MovesBase[(int)ActiveMenu.positionIndex].weapon_bitfield & 0xFE;	
	} else {
		MovesBase[(int)ActiveMenu.positionIndex].weapon_bitfield = MovesBase[(int)ActiveMenu.positionIndex].weapon_bitfield | 1;
	}
	openFunkyMenu();
};

void toggleHoming(void) {
	char _base = MovesBase[0].weapon_bitfield & 2;
	for (int i = 0; i < 5; i++) {
		if (_base) {
			MovesBase[i].weapon_bitfield = MovesBase[i].weapon_bitfield & 0xFD;	
		} else {
			MovesBase[i].weapon_bitfield = MovesBase[i].weapon_bitfield | 2;
		}
	}
	openFunkyMenu();
};

void toggleSniper(void) {
	char _base = MovesBase[0].weapon_bitfield & 4;
	for (int i = 0; i < 5; i++) {
		if (_base) {
			MovesBase[i].weapon_bitfield = MovesBase[i].weapon_bitfield & 0xFB;	
		} else {
			MovesBase[i].weapon_bitfield = MovesBase[i].weapon_bitfield | 4;
		}
	}
	openFunkyMenu();
};

static const int funky_functions[] = {
	(int)&toggleGun,
	(int)&toggleGun,
	(int)&toggleGun,
	(int)&toggleGun,
	(int)&toggleGun,
	(int)&toggleAmmoBelt,
	(int)&toggleHoming,
	(int)&toggleSniper,
};

const Screen funky_struct = {
	.TextArray = (int*)funky_array,
	.FunctionArray = funky_functions,
	.ArrayItems = 8,
	.ParentScreen = ACTIVEMENU_SCREEN_MOVES_ROOT,
	.ParentPosition = 3
};