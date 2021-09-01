#include "../include/common.h"

static const char filestates_nle[] = "NO LEVELS EARLY";
static const char filestates_101[] = "101%";
static const char filestates_general[] = "GENERAL";
static const char filestates_101org[] = "ORGANIC ROUTE";
static const char filestates_101jfm[] = "JAPES FOR MOVES ROUTE";
static const char filestates_101ffm[] = "FACTORY FOR MOVES ROUTE";

static const char state_text_japes[] = "JAPES";
static const char state_text_japes1[] = "JAPES 1";
static const char state_text_japes2[] = "JAPES 2";
static const char state_text_aztec[] = "AZTEC";
static const char state_text_aztec1[] = "AZTEC 1";
static const char state_text_aztec2[] = "AZTEC 2";
static const char state_text_factory[] = "FACTORY";
static const char state_text_galleon[] = "GALLEON";
static const char state_text_fungi[] = "FUNGI";
static const char state_text_caves[] = "CAVES";
static const char state_text_castle[] = "CASTLE";
static const char state_text_castle1[] = "CASTLE 1";
static const char state_text_castle2[] = "CASTLE 2";
static const char state_text_helm[] = "HELM";

static const char state_text_takeoff[] = "TAKEOFF SKIP";
static const char state_text_clean[] = "CLEAN FILE";

