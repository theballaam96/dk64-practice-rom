#include "../include/common.h"

void patchHooks(void) {
	if ((Gamemode == 0) && (LoadedHooks == 0)) {
		LoadedHooks = 1;
		Precision = 2;
		InputDisplayIndex = -1;
		patchHook(0x80600674,0,8);
	}
}