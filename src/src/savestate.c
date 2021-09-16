#include "../include/common.h"

static const char state_selected1[] = "Selected State: 1";
static const char state_selected2[] = "Selected State: 2";
static const char state_selected3[] = "Selected State: 3";
static const char state_selected4[] = "Selected State: 4";
static const char state_change[] = "Change Savestate";
static const char state_save[] = "Save State";
static const char state_load_position[] = "Load State from Position";
static const char state_load_exit[] = "Load State from Exit";
static const char state_view[] = "View State Variables";

static const char change_savestate1[] = "Set to: Savestate 1";
static const char change_savestate2[] = "Set to: Savestate 2";
static const char change_savestate3[] = "Set to: Savestate 3";
static const char change_savestate4[] = "Set to: Savestate 4";

static const char var_data_true[] = "Has Data: True";
static const char var_data_false[] = "Has Data: False";
static const char var_xPos[16] = "X: 0";
static const char var_yPos[16] = "Y: 0";
static const char var_zPos[16] = "Z: 0";
static const char var_facing[20] = "Facing: 0";
static const char var_skew[20] = "Skew: 0";
static const char var_map[10] = "Map: 0x0";
static const char var_exit[10] = "Exit: 0";
static const char var_character[13] = "Character: 0";
static const char var_helmtimer_off[] = "Helm Timer: Off";
static const char var_helmtimer_time[25] = "Helm Timer: 00:00.00";
static const char var_isgtimer_off[] = "ISG Timer: Off";
static const char var_isgtimer_timer[25] = "ISG Timer: 00:00.00";
static const char var_created_off[] = "Created: Unknown";
static const char var_created_diff[22] = "Created: 00:00:00 Ago";

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
		dk_strFormat((char *)var_created_diff,"Created: %02d:%02d:%02d Ago",createdHours,createdMins,createdSecs);
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
			dk_strFormat((char *)var_helmtimer_time,"Helm Timer: %d:0%f",helmTimeMins,helmTimeSecs);
		} else {
			dk_strFormat((char *)var_helmtimer_time,"Helm Timer: %d:%f",helmTimeMins,helmTimeSecs);
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
			dk_strFormat((char *)var_isgtimer_timer,"ISG Timer: %d:0%f",isgTimeMins,isgTimeSecs);
		} else {
			dk_strFormat((char *)var_isgtimer_timer,"ISG Timer: %d:%f",isgTimeMins,isgTimeSecs);
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
	dk_strFormat((char *)var_facing,"Facing: %f",facing);
	dk_strFormat((char *)var_skew,"Skew: %f",skew);
	dk_strFormat((char *)var_map,"Map: 0x%X",states[_focused_state]->Map);
	dk_strFormat((char *)var_exit,"Exit: %d",states[_focused_state]->Exit);
	dk_strFormat((char *)var_character,"Character: %d",states[_focused_state]->Character);
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
	.TextArray = (int*)state_array,
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
	.TextArray = (int*)changestate_array,
	.FunctionArray = changestate_functions,
	.ArrayItems = 4,
	.ParentScreen = 31,
	.ParentPosition = 1
};

static const int viewstate_functions[12] = {};

const Screen viewstate_struct = {
	.TextArray = (int*)viewstate_array,
	.FunctionArray = viewstate_functions,
	.ArrayItems = 12,
	.ParentScreen = 31,
	.ParentPosition = 5
};

