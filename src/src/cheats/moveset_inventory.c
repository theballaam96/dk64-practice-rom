#include "../../include/common.h"

static const char moveset_giveallmoves[] = "Give All Moves";
static const char moveset_revokeallmoves[] = "Revoke All Moves";
static const char moveset_cranky[] = "Cranky";
static const char moveset_funky[] = "Funky";
static const char moveset_candy[] = "Candy";
static const char moveset_trainingbarrels[] = "Training Barrels";
static const char moveset_camerashockwave_on[] = "Camera & Shockwave: On";
static const char moveset_camerashockwave_off[] = "Camera & Shockwave: Off";
static const char moveset_givecoins[] = "Give Coins";
static const char moveset_restockinventory[] = "Restock Inventory";
static const char moveset_restockhoming[] = "Give Homing Ammo";

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
	moveset_restockhoming,
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

void restockHoming(void) {
	CollectableBase.HomingAmmo = 100;
	playSFX(494); // Homing
}

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
	(int)&restockHoming,
};

const Screen moveset_struct = {
	.TextArray = (int*)moveset_array,
	.FunctionArray = moveset_functions,
	.ArrayItems = 10,
	.ParentScreen = 55,
	.ParentPosition = 0
};