static const char filestates_nle_stateindex[] = {0,1,2,3,4,5,6,7,8,9};
static const char filestates_101org_stateindex[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
static const char filestates_101jfm_stateindex[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
static const char filestates_101ffm_stateindex[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
static const char filestates_general_stateindex[] = {10};

void openFileStateMainMenu(void) {
	changeMenu(35);
}

void openFileStateNLEMenu(void) {
	changeMenu(36);
}

void openFileState101MainMenu(void) {
	changeMenu(37);
}

void openFileStateGeneralMenu(void) {
	changeMenu(38);
}

void openFileState101OrganicMenu(void) {
	changeMenu(39);
}

void openFileState101JFMMenu(void) {
	changeMenu(40);
}

void openFileState101FFMMenu(void) {
	changeMenu(41);
}

void portFileStateToMemory(int state_index) {
	unsigned int _start = FileStatesROMStart + (state_index * FileStateSize);
	filestateInfo* copy_space = dk_malloc(FileStateSize);
	int* file_size;
	*(int*)(&file_size) = FileStateSize;
	copyFromROM(_start,copy_space,&file_size,0,0,0,0);
	int* _perm_flags = getFlagBlockAddress(0);
	if (_perm_flags) {
		dk_memcpy(_perm_flags,copy_space,0x13C);
	}
	dk_memcpy(&MovesBase,&copy_space->moves_base,0x1D6);
	dk_memcpy(&CollectableBase,&copy_space->inventory,0xD);
	dk_memcpy(&TempFlagBlock,&copy_space->temp_flags,0x10);
	dk_free(copy_space);
}

void loadFileState(void) {
	int _position = ActiveMenu.positionIndex;
	int _stateindex = -1;
	switch(ActiveMenu.screenIndex){
		case 36:
			// NLE
			_stateindex = filestates_nle_stateindex[_position];
			break;
		case 38:
			// General
			_stateindex = filestates_general_stateindex[_position];
			break;
		case 39:
			// 101% Organic Route
			_stateindex = filestates_101org_stateindex[_position];
			break;
		case 40:
			// 101% JFM Route
			_stateindex = filestates_101jfm_stateindex[_position];
			break;
		case 41:
			// 101% FFM Route
			_stateindex = filestates_101ffm_stateindex[_position];
		break;
	}
	if (_stateindex > -1) {
		portFileStateToMemory(_stateindex);
	}
}

void loadOtherStates(void) {
	loadFileState();
	playSFX(BeepHigh);
}

void takeoffSkip(void) {
	// Easter Egg
	loadFileState();
	playSFX(KLumsy);
}

static const char* filestates_main_array[] = {
	filestates_general,
	filestates_nle,
	filestates_101,
};

static const int filestates_main_functions[] = {
	(int)&openFileStateGeneralMenu,
	(int)&openFileStateNLEMenu,
	(int)&openFileState101MainMenu,
};

const Screen filestates_main_struct = {
	.TextArray = (int*)filestates_main_array,
	.FunctionArray = filestates_main_functions,
	.ArrayItems = 2, // Would be 3, waiting on 101% states
	.ParentScreen = 0,
	.ParentPosition = 6
};

static const char* filestates_nle_array[] = {
	state_text_japes1,
	state_text_aztec,
	state_text_factory,
	state_text_japes2,
	state_text_galleon,
	state_text_fungi,
	state_text_caves,
	state_text_castle,
	state_text_helm,
	state_text_takeoff
};

static const int filestates_nle_functions[] = {
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&takeoffSkip
};

const Screen filestates_nle_struct = {
	.TextArray = (int*)filestates_nle_array,
	.FunctionArray = filestates_nle_functions,
	.ArrayItems = 10,
	.ParentScreen = 35,
	.ParentPosition = 1
};

static const char* filestates_101main_array[] = {
	filestates_101org,
	filestates_101jfm,
	filestates_101ffm,
};

static const int filestates_101main_functions[] = {
	(int)&openFileState101OrganicMenu,
	(int)&openFileState101JFMMenu,
	(int)&openFileState101FFMMenu,
};

const Screen filestates_101main_struct = {
	.TextArray = (int*)filestates_101main_array,
	.FunctionArray = filestates_101main_functions,
	.ArrayItems = 3,
	.ParentScreen = 35,
	.ParentPosition = 2
};

static const char* filestates_general_array[] = {
	state_text_clean
};

static const int filestates_general_functions[] = {
	(int)&loadOtherStates,
};

const Screen filestates_general_struct = {
	.TextArray = (int*)filestates_general_array,
	.FunctionArray = filestates_general_functions,
	.ArrayItems = 1,
	.ParentScreen = 35,
	.ParentPosition = 0
};

static const char* filestates_101org_array[] = {
	state_text_japes1,
	state_text_aztec1,
	state_text_factory,
	state_text_galleon,
	state_text_helm,
	state_text_castle,
	state_text_aztec2,
	state_text_caves,
	state_text_japes2,
	state_text_fungi
};

static const int filestates_101org_functions[] = {
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates
};

const Screen filestates_101org_struct = {
	.TextArray = (int*)filestates_101org_array,
	.FunctionArray = filestates_101org_functions,
	.ArrayItems = 10,
	.ParentScreen = 37,
	.ParentPosition = 0
};

static const char* filestates_101jfm_array[] = {
	state_text_aztec1,
	state_text_castle1,
	state_text_japes,
	state_text_factory,
	state_text_galleon,
	state_text_helm,
	state_text_castle2,
	state_text_aztec2,
	state_text_caves,
	state_text_fungi
};

static const int filestates_101jfm_functions[] = {
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates
};

const Screen filestates_101jfm_struct = {
	.TextArray = (int*)filestates_101jfm_array,
	.FunctionArray = filestates_101jfm_functions,
	.ArrayItems = 10,
	.ParentScreen = 37,
	.ParentPosition = 1
};

static const char* filestates_101ffm_array[] = {
	state_text_aztec1,
	state_text_castle1,
	state_text_factory,
	state_text_galleon,
	state_text_helm,
	state_text_japes,
	state_text_castle2,
	state_text_aztec2,
	state_text_caves,
	state_text_fungi
};

static const int filestates_101ffm_functions[] = {
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates,
	(int)&loadOtherStates
};

const Screen filestates_101ffm_struct = {
	.TextArray = (int*)filestates_101ffm_array,
	.FunctionArray = filestates_101ffm_functions,
	.ArrayItems = 10,
	.ParentScreen = 37,
	.ParentPosition = 2
};