void savestateHandler(void) {
	int _focused_state = FocusedSavestate;
	int tag_found = 0;
	int search_actor_index = 0;
	float tag_y = 0;
	float nearest_tag_distance = 999999;
	float current_tag_distance = 0;
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
							states[_focused_state]->floor = Player->floor;
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
						states[_focused_state]->stored_damage = StoredDamage;
						states[_focused_state]->rng = RNG;
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
						for (int i = 0; i < LoadedActorCount; i++) {
							search_actor_index = LoadedActorArray[i].actor->actorType;
							if ((search_actor_index == 98) || (search_actor_index == 136) || (search_actor_index == 137)) { // Tag Barrel Actors
								float a_x = LoadedActorArray[i].actor->xPos;
								float a_z = LoadedActorArray[i].actor->zPos;
								float p_x = Player->xPos;
								float p_z = Player->zPos;
								current_tag_distance = (float)((a_x - p_x) * (a_x - p_x)) + ((a_z - p_z) * (a_z - p_z));
								if (current_tag_distance < nearest_tag_distance) {
									tag_found = 1;
									tagBarrel* tag_actor = (tagBarrel*)LoadedActorArray[i].actor;
									tag_y = tag_actor->tag_oscillation_timer;
									nearest_tag_distance = current_tag_distance;
								}
							}
						}
						states[_focused_state]->nearest_tag_enabled = tag_found;
						states[_focused_state]->nearest_tag_oscillation_timer = tag_y;
						dk_memcpy((int *)states[_focused_state]->InventoryBase,&CollectableBase,0xC);
						dk_memcpy((int *)states[_focused_state]->TempFlagBlock,&TempFlagBlock,0x10);
						break;
					case 2:
					case 3:
						// Load State (2 = from position, 3 = from exit)
						LastLoadStateAction = MenuSavestateAction;
						if (states[_focused_state]->HasData) {
							TimerData.Mode = 0;
							TimerData.Timer = 0;
							TimerData.Start = 0;
							TimerData.Reduction = 0;
							TimerData.TimerPostReduction = 0;
							HasNeutralStickInput = 0;
							dk_memcpy(_perm_flag_block,(int *)states[_focused_state]->PermanentFlagBlock,0x13C);
							dk_memcpy(&MovesBase,(int *)states[_focused_state]->KongBase,0x1D8);
							dk_memcpy(&TempFlagBlock,(int *)states[_focused_state]->TempFlagBlock,0x10);
							resetMap();
							Character = states[_focused_state]->Character;
							StoredDamage = states[_focused_state]->stored_damage;
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
							CutsceneFadeActive = 0; // Prevent wrong cutscene crashes
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
	tagBarrel* tag_found_addr = 0;
	int search_actor_index = 0;
	float nearest_tag_distance = 999999;
	float current_tag_distance = 0;
	if ((ObjectModel2Timer == 2) && (TransitionSpeed < 0) && (LoadVarsOnMapLoad == 1)) {
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
		RNG = states[_focused_state]->rng;
		if (Player) {
			if (LastLoadStateAction == 2) {
				Player->facing_angle = states[_focused_state]->facing_angle;
				Player->skew_angle = states[_focused_state]->skew_angle;
				Player->floor = states[_focused_state]->floor;
				if (Player->camera_pointer) {
					Player->camera_pointer->facing_angle = states[_focused_state]->camera_angle;
				}
				for (int i = 0; i < LoadedActorCount; i++) {
					search_actor_index = LoadedActorArray[i].actor->actorType;
					if ((search_actor_index == 98) || (search_actor_index == 136) || (search_actor_index == 137)) { // Tag Barrel Actors
						float a_x = LoadedActorArray[i].actor->xPos;
						float a_z = LoadedActorArray[i].actor->zPos;
						float p_x = Player->xPos;
						float p_z = Player->zPos;
						current_tag_distance = (float)((a_x - p_x) * (a_x - p_x)) + ((a_z - p_z) * (a_z - p_z));
						if (current_tag_distance < nearest_tag_distance) {
							tag_found_addr = (tagBarrel*)LoadedActorArray[i].actor;
							nearest_tag_distance = current_tag_distance;
						}
					}
				}
				if (tag_found_addr) {
					tag_found_addr->tag_oscillation_timer = states[_focused_state]->nearest_tag_oscillation_timer;
				}
			}
		}
		LoadVarsOnMapLoad = 0;
	}
}