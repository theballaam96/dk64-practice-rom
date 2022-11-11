#include "../../include/common.h"

#define GLOOMY_GALLEON 0x1E
#define ANGRY_AZTEC 0x26
#define FUNGI_FOREST 0x30
#define CRYSTAL_CAVES 0x48

void loadObjScript(int obj_instance_id) {
	scriptsAttemptLoadCount += 1;
	int script_index = scriptsRunningCount;
	if (script_index != 0x46) {
		scriptsRunningCount = script_index + 1;
		scriptsLoadedArray[script_index] = obj_instance_id;
		int obj_idx = convertIDToIndex(obj_instance_id);
		int* m2location = (int*)ObjectModel2Pointer;
		ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,obj_idx);
		int* behav = _object->behaviour_pointer;
		updateObjectScript(behav);
		executeBehaviourScript(behav, obj_instance_id);
	}
}

void fixModifiers(void) {
	if (ObjectModel2Timer < 5) {
		if (CurrentMap == GLOOMY_GALLEON) {
			if ((scriptsNotAutoloading & 2) == 0) {
				loadObjScript(0);
				if (checkFlag(FLAG_MODIFIER_GALLEONWATER,0)) {
					for (int i = 0; i < 20; i++) {
						setWaterHeight(i,55.0f,1000.0f);
					}
				}
			}
		} else if (CurrentMap == ANGRY_AZTEC) {
			if ((scriptsNotAutoloading & 1) == 0) {
				loadObjScript(0xC1);
			}
		} else if (CurrentMap == CRYSTAL_CAVES) {
			if ((scriptsNotAutoloading & 4) == 0) {
				loadObjScript(0x31);
			}
		} else if (CurrentMap == FUNGI_FOREST) {
			if ((scriptsNotAutoloading & 8) == 0) {
				loadObjScript(0x4);
			}
		}
	}
}

int isScriptLoaded(int idx) {
	if (scriptsRunningCount > 0) {
		for (int i = 0; i < scriptsRunningCount; i++) {
			if (scriptsLoadedArray[i] == idx) {
				return 1;
			}
		}
	}
	return 0;
}