#include "../include/common.h"

static const char state_selected1[] = "SELECTED STATE: 1";
static const char state_selected2[] = "SELECTED STATE: 2";
static const char state_selected3[] = "SELECTED STATE: 3";
static const char state_selected4[] = "SELECTED STATE: 4";
static const char state_change[] = "CHANGE SAVESTATE";
static const char state_save[] = "SAVE STATE";
static const char state_load_position[] = "LOAD STATE FROM POSITION";
static const char state_load_exit[] = "LOAD STATE FROM EXIT";
static const char state_view[] = "VIEW STATE VARIABLES";

static const char change_savestate1[] = "SET TO: SAVESTATE 1";
static const char change_savestate2[] = "SET TO: SAVESTATE 2";
static const char change_savestate3[] = "SET TO: SAVESTATE 3";
static const char change_savestate4[] = "SET TO: SAVESTATE 4";

static const char var_data_true[] = "HAS DATA: TRUE";
static const char var_data_false[] = "HAS DATA: FALSE";
static const char var_xPos[16] = "X: 0";
static const char var_yPos[16] = "Y: 0";
static const char var_zPos[16] = "Z: 0";
static const char var_facing[20] = "FACING: 0";
static const char var_skew[20] = "SKEW: 0";
static const char var_map[10] = "MAP: 0x0";
static const char var_exit[10] = "EXIT: 0";
static const char var_character[13] = "CHARACTER: 0";
static const char var_helmtimer_off[] = "HELM TIMER: OFF";
static const char var_helmtimer_time[25] = "HELM TIMER: 00:00.00";
static const char var_isgtimer_off[] = "ISG TIMER: OFF";
static const char var_isgtimer_timer[25] = "ISG TIMER: 00:00.00";
static const char var_created_off[] = "CREATED: UNKNOWN";
static const char var_created_diff[22] = "CREATED: 00:00:00 AGO";

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

static const char* viewstate_array[] = {
	var_data_false,
	var_created_off,
	var_map,
	var_exit,
	var_character,
	var_xPos,
	var_yPos,
	var_zPos,
	var_facing,
	var_skew,
	var_helmtimer_off,
	var_isgtimer_off,
};

void openStateMenu(void) {
	changeMenu(31);
}

void openChangeStateMenu(void) {
	changeMenu(32);
}

void openStateViewMenu(void) {
	int _focused_state = FocusedSavestate;
	float helmTimerUsed;
	char helmTimeMins;
	float helmTimeSecs;
	float isgTimerUsed;
	char isgTimeMins;
	float isgTimeSecs;
	char createdSecs;
	char createdMins;
	char createdHours;
	float facing;
	float skew;
	if (states[_focused_state]->HasData) {
		viewstate_array[0] = var_data_true;
		viewstate_array[1] = var_created_diff;
		int _frame_diff = FrameReal - states[_focused_state]->createdTime;
		int _time_diff = _frame_diff / 60;
		createdHours = _time_diff / 3600;
		createdMins = (_time_diff - (60 * createdHours)) / 60;
		createdSecs = _time_diff - (3600 * createdHours) - (60 * createdMins);
		dk_strFormat((char *)var_created_diff,"CREATED: %02d:%02d:%02d AGO",createdHours,createdMins,createdSecs);
	} else {
		viewstate_array[0] = var_data_false;
		viewstate_array[1] = var_created_off;
	}
	if (states[_focused_state]->HelmTimerOn) {
		viewstate_array[10] = var_helmtimer_time;
		helmTimerUsed = timestampDiffToMilliseconds(states[_focused_state]->HelmTimerDifferenceMajor,states[_focused_state]->HelmTimerDifferenceMinor);
		helmTimerUsed = (float)(states[_focused_state]->HelmStart * 100) - helmTimerUsed;
		helmTimerUsed = helmTimerUsed / 100;
		helmTimeMins = (int)(float)(helmTimerUsed / 60);
		helmTimeSecs = helmTimerUsed - (60 * helmTimeMins);
		if (helmTimeSecs < 10) {
			dk_strFormat((char *)var_helmtimer_time,"HELM TIMER: %d:0%f",helmTimeMins,helmTimeSecs);
		} else {
			dk_strFormat((char *)var_helmtimer_time,"HELM TIMER: %d:%f",helmTimeMins,helmTimeSecs);
		}
	} else {
		viewstate_array[10] = var_helmtimer_off;
	}
	if (states[_focused_state]->ISGOn) {
		viewstate_array[11] = var_isgtimer_timer;
		isgTimerUsed = timestampDiffToMilliseconds(states[_focused_state]->ISGTimerDifferenceMajor,states[_focused_state]->ISGTimerDifferenceMinor);
		isgTimerUsed = (isgTimerUsed + 200) / 100;
		isgTimeMins = (int)(float)(isgTimerUsed / 60);
		isgTimeSecs = isgTimerUsed - (60 * isgTimeMins);
		if (isgTimeSecs < 10) {
			dk_strFormat((char *)var_isgtimer_timer,"ISG TIMER: %d:0%f",isgTimeMins,isgTimeSecs);
		} else {
			dk_strFormat((char *)var_isgtimer_timer,"ISG TIMER: %d:%f",isgTimeMins,isgTimeSecs);
		}
	} else {
		viewstate_array[11] = var_isgtimer_off;
	}
	facing = states[_focused_state]->facing_angle;
	facing = facing / 4096;
	facing = facing * 360;
	skew = states[_focused_state]->skew_angle;
	skew = skew / 4096;
	skew = skew * 360;
	dk_strFormat((char *)var_xPos,"X: %f",states[_focused_state]->xPos);
	dk_strFormat((char *)var_yPos,"Y: %f",states[_focused_state]->yPos);
	dk_strFormat((char *)var_zPos,"Z: %f",states[_focused_state]->zPos);
	dk_strFormat((char *)var_facing,"FACING: %f",facing);
	dk_strFormat((char *)var_skew,"SKEW: %f",skew);
	dk_strFormat((char *)var_map,"MAP: 0x%X",states[_focused_state]->Map);
	dk_strFormat((char *)var_exit,"EXIT: %d",states[_focused_state]->Exit);
	dk_strFormat((char *)var_character,"CHARACTER: %d",states[_focused_state]->Character);
	changeMenu(42);
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
	state_load_exit,
	state_view,
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
	(int)&stateaction_loadexit,
	(int)&openStateViewMenu
};

