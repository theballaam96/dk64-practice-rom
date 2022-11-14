#include "../../include/common.h"

static const file_state_indexes filestates_nle_stateindex[] = {
	NLE_GENERAL_JAPES1,
	NLE_HELMESCAPE_AZTEC,
	NLE_HELMESCAPE_FACTORY,
	NLE_HELMESCAPE_JAPES2,
	NLE_HELMESCAPE_GALLEON,
	NLE_HELMESCAPE_FUNGI,
	NLE_HELMESCAPE_CAVES,
	NLE_HELMESCAPE_CASTLE,
	NLE_HELMESCAPE_HELM,
	NLE_HELMESCAPE_TAKEOFF,
};
static const file_state_indexes filestates_101org_stateindex[] = {
	_101ORG_CAVES1,
	_101ORG_JAPES1,
	_101ORG_AZTEC1,
	_101ORG_FACTORY,
	_101ORG_GALLEON,
	_101ORG_HELM,
	_101ORG_CASTLE,
	_101ORG_AZTEC2_ALT,
	_101ORG_AZTEC2,
	_101ORG_CAVES2,
	_101ORG_JAPES2,
	_101GEN_FUNGI,
};
static const file_state_indexes filestates_101jfm_stateindex[] = {
	_101JFM_AZTEC1,
	_101JFM_CASTLE1,
	_101JFM_JAPES,
	_101JFM_FACTORY,
	_101JFM_GALLEON,
	_101JFM_HELM,
	_101JFM_CASTLE2,
	_101JFM_AZTEC2,
	_101JFM_CAVES,
	_101GEN_FUNGI,
};
static const file_state_indexes filestates_101wbr_stateindex[] = {
	_101FH_AZTEC1,
	_101FH_CASTLE1,
	_101FH_JAPES,
	_101FH_FACTORY,
	_101FH_GALLEON,
	_101FH_HELM,
	_101FH_CASTLE2,
	_101FH_AZTEC2,
	_101FH_CAVES,
	_101FH_FUNGI,
};
static const file_state_indexes filestates_101ffm_stateindex[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
static const file_state_indexes filestates_glitchless_stateindex[] = {
	GLITCHLESS_ANY_JAPES1,
	GLITCHLESS_ANY_AZTEC,
	GLITCHLESS_ANY_FACTORY,
	GLITCHLESS_ANY_JAPES2,
	GLITCHLESS_ANY_GALLEON,
	GLITCHLESS_ANY_FUNGI,
	GLITCHLESS_ANY_CAVES,
	GLITCHLESS_ANY_CASTLE,
	GLITCHLESS_ANY_HELM,
};
static const file_state_indexes filestates_nle40_stateindex[] = {
	NLE_GENERAL_JAPES1,
	NLE_40BP_AZTEC1,
	NLE_40BP_FACTORY,
	NLE_40BP_JAPES2,
	NLE_40BP_GALLEON,
	NLE_40BP_FUNGI,
	NLE_40BP_CAVES,
	NLE_40BP_CASTLE,
	NLE_40BP_AZTEC2,
	NLE_40BP_HELM,
};
static const file_state_indexes filestates_general_stateindex[] = {
	GENERAL_EMPTY
};

static char load_filestate_vars = 0;
static short filestate_floor = 0;

void openFileStateMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_ROOT);
}

void openFileStateNLEMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_NLE);
}

void openFileState101MainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_101ROOT);
}

void openFileStateGeneralMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_GENERAL);
}

void openFileState101OrganicMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_101ORG);
}

void openFileState101JFMMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_101JFM);
}

void openFileState101FFMMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_101FFM);
}

void openFileState101WBRMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_101WBR);
}

void openFileStateGlitchlessMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_GLITCHLESSANY);
}

void openFileStateNLE40Menu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_NLE40);
}

void openFileStateNLEMainMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_FILE_NLE_ROOT);
}

