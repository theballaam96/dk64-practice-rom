#include "../../include/common.h"

static const char viewed_lag[] = "LAG (!)";
static const char viewed_avglag[] = "AVERAGE LAG (!)";
static const char viewed_speed[] = "SPEED (!)";
static const char viewed_timer[] = "TIMER (!)";
static const char viewed_gktimer[] = "GIANT KOSHA TIMER (!)";
static const char viewed_movement[] = "MOVEMENT STATE (!)";
static const char viewed_angle[] = "ANGLE (!)";
static const char viewed_input[] = "INPUT (!)";
static const char viewed_heldactor[] = "HELD ACTOR (!)";
static const char viewed_isg[] = "INTRO STORY TIMER (!)";
static const char viewed_position[] = "POSITION (!)";

static const char change_lag[] = "LAG";
static const char change_avglag[] = "AVERAGE LAG";
static const char change_speed[] = "SPEED";
static const char change_timer[] = "TIMER";
static const char change_gktimer[] = "GIANT KOSHA TIMER";
static const char change_movement[] = "MOVEMENT STATE";
static const char change_angle[] = "ANGLE";
static const char change_input[] = "INPUT";
static const char change_heldactor[] = "HELD ACTOR";
static const char change_isg[] = "INTRO STORY TIMER";
static const char change_position[] = "POSITION";

void destroyWatch(int slot) {
	if (WatchActor[slot]) {
		deleteActor((void *)WatchActor[slot]);
		WatchActor[slot] = 0;
	}
};

void spawnWatch(int slot) {
	TextOverlay* textOverlay;
	int y = 200 - (slot * 10);
	if (InputDisplayIndex > -1) {
		if (slot > InputDisplayIndex) {
			y += 10;
		} else {
			if (slot == InputDisplayIndex) {
				y = 19;
			}
		}
	}
	destroyWatch(slot);
	spawnTextOverlay(10,25,y,"CALIBRATING",0,0,2,0);
	textOverlay = (TextOverlay *)CurrentActorPointer;
	if (textOverlay) {
		WatchActor[slot] = textOverlay;
		textOverlay->string = (char *)&WatchTextSpace[slot];
		if ((InputDisplayIndex == -1) || (slot != InputDisplayIndex)) {
			textOverlay->opacity = 0xFF;
		}
	}
	
};

void colorWatch(char _red, char _green, char _blue, int slot) {
	if (WatchActor[slot]) {
		WatchActor[slot]->red = _red;
		WatchActor[slot]->green = _green;
		WatchActor[slot]->blue = _blue;
	}
}

void closeWatchesOnTransition(void) {
	for (int i = 0; i < WatchCount; i++) {
		if (WatchActor[i]) {
			if ((TransitionSpeed > 0) || (CutsceneActive == 6)) {
				destroyWatch(i);
			}
		}
	}
}

