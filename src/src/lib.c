#include "../include/common.h"

void playSFX(short sfxIndex) {
	playSound(sfxIndex,0x7FFF,0x427C0000,0x3F800000,0,0);
}

void setPermFlag(short flagIndex) {
	setFlag(flagIndex,1,0);
}

int convertIDToIndex(short obj_index) {
	//int _count = ObjectModel2Count;
	int index = -1;
	// for (int i = 0; i < _count; i++) {
	// 	ModelTwoData _object = &(*(int *)ObjectModel2Pointer) + (i * 0x90);
	// 	if (_object.object_id == obj_index) {
	// 		index = i;
	// 	}
	// }
	return index;
}