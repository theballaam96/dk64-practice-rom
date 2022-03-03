#include "../../include/common.h"

static const char moveset_camerashockwave_on[] = "} CAMERA AND SHOCKWAVE";
static const char moveset_camerashockwave_off[] = "{ CAMERA AND SHOCKWAVE";

static const char* moveset_array[] = {
	"GIVE ALL MOVES",
	"REVOKE ALL MOVES",
	"CRANKY",
	"FUNKY",
	"CANDY",
	"TRAINING BARRELS",
	moveset_camerashockwave_off,
	"GIVE COINS",
	"RESTOCK INVENTORY",
	"GIVE HOMING AMMO",
};

void openMovesetInventoryMenu(void) {
	char _camera = checkFlag(FLAG_ABILITY_CAMERA,0);
	if (_camera) {
		moveset_array[6] = moveset_camerashockwave_on;
	} else {
		moveset_array[6] = moveset_camerashockwave_off;
	}
	changeMenu(ACTIVEMENU_SCREEN_MOVES_ROOT);
};

void giveCoins(void) {
	for (int i = 0; i < 5; i++) {
		MovesBase[i].coins = 50;
	}
	playSFX(Coin);
};

void restockInventory(void) {
	CollectableBase.StandardAmmo = 200;
	CollectableBase.Crystals = 3000;
	CollectableBase.Oranges = 20;
	CollectableBase.Film = 20;
	CollectableBase.Health = CollectableBase.Melons << 2;
	short _energy = 10;
	for (int i = 0; i < 5; i++) {
		MovesBase[i].instrument_energy = _energy;
	}
	playSFX(AmmoPickup);
};

void restockHoming(void) {
	CollectableBase.HomingAmmo = 100;
	playSFX(494); // Homing
}

void toggleCamera(void) {
	int _camera = checkFlag(FLAG_ABILITY_CAMERA,0);
	setFlag(FLAG_ABILITY_CAMERA,1 ^ _camera,0);
	openMovesetInventoryMenu();
}

void setMoveState(int state) {
	for (int i = 0; i < 5; i++) {
		MovesBase[i].special_moves = 3 * state;
		MovesBase[i].simian_slam = 3 * state;
		MovesBase[i].weapon_bitfield = 7 * state;
		MovesBase[i].ammo_belt = 2 * state;
		MovesBase[i].instrument_bitfield = 15 * state;
	};
	CollectableBase.Melons = (2 * state) + 1;
	CollectableBase.Health = (8 * state) + 4;
	for (int i = 0; i < 4; i++) {
		setFlag(FLAG_TBARREL_DIVE + i,state,0); // Training Barrels
	}
	setFlag(FLAG_ABILITY_CAMERA,state,0); // Canera
	setFlag(FLAG_TBARREL_SPAWNED,state,0); // Spawned TBarrels
	setFlag(FLAG_ABILITY_SIMSLAM,state,0); // SSlam purchased from Cranky
	setFlag(FLAG_TBARREL_COMPLETE,state,0); // All TBarrels cleared
	// Kong flags
	setFlag(FLAG_KONG_DK,state,0);
	setFlag(FLAG_KONG_DIDDY,state,0);
	setFlag(FLAG_KONG_LANKY,state,0);
	setFlag(FLAG_KONG_TINY,state,0);
	setFlag(FLAG_KONG_CHUNKY,state,0);
	if (state) {
		playSFX(Potion);
	} else {
		playSFX(MatchingSound);
	}
	openMovesetInventoryMenu();
};

void giveallmoves(void) {
	setMoveState(1);
};

void revokeallmoves(void) {
	setMoveState(0);
};

static const int moveset_functions[] = {
	(int)&giveallmoves,
	(int)&revokeallmoves,
	(int)&openCrankyMenu,
	(int)&openFunkyMenu,
	(int)&openCandyMenu,
	(int)&openFlagsTBarrelMenu,
	(int)&toggleCamera,
	(int)&giveCoins,
	(int)&restockInventory,
	(int)&restockHoming,
};

const Screen moveset_struct = {
	.TextArray = (int*)moveset_array,
	.FunctionArray = moveset_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_CHEATS_ROOT,
	.ParentPosition = 0
};