#include "../include/common.h"

/*
	Oranges
	Health
	Crystals
	Film
	Ammo
	Homing Ammo
	Instrument Energy
*/

static char inftext_ammo[18] = "";
static char inftext_homing[16] = "";
static char inftext_crystals[11] = "";
static char inftext_health[9] = "";
static char inftext_instrument[20] = "";
static char inftext_film[7] = "";
static char inftext_oranges[10] = "";

static char* infinite_names[] = {
	"AMMO <STANDARD>",
	"AMMO <HOMING>",
	"CRYSTALS",
	"HEALTH",
	"INSTRUMENT ENERGY",
	"FILM",
	"ORANGES",
};

static char* infinite_array[] = {
	inftext_ammo,
	inftext_homing,
	inftext_crystals,
	inftext_health,
	inftext_instrument,
	inftext_film,
	inftext_oranges,
	"TURN OFF ALL",
};

static char inf_oranges_on = 0;
static char inf_ammo_on = 0;
static char inf_homing_on = 0;
static char inf_crystals_on = 0;
static char inf_instrument_on = 0;
static char inf_film_on = 0;

static char* infinite_addrs[] = {
	(char*)&inf_ammo_on,
	(char*)&inf_homing_on,
	(char*)&inf_crystals_on,
	(char*)&InfiniteHealthCheatOn,
	(char*)&inf_instrument_on,
	(char*)&inf_film_on,
	(char*)&inf_oranges_on,
};

static const short infinite_sfx[] = {
	343, // Ammo Crate Pickup
	494, // Homing Shot
	212, // Entering OSprint
	587, // Lost Health
	229, // Instrument Shoom
	441, // Pull Out Camera
	244, // Orange Thrown
};

static char* on_off[] = {
	"{",
	"}",
};

void openInfinitesMenu(void) {
	for (int i = 0; i < sizeof(infinite_addrs) / 4; i++) {
		int val = *(char*)infinite_addrs[i];
		dk_strFormat(infinite_array[i],"%s %s",on_off[val],infinite_names[i]);
	}
	changeMenu(ACTIVEMENU_SCREEN_CHEATS_INFINITES);
}

void toggleInfinite(void) {
	int pos = ActiveMenu.positionIndex;
	*(char*)infinite_addrs[pos] = 1 ^ *(char*)infinite_addrs[pos];
	playSFX(infinite_sfx[pos]);
	openInfinitesMenu();
}

void turnoffinfinites(void) {
	for (int i = 0; i < sizeof(infinite_addrs) / 4; i++) {
		*(char*)infinite_addrs[i] = 0;
	}
	openInfinitesMenu();
}

static const int infinite_functions[] = {
	(int)&toggleInfinite,
	(int)&toggleInfinite,
	(int)&toggleInfinite,
	(int)&toggleInfinite,
	(int)&toggleInfinite,
	(int)&toggleInfinite,
	(int)&toggleInfinite,
	(int)&turnoffinfinites,
};

const Screen infinite_struct = {
	.TextArray = (int*)infinite_array,
	.FunctionArray = infinite_functions,
	.ArrayItems = 8,
	.ParentScreen = ACTIVEMENU_SCREEN_CHEATS_ROOT,
	.ParentPosition = 7
};

void handleInfinites(void) {
	if (inf_oranges_on) {
		CollectableBase.Oranges = 20;
	}
	if (inf_ammo_on) {
		CollectableBase.StandardAmmo = 200;
	}
	if (inf_homing_on) {
		CollectableBase.HomingAmmo = 100;
	}
	if (inf_crystals_on) {
		CollectableBase.Crystals = 3000;
	}
	if (inf_film_on) {
		CollectableBase.Film = 20;
	}
	if (inf_instrument_on) {
		for (int i = 0; i < 5; i++) {
			MovesBase[i].instrument_energy = 10;
		}
	}
	if (InfiniteHealthCheatOn) {
		CollectableBase.Health = CollectableBase.Melons << 2;
	}
}