#include "../../include/common.h"

static const char moveset_giveallmoves[] = "GIVE ALL MOVES";
static const char moveset_revokeallmoves[] = "REVOKE ALL MOVES";
static const char moveset_cranky[] = "CRANKY";
static const char moveset_funky[] = "FUNKY";
static const char moveset_candy[] = "CANDY";
static const char moveset_trainingbarrels[] = "TRAINING BARRELS";
static const char moveset_camerashockwave_on[] = "CAMERA AND SHOCKWAVE: ON";
static const char moveset_camerashockwave_off[] = "CAMERA AND SHOCKWAVE: OFF";
static const char moveset_givecoins[] = "GIVE COINS";
static const char moveset_restockinventory[] = "RESTOCK INVENTORY";

static const char* moveset_array[] = {
	moveset_giveallmoves,
	moveset_revokeallmoves,
	moveset_cranky,
	moveset_funky,
	moveset_candy,
	moveset_trainingbarrels,
	moveset_camerashockwave_off,
	moveset_givecoins,
	moveset_restockinventory,
};

void openMovesetInventoryMenu(void) {
	char _camera = checkFlag(0x179,0);
	if (_camera) {
		moveset_array[6] = moveset_camerashockwave_on;
	} else {
		moveset_array[6] = moveset_camerashockwave_off;
	}
	changeMenu(63);
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

void toggleCamera(void) {
	char _camera = checkFlag(0x179,0);
	setFlag(0x179,1 - _camera,0);
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
		setFlag(0x182 + i,state,0); // Training Barrels
	}
	setFlag(0x179,state,0); // Canera
	setFlag(0x17F,state,0); // Spawned TBarrels
	setFlag(0x180,state,0); // SSlam purchased from Cranky
	setFlag(0x187,state,0); // All TBarrels cleared
	// Kong flags
	setFlag(0x6,state,0);
	setFlag(0x42,state,0);
	setFlag(0x46,state,0);
	setFlag(0x75,state,0);
	setFlag(0x181,state,0);
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
};

const Screen moveset_struct = {
	.TextArray = (int*)moveset_array,
	.FunctionArray = moveset_functions,
	.ArrayItems = 9,
	.ParentScreen = 55,
	.ParentPosition = 0
};