#include "../../include/common.h"

#define HIDEOUT_HELM 0x11
#define FRANTIC_FACTORY 0x1A

int getFakeKeyStatus(void) {
	/*
		0 = Wrong Map
		1 = Not Loaded
		2 = Loaded
		3 = Key Obtained
		4 = Unknown
		5 = Key not in map
	*/
	if (CurrentMap == HIDEOUT_HELM) {
		if (checkFlag(FLAG_KEYHAVE_KEY8,0)) {
			return 3;
		} else {
			int key_index = convertIDToIndex(0x5A);
			if (key_index > -1) {
				if (ChunkArrayPointer) {
					chunk_struct chunk_0 = *(chunk_struct*)ChunkArrayPointer;
					return chunk_0.loaded + 1;
				}
			}
			return 5;
		}
		return 4;
	}
	return 0;
}

int getFakeProdRoomStatus(void) {
	/*
		0 = Wrong Map
		1 = Production Room Off
		2 = Unknown
		3 = Not Loaded
		4 = Preparing to be fake
		5 = Fake
		6 = Real
	*/
	if (CurrentMap == FRANTIC_FACTORY) {
		if (checkFlag(FLAG_MODIFIER_PRODROOM,0)) {
			int* m2location = ObjectModel2Pointer;
			int lms_index = -1;
			int crusher_index = -1;
			if (ObjectModel2Pointer) {
				lms_index = convertIDToIndex(0x0);
				crusher_index = convertIDToIndex(0x1);
				if ((lms_index > -1) && (crusher_index > -1)) {
					ModelTwoData* lms_object = getObjectArrayAddr(m2location,0x90,lms_index);
					ModelTwoData* crusher_object = getObjectArrayAddr(m2location,0x90,crusher_index);
					snagData* lms_behaviour = lms_object->behaviour_pointer;
					snagData* crusher_behaviour = crusher_object->behaviour_pointer;
					if ((lms_behaviour) && (crusher_behaviour)) {
						int lms_reset = lms_behaviour->reset;
						int crusher_reset = crusher_behaviour->reset;
						int crusher_reset_new = crusher_behaviour->reset_next;
						if (lms_reset >= 11) {
							if (crusher_reset_new == 0) {
								if (crusher_reset >= 10) {
									return 4;
								}
								return 5;
							}
							return 6;
						}
						return 3;
					}
				}
			}
			return 2;
		}
		return 1;
	}
	return 0;
}