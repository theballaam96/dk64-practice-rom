#include "../../include/common.h"

static const char viewed_lag[] = "Lag (!)";
static const char viewed_avglag[] = "Average Lag (!)";
static const char viewed_speed[] = "Speed (!)";
static const char viewed_timer[] = "Timer (!)";
static const char viewed_gktimer[] = "Giant Kosha Timer (!)";
static const char viewed_movement[] = "Movement State (!)";
static const char viewed_angle[] = "Angle (!)";
static const char viewed_input[] = "Input (!)";
static const char viewed_heldactor[] = "Held Actor (!)";
static const char viewed_isg[] = "Intro Story Timer (!)";
static const char viewed_position[] = "Position (!)";
static const char viewed_storedposition1[] = "Stored Position 1 (!)";
static const char viewed_storedposition2[] = "Stored Position 2 (!)";
static const char viewed_floor[] = "Floor (!)";
static const char viewed_phaseassistant[] = "Phasewalk Assistant (!)";
static const char viewed_avgspd[] = "Average Speed (!)";
static const char viewed_fairy[] = "Fairy Viewer (!)";

static const char change_lag[] = "Lag";
static const char change_avglag[] = "Average Lag";
static const char change_speed[] = "Speed";
static const char change_timer[] = "Timer";
static const char change_gktimer[] = "Giant Kosha Timer";
static const char change_movement[] = "Movement State";
static const char change_angle[] = "Angle";
static const char change_input[] = "Input";
static const char change_heldactor[] = "Held Actor";
static const char change_isg[] = "Intro Story Timer";
static const char change_position[] = "Position";
static const char change_storedposition1[] = "Stored Position 1";
static const char change_storedposition2[] = "Stored Position 2";
static const char change_floor[] = "Floor";
static const char change_phaseassistant[] = "Phasewalk Assistant";
static const char change_avgspd[] = "Average Speed";
static const char change_fairy[] = "Fairy Viewer";

static const char watchdisplay_player[] = "Player Variables";
static const char watchdisplay_sys[] = "System Environment";
static const char watchdisplay_timers[] = "Timers";
static const char watchdisplay_snag[] = "Spawn Snag Collectables";
static const char watchdisplay_assistants[] = "Assistants";
static const char watchdisplay_clearall[] = "Clear all Watches";

static const char phasereason_0[] = "SUCCESSFUL"; // Phasewalk has been successful
static const char phasereason_1[] = "LOW MAG DIFF (DOWN TOO SLOW)"; // Down flick too slow, not satisfying the 14-magnitude difference rule
static const char phasereason_2[] = "POTENTIALLY INSUFFICIENT SPEED"; // No fast acceleration/Not enough power in fast accel
static const char phasereason_3[] = "BAD INITIAL ANGLE"; // Initial angle outside of bounds
static const char phasereason_4[] = "LOW MAG DIFF (OPPOSITE SIMILAR MAG)"; // Not satisfying the 14-magnitude difference rule because got to the other side with a magnitude similar in size
static const char phasereason_5[] = "READING INPUTS"; // Phasewalk in progress
static const char phasereason_6[] = "READY FOR SEQUENCE"; // In first person pre-phase sequence
static const char phasereason_7[] = "EARLY Z PRESS"; // Pressed Z before the 2f window
static const char phasereason_8[] = "LATE Z PRESS"; // Pressed Z after the 2f window
static const char phasereason_9[] = "LOW MAG DIFF (UP TOO SLOW)"; // Up flick too slow, not satisfying the 14-magnitude difference rule
static const char phasereason_10[] = "LOW MAG DIFF (RELEASE TOO SLOW)"; // Release too slow, not satisfying the 14-magnitude difference rule
static const char phasereason_11[] = "NO DOWN FLICK"; // Pretty self-explanatory
static const char phasereason_12[] = "POTENTIALLY SUBOPTIMAL ANGLE"; // Trunacted Angle < 150

static const char watches_player_indexes[] = {11,3,17,7,14,6,9,12,13};
static const char watches_timers_indexes[] = {4,5,10};
static const char watches_sysenv_indexes[] = {1,2,8};
static const char watches_assist_indexes[] = {16,-1};

