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

static const char* watch_array[] = {
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
};

void setWatch(void) {
	int i = 0;
	int intended_watch_index = ActiveMenu.positionIndex + 1;
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
		watch_array[(int)ActiveMenu.positionIndex] = watch_change_array[(int)ActiveMenu.positionIndex];
	} else {
		i = 0;
		while (i < WatchCount) {
			if (WatchIndex[i] == 0) {
				WatchIndex[i] = intended_watch_index;
				spawnWatch(i);
				colorWatch(0xFF,0xFF,0xFF,i);
				watch_array[(int)ActiveMenu.positionIndex] = watch_viewed_array[(int)ActiveMenu.positionIndex];
				break;
			};
			i++;
		}
	}
	changeMenu(12);
};

void openWatchMenu(void) {
	changeMenu(12);
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
	if (InputDisplayOpen) {
		watch_array[7] = watch_viewed_array[7];
	} else {
		watch_array[7] = watch_change_array[7];
	}
	openWatchMenu();
}

static const int watch_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&toggleInputDisplay,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch
};

const Screen watch_struct = {
	.TextArray = (int*)watch_array,
	.FunctionArray = watch_functions,
	.ArrayItems = 13,
	.ParentScreen = 0,
	.ParentPosition = 3
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
	documentPastLag();
	for (int j = 0; j < WatchCount; j++) {
		if (WatchIndex[j]) {
			watch_present = 1;
			colorWatch(0xFF,0xFF,0xFF,j);
			switch(WatchIndex[j]) {
				case 1:
					// Lag
					dk_strFormat((char *)WatchTextSpace[j],"Lag: %d",StoredLag);
					break;
				case 2:
					// Average Lag
					for (int k = 0; k < 16; k++) {
						_lagsum += PreviousLagArray[k];
					}
					AverageLag = (float)(_lagsum) / 16;
					dk_strFormat((char *)WatchTextSpace[j],"Average Lag: %f",AverageLag);
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
					dk_strFormat((char *)WatchTextSpace[j],"Speed: %f",_speed);
					break;
				case 4:
					// Timer
					_time = TimerData.TimerPostReduction;
					_time = _time / 60;
					_timemins = (int)(float)(_time / 60);
					_time = _time - (60 * _timemins);
					if (_time >= 10) {
						dk_strFormat((char *)WatchTextSpace[j],"Time: %2d:%f",_timemins,_time);
					} else {
						dk_strFormat((char *)WatchTextSpace[j],"Time: %2d:0%f",_timemins,_time);
					}
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
						dk_strFormat((char *)WatchTextSpace[j],"Kosha Timer: %d",GiantKoshaTimerValue);
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
						dk_strFormat((char *)WatchTextSpace[j],"This ain't Caves, Bud");
					};
					break;
				case 6:
					// Movement
					if (Player) {
						_movement_state = Player->control_state;
						dk_strFormat((char *)WatchTextSpace[j],"Movement State:0x%X",_movement_state);
					};
					break;
				case 7:
					// Angle
					if (Player) {
						_angle = Player->facing_angle % 4096;
						_angle = (_angle / 4096) * 360;
						dk_strFormat((char *)WatchTextSpace[j],"Angle: %f",_angle);
						if (Player->facing_angle >= 4096) {
							colorWatch(0xFF,0x45,0x00,j);
						};
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
							dk_strFormat((char *)WatchTextSpace[j],"Held Actor: %d",held_actor_index);
						} else {
							dk_strFormat((char *)WatchTextSpace[j],"No Actor Held");
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
					if (_isgsecs >= 10) {
						dk_strFormat((char *)WatchTextSpace[j], "ISG Time: %d:%f",_isgmins,_isgsecs);
					} else {
						dk_strFormat((char *)WatchTextSpace[j], "ISG Time: %d:0%f",_isgmins,_isgsecs);
					}
					break;
				case 11:
					if (Player) {
						_x = Player->xPos;
						_y = Player->yPos;
						_z = Player->zPos;
					}
					dk_strFormat((char *)WatchTextSpace[j], "Position: %d, %d, %d",_x,_y,_z);
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
					dk_strFormat((char *)WatchTextSpace[j], "Stored Position 1: %d, %d, %d",xStored,yStored,zStored);
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
					dk_strFormat((char *)WatchTextSpace[j], "Stored Position 2: %d, %d, %d",xStored,yStored,zStored);
				break;
			}
			_KRoolTimerX = 220;
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