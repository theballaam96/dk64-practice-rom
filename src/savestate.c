#include "../include/common.h"

static const char state_selected1[] = "SELECTED STATE:1";
static const char state_selected2[] = "SELECTED STATE:2";
static const char state_selected3[] = "SELECTED STATE:3";
static const char state_selected4[] = "SELECTED STATE:4";

static const char var_data_true[] = "HAS DATA:TRUE";
static const char var_data_false[] = "HAS DATA:FALSE";
static const char var_xPos[16] = "X:0";
static const char var_yPos[16] = "Y:0";
static const char var_zPos[16] = "Z:0";
static const char var_facing[20] = "FACING:0";
static const char var_skew[20] = "SKEW:0";
static const char var_map[10] = "MAP:0X0";
static const char var_exit[10] = "EXIT:0";
static const char var_character[13] = "CHARACTER:0";
static const char var_helmtimer_off[] = "HELM TIMER:OFF";
static const char var_helmtimer_time[25] = "Helm Timer:00:00.00";
static const char var_isgtimer_off[] = "ISG TIMER:OFF";
static const char var_isgtimer_timer[25] = "ISG TIMER:00:00.00";
static const char var_created_off[] = "CREATED:UNKNOWN";
static const char var_created_diff[22] = "CREATED:00:00:00 AGO";

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
		dk_strFormat((char *)var_created_diff,"CREATED:%02d:%02d:%02d AGO",createdHours,createdMins,createdSecs);
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
			dk_strFormat((char *)var_helmtimer_time,"HELM TIMER:%d:0%f",helmTimeMins,helmTimeSecs);
		} else {
			dk_strFormat((char *)var_helmtimer_time,"HELM TIMER:%d:%f",helmTimeMins,helmTimeSecs);
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
			dk_strFormat((char *)var_isgtimer_timer,"ISG TIMER:%d:0%f",isgTimeMins,isgTimeSecs);
		} else {
			dk_strFormat((char *)var_isgtimer_timer,"ISG TIMER:%d:%f",isgTimeMins,isgTimeSecs);
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
	dk_strFormat((char *)var_xPos,"X:%f",states[_focused_state]->xPos);
	dk_strFormat((char *)var_yPos,"Y:%f",states[_focused_state]->yPos);
	dk_strFormat((char *)var_zPos,"Z:%f",states[_focused_state]->zPos);
	dk_strFormat((char *)var_facing,"FACING:%f",facing);
	dk_strFormat((char *)var_skew,"SKEW:%f",skew);
	dk_strFormat((char *)var_map,"MAP:0X%X",states[_focused_state]->Map);
	dk_strFormat((char *)var_exit,"EXIT:%d",states[_focused_state]->Exit);
	dk_strFormat((char *)var_character,"CHARACTER:%d",states[_focused_state]->Character);
	changeMenu(42);
}

void stateaction_save(void) {
	MenuSavestateAction = 1;
	savestateHandler();
}

void stateaction_loadpos(void) {
	MenuSavestateAction = 2;
	LastLoadStateAction = 2;
	savestateHandler();
}

void stateaction_loadexit(void) {
	MenuSavestateAction = 3;
	LastLoadStateAction = 3;
	savestateHandler();
}