static int watch_cache_slot0[] = {0,0,0,0};
static int watch_cache_slot1[] = {0,0,0,0};
static int watch_cache_slot2[] = {0,0,0,0};
static int watch_cache_slot3[] = {0,0,0,0};
static float watch_cache_slotf[] = {0,0,0,0};

static int* watch_cache_array[] = {
	watch_cache_slot0,
	watch_cache_slot1,
	watch_cache_slot2,
	watch_cache_slot3,
};

static const char* phasereason_list[] = {
	phasereason_0,
	phasereason_1,
	phasereason_2,
	phasereason_3,
	phasereason_4,
	phasereason_5,
	phasereason_6,
	phasereason_7,
	phasereason_8,
	phasereason_9,
	phasereason_10,
	phasereason_11,
	phasereason_12,
};

static float past_speeds[64];
static int speed_doc_index = 0;

void destroyWatch(int slot) {
	if (WatchActor[slot]) {
		deleteActor((void *)WatchActor[slot]);
		WatchActor[slot] = 0;
	}
};

void spawnWatch(int slot) {
	TextOverlay* textOverlay;
	int y = 210 - (slot * 13);
	destroyWatch(slot);
	spawnTextOverlay(10,25,y,"CALIBRATING",0,0,2,0);
	textOverlay = (TextOverlay *)CurrentActorPointer;
	if (textOverlay) {
		WatchActor[slot] = textOverlay;
		textOverlay->string = (char *)&WatchTextSpace[slot];
		//textOverlay->style = 128;
	}
};

void colorWatch(char _red, char _green, char _blue, int slot) {
	if (WatchActor[slot]) {
		WatchActor[slot]->red = _red;
		WatchActor[slot]->green = _green;
		WatchActor[slot]->blue = _blue;
	}
};

void controlWatchView(void) {
	for (int i = 0; i < WatchCount; i++) {
		if (WatchActor[i]) {
			if (ActiveMenu.isOpen) {
				WatchActor[i]->opacity = 0;
			} else {
				WatchActor[i]->opacity = 0xFF;
			}
		}
	}
}

void closeWatchesOnTransition(void) {
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		for (int i = 0; i < WatchCount; i++) {
			if (WatchActor[i]) {
				destroyWatch(i);
			}
		}
	}
}

void openWatchesOnTransition(void) {
	if ((TransitionSpeed < 0) || ((CutsceneActive == 6) && (CurrentMap != 0x50))) {
		for (int i = 0; i < WatchCount; i++) {
			if (WatchIndex[i]) {
				if (WatchActor[i] == 0) {
					spawnWatch(i);
				}
			}
		}
	}
};

static const char* watch_listed_array[] = {
	change_lag,
	change_avglag,
	change_speed,
	change_timer,
	change_gktimer,
	change_movement,
	change_angle,
	change_input,
	change_heldactor,
	change_isg,
	change_position,
	change_storedposition1,
	change_storedposition2,
	change_floor,
	0,
	change_phaseassistant,
	change_avgspd,
	change_fairy,
};

static const char* watch_viewed_array[] = {
	viewed_lag,
	viewed_avglag,
	viewed_speed,
	viewed_timer,
	viewed_gktimer,
	viewed_movement,
	viewed_angle,
	viewed_input,
	viewed_heldactor,
	viewed_isg,
	viewed_position,
	viewed_storedposition1,
	viewed_storedposition2,
	viewed_floor,
	0,
	viewed_phaseassistant,
	viewed_avgspd,
	viewed_fairy,
};

static const char* watch_change_array[] = {
	change_lag,
	change_avglag,
	change_speed,
	change_timer,
	change_gktimer,
	change_movement,
	change_angle,
	change_input,
	change_heldactor,
	change_isg,
	change_position,
	change_storedposition1,
	change_storedposition2,
	change_floor,
	0,
	change_phaseassistant,
	change_avgspd,
	change_fairy,
};

