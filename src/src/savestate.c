#include "../include/common.h"

static const char state_selected1[] = "SELECTED STATE: 1";
static const char state_selected2[] = "SELECTED STATE: 2";
static const char state_selected3[] = "SELECTED STATE: 3";
static const char state_selected4[] = "SELECTED STATE: 4";
static const char state_change[] = "CHANGE SAVESTATE";
static const char state_save[] = "SAVE STATE";
static const char state_load_position[] = "LOAD STATE FROM POSITION";
static const char state_load_exit[] = "LOAD STATE FROM EXIT";

static const char change_savestate1[] = "SET TO: SAVESTATE 1";
static const char change_savestate2[] = "SET TO: SAVESTATE 2";
static const char change_savestate3[] = "SET TO: SAVESTATE 3";
static const char change_savestate4[] = "SET TO: SAVESTATE 4";

static Savestate state1 = {};
static Savestate state2 = {};
static Savestate state3 = {};
static Savestate state4 = {};

static Savestate* states[] = {
	&state1,
	&state2,
	&state3,
	&state4
};

static const char* change_states[] = {
	state_selected1,
	state_selected2,
	state_selected3,
	state_selected4
};

void openStateMenu(void) {
	changeMenu(31);
}

void openChangeStateMenu(void) {
	changeMenu(32);
}

void stateaction_save(void) {
	MenuSavestateAction = 1;
}

void stateaction_loadpos(void) {
	MenuSavestateAction = 2;
	LastLoadStateAction = 2;
}

void stateaction_loadexit(void) {
	MenuSavestateAction = 3;
	LastLoadStateAction = 3;
}


static const char* state_array[] = {
	state_selected1,
	state_change,
	state_save,
	state_load_position,
	state_load_exit
};

void changeSavestate(void) {
	FocusedSavestate = ActiveMenu.positionIndex;
	state_array[0] = change_states[(int)FocusedSavestate];
	openStateMenu();
};

static const int state_functions[] = {
	0,
	(int)&openChangeStateMenu,
	(int)&stateaction_save,
	(int)&stateaction_loadpos,
	(int)&stateaction_loadexit
};

const Screen state_struct = {
	.TextArray = (const int*)state_array,
	.FunctionArray = state_functions,
	.ArrayItems = 5,
	.ParentScreen = 0,
	.ParentPosition = 2
};

static const char* changestate_array[] = {
	change_savestate1,
	change_savestate2,
	change_savestate3,
	change_savestate4
};

static const int changestate_functions[] = {
	(int)&changeSavestate,
	(int)&changeSavestate,
	(int)&changeSavestate,
	(int)&changeSavestate
};

const Screen changestate_struct = {
	.TextArray = (const int*)changestate_array,
	.FunctionArray = changestate_functions,
	.ArrayItems = 4,
	.ParentScreen = 31,
	.ParentPosition = 1
};

void savestateHandler(void) {
	int _focused_state = FocusedSavestate;
	if (MenuSavestateAction > 0) {
		if (InBadMap) {
			playSFX(Wrong);
		} else {
			int* _perm_flag_block = getFlagBlockAddress(0);
			if (_perm_flag_block) {
				switch(MenuSavestateAction) {
					case 1:
						// Save State
						dk_memcpy((int *)states[_focused_state]->PermanentFlagBlock,_perm_flag_block,0x13C);
						playSFX(Okay);
						dk_memcpy((int *)states[_focused_state]->KongBase,&MovesBase,0x1E0);
						if (Player) {
							states[_focused_state]->xPos = Player->xPos;
							states[_focused_state]->yPos = Player->yPos;
							states[_focused_state]->zPos = Player->zPos;
						}
						states[_focused_state]->Map = CurrentMap;
						states[_focused_state]->Exit = DestExit;
						states[_focused_state]->Character = Character;
						states[_focused_state]->HasData = 1;
						dk_memcpy((int *)states[_focused_state]->InventoryBase,&CollectableBase,0x10);
						dk_memcpy((int *)states[_focused_state]->TempFlagBlock,&TempFlagBlock,0x10);
						break;
					case 2:
					case 3:
						// Load State (2 = from position, 3 = from exit)
						if (states[_focused_state]->HasData) {
							TimerData.Mode = 0;
							TimerData.Timer = 0;
							TimerData.Start = 0;
							TimerData.Reduction = 0;
							TimerData.TimerPostReduction = 0;
							HasNeutralStickInput = 0;
							dk_memcpy(_perm_flag_block,(int *)states[_focused_state]->PermanentFlagBlock,0x13C);
							dk_memcpy(&MovesBase,(int *)states[_focused_state]->KongBase,0x1E0);
							dk_memcpy(&TempFlagBlock,(int *)states[_focused_state]->TempFlagBlock,0x10);
							resetMap();
							Character = states[_focused_state]->Character;
							initiateTransition(states[_focused_state]->Map,states[_focused_state]->Exit);
							dk_memcpy(&CollectableBase,(int *)states[_focused_state]->InventoryBase,0x10);
							if (MenuSavestateAction == 2) {
								PositionWarpInfo[0] = states[_focused_state]->xPos;
								PositionWarpInfo[1] = states[_focused_state]->yPos;
								PositionWarpInfo[2] = states[_focused_state]->zPos;
								PositionFloatWarps[0] = states[_focused_state]->xPos;
								PositionFloatWarps[1] = states[_focused_state]->yPos;
								PositionFloatWarps[2] = states[_focused_state]->zPos;
								PositionWarpBitfield = PositionWarpBitfield | 1;
							}
						} else {
							playSFX(Wrong);
						}
					break;
				}
			} else {
				playSFX(Wrong);
			}
		}
	}
	MenuSavestateAction = 0;
};

void shorthandSavestate(void) {
	if ((ControllerInput.Buttons & L_Button) && (ControllerInput.Buttons & R_Button)) {
		if (NewlyPressedControllerInput.Buttons & D_Up) {
			char _action = LastLoadStateAction;
			if (_action == 0) {
				_action = 2;
			};
			if ((InBadMap) || (states[(int)FocusedSavestate]->HasData == 0)) {
				playSFX(Wrong);
			} else {
				MenuSavestateAction = _action;
			}
		}
	}
}