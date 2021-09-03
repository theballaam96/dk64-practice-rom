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

static const char watchdisplay_player[] = "Player Variables";
static const char watchdisplay_sys[] = "System Environment";
static const char watchdisplay_timers[] = "Timers";
static const char watchdisplay_clearall[] = "Clear all Watches";

static const char watches_player_indexes[] = {11,3,7,14,6,9,12,13};
static const char watches_timers_indexes[] = {4,5};
static const char watches_sysenv_indexes[] = {1,2,8};

static int watch_cache_slot0[] = {0,0,0,0};
static int watch_cache_slot1[] = {0,0,0,0};
static int watch_cache_slot2[] = {0,0,0,0};
static int watch_cache_slot3[] = {0,0,0,0};

static int* watch_cache_array[] = {
	watch_cache_slot0,
	watch_cache_slot1,
	watch_cache_slot2,
	watch_cache_slot3,
};

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
	spawnTextOverlay(10,25,y,"Calibrating",0,0,2,0);
	textOverlay = (TextOverlay *)CurrentActorPointer;
	if (textOverlay) {
		WatchActor[slot] = textOverlay;
		textOverlay->string = (char *)&WatchTextSpace[slot];
		textOverlay->style = 128;
	}
	
};

void colorWatch(char _red, char _green, char _blue, int slot) {
	if (WatchActor[slot]) {
		WatchActor[slot]->red = _red;
		WatchActor[slot]->green = _green;
		WatchActor[slot]->blue = _blue;
	}
}

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
	for (int i = 0; i < WatchCount; i++) {
		if (WatchActor[i]) {
			if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
				destroyWatch(i);
			}
		}
	}
}