static const char* watch_player_array[] = {
	change_position,
	change_speed,
	change_avgspd,
	change_angle,
	change_floor,
	change_movement,
	change_heldactor,
	change_storedposition1,
	change_storedposition2,
};

static const char* watch_timers_array[] = {
	change_timer,
	change_gktimer,
	change_isg,
};

static const char* watch_sysenv_array[] = {
	change_lag,
	change_avglag,
	change_input,
};

static const char* watch_assist_array[] = {
	change_phaseassistant,
	change_fairy,
};

void openWatchMenu(void) {
	changeMenu(12);
};

void updateWatchText(void) {
	int _index;
	int watch_index = 0;
	for (int i = 0; i < (sizeof(watch_listed_array) / 4); i++) {
		watch_listed_array[i] = watch_change_array[i];
	}
	for (int i = 0; i < WatchCount; i++) {
		if (WatchIndex[i] != 0) {
			_index = WatchIndex[i] - 1;
			watch_listed_array[_index] = watch_viewed_array[_index];
		}
	}
	if (InputDisplayOpen) {
		watch_listed_array[7] = watch_viewed_array[7];
	} else {
		watch_listed_array[7] = watch_change_array[7];
	}
	if (FairyViewerOpen) {
		watch_listed_array[17] = watch_viewed_array[17];
	} else {
		watch_listed_array[17] = watch_change_array[17];
	}
	watch_assist_array[1] = watch_listed_array[17];
	for (int i = 0; i < sizeof(watches_player_indexes); i++) {
		watch_index = (int)watches_player_indexes[i] - 1;
		if (watch_index > -1) {
			watch_player_array[i] = watch_listed_array[watch_index];
		}
	}
	for (int i = 0; i < sizeof(watches_timers_indexes); i++) {
		watch_index = (int)watches_timers_indexes[i] - 1;
		if (watch_index > -1) {
			watch_timers_array[i] = watch_listed_array[watch_index];
		}
	}
	for (int i = 0; i < sizeof(watches_sysenv_indexes); i++) {
		watch_index = (int)watches_sysenv_indexes[i] - 1;
		if (watch_index > -1) {
			watch_sysenv_array[i] = watch_listed_array[watch_index];
		}
	}
	for (int i = 0; i < sizeof(watches_assist_indexes); i++) {
		watch_index = (int)watches_assist_indexes[i] - 1;
		if (watch_index > -1) {
			watch_assist_array[i] = watch_listed_array[watch_index];
		}
	}
}

void openWatchPlayerMenu(void) {
	updateWatchText();
	changeMenu(79);
}

void openWatchTimersMenu(void) {
	updateWatchText();
	changeMenu(80);
}

void openWatchSysMenu(void) {
	updateWatchText();
	changeMenu(81);
}

void openWatchAssistMenu(void) {
	updateWatchText();
	changeMenu(83);
}

void clearAllWatches(void) {
	InputDisplayOpen = 0;
	if (FairyViewerOpen) {
		toggleFairyViewer();
	}
	FairyViewerOpen = 0;
	closeOverlay();
	hideRacePosition(1);
	for (int i = 0; i < WatchCount; i++) {
		destroyWatch(i);
		WatchIndex[i] = 0;
		ViewedSnagWatches[i] = -1;
	}
}

void setWatch(void) {
	int i = 0;
	int intended_watch_index = 0;
	switch(ActiveMenu.screenIndex) {
		case 79:
			intended_watch_index = watches_player_indexes[(int)ActiveMenu.positionIndex];
			break;
		case 80:
			intended_watch_index = watches_timers_indexes[(int)ActiveMenu.positionIndex];
			break;
		case 81:
			intended_watch_index = watches_sysenv_indexes[(int)ActiveMenu.positionIndex];
			break;
		case 83:
			intended_watch_index = watches_assist_indexes[(int)ActiveMenu.positionIndex];
		break;
	}
	char index_already_spawned = 0;
	while (i < WatchCount) {
		if (WatchIndex[i] == intended_watch_index) {
			index_already_spawned = 1;
			break;
		};
		i++;
	};
	if (index_already_spawned) {
		destroyWatch(i);
		WatchIndex[i] = 0;
		hideRacePosition(1);
	} else {
		i = 0;
		while (i < WatchCount) {
			if (WatchIndex[i] == 0) {
				WatchIndex[i] = intended_watch_index;
				spawnWatch(i);
				colorWatch(0xFF,0xFF,0xFF,i);
				break;
			};
			i++;
		}
	}
	switch(ActiveMenu.screenIndex) {
		case 79:
			openWatchPlayerMenu();
			break;
		case 80:
			openWatchTimersMenu();
			break;
		case 81:
			openWatchSysMenu();
			break;
		case 83:
			openWatchAssistMenu();
		break;
	}
};

