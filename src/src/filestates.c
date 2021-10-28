#include "../include/common.h"

static const char filestates_nle[] = "No Levels Early";
static const char filestates_101[] = "101%";
static const char filestates_general[] = "General";
static const char filestates_101org[] = "Organic Route";
static const char filestates_101jfm[] = "Japes for Moves Route";
static const char filestates_101ffm[] = "Factory for Moves Route";
static const char filestates_glitchless[] = "Glitchless Any%";

static const char state_text_japes[] = "Japes";
static const char state_text_japes1[] = "Japes 1";
static const char state_text_japes2[] = "Japes 2";
static const char state_text_aztec[] = "Aztec";
static const char state_text_aztec1[] = "Aztec 1";
static const char state_text_aztec2[] = "Aztec 2";
static const char state_text_factory[] = "Factory";
static const char state_text_galleon[] = "Galleon";
static const char state_text_fungi[] = "Fungi";
static const char state_text_caves[] = "Caves";
static const char state_text_caves1[] = "Caves 1";
static const char state_text_caves2[] = "Caves 2";
static const char state_text_castle[] = "Castle";
static const char state_text_castle1[] = "Castle 1";
static const char state_text_castle2[] = "Castle 2";
static const char state_text_helm[] = "Helm";

static const char state_text_takeoff[] = "Takeoff Skip";
static const char state_text_clean[] = "Clean File";

static const char filestates_nle_stateindex[] = {0,1,2,3,4,5,6,7,8,9};
static const char filestates_101org_stateindex[] = {11,12,13,14,15,16,17,18,19,20,21};
static const char filestates_101jfm_stateindex[] = {22,23,24,25,26,27,28,29,30,21};
static const char filestates_101ffm_stateindex[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
static const char filestates_glitchless_stateindex[] = {31,32,33,34,35,36,37,38,39};
static const char filestates_general_stateindex[] = {10};

static char load_filestate_vars = 0;
static short filestate_floor = 0;

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

void openFileStateGlitchlessMenu(void) {
	changeMenu(89);
}

void portFileStateToMemory(int state_index) {
	unsigned int _start = FileStatesROMStart + (state_index * FileStateSize);
	filestateInfo* copy_space = dk_malloc(FileStateSize);
	TestVariable = (int)copy_space;
	int* file_size;
	*(int*)(&file_size) = FileStateSize;
	//copyFromROM(_start,copy_space,&file_size,0,0,0,1);
	//pm64ReadFromROM(_start,_start + FileStateSize, copy_space);
	copyFunc(_start - pointer_table_offset, FileStateSize, copy_space);
	int* _perm_flags = getFlagBlockAddress(0);
	if (_perm_flags) {
		dk_memcpy(_perm_flags,copy_space,0x13C);
	}
	dk_memcpy(&MovesBase,&copy_space->moves_base,0x1D6);
	dk_memcpy(&CollectableBase,&copy_space->inventory,0xD);
	dk_memcpy(&TempFlagBlock,&copy_space->temp_flags,0x10);
	resetMap();
	int _map = 0x22;
	int _character = 0;
	if (state_index != 10) {
		_map = copy_space->map;
		_character = copy_space->kong;
		initiateTransition(_map,0);
		setWarpPosition((float)copy_space->xPos,(float)copy_space->yPos,(float)copy_space->zPos);
		filestate_floor = copy_space->yPos;
	} else {
		initiateTransition(_map,0);
	}
	load_filestate_vars = 1;
	Character = _character;
	HelmTimerShown = 0;
	ISGActive = 0;
	__osWritebackDCache(copy_space, FileStateSize);
	__osInvalICache(copy_space, FileStateSize);
	__osInvalDCache(copy_space, FileStateSize);
	dk_free(copy_space);
}

void fileStateMapLoadVars(void) {
	if ((ObjectModel2Timer == 2) && (TransitionSpeed < 0) && (load_filestate_vars)) {
		if (Player) {
			Player->floor = filestate_floor;
			load_filestate_vars = 0;
		}
	}
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
		case 89:
			_stateindex = filestates_glitchless_stateindex[_position];
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
	filestates_glitchless,
};

static const int filestates_main_functions[] = {
	(int)&openFileStateGeneralMenu,
	(int)&openFileStateNLEMenu,
	(int)&openFileState101MainMenu,
	(int)&openFileStateGlitchlessMenu,
};

const Screen filestates_main_struct = {
	.TextArray = (int*)filestates_main_array,
	.FunctionArray = filestates_main_functions,
	.ArrayItems = 4,
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
	.ArrayItems = 2,
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
	state_text_caves1,
	state_text_japes1,
	state_text_aztec1,
	state_text_factory,
	state_text_galleon,
	state_text_helm,
	state_text_castle,
	state_text_aztec2,
	state_text_caves2,
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
	(int)&loadOtherStates,
	(int)&loadOtherStates
};

const Screen filestates_101org_struct = {
	.TextArray = (int*)filestates_101org_array,
	.FunctionArray = filestates_101org_functions,
	.ArrayItems = 11,
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

static const char* filestates_glitchless_array[] = {
	state_text_japes1,
	state_text_aztec,
	state_text_factory,
	state_text_japes2,
	state_text_galleon,
	state_text_fungi,
	state_text_caves,
	state_text_castle,
	state_text_helm
};

static const int filestates_glitchless_functions[] = {
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

const Screen filestates_glitchless_struct = {
	.TextArray = (int*)filestates_glitchless_array,
	.FunctionArray = filestates_glitchless_functions,
	.ArrayItems = 9,
	.ParentScreen = 37,
	.ParentPosition = 3
};