const Screen state_struct = {
	.TextArray = (const int*)state_array,
	.FunctionArray = state_functions,
	.ArrayItems = 6,
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

static const int viewstate_functions[3] = {};

const Screen viewstate_struct = {
	.TextArray = (const int*)viewstate_array,
	.FunctionArray = viewstate_functions,
	.ArrayItems = 12,
	.ParentScreen = 31,
	.ParentPosition = 5
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
							if (Player->camera_pointer) {
								states[_focused_state]->camera_angle = Player->camera_pointer->facing_angle;
							}
						}
						states[_focused_state]->facing_angle = Player->facing_angle;
						states[_focused_state]->skew_angle = Player->skew_angle;
						states[_focused_state]->Map = CurrentMap;
						states[_focused_state]->Exit = DestExit;
						states[_focused_state]->Character = Character;
						states[_focused_state]->HasData = 1;
						states[_focused_state]->HelmTimerOn = HelmTimerShown;
						states[_focused_state]->ISGOn = ISGActive;
						states[_focused_state]->createdTime = FrameReal;
						if (HelmTimerShown) {
							getTimestampDiffInTicks(HelmStartTimestampMajor,HelmStartTimestampMinor);
							states[_focused_state]->HelmTimerDifferenceMajor = TempTimestampStorageMajor;
							states[_focused_state]->HelmTimerDifferenceMinor = TempTimestampStorageMinor;
							states[_focused_state]->HelmStart = HelmStartTime;
						}
						if (ISGActive) {
							getTimestampDiffInTicks(ISGTimestampMajor,ISGTimestampMinor);
							states[_focused_state]->ISGTimerDifferenceMajor = TempTimestampStorageMajor;
							states[_focused_state]->ISGTimerDifferenceMinor = TempTimestampStorageMinor;
							states[_focused_state]->ISGPrevFade = ISGPreviousFadeout;
						}
						dk_memcpy((int *)states[_focused_state]->InventoryBase,&CollectableBase,0xC);
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
							dk_memcpy(&CollectableBase,(int *)states[_focused_state]->InventoryBase,0xC);
							if (MenuSavestateAction == 2) {
								PositionWarpInfo.xPos = states[_focused_state]->xPos;
								PositionWarpInfo.yPos = states[_focused_state]->yPos;
								PositionWarpInfo.zPos = states[_focused_state]->zPos;
								PositionFloatWarps[0] = states[_focused_state]->xPos;
								PositionFloatWarps[1] = states[_focused_state]->yPos;
								PositionFloatWarps[2] = states[_focused_state]->zPos;
								PositionWarpBitfield = PositionWarpBitfield | 1;
							};
							HelmTimerShown = 0; // Prevent Game Over fadeout
							ISGActive = 0; // Prevent ISG Fade
							LoadVarsOnMapLoad = 1;
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
};

void savestateLoadMapLoadVars(void) {
	int _focused_state = FocusedSavestate;
	if ((ObjectModel2Timer == 1) && (TransitionSpeed < 0) && (LoadVarsOnMapLoad == 1)) {
		HelmTimerShown = states[_focused_state]->HelmTimerOn;
		if (HelmTimerShown) {
			getTimestampDiffInTicks(states[_focused_state]->HelmTimerDifferenceMajor,states[_focused_state]->HelmTimerDifferenceMinor);
			HelmStartTimestampMajor = TempTimestampStorageMajor;
			HelmStartTimestampMinor = TempTimestampStorageMinor;
			HelmStartTime = states[_focused_state]->HelmStart;
		}
		ISGActive = states[_focused_state]->ISGOn;
		if (ISGActive) {
			getTimestampDiffInTicks(states[_focused_state]->ISGTimerDifferenceMajor,states[_focused_state]->ISGTimerDifferenceMinor);
			ISGTimestampMajor = TempTimestampStorageMajor;
			ISGTimestampMinor = TempTimestampStorageMinor;
			ISGPreviousFadeout = states[_focused_state]->ISGPrevFade;
		}
		if (Player) {
			Player->facing_angle = states[_focused_state]->facing_angle;
			Player->skew_angle = states[_focused_state]->skew_angle;
			if (Player->camera_pointer) {
				Player->camera_pointer->facing_angle = states[_focused_state]->camera_angle;
			}
		}
		LoadVarsOnMapLoad = 0;
	}
}