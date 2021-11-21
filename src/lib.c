#include "../include/common.h"

void playSFX(short sfxIndex) {
	playSound(sfxIndex,0x7FFF,0x427C0000,0x3F800000,0,0);
}

void setPermFlag(short flagIndex) {
	setFlag(flagIndex,1,0);
}

int convertIDToIndex(short obj_index) {
	int _count = ObjectModel2Count;
	int index = -1;
	int* m2location = ObjectModel2Pointer;
	for (int i = 0; i < _count; i++) {
		ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,i);
		if (_object->object_id == obj_index) {
			index = i;
		}
	}
	return index;
}

void checkMapType(void) {
	int levelIndex = levelIndexMapping[CurrentMap];
	if ((levelIndex == 0x9) || (levelIndex == 0xD)) {
		InBadMap = 1;
	} else {
		InBadMap = 0;
	}
}

void* findActorWithType(int search_actor_type) {
	for (int i = 0; i < ActorCount; i++) {
		actorData* _actor_ = (actorData*)ActorArray[i];
		if (_actor_->actorType == search_actor_type) {
			return _actor_;
		}
	}
	return 0;
}

int isRDRAM(void* address) {
	if (((int)address >= 0x80000000) && ((int)address < 0x80800000)) {
		return 1;
	}
	return 0;
}

void setWarpPosition(float x, float y, float z) {
	PositionWarpInfo.xPos = x;
	PositionWarpInfo.yPos = y;
	PositionWarpInfo.zPos = z;
	PositionFloatWarps[0] = x;
	PositionFloatWarps[1] = y;
	PositionFloatWarps[2] = z;
	PositionWarpBitfield = PositionWarpBitfield | 1;
}

typedef struct race_controller {
	/* 0x000 */ char unk_000[0x178];
	/* 0x178 */ unsigned char control_byte;
} race_controller;

typedef struct vehicle_paad {
	/* 0x000 */ char unk_000[0x30];
	/* 0x030 */ race_controller* controller;
} vehicle_paad;

typedef struct race_vehicle {
	/* 0x000 */ char unk_000[0x174];
	/* 0x174 */ vehicle_paad* paad;
	/* 0x178 */ char unk_178[0x1A8-0x178];
	/* 0x1A8 */ race_controller* controller;
} race_vehicle;

void hideRacePosition(int show) {
	unsigned char race_maps[] = {
		0xE, // Aztec Beetle Race
		0x52, // Caves Beetle Race
		0x1B, // Factory Car Race
		0xB9, // Castle Car Race
		0x27, // Seal Race
	};
	unsigned char control_value[] = {
		0x2,
		0x2,
		0x17,
		0xE,
		0xE,
	};
	int in_race = -1;
	for (int i = 0; i < sizeof(race_maps); i++) {
		if (CurrentMap == race_maps[i]) {
			in_race = i;
		}
	}
	if (in_race > -1) {
		if (Player) {
			race_vehicle* vehicle = (race_vehicle*)Player->vehicle_actor_pointer;
			if (vehicle) {
				vehicle_paad* paad = vehicle->paad;
				if (paad) {
					race_controller* controller = paad->controller;
					if (controller) {
						if (isRDRAM(controller)) {
							controller->control_byte = show * control_value[in_race];
						}
					}
				}
			}
		}
	}
}

void customHideHUD(void) {
	for (int i = 0; i < 0xE; i++) {
		HUD->item[i].hud_state = 0;
	}
}