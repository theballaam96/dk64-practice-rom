#include "../../include/common.h"

void getSandstormAddress(void) {
	short _torch_index = -1;
	int* m2location = (int*)ObjectModel2Pointer;
	if (CurrentMap == 0x26) {
		if (ObjectModel2Timer == 1) {
			_torch_index = convertIDToIndex(0xC1);
			ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,_torch_index);
			if (_object->behaviour_pointer) {
				sandstormData* _behaviour = _object->behaviour_pointer;
				SandstormAddress = (int *)&_behaviour->sandstorm_active;
			}
		}
	}
}

void toggleSandstorm(void) {
	if (CurrentMap == 0x26) {
		if ((TBVoidByte & 2) == 0) {
			*(char *)SandstormAddress = 1 ^ *(char *)SandstormAddress;
			openTogglesMenu();
		}
	}
}