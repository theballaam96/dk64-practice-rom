#include "../../include/common.h"

static const char banned_enemy_types[] = {
	0x01, // Giant Clam
	0x08, // Army Dillo
	0x0B, // Cranky
	0x0C, // Funky
	0x0D, // Candy
	0x0E, // Beetle
	0x0F, // Mermaid
	0x13, // Cutscene DK
	0x14, // Cutscene Diddy
	0x15, // Cutscene Lanky
	0x16, // Cutscene Tiny
	0x17, // Cutscene Chunky
	0x18, // T&S Padlock
	0x19, // Llama
	0x1A, // MJ
	0x1D, // Race Vulture
	0x26, // Pufftoss
	0x28, // K Rool's Foot
	0x2E, // Troff
	0x30, // BHDM
	0x34, // Toy Box (BHDM)
	0x37, // Scoff
	0x39, // Dogadon
	0x42, // Mech Fish
	0x44, // Fairy
	0x48, // Rabbit
	0x49, // Owl
	0x5A, // Rabbit
	0x5D, // K. Lumsy
	0x5E, // Spider Boss
	0x61, // K. Rool (DK Phase)
	0x69, // Enemy Car
	0x6A, // K. Rool (Diddy Phase)
	0x6B, // K. Rool (Lanky Phase)
	0x6C, // K. Rool (Tiny Phase)
	0x6D, // K. Rool (Chunky Phase)
	0x6E, // Bug
	0x6F, // BFI Fairy
	0x70, // Ice Tomato
};

void handleSpawnPrevention(void) {
	SpawnerArray* spawner_array;
	SpawnerInfo* focused_spawner;
	char _allowed;
	if (ObjectModel2Timer == 1) {
		if (EnemySpawnOff) {
			spawner_array = SpawnerMasterData.array;
			for (int i = 0; i < SpawnerMasterData.count; i++) {
				_allowed = 1;
				focused_spawner = getObjectArrayAddr(spawner_array,0x48,i);
				for (int j = 0; j < 39; j++) {
					if (focused_spawner->enemy_value == banned_enemy_types[j]) {
						_allowed = 0;
					}
				}
				if (_allowed) {
					focused_spawner->spawn_state = focused_spawner->spawn_state + 8;
				}
			}
		}
	}
}

void toggleSpawnPrevention(void) {
	EnemySpawnOff = 1 - EnemySpawnOff;
	SpawnerArray* spawner_array;
	SpawnerInfo* focused_spawner;
	char _allowed;
	char _change;
	if (EnemySpawnOff) {
		_change = 8;
	} else {
		_change = -8;
	}
	spawner_array = SpawnerMasterData.array;
	for (int i = 0; i < SpawnerMasterData.count; i++) {
		_allowed = 1;
		focused_spawner = getObjectArrayAddr(spawner_array,0x48,i);
		for (int j = 0; j < 39; j++) {
			if (focused_spawner->enemy_value == banned_enemy_types[j]) {
				_allowed = 0;
			}
		}
		if (_allowed) {
			focused_spawner->spawn_state = focused_spawner->spawn_state + _change;
		}
	}
	openTogglesMenu();
}