void togglePhaseAssistant(void) {
	PhaseChecker.assistant_on = 1 - PhaseChecker.assistant_on;
	PhaseChecker.reason_code = 6;
	setWatch();
}

void getISGTimer(void) {
	ISGTimer = 0;
	if (ISGActive) {
		if ((ISGTimestampMajor) || (ISGTimestampMinor)) {
			ISGTimer = getTimestampDiff(ISGTimestampMajor,ISGTimestampMinor);
		}
	}
};

void toggleInputDisplay(void) {
	InputDisplayOpen = 1 - InputDisplayOpen;
	if (InputDisplayOpen) {
		spawnOverlay();
	} else if (FairyViewerOpen == 0) {
		closeOverlay();
	}
	openWatchSysMenu();
};

void fairyViewerContainerToggle(void) {
	toggleFairyViewer();
	if (FairyViewerOpen) {
		spawnOverlay();
	} else if (InputDisplayOpen == 0) {
		closeOverlay();
	}
	openWatchAssistMenu();
}

static const char* watch_array[] = {
	watchdisplay_player,
	watchdisplay_timers,
	watchdisplay_sys,
	watchdisplay_snag,
	watchdisplay_assistants,
	watchdisplay_clearall,
};

static const int watch_functions[] = {
	(int)&openWatchPlayerMenu,
	(int)&openWatchTimersMenu,
	(int)&openWatchSysMenu,
	(int)&openWatchSnagMenu,
	(int)&openWatchAssistMenu,
	(int)&clearAllWatches,
};

const Screen watch_struct = {
	.TextArray = (int*)watch_array,
	.FunctionArray = watch_functions,
	.ArrayItems = 6,
	.ParentScreen = 0,
	.ParentPosition = 3
};

static const int watch_player_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
};

const Screen watch_player_struct = {
	.TextArray = (int*)watch_player_array,
	.FunctionArray = watch_player_functions,
	.ArrayItems = 9,
	.ParentScreen = 12,
	.ParentPosition = 0
};

static const int watch_timers_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
};

const Screen watch_timers_struct = {
	.TextArray = (int*)watch_timers_array,
	.FunctionArray = watch_timers_functions,
	.ArrayItems = 3,
	.ParentScreen = 12,
	.ParentPosition = 1
};

static const int watch_sysenv_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&toggleInputDisplay,
};

const Screen watch_sysenv_struct = {
	.TextArray = (int*)watch_sysenv_array,
	.FunctionArray = watch_sysenv_functions,
	.ArrayItems = 3,
	.ParentScreen = 12,
	.ParentPosition = 2
};

static const int watch_assist_functions[] = {
	(int)&togglePhaseAssistant,
	(int)&fairyViewerContainerToggle,
};

const Screen watch_assist_struct = {
	.TextArray = (int*)watch_assist_array,
	.FunctionArray = watch_assist_functions,
	.ArrayItems = 1,
	.ParentScreen = 12,
	.ParentPosition = 4
};

void clampWatchFloats(void) {
	int j;
	char _precision;
	char found_decimal;
	for (int i = 0; i < WatchCount; i++) {
		j = 0;
		found_decimal = 0;
		_precision = Precision;
		while (j < 0x30) {
			if (WatchTextSpace[i][j] == 0) {
				break;
			} else {
				if (WatchTextSpace[i][j] == 0x2E) { // "."
					found_decimal = 1;
					if (_precision == 0) {
						WatchTextSpace[i][j] = 0;
						break;
					} else {
						_precision += 2;
					}
				}
			}
			if (found_decimal) {
				_precision--;
				if (_precision == 0) {
					WatchTextSpace[i][j] = 0;
					break;
				}
			}
			j++;
		}
	}
};

