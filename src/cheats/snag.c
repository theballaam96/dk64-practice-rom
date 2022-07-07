#include "../include/common.h"

static const char* snagcheats_array[] = {
	"VISIFY SNAG COLLECTABLES",
	"RESET SNAG COLLECTABLES",
};

void openSnagMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_CHEATS_SNAG);
}

void visifySnagGBs(void) {
	int _count = ObjectModel2Count;
	int* m2location = ObjectModel2Pointer;
	for (int i = 0; i < _count; i++) {
		ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,i);
		if ((_object->object_type == 0x74) || (_object->object_type == 0x90)) {
			snagData* _behaviour = _object->behaviour_pointer;
			if (_behaviour) {
				_behaviour->check = 2;
				_behaviour->state = 0;
			}
		}
	}
}

void resetSnagGBs(void) {
	int _count = ObjectModel2Count;
	int* m2location = ObjectModel2Pointer;
	for (int i = 0; i < _count; i++) {
		ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,i);
		if ((_object->object_type == 0x74) || (_object->object_type == 0x90)) {
			snagData* _behaviour = _object->behaviour_pointer;
			if (_behaviour) {
				_behaviour->check = 0;
				_behaviour->state = 0;
				_behaviour->reset = 0;
			}
		}
	}
}

static const int snagcheats_functions[] = {
	(int)&visifySnagGBs,
	(int)&resetSnagGBs,
};

const Screen snagcheats_struct = {
	.TextArray = (int*)snagcheats_array,
	.FunctionArray = snagcheats_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_CHEATS_ROOT,
	.ParentPosition = 4
};