static const char* state_array[] = {
	state_selected1,
	"CHANGE SAVESTATE",
	"SAVE STATE",
	"LOAD STATE FROM POSITION",
	"LOAD STATE FROM EXIT",
	"VIEW STATE VARIABLES",
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
	"SET TO: SAVESTATE 1",
	"SET TO: SAVESTATE 2",
	"SET TO: SAVESTATE 3",
	"SET TO: SAVESTATE 4"
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
		if (CurrentMap == 0x51) { // Prevent savestate load in console menu
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
						if (SwapObject) {
							states[_focused_state]->cameraPos.xPos = SwapObject->cameraPositions[0].xPos;
							states[_focused_state]->cameraPos.yPos = SwapObject->cameraPositions[0].yPos;
							states[_focused_state]->cameraPos.zPos = SwapObject->cameraPositions[0].zPos;
						}
						if (Camera) {
							states[_focused_state]->camera_rotation = Camera->viewportRotation;
						}
						

						// Parent Map Shenanigans
						int levelIndex = levelIndexMapping[CurrentMap];
						int boss_index = -1;
						unsigned char boss_maps[7] = {0x8,0xC5,0x9A,0x6F,0x53,0xC4,0xC7};
						for (int i = 0; i < 7; i++) {
							if (boss_maps[i] == CurrentMap) {
								boss_index = i;
							}
						}
						int getParent = -1;
						if (((levelIndex == 0x9) || (levelIndex == 0xD) || (boss_index > -1))) {
							for (int i = 0; i < 0x11; i++) {
								if ((parentData[0x10 - i].transition_properties_bitfield & 2) && (parentData[0x10 - i].in_submap)) {
									getParent = 0x10 - i;
								}
							}
						}
						if (getParent > -1) {
							states[_focused_state]->par_bool = 1;
							states[_focused_state]->par_map = parentData[getParent].map;
							states[_focused_state]->par_exit = parentData[getParent].exit;
							states[_focused_state]->par_x = parentData[getParent].positions.xPos;
							states[_focused_state]->par_y = parentData[getParent].positions.yPos;
							states[_focused_state]->par_z = parentData[getParent].positions.zPos;
							states[_focused_state]->par_tpb = parentData[getParent].transition_properties_bitfield;
						} else {
							states[_focused_state]->par_bool = 0;
						}

						
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
							resetMap();
							if (states[_focused_state]->par_bool) {
								handleMapWarping(states[_focused_state]->Map,states[_focused_state]->Exit,0,SAVESTATE);
								parentData[0].map = states[_focused_state]->par_map;
								parentData[0].exit = states[_focused_state]->par_exit;
								parentData[0].positions.xPos = states[_focused_state]->par_x;
								parentData[0].positions.yPos = states[_focused_state]->par_y;
								parentData[0].positions.zPos = states[_focused_state]->par_z;
								parentData[0].transition_properties_bitfield = states[_focused_state]->par_tpb;
								parentData[0].in_submap |= 3;
							} else {
								initiateTransition(states[_focused_state]->Map,states[_focused_state]->Exit);
							}
							if (MenuSavestateAction == 2) {
								setWarpPosition(states[_focused_state]->xPos, states[_focused_state]->yPos, states[_focused_state]->zPos);
							};
							int* _perm_flag_block = getFlagBlockAddress(0);
							if (_perm_flag_block) {
								dk_memcpy(_perm_flag_block,(int *)states[_focused_state]->PermanentFlagBlock,0x13C);
							}
							dk_memcpy(&MovesBase,(int *)states[_focused_state]->KongBase,0x1D8);
							dk_memcpy(&TempFlagBlock,(int *)states[_focused_state]->TempFlagBlock,0x10);
							StoredDamage = states[_focused_state]->stored_damage;
							dk_memcpy(&CollectableBase,(int *)states[_focused_state]->InventoryBase,0xC);
							Character = states[_focused_state]->Character;
							HelmTimerShown = 0; // Prevent Game Over fadeout
							ISGActive = 0; // Prevent ISG Fade
							CutsceneFadeActive = 0; // Prevent wrong cutscene crashes
							LZFadeoutProgress = 28.0f;
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
				savestateHandler();
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
	if ((TransitionSpeed < 0) && (ObjectModel2Timer < 2) && (LoadVarsOnMapLoad == 1)) {
		int* _perm_flag_block = getFlagBlockAddress(0);
		if (_perm_flag_block) {
			dk_memcpy(_perm_flag_block,(int *)states[_focused_state]->PermanentFlagBlock,0x13C);
		}
		dk_memcpy(&MovesBase,(int *)states[_focused_state]->KongBase,0x1D8);
		dk_memcpy(&TempFlagBlock,(int *)states[_focused_state]->TempFlagBlock,0x10);
		StoredDamage = states[_focused_state]->stored_damage;
		dk_memcpy(&CollectableBase,(int *)states[_focused_state]->InventoryBase,0xC);
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
				LZFadeoutProgress = 1.0f;
				Player->facing_angle = states[_focused_state]->facing_angle;
				Player->skew_angle = states[_focused_state]->skew_angle;
				Player->floor = states[_focused_state]->floor;
				if (SwapObject) {
					for (int i = 0; i < 4; i++) {
						SwapObject->cameraPositions[i].xPos = states[_focused_state]->cameraPos.xPos;
						SwapObject->cameraPositions[i].yPos = states[_focused_state]->cameraPos.yPos;
						SwapObject->cameraPositions[i].zPos = states[_focused_state]->cameraPos.zPos;
					}
				}
				if (Camera) {
					Camera->viewportX = states[_focused_state]->cameraPos.xPos;
					Camera->viewportY = states[_focused_state]->cameraPos.yPos;
					Camera->viewportZ = states[_focused_state]->cameraPos.zPos;
					Camera->viewportRotation = states[_focused_state]->camera_rotation;
				}
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
		stateLoadTimer = 60;
		LoadVarsOnMapLoad = 0;
	}
}