void documentPastLag(void) {
	PreviousLagArray[(int)LagDocumentationIndex] = StoredLag;
	LagDocumentationIndex++;
	if (LagDocumentationIndex > 15) {
		LagDocumentationIndex = 0;
	}
}

void documentPastSpeed(void) {
	float spd = 0;
	if (Player) {
		spd = Player->hSpeed;
	}
	past_speeds[speed_doc_index] = spd;
	speed_doc_index++;
	if (speed_doc_index > 63) {
		speed_doc_index = 0;
	}
}

void handleWatch(void) {
	float _KRoolTimerX = 125;
	char watch_present = 0;
	documentPastLag();
	documentPastSpeed();
	if (ActiveMenu.isOpen == 0) {
		for (int j = 0; j < WatchCount; j++) {
			if (WatchIndex[j]) {
				watch_present = 1;
				colorWatch(0xFF,0xFF,0xFF,j);
				switch(WatchIndex[j]) {
					case 1:
						{
							// Lag
							if ((watch_cache_array[j][1] != StoredLag) || (watch_cache_array[j][0] != 1)) {
								dk_strFormat((char *)WatchTextSpace[j],"LAG: %d",StoredLag);
							}
							watch_cache_array[j][0] = 1;
							watch_cache_array[j][1] = StoredLag;
						}
						break;
					case 2:
						{
							// Average Lag
							int _lagsum = 0;
							for (int k = 0; k < 16; k++) {
								_lagsum += PreviousLagArray[k];
							}
							AverageLag = (float)(_lagsum) / 16;
							if ((watch_cache_array[j][1] != _lagsum) || (watch_cache_array[j][0] != 2)) {
								dk_strFormat((char *)WatchTextSpace[j],"AVERAGE LAG: %f",AverageLag);
							}
							watch_cache_array[j][0] = 2;
							watch_cache_array[j][1] = _lagsum;
						}
						break;
					case 3:
						{
							// Speed
							float _speed = 0;
							if (Player) {
								_speed = Player->hSpeed;
								if (_speed == 0) {
									if (Player->vehicle_actor_pointer) {
										actorData* vehicle = Player->vehicle_actor_pointer;
										_speed = vehicle->hSpeed;
									}
								}
							}
							if ((watch_cache_slotf[j] != _speed) || (watch_cache_array[j][0] != 3)) {
								dk_strFormat((char *)WatchTextSpace[j],"SPEED: %f",_speed);
							}
							watch_cache_array[j][0] = 3;
							watch_cache_slotf[j] = _speed;
						}
						break;
					case 4:
						{
							// Timer
							float _time = 0;
							int _timemins = 0;
							_time = TimerData.TimerPostReduction;
							_time = _time / 60;
							_timemins = (int)(float)(_time / 60);
							_time = _time - (60 * _timemins);
							if ((watch_cache_array[j][1] != TimerData.TimerPostReduction) || (watch_cache_array[j][0] != 4)) {
								if (_time >= 10) {
									dk_strFormat((char *)WatchTextSpace[j],"TIME: %2d:%f",_timemins,_time);
								} else {
									dk_strFormat((char *)WatchTextSpace[j],"TIME: %2d:0%f",_timemins,_time);
								}
							}
							watch_cache_array[j][0] = 4;
							watch_cache_array[j][1] = TimerData.TimerPostReduction;
						}
						break;
					case 5:
						{
							// GK Timer
							short _chunk = 0;
							if (CurrentMap == 0x48) {
								GiantKoshaTimerValue = 0;
								if (ObjectModel2Timer) {
									if (GiantKoshaTimerAddress) {
										GiantKoshaTimerValue = GiantKoshaTimerAddress->timer;
									}
								}
								if ((watch_cache_array[j][1] != GiantKoshaTimerValue) || (watch_cache_array[j][0] != 5)) {
									dk_strFormat((char *)WatchTextSpace[j],"KOSHA TIMER: %d",GiantKoshaTimerValue);
								}
								watch_cache_array[j][0] = 5;
								watch_cache_array[j][1] = GiantKoshaTimerValue;
								if (GiantKoshaTimerValue < 51) {
									colorWatch(0x8B,0x00,0x00,j);
								} else {
									if (GiantKoshaTimerValue < 101) {
										colorWatch(0xD2,0x69,0x1E,j);
									} else {
										if (GiantKoshaTimerValue < 201) {
											colorWatch(0xFF,0xD7,0x00,j);
										} else {
											if (Player) {
												_chunk = Player->chunk;
												if ((_chunk == 0) || (_chunk == 2) || (_chunk == 3) || (_chunk == 7)) {
													colorWatch(0x00,0x8B,0x8B,j);
												}
											}
										}
									}
								}
							} else {
								if ((watch_cache_array[j][1] != -1) || (watch_cache_array[j][0] != 5)) {
									dk_strFormat((char *)WatchTextSpace[j],"THIS AIN'T CAVES BUD");
								}
								watch_cache_array[j][0] = 5;
								watch_cache_array[j][1] = -1;
							};
						}
						break;
					case 6:
						{
							// Movement
							int _movement_state = 0;
							if (Player) {
								_movement_state = Player->control_state;
								if ((watch_cache_array[j][1] != _movement_state) || (watch_cache_array[j][0] != 6)) {
									dk_strFormat((char *)WatchTextSpace[j],"MOVEMENT STATE: 0x%X",_movement_state);
								}
								watch_cache_array[j][0] = 6;
								watch_cache_array[j][1] = _movement_state;
							} else {
								watch_cache_array[j][0] = 6;
								watch_cache_array[j][1] = -1;
							};
						}
						break;
					case 7:
						{
							// Angle
							float _angle = 0;
							if (Player) {
								_angle = Player->facing_angle % 4096;
								_angle = (_angle / 4096) * 360;
								if ((watch_cache_array[j][1] != Player->facing_angle) || (watch_cache_array[j][0] != 7)) {
									dk_strFormat((char *)WatchTextSpace[j],"ANGLE: %f",_angle);
								}
								watch_cache_array[j][0] = 7;
								watch_cache_array[j][1] = Player->facing_angle;
								if (Player->facing_angle >= 4096) {
									colorWatch(0xFF,0x45,0x00,j);
								};
							} else {
								watch_cache_array[j][0] = 7;
								watch_cache_array[j][1] = -1;
							};
						}
						break;
					case 9:
						{
							// Held Actor
							short held_actor_index = 0;
							if (Player) {
								if (Player->held_actor) {
									held_actor_index = Player->held_actor->actorType;
									if (isAddressActor(Player->held_actor)) {
										colorWatch(0xFF,0x45,0x00,j);
									}
									if ((watch_cache_array[j][1] != held_actor_index) || (watch_cache_array[j][0] != 9)) {
										dk_strFormat((char *)WatchTextSpace[j],"HELD ACTOR: %d",held_actor_index);
									}
									watch_cache_array[j][0] = 9;
									watch_cache_array[j][1] = held_actor_index;
								} else {
									if ((watch_cache_array[j][1] != -1) || (watch_cache_array[j][0] != 9)) {
										dk_strFormat((char *)WatchTextSpace[j],"NO ACTOR HELD");
									}
									watch_cache_array[j][0] = 9;
									watch_cache_array[j][1] = -1;
								};
							};
						}
						break;
					case 10:
						{
							// ISG Timer
							float _isgtime;
							int _isgmins;
							float _isgsecs;
							getISGTimer();
							_isgtime = 0;
							if (ISGActive && ((ISGTimestampMinor) || (ISGTimestampMajor))) {
								_isgtime = ISGTimer + 200;
								int i = 0;
								ISGStage = 0;
								while (i < 7) {
									if (ISGTimer < ISGFadeoutArray[i].FadeoutTime) {
										ISGStage = i;
										break;
									}
									i += 1;
								};
								if (ISGStage) {
									if (ISGStage != ISGPreviousFadeout) {
										colorWatch(0xFF,0x45,0x00,j);
									};
								};
								if ((ISGStage == 0) || (ISGStage != ISGPreviousFadeout)) {
									if (ISGFadeoutArray[i].FadeoutMap == DestMap) {
										if (TransitionSpeed > 0) {
											colorWatch(0xFF,0x00,0x00,j);
										};
									};
								};
							};
							_isgsecs = _isgtime / 100;
							_isgmins = (int)(float)(_isgsecs / 60);
							_isgsecs = _isgsecs - (60 * _isgmins);
							if ((watch_cache_array[j][1] != ISGTimer) || (watch_cache_array[j][0] != 10)) {
								if (_isgsecs >= 10) {
									dk_strFormat((char *)WatchTextSpace[j], "ISG TIME: %d:%f",_isgmins,_isgsecs);
								} else {
									dk_strFormat((char *)WatchTextSpace[j], "ISG TIME: %d:0%f",_isgmins,_isgsecs);
								}
							}
							watch_cache_array[j][0] = 10;
							watch_cache_array[j][1] = ISGTimer;
						}
						break;
					case 11:
						{
							int _x = 0;
							int _y = 0;
							int _z = 0;
							if (Player) {
								_x = Player->xPos;
								_y = Player->yPos;
								_z = Player->zPos;
							}
							if (((watch_cache_array[j][1] != _x) || (watch_cache_array[j][2] != _y) || (watch_cache_array[j][3] != _z)) || (watch_cache_array[j][0] != 11)) {
								dk_strFormat((char *)WatchTextSpace[j], "POSITION: %d, %d, %d",_x,_y,_z);
							}
							watch_cache_array[j][0] = 11;
							watch_cache_array[j][1] = _x;
							watch_cache_array[j][2] = _y;
							watch_cache_array[j][3] = _z;
						}
						break;
					case 12:
						{
							short xStored = 0;
							short yStored = 0;
							short zStored = 0;
							if (Player) {
								if (Player->rendering_param_pointer) {
									if (Player->rendering_param_pointer->bone_array1) {
										xStored = Player->rendering_param_pointer->bone_array1->xPos;
										yStored = Player->rendering_param_pointer->bone_array1->yPos;
										zStored = Player->rendering_param_pointer->bone_array1->zPos;
									}
								}
							}
							if (((watch_cache_array[j][1] != xStored) || (watch_cache_array[j][2] != yStored) || (watch_cache_array[j][3] != zStored)) || (watch_cache_array[j][0] != 12)) {
								dk_strFormat((char *)WatchTextSpace[j], "STORED POSITION 1: %d, %d, %d",xStored,yStored,zStored);
							}
							watch_cache_array[j][0] = 12;
							watch_cache_array[j][1] = xStored;
							watch_cache_array[j][2] = yStored;
							watch_cache_array[j][3] = zStored;
						}
						break;
					case 13:
						{
							short xStored = 0;
							short yStored = 0;
							short zStored = 0;
							if (Player) {
								if (Player->rendering_param_pointer) {
									if (Player->rendering_param_pointer->bone_array2) {
										xStored = Player->rendering_param_pointer->bone_array2->xPos;
										yStored = Player->rendering_param_pointer->bone_array2->yPos;
										zStored = Player->rendering_param_pointer->bone_array2->zPos;
									}
								}
							}
							if (((watch_cache_array[j][1] != xStored) || (watch_cache_array[j][2] != yStored) || (watch_cache_array[j][3] != zStored)) || (watch_cache_array[j][0] != 13)) {
								dk_strFormat((char *)WatchTextSpace[j], "STORED POSITION 2: %d, %d, %d",xStored,yStored,zStored);
							}
							watch_cache_array[j][0] = 13;
							watch_cache_array[j][1] = xStored;
							watch_cache_array[j][2] = yStored;
							watch_cache_array[j][3] = zStored;
						}
						break;
					case 14:
						{
							float _floor = 0;
							if (Player) {
								_floor = Player->floor;
							}
							if ((watch_cache_slotf[j] != _floor) || (watch_cache_array[j][0] != 14)) {
								dk_strFormat((char *)WatchTextSpace[j], "FLOOR: %f",_floor);
							}
							watch_cache_array[j][0] = 14;
							watch_cache_slotf[j] = _floor;
						}
						break;
					case 15:
						// Snag Watches
						{
							int snag_list_index = ViewedSnagWatches[j];
							int _map = snag_data[snag_list_index].map;
							int _id = snag_data[snag_list_index].om2_id;
							int* m2location = ObjectModel2Pointer;
							encodedSnagState snag_state = {
								.state = -1,
								.check = -1,
								.reset = -1,
								.spawned = -1,
							};
							int _m2_index = -1;
							if (m2location) {
								_m2_index = convertIDToIndex(_id);
								if (_m2_index > -1) {
									ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,_m2_index);
									snagData* _behaviour = _object->behaviour_pointer;
									if (_behaviour) {
										snag_state.check = _behaviour->check;
										snag_state.state = _behaviour->state;
										snag_state.reset = _behaviour->resettrigger;
										snag_state.spawned = 0;
									}
								}
							}
							if (_m2_index < 0) {
								snag_state.spawned = -1;
							}
							if (((watch_cache_array[j][1] != snag_list_index) || (watch_cache_array[j][2] != CurrentMap) || (watch_cache_array[j][3] != snag_state.data)) || (watch_cache_array[j][0] != 15)) {
								if (CurrentMap == _map) {
									if (_m2_index > -1) {
										if (snag_state.state) {
											dk_strFormat((char *)WatchTextSpace[j], "%s: UNCOLLECTABLE",snagwatch_names_array[j]);
										} else {
											dk_strFormat((char *)WatchTextSpace[j], "%s: COLLECTABLE",snagwatch_names_array[j]);
										}
									} else {
										dk_strFormat((char *)WatchTextSpace[j], "%s: NOT SPAWNED",snagwatch_names_array[j]);
									}
								} else {
									dk_strFormat((char *)WatchTextSpace[j], "%s: WRONG MAP",snagwatch_names_array[j]);
									colorWatch(0xFF,0xFF,0xFF,j);
								}
							}
							colorWatch(0xFF,0xFF,0xFF,j);
							if ((_m2_index > -1) && (CurrentMap == _map)) {
								if (snag_state.check != 0) {
									colorWatch(0xFF,0x45,0x00,j);
								}
							}
							watch_cache_array[j][0] = 15;
							watch_cache_array[j][1] = snag_list_index;
							watch_cache_array[j][2] = CurrentMap;
							watch_cache_array[j][3] = snag_state.data;
						}
						break;
					case 16:
						// Phasewalk Assistant
						{
							if ((watch_cache_array[j][1] != PhaseChecker.reason_code) || (watch_cache_array[j][0] != 16)) {
								dk_strFormat((char *)WatchTextSpace[j], "PWALK: %s",phasereason_list[(int)PhaseChecker.reason_code]);
							}
							watch_cache_array[j][0] = 16;
							watch_cache_array[j][1] = PhaseChecker.reason_code;
						}
						break;
					case 17:
						// Avg Speed
						{
							int _spdsum = 0;
							float _avgspd = 0;
							for (int k = 0; k < 64; k++) {
								_spdsum += past_speeds[k];
							}
							_avgspd = (float)(_spdsum) / 64;
							if ((watch_cache_array[j][1] != _spdsum) || (watch_cache_array[j][0] != 17)) {
								dk_strFormat((char *)WatchTextSpace[j],"AVERAGE SPEED: %f",_avgspd);
							}
							watch_cache_array[j][0] = 17;
							watch_cache_array[j][1] = _spdsum;
						}
					break;
				}
				_KRoolTimerX = 220;
			}
		}
	}
	if ((CurrentMap > 0xCA) && (CurrentMap < 0xD0) && (watch_present)) {
		if (Player) {
			if (Player->krool_timer_pointer) {
				Player->krool_timer_pointer->xPos = _KRoolTimerX;
			}
		}
	}
}