void portFileStateToMemory(int state_index) {
	unsigned int _start = FileStatesROMStart + (state_index * FileStateSize);
	filestateInfo* copy_space = dk_malloc(FileStateSize);
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
	if ((file_state_indexes)state_index != GENERAL_EMPTY) {
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
	if ((ObjectModel2Timer < 2) && (TransitionSpeed < 0) && (load_filestate_vars)) {
		if (Player) {
			Player->floor = filestate_floor;
			clearDKPortal();
			load_filestate_vars = 0;
		}
	}
}

void loadFileState(void) {
	int _position = ActiveMenu.positionIndex;
	int _stateindex = -1;
	switch(ActiveMenu.screenIndex){
		case ACTIVEMENU_SCREEN_FILE_NLE:
			// NLE
			_stateindex = (int)filestates_nle_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_GENERAL:
			// General
			_stateindex = (int)filestates_general_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_101ORG:
			// 101% Organic Route
			_stateindex = (int)filestates_101org_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_101JFM:
			// 101% JFM Route
			_stateindex = (int)filestates_101jfm_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_101FFM:
			// 101% FFM Route
			_stateindex = (int)filestates_101ffm_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_101WBR:
			// 101% WBR (Fun Hideout) Route
			_stateindex = (int)filestates_101wbr_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_GLITCHLESSANY:
			_stateindex = (int)filestates_glitchless_stateindex[_position];
			break;
		case ACTIVEMENU_SCREEN_FILE_NLE40:
			_stateindex = (int)filestates_nle40_stateindex[_position];
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
	"GENERAL",
	"NO LEVELS EARLY",
	"101$",
	"ANY$ GLITCHLESS",
};

static const int filestates_main_functions[] = {
	(int)&openFileStateGeneralMenu,
	(int)&openFileStateNLEMainMenu,
	(int)&openFileState101MainMenu,
	(int)&openFileStateGlitchlessMenu,
};

const Screen filestates_main_struct = {
	.TextArray = (int*)filestates_main_array,
	.FunctionArray = filestates_main_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 7
};

static const char* filestates_nlemain_array[] = {
	"HELM ESCAPE",
	"40 BLUEPRINTS",
};

static const int filestates_nlemain_functions[] = {
	(int)&openFileStateNLEMenu,
	(int)&openFileStateNLE40Menu,
};

const Screen filestates_nlemain_struct = {
	.TextArray = (int*)filestates_nlemain_array,
	.FunctionArray = filestates_nlemain_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_ROOT,
	.ParentPosition = 1
};

static const char* filestates_nle40_array[] = {
	"JAPES 1",
	"AZTEC 1",
	"FACTORY",
	"JAPES 2",
	"GALLEON",
	"FUNGI",
	"CAVES",
	"CASTLE",
	"AZTEC 2",
	"HELM"
};

static const int filestates_nle40_functions[] = {
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
};

const Screen filestates_nle40_struct = {
	.TextArray = (int*)filestates_nle40_array,
	.FunctionArray = filestates_nle40_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_NLE_ROOT,
	.ParentPosition = 1
};

static const char* filestates_nle_array[] = {
	"JAPES 1",
	"AZTEC",
	"FACTORY",
	"JAPES 2",
	"GALLEON",
	"FUNGI",
	"CAVES",
	"CASTLE",
	"HELM",
	"TAKEOFF SKIP"
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
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_NLE_ROOT,
	.ParentPosition = 0
};

static const char* filestates_101main_array[] = {
	"ORGANIC ROUTE",
	"JAPES FOR MOVES ROUTE",
	"WRONG BARREL RESOLUTION ROUTE",
	"FACTORY FOR MOVES ROUTE",
};

static const int filestates_101main_functions[] = {
	(int)&openFileState101OrganicMenu,
	(int)&openFileState101JFMMenu,
	(int)&openFileState101WBRMenu,
	(int)&openFileState101FFMMenu,
};

const Screen filestates_101main_struct = {
	.TextArray = (int*)filestates_101main_array,
	.FunctionArray = filestates_101main_functions,
	.ArrayItems = 3,
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_ROOT,
	.ParentPosition = 2
};

static const char* filestates_general_array[] = {
	"CLEAN FILE"
};

static const int filestates_general_functions[] = {
	(int)&loadOtherStates,
};

const Screen filestates_general_struct = {
	.TextArray = (int*)filestates_general_array,
	.FunctionArray = filestates_general_functions,
	.ArrayItems = 1,
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_ROOT,
	.ParentPosition = 0
};

static const char* filestates_101org_array[] = {
	"CAVES 1",
	"JAPES 1",
	"AZTEC 1",
	"FACTORY",
	"GALLEON",
	"HELM",
	"CASTLE",
	"AZTEC 2 <BEGINNER>",
	"AZTEC 2 <EXPERT>",
	"CAVES 2",
	"JAPES 2",
	"FUNGI"
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
	(int)&loadOtherStates,
	(int)&loadOtherStates
};

const Screen filestates_101org_struct = {
	.TextArray = (int*)filestates_101org_array,
	.FunctionArray = filestates_101org_functions,
	.ArrayItems = 12,
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_101ROOT,
	.ParentPosition = 0
};

static const char* filestates_101jfm_array[] = {
	"AZTEC 1",
	"CASTLE 1",
	"JAPES",
	"FACTORY",
	"GALLEON",
	"HELM",
	"CASTLE 2",
	"AZTEC 2",
	"CAVES",
	"FUNGI"
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
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_101ROOT,
	.ParentPosition = 1
};

static const char* filestates_101wbr_array[] = {
	"AZTEC 1",
	"CASTLE 1",
	"JAPES",
	"FACTORY",
	"GALLEON",
	"HELM",
	"CASTLE 2",
	"AZTEC 2",
	"CAVES",
	"FUNGI 2"
};

static const int filestates_101wbr_functions[] = {
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

const Screen filestates_101wbr_struct = {
	.TextArray = (int*)filestates_101wbr_array,
	.FunctionArray = filestates_101wbr_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_101ROOT,
	.ParentPosition = 2
};

static const char* filestates_101ffm_array[] = {
	"AZTEC 1",
	"CASTLE 1",
	"FACTORY",
	"GALLEON",
	"HELM",
	"JAPES",
	"CASTLE 2",
	"AZTEC 2",
	"CAVES",
	"FUNGI"
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
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_101ROOT,
	.ParentPosition = 3
};

static const char* filestates_glitchless_array[] = {
	"JAPES 1",
	"AZTEC",
	"FACTORY",
	"JAPES 2",
	"GALLEON",
	"FUNGI",
	"CAVES",
	"CASTLE",
	"HELM"
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
	.ParentScreen = ACTIVEMENU_SCREEN_FILE_ROOT,
	.ParentPosition = 3
};