void openWatchesOnTransition(void) {
	for (int i = 0; i < WatchCount; i++) {
		if (WatchIndex[i]) {
			if (WatchActor[i] == 0) {
				if (TransitionSpeed < 0) {
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
	change_position
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
	viewed_position
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
	change_position
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
		if (WatchIndex[i] == 8) {
			InputDisplayIndex = -1;
		}
		WatchIndex[i] = 0;
		watch_array[(int)ActiveMenu.positionIndex] = watch_change_array[(int)ActiveMenu.positionIndex];
	} else {
		i = 0;
		while (i < WatchCount) {
			if (WatchIndex[i] == 0) {
				WatchIndex[i] = intended_watch_index;
				if (intended_watch_index == 8) {
					InputDisplayIndex = i;
				}
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

static const int watch_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch
};

const Screen watch_struct = {
	.TextArray = (const int*)watch_array,
	.FunctionArray = watch_functions,
	.ArrayItems = 11,
	.ParentScreen = 0,
	.ParentPosition = 3
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
	documentPastLag();
	for (int j = 0; j < WatchCount; j++) {
		if (WatchIndex[j]) {
			watch_present = 1;
			colorWatch(0xFF,0xFF,0xFF,j);
			switch(WatchIndex[j]) {
				case 1:
					// Lag
					dk_strFormat((char *)WatchTextSpace[j],"LAG: %d",StoredLag);
					break;
				case 2:
					// Average Lag
					for (int k = 0; k < 16; k++) {
						_lagsum += PreviousLagArray[k];
					}
					AverageLag = (float)(_lagsum) / 16;
					dk_strFormat((char *)WatchTextSpace[j],"AVERAGE LAG: %f",AverageLag);
					break;
				case 3:
					// Speed
					if (Player) {
						_speed = Player->hSpeed;
					}
					dk_strFormat((char *)WatchTextSpace[j],"SPEED: %f",_speed);
					break;
				case 4:
					// Timer
					_time = TimerData.TimerPostReduction;
					_time = _time / 60;
					_timemins = (int)(float)(_time / 60);
					_time = _time - (60 * _timemins);
					if (_time >= 10) {
						dk_strFormat((char *)WatchTextSpace[j],"TIME: %2d:%f",_timemins,_time);
					} else {
						dk_strFormat((char *)WatchTextSpace[j],"TIME: %2d:0%f",_timemins,_time);
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
						dk_strFormat((char *)WatchTextSpace[j],"KOSHA TIMER: %d",GiantKoshaTimerValue);
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
						dk_strFormat((char *)WatchTextSpace[j],"THIS AIN'T CAVES, BUD");
					};
					break;
				case 6:
					// Movement
					if (Player) {
						_movement_state = Player->control_state;
						dk_strFormat((char *)WatchTextSpace[j],"MOVEMENT STATE:0x%X",_movement_state);
					};
					break;
				case 7:
					// Angle
					if (Player) {
						_angle = Player->facing_angle % 4096;
						_angle = (_angle / 4096) * 360;
						dk_strFormat((char *)WatchTextSpace[j],"ANGLE: %f",_angle);
						if (Player->facing_angle >= 4096) {
							colorWatch(0xFF,0x45,0x00,j);
						};
					};
					break;
				case 8:
					// Input
					dk_strFormat((char *)WatchTextSpace[j],"ABZSLR D:UDLR C:UDLR X:%d Y:%d",(int)ControllerInput.stickX,(int)ControllerInput.stickY);
					char _replace_char = 0x20;
					if ((ControllerInput.Buttons & A_Button) == 0) {
						WatchTextSpace[j][0] = _replace_char;
					}
					if ((ControllerInput.Buttons & B_Button) == 0) {
						WatchTextSpace[j][1] = _replace_char;
					}
					if ((ControllerInput.Buttons & Z_Button) == 0) {
						WatchTextSpace[j][2] = _replace_char;
					}
					if ((ControllerInput.Buttons & Start_Button) == 0) {
						WatchTextSpace[j][3] = _replace_char;
					}
					if ((ControllerInput.Buttons & L_Button) == 0) {
						WatchTextSpace[j][4] = _replace_char;
					}
					if ((ControllerInput.Buttons & R_Button) == 0) {
						WatchTextSpace[j][5] = _replace_char;
					}
					if ((ControllerInput.Buttons & D_Up) == 0) {
						WatchTextSpace[j][9] = _replace_char;
					}
					if ((ControllerInput.Buttons & D_Down) == 0) {
						WatchTextSpace[j][10] = _replace_char;
					}
					if ((ControllerInput.Buttons & D_Left) == 0) {
						WatchTextSpace[j][11] = _replace_char;
					}
					if ((ControllerInput.Buttons & D_Right) == 0) {
						WatchTextSpace[j][12] = _replace_char;
					}
					if ((ControllerInput.Buttons & C_Up) == 0) {
						WatchTextSpace[j][16] = _replace_char;
					}
					if ((ControllerInput.Buttons & C_Down) == 0) {
						WatchTextSpace[j][17] = _replace_char;
					}
					if ((ControllerInput.Buttons & C_Left) == 0) {
						WatchTextSpace[j][18] = _replace_char;
					}
					if ((ControllerInput.Buttons & C_Right) == 0) {
						WatchTextSpace[j][19] = _replace_char;
					}
					break;
				case 9:
					// Held Actor
					if (Player) {
						if (Player->held_actor) {
							held_actor_index = Player->held_actor->actorType;
							if (isAddressActor(Player->held_actor)) {
								colorWatch(0xFF,0x45,0x00,j);
							}
							dk_strFormat((char *)WatchTextSpace[j],"HELD ACTOR: %d",held_actor_index);
						} else {
							dk_strFormat((char *)WatchTextSpace[j],"NO ACTOR HELD");
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
						dk_strFormat((char *)WatchTextSpace[j], "ISG TIME: %d:%f",_isgmins,_isgsecs);
					} else {
						dk_strFormat((char *)WatchTextSpace[j], "ISG TIME: %d:0%f",_isgmins,_isgsecs);
					}
					break;
				case 11:
					if (Player) {
						_x = Player->xPos;
						_y = Player->yPos;
						_z = Player->zPos;
					}
					dk_strFormat((char *)WatchTextSpace[j], "POSITION: %d, %d, %d",_x,_y,_z);
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