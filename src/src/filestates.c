#include "../include/common.h"

static const char filestates_nle[] = "NO LEVELS EARLY";
static const char filestates_101[] = "101%";
static const char filestates_general[] = "GENERAL";

static const char* filestates_main_array[] = {
	filestates_nle,
	filestates_101,
	ilestates_general
};

static const int state_functions[] = {
	0,
	0,
	0,
};

void portFileStateToMemory(int state_index) {
	int _start = FileStatesROMStart + (state_index * FileStateSize);
	int* _perm_flags = getFlagBlockAddress(0);
	if (_perm_flags) {
		dmaFileTransfer(_start,_start+0x13C,&_perm_flags);
	}
	dmaFileTransfer(_start+0x13C,_start+0x13C+0x1E0,&MovesBase);
	dmaFileTransfer(_start+0x13C+0x1E0,_start+0x13C+0x1E0+0xC,&CollectableBase);
}