void openWatchesOnTransition(void) {
	for (int i = 0; i < WatchCount; i++) {
		if (WatchIndex[i]) {
			if (WatchActor[i] == 0) {
				if ((TransitionSpeed < 0) || ((CutsceneActive == 6) && (CurrentMap != 0x50))) {
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
};

static const char* watch_player_array[] = {
	change_position,
	change_speed,
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
};

static const char* watch_sysenv_array[] = {
	change_lag,
	change_avglag,
	change_input,
};

void openWatchMenu(void) {
	changeMenu(12);
};

void updateWatchText(void) {
	int _index;
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
	for (int i = 0; i < sizeof(watches_player_indexes); i++) {
		watch_player_array[i] = watch_listed_array[(int)watches_player_indexes[i] - 1];
	}
	for (int i = 0; i < sizeof(watches_timers_indexes); i++) {
		watch_timers_array[i] = watch_listed_array[(int)watches_timers_indexes[i] - 1];
	}
	for (int i = 0; i < sizeof(watches_sysenv_indexes); i++) {
		watch_sysenv_array[i] = watch_listed_array[(int)watches_sysenv_indexes[i] - 1];
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

void clearAllWatches(void) {
	InputDisplayOpen = 0;
	for (int i = 0; i < WatchCount; i++) {
		destroyWatch(i);
		WatchIndex[i] = 0;
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
	}
};

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
	openWatchMenu();
}

static const char* watch_array[] = {
	watchdisplay_player,
	watchdisplay_timers,
	watchdisplay_sys,
	watchdisplay_clearall,
};

static const int watch_functions[] = {
	(int)&openWatchPlayerMenu,
	(int)&openWatchTimersMenu,
	(int)&openWatchSysMenu,
	(int)&clearAllWatches,
};

const Screen watch_struct = {
	.TextArray = (int*)watch_array,
	.FunctionArray = watch_functions,
	.ArrayItems = 4,
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
};

const Screen watch_player_struct = {
	.TextArray = (int*)watch_player_array,
	.FunctionArray = watch_player_functions,
	.ArrayItems = 8,
	.ParentScreen = 12,
	.ParentPosition = 0
};

static const int watch_timers_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
};

const Screen watch_timers_struct = {
	.TextArray = (int*)watch_timers_array,
	.FunctionArray = watch_timers_functions,
	.ArrayItems = 2,
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

void handleWatch(void) {
	float _KRoolTimerX = 125;
	float _speed = 0;
	float _time = 0;
	char _timemins = 0;
	short _chunk = 0;
	float _angle = 0;
	short held_actor_index = 0;
	float _isgtime;
	char _isgmins;
	float _isgsecs;
	char watch_present = 0;
	int _x = 0;
	int _y = 0;
	int _z = 0;
	int _lagsum = 0;
	char _movement_state = 0;
	short xStored;
	short yStored;
	short zStored;
	float _floor;
	documentPastLag();
	if (ActiveMenu.isOpen == 0) {
		for (int j = 0; j < WatchCount; j++) {
			if (WatchIndex[j]) {
				watch_present = 1;
				colorWatch(0xFF,0xFF,0xFF,j);
				switch(WatchIndex[j]) {
					case 1:
						// Lag
						if ((watch_cache_array[j][1] != StoredLag) || (watch_cache_array[j][0] != 1)) {
							dk_strFormat((char *)WatchTextSpace[j],"Lag: %d",StoredLag);
						}
						watch_cache_array[j][0] = 1;
						watch_cache_array[j][1] = StoredLag;
						break;
					case 2:
						// Average Lag
						for (int k = 0; k < 16; k++) {
							_lagsum += PreviousLagArray[k];
						}
						AverageLag = (float)(_lagsum) / 16;
						if ((watch_cache_array[j][1] != _lagsum) || (watch_cache_array[j][0] != 2)) {
							dk_strFormat((char *)WatchTextSpace[j],"Average Lag: %f",AverageLag);
						}
						watch_cache_array[j][0] = 2;
						watch_cache_array[j][1] = _lagsum;
						break;
					case 3:
						// Speed
						if (Player) {
							_speed = Player->hSpeed;
							if (_speed == 0) {
								if (Player->vehicle_actor_pointer) {
									actorData* vehicle = Player->vehicle_actor_pointer;
									_speed = vehicle->hSpeed;
								}
							}
						}
						if ((watch_cache_array[j][1] != (int)_speed) || (watch_cache_array[j][0] != 3)) {
							dk_strFormat((char *)WatchTextSpace[j],"Speed: %f",_speed);
						}
						watch_cache_array[j][0] = 3;
						watch_cache_array[j][1] = (int)_speed;
						break;
					case 4:
						// Timer
						_time = TimerData.TimerPostReduction;
						_time = _time / 60;
						_timemins = (int)(float)(_time / 60);
						_time = _time - (60 * _timemins);
						if ((watch_cache_array[j][1] != TimerData.TimerPostReduction) || (watch_cache_array[j][0] != 4)) {
							if (_time >= 10) {
								dk_strFormat((char *)WatchTextSpace[j],"Time: %2d:%f",_timemins,_time);
							} else {
								dk_strFormat((char *)WatchTextSpace[j],"Time: %2d:0%f",_timemins,_time);
							}
						}
						watch_cache_array[j][0] = 4;
						watch_cache_array[j][1] = TimerData.TimerPostReduction;
						break;
					case 5:
						// GK Timer
						if (CurrentMap == 0x48) {
							GiantKoshaTimerValue = 0;
							if (ObjectModel2Timer) {
								if (GiantKoshaTimerAddress) {
									GiantKoshaTimerValue = GiantKoshaTimerAddress->timer;
								}
							}
							if ((watch_cache_array[j][1] != GiantKoshaTimerValue) || (watch_cache_array[j][0] != 5)) {
								dk_strFormat((char *)WatchTextSpace[j],"Kosha Timer: %d",GiantKoshaTimerValue);
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
								dk_strFormat((char *)WatchTextSpace[j],"This ain't Caves, Bud");
							}
							watch_cache_array[j][0] = 5;
							watch_cache_array[j][1] = -1;
						};
						break;
					case 6:
						// Movement
						if (Player) {
							_movement_state = Player->control_state;
							if ((watch_cache_array[j][1] != _movement_state) || (watch_cache_array[j][0] != 6)) {
								dk_strFormat((char *)WatchTextSpace[j],"Movement State: 0x%X",_movement_state);
							}
							watch_cache_array[j][0] = 6;
							watch_cache_array[j][1] = _movement_state;
						} else {
							watch_cache_array[j][0] = 6;
							watch_cache_array[j][1] = -1;
						};
						break;
					case 7:
						// Angle
						if (Player) {
							_angle = Player->facing_angle % 4096;
							_angle = (_angle / 4096) * 360;
							if ((watch_cache_array[j][1] != Player->facing_angle) || (watch_cache_array[j][0] != 7)) {
								dk_strFormat((char *)WatchTextSpace[j],"Angle: %f",_angle);
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
						break;
					case 8:
						// Input - Deprecated
						break;
					case 9:
						// Held Actor
						if (Player) {
							if (Player->held_actor) {
								held_actor_index = Player->held_actor->actorType;
								if (isAddressActor(Player->held_actor)) {
									colorWatch(0xFF,0x45,0x00,j);
								}
								if ((watch_cache_array[j][1] != held_actor_index) || (watch_cache_array[j][0] != 9)) {
									dk_strFormat((char *)WatchTextSpace[j],"Held Actor: %d",held_actor_index);
								}
								watch_cache_array[j][0] = 9;
								watch_cache_array[j][1] = held_actor_index;
							} else {
								if ((watch_cache_array[j][1] != -1) || (watch_cache_array[j][0] != 9)) {
									dk_strFormat((char *)WatchTextSpace[j],"No Actor Held");
								}
								watch_cache_array[j][0] = 9;
								watch_cache_array[j][1] = -1;
							};
						};
						break;
					case 10:
						// ISG Timer
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
								dk_strFormat((char *)WatchTextSpace[j], "ISG Time: %d:%f",_isgmins,_isgsecs);
							} else {
								dk_strFormat((char *)WatchTextSpace[j], "ISG Time: %d:0%f",_isgmins,_isgsecs);
							}
						}
						watch_cache_array[j][0] = 10;
						watch_cache_array[j][1] = ISGTimer;
						break;
					case 11:
						if (Player) {
							_x = Player->xPos;
							_y = Player->yPos;
							_z = Player->zPos;
						}
						if (((watch_cache_array[j][1] != _x) && (watch_cache_array[j][2] != _y) && (watch_cache_array[j][3] != _z)) || (watch_cache_array[j][0] != 11)) {
							dk_strFormat((char *)WatchTextSpace[j], "Position: %d, %d, %d",_x,_y,_z);
						}
						watch_cache_array[j][0] = 11;
						watch_cache_array[j][1] = _x;
						watch_cache_array[j][2] = _y;
						watch_cache_array[j][3] = _z;
						break;
					case 12:
						xStored = 0;
						yStored = 0;
						zStored = 0;
						if (Player) {
							if (Player->rendering_param_pointer) {
								if (Player->rendering_param_pointer->bone_array1) {
									xStored = Player->rendering_param_pointer->bone_array1->xPos;
									yStored = Player->rendering_param_pointer->bone_array1->yPos;
									zStored = Player->rendering_param_pointer->bone_array1->zPos;
								}
							}
						}
						if (((watch_cache_array[j][1] != xStored) && (watch_cache_array[j][2] != yStored) && (watch_cache_array[j][3] != zStored)) || (watch_cache_array[j][0] != 12)) {
							dk_strFormat((char *)WatchTextSpace[j], "Stored Position 1: %d, %d, %d",xStored,yStored,zStored);
						}
						watch_cache_array[j][0] = 12;
						watch_cache_array[j][1] = xStored;
						watch_cache_array[j][2] = yStored;
						watch_cache_array[j][3] = zStored;
						break;
					case 13:
						xStored = 0;
						yStored = 0;
						zStored = 0;
						if (Player) {
							if (Player->rendering_param_pointer) {
								if (Player->rendering_param_pointer->bone_array2) {
									xStored = Player->rendering_param_pointer->bone_array2->xPos;
									yStored = Player->rendering_param_pointer->bone_array2->yPos;
									zStored = Player->rendering_param_pointer->bone_array2->zPos;
								}
							}
						}
						if (((watch_cache_array[j][1] != xStored) && (watch_cache_array[j][2] != yStored) && (watch_cache_array[j][3] != zStored)) || (watch_cache_array[j][0] != 13)) {
							dk_strFormat((char *)WatchTextSpace[j], "Stored Position 2: %d, %d, %d",xStored,yStored,zStored);
						}
						watch_cache_array[j][0] = 13;
						watch_cache_array[j][1] = xStored;
						watch_cache_array[j][2] = yStored;
						watch_cache_array[j][3] = zStored;
					case 14:
						_floor = 0;
						if (Player) {
							_floor = Player->floor;
						}
						if ((watch_cache_array[j][1] != (int)_floor) || (watch_cache_array[j][0] != 14)) {
							dk_strFormat((char *)WatchTextSpace[j], "Floor: %f",_floor);
						}
						watch_cache_array[j][0] = 14;
						watch_cache_array[j][1] = (int)_floor;
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