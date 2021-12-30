#include "../../include/common.h"

void corruptGame(void) {
	playSFX(246); // Exploding Orange
	int to_spawn = 65 - LoadedActorCount;
	for (int i = 0; i < to_spawn; i++) {
		spawnActor(265,48);
	}
}