#include "../include/common.h"

void giveCoins(void) {
	for (int i = 0; i < 5; i++) {
		MovesBase[i]->coins = 50;
	}
	playSFX(Coin)
}

void restockInventory(void) {
	CollectableBase.StandardAmmo = 200;
	CollectableBase.Crystals = 3000;
	CollectableBase.Oranges = 20;
	CollectableBase.Film = 20;
	CollectableBase.Health = CollectableBase.Melons << 2;
	short _energy = 10;
	for (int i = 0; i < 5; i++) {
		MovesBase[i]->instrument_energy = _energy;
	}
}