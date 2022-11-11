#include "../../include/common.h"

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
static const char phasereason_13[] = "PHASE LOST DUE TO UNKNOWN CAUSES"; // idk wtf happened

static const char fakekey_0[] = "WRONG MAP";
static const char fakekey_1[] = "FAKE";
static const char fakekey_2[] = "REAL";
static const char fakekey_3[] = "KEY OBTAINED";
static const char fakekey_4[] = "UNKNOWN";
static const char fakekey_5[] = "KEY NOT IN MAP";

static const char fakeprodroom_0[] = "WRONG MAP";
static const char fakeprodroom_1[] = "PROD ROOM OFF";
static const char fakeprodroom_2[] = "UNKNOWN";
static const char fakeprodroom_3[] = "NOT LOADED";
static const char fakeprodroom_4[] = "PREPARING BEING FAKE";
static const char fakeprodroom_5[] = "FAKE";
static const char fakeprodroom_6[] = "REAL";

static int watch_cache_slot0[] = {0,0,0,0};
static int watch_cache_slot1[] = {0,0,0,0};
static int watch_cache_slot2[] = {0,0,0,0};
static int watch_cache_slot3[] = {0,0,0,0};
static float watch_cache_slotf[] = {0,0,0,0};

static float player_ref_x = 0.0f;
static float player_ref_z = 0.0f;
static char player_ref_bool = 0;

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
	phasereason_13,
};

static const char* fakekey_list[] = {
	fakekey_0,
	fakekey_1,
	fakekey_2,
	fakekey_3,
	fakekey_4,
	fakekey_5,
};

static const char* fakeprodroom_list[] = {
	fakeprodroom_0,
	fakeprodroom_1,
	fakeprodroom_2,
	fakeprodroom_3,
	fakeprodroom_4,
	fakeprodroom_5,
	fakeprodroom_6,
};

static float past_speeds[64];
static int speed_doc_index = 0;
static unsigned char watch_red[WatchCount];
static unsigned char watch_green[WatchCount];
static unsigned char watch_blue[WatchCount];

void colorWatch(char _red, char _green, char _blue, int slot) {
	watch_red[slot] = _red;
	watch_green[slot] = _green;
	watch_blue[slot] = _blue;
};

int* displayWatches(int* dl) {
	int y = 0;
	int k = 0;
	for (int i = 0; i < WatchCount; i++) {
		if (WatchIndex[i]) {
			y = 340 - (k++ * 13);
			if (ROM_VERSION < 2) {
				dl = drawTextContainer(dl, 6, 20, y, (char*)WatchTextSpace[i], watch_red[i], watch_green[i], watch_blue[i], 0xFF, 0);
			} else {
				dl = drawPixelTextContainer(dl, 20, y - 130, (char*)WatchTextSpace[i], watch_red[i], watch_green[i], watch_blue[i], 0xFF,0);
			}
		}
	}
	return dl;
}

void checkWatchCapacity(void) {
	int slot_vacant = 0;
	for (int i = 0; i < WatchCount; i++) {
		if (WatchIndex[i] == 0) {
			slot_vacant = 1;
		}
	}
	if (!slot_vacant) {
		NoVacantWatchTimer = HERTZ;;
	}
}

static char float_str[22] = {};
//static float test_floats[2] = {};

void openWatchMenu(void) {
	changeMenu(ACTIVEMENU_SCREEN_WATCH_ROOT);
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
		watch_listed_array[WATCH_INPUT_INDEX - 1] = watch_viewed_array[WATCH_INPUT_INDEX - 1];
	} else {
		watch_listed_array[WATCH_INPUT_INDEX - 1] = watch_change_array[WATCH_INPUT_INDEX - 1];
	}
	if (FairyViewerOpen) {
		watch_listed_array[WATCH_FAIRY_INDEX - 1] = watch_viewed_array[WATCH_FAIRY_INDEX - 1];
	} else {
		watch_listed_array[WATCH_FAIRY_INDEX - 1] = watch_change_array[WATCH_FAIRY_INDEX - 1];
	}
	watch_assist_array[1] = watch_listed_array[WATCH_FAIRY_INDEX - 1];
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
	for (int i = 0; i < sizeof(watches_fake_indexes); i++) {
		watch_index = (int)watches_fake_indexes[i] - 1;
		if (watch_index > -1) {
			watch_fake_array[i] = watch_listed_array[watch_index];
		}
	}
}

void openWatchPlayerMenu(void) {
	updateWatchText();
	changeMenu(ACTIVEMENU_SCREEN_WATCH_PLAYER);
}

void openWatchTimersMenu(void) {
	updateWatchText();
	changeMenu(ACTIVEMENU_SCREEN_WATCH_TIMERS);
}

void openWatchSysMenu(void) {
	updateWatchText();
	changeMenu(ACTIVEMENU_SCREEN_WATCH_SYSTEM);
}

void openWatchAssistMenu(void) {
	updateWatchText();
	changeMenu(ACTIVEMENU_SCREEN_WATCH_ASSISTS);
}

void openWatchFakeMenu(void) {
	updateWatchText();
	changeMenu(ACTIVEMENU_SCREEN_WATCH_FAKE);
}

void clearAllWatches(void) {
	InputDisplayOpen = 0;
	if (FairyViewerOpen) {
		toggleFairyViewer();
	}
	FairyViewerOpen = 0;
	doubleBeaverEnabledBitfield = 0;
	closeOverlay();
	PhaseChecker.assistant_on = 0;
	PhaseChecker.reason_code = 6;
	hideRacePosition(1);
	for (int i = 0; i < WatchCount; i++) {
		WatchIndex[i] = 0;
		ViewedSnagWatches[i] = -1;
		dynamic_watches[i].used = -1;
	}
}

void setWatch(void) {
	int i = 0;
	int intended_watch_index = 0;
	switch(ActiveMenu.screenIndex) {
		case ACTIVEMENU_SCREEN_WATCH_PLAYER:
			intended_watch_index = watches_player_indexes[(int)ActiveMenu.positionIndex];
			break;
		case ACTIVEMENU_SCREEN_WATCH_TIMERS:
			intended_watch_index = watches_timers_indexes[(int)ActiveMenu.positionIndex];
			break;
		case ACTIVEMENU_SCREEN_WATCH_SYSTEM:
			intended_watch_index = watches_sysenv_indexes[(int)ActiveMenu.positionIndex];
			break;
		case ACTIVEMENU_SCREEN_WATCH_ASSISTS:
			intended_watch_index = watches_assist_indexes[(int)ActiveMenu.positionIndex];
			break;
		case ACTIVEMENU_SCREEN_WATCH_FAKE:
			intended_watch_index = watches_fake_indexes[(int)ActiveMenu.positionIndex];
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
		WatchIndex[i] = 0;
		hideRacePosition(1);
	} else {
		checkWatchCapacity();
		i = 0;
		while (i < WatchCount) {
			if (WatchIndex[i] == 0) {
				WatchIndex[i] = intended_watch_index;
				colorWatch(0xFF,0xFF,0xFF,i);
				break;
			};
			i++;
		}
	}
	switch(ActiveMenu.screenIndex) {
		case ACTIVEMENU_SCREEN_WATCH_PLAYER:
			openWatchPlayerMenu();
			break;
		case ACTIVEMENU_SCREEN_WATCH_TIMERS:
			openWatchTimersMenu();
			break;
		case ACTIVEMENU_SCREEN_WATCH_SYSTEM:
			openWatchSysMenu();
			break;
		case ACTIVEMENU_SCREEN_WATCH_ASSISTS:
			openWatchAssistMenu();
			break;
		case ACTIVEMENU_SCREEN_WATCH_FAKE:
			openWatchFakeMenu();
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
	InputDisplayOpen = 1 ^ InputDisplayOpen;
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

void setReferencePosition(void) {
	if (Player) {
		player_ref_x = Player->xPos;
		player_ref_z = Player->zPos;
		player_ref_bool = 1;
		playSFX(61);
	}
}

static const char* watch_array[] = {
	"PLAYER VARIABLES",
	"TIMERS",
	"SYSTEM ENVIRONMENT",
	"SPAWN SNAG COLLECTABLES",
	"ASSISTANTS",
	"FAKE ITEMS",
	"DYNAMIC WATCHES",
	"BEAVER BOTHER",
	"SET REFERENCE POINT",
	"CLEAR ALL WATCHES",
};

static const int watch_functions[] = {
	(int)&openWatchPlayerMenu,
	(int)&openWatchTimersMenu,
	(int)&openWatchSysMenu,
	(int)&openWatchSnagMenu,
	(int)&openWatchAssistMenu,
	(int)&openWatchFakeMenu,
	(int)&openDynwatchScreen,
	(int)&openBeaverBotherMenu,
	(int)&setReferencePosition,
	(int)&clearAllWatches,
};

static const char watch_access[] = {
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Player Vars
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Timers
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // System Environment
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Snag Watches
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Assistants
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Fake Items
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_EMU, // Dynamic
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Beaver Bother
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Reference Position
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Clear All
};

const Screen watch_struct = {
	.TextArray = (int*)watch_array,
	.FunctionArray = watch_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 3,
	.hasAccessArray = 1,
	.AccessArray = watch_access,
};

const char watch_assist_access[] = {
	ACCESS_US | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU,
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU,
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

void stringConcat(char* dest,char* str1,char* str2) {
	int offset = 0;
	for (int i = 0; i < 2; i++) {
		int stop_str = 0;
		int str_offset = 0;
		while (!stop_str) {
			if (i == 0) {
				stop_str = str1[str_offset] == 0;
			} else {
				stop_str = str2[str_offset] == 0;
			}
			if (!stop_str) {
				if (i == 0) {
					dest[offset++] = str1[str_offset++];
				} else {
					dest[offset++] = str2[str_offset++];
				}
			}
		}
	}
	dest[offset++] = 0;
}

void reverse(char* str, int len) {
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int intToStr(int x, char str[], int digits) {
	int i = 0;
	if (x < 0) {
		str[i] = 0x2D;
		x = -x;
		i = 1;
	}
	while (x) {
		str[i++] = (x % 10) + 0x30;
		x /= 10;
	}
	// If num digits is more, add 0s at beginning
	while (i < digits) {
		str[i++] = 0x30;
	}
	reverse(str,i);
	str[i] = 0;
	return i;
}

void floatToString(float flt, char* res, int precision) {
	int is_negative = flt < 0;
	if (is_negative) {
		flt = -flt;
	}
	// Extract integer part
	int ipart = (int)(flt + 0);

	// Extract floating part
	float fpart = (flt + 0) - (float)ipart;
	// test_floats[0] = flt;
	// test_floats[1] = fpart;
	// TestVariable = (int)&test_floats;

	// convert int to string
	int i = intToStr(ipart, res + is_negative, 1);
	i += is_negative;
	if (is_negative) {
		res[0] = 0x2D;
	}
	int pow = 1;

	if (precision != 0) {
		for (int k = 0; k < precision; k++) {
			pow *= 10;
		}
		res[i] = 0x2E;
		fpart *= pow;
		intToStr((int)fpart, res + i + 1, precision);
	}
}

typedef enum format_mode {
	FLOAT_TYPE,
	INT_TYPE,
} format_mode;

void headerFormatter(char* header, float _fval, int _ival, format_mode mode, int watch_index) {
	if (mode == 0) {
		floatToString(_fval,float_str,Precision);
	} else {
		intToStr(_ival,float_str,1);
	}
	stringConcat((char*)WatchTextSpace[watch_index],header,float_str);
}

#define IGT_STATE_LOCKED 0
#define IGT_STATE_CANSAVE 1

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
					case WATCH_LAG_INDEX:
						{
							// Lag
							if ((watch_cache_array[j][1] != StoredLag) || (watch_cache_array[j][0] != WATCH_LAG_INDEX)) {
								headerFormatter("LAG: ",0,StoredLag,INT_TYPE,j);
								//dk_strFormat((char *)WatchTextSpace[j],"LAG: %d",StoredLag);
							}
							watch_cache_array[j][0] = WATCH_LAG_INDEX;
							watch_cache_array[j][1] = StoredLag;
						}
						break;
					case WATCH_AVGLAG_INDEX:
						{
							// Average Lag
							int _lagsum = 0;
							for (int k = 0; k < 16; k++) {
								_lagsum += PreviousLagArray[k];
							}
							AverageLag = (float)(_lagsum) / 16;
							if ((watch_cache_array[j][1] != _lagsum) || (watch_cache_array[j][0] != WATCH_AVGLAG_INDEX)) {
								headerFormatter("AVERAGE LAG: ",AverageLag,0,FLOAT_TYPE,j);
								// floatToString(AverageLag,float_str,Precision);
								// stringConcat((char *)WatchTextSpace[j],"AVERAGE LAG: ",float_str);
								//dk_strFormat((char *)WatchTextSpace[j],"AVERAGE LAG: %f",AverageLag);
							}
							watch_cache_array[j][0] = WATCH_AVGLAG_INDEX;
							watch_cache_array[j][1] = _lagsum;
						}
						break;
					case WATCH_SPEED_INDEX:
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
							if ((watch_cache_slotf[j] != _speed) || (watch_cache_array[j][0] != WATCH_SPEED_INDEX)) {
								headerFormatter("SPEED: ",_speed,0,FLOAT_TYPE,j);
							}
							watch_cache_array[j][0] = WATCH_SPEED_INDEX;
							watch_cache_slotf[j] = _speed;
						}
						break;
					case WATCH_TIMER_INDEX:
						{
							// Timer
							float _time = 0;
							int _timemins = 0;
							_time = TimerData.TimerPostReduction;
							_time = _time / HERTZ;
							_timemins = (int)(float)(_time / HERTZ);
							_time = _time - (60 * _timemins);
							if ((watch_cache_array[j][1] != TimerData.TimerPostReduction) || (watch_cache_array[j][0] != WATCH_TIMER_INDEX)) {
								if (_time >= 10) {
									dk_strFormat((char *)WatchTextSpace[j],"TIME: %2d:%f",_timemins,_time);
								} else {
									dk_strFormat((char *)WatchTextSpace[j],"TIME: %2d:0%f",_timemins,_time);
								}
							}
							watch_cache_array[j][0] = WATCH_TIMER_INDEX;
							watch_cache_array[j][1] = TimerData.TimerPostReduction;
						}
						break;
					case WATCH_GKTIMER_INDEX:
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
								if ((watch_cache_array[j][1] != GiantKoshaTimerValue) || (watch_cache_array[j][0] != WATCH_GKTIMER_INDEX)) {
									headerFormatter("KOSHA TIMER: ",0,GiantKoshaTimerValue,INT_TYPE,j);
								}
								watch_cache_array[j][0] = WATCH_GKTIMER_INDEX;
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
								if ((watch_cache_array[j][1] != -1) || (watch_cache_array[j][0] != WATCH_GKTIMER_INDEX)) {
									stringConcat((char *)WatchTextSpace[j],"THIS AIN'T CAVES BUD","");
									//dk_strFormat((char *)WatchTextSpace[j],"THIS AIN'T CAVES BUD");
								}
								watch_cache_array[j][0] = WATCH_GKTIMER_INDEX;
								watch_cache_array[j][1] = -1;
							};
						}
						break;
					case WATCH_MOVEMENT_INDEX:
						{
							// Movement
							int _movement_state = 0;
							if (Player) {
								_movement_state = Player->control_state;
								if ((watch_cache_array[j][1] != _movement_state) || (watch_cache_array[j][0] != WATCH_MOVEMENT_INDEX)) {
									dk_strFormat((char *)WatchTextSpace[j],"MOVEMENT STATE: 0x%X",_movement_state);
								}
								watch_cache_array[j][0] = WATCH_MOVEMENT_INDEX;
								watch_cache_array[j][1] = _movement_state;
							} else {
								watch_cache_array[j][0] = WATCH_MOVEMENT_INDEX;
								watch_cache_array[j][1] = -1;
							};
						}
						break;
					case WATCH_ANGLE_INDEX:
						{
							// Angle
							float _angle = 0;
							if (Player) {
								_angle = Player->facing_angle % 4096;
								_angle = (_angle / 4096) * 360;
								if ((watch_cache_array[j][1] != Player->facing_angle) || (watch_cache_array[j][0] != WATCH_ANGLE_INDEX)) {
									headerFormatter("ANGLE: ",_angle,0,FLOAT_TYPE,j);
								}
								watch_cache_array[j][0] = WATCH_ANGLE_INDEX;
								watch_cache_array[j][1] = Player->facing_angle;
								if (Player->facing_angle >= 4096) {
									colorWatch(0xFF,0x45,0x00,j);
								};
							} else {
								watch_cache_array[j][0] = WATCH_ANGLE_INDEX;
								watch_cache_array[j][1] = -1;
							};
						}
						break;
					case WATCH_HELDACTOR_INDEX:
						{
							// Held Actor
							short held_actor_index = 0;
							if (Player) {
								if (Player->held_actor) {
									held_actor_index = Player->held_actor->actorType;
									if (isAddressActor(Player->held_actor)) {
										colorWatch(0xFF,0x45,0x00,j);
									}
									if ((watch_cache_array[j][1] != held_actor_index) || (watch_cache_array[j][0] != WATCH_HELDACTOR_INDEX)) {
										headerFormatter("HELD ACTOR: ",0,held_actor_index,INT_TYPE,j);
									}
									watch_cache_array[j][0] = WATCH_HELDACTOR_INDEX;
									watch_cache_array[j][1] = held_actor_index;
								} else {
									if ((watch_cache_array[j][1] != -1) || (watch_cache_array[j][0] != WATCH_HELDACTOR_INDEX)) {
										stringConcat((char *)WatchTextSpace[j],"NO ACTOR HELD","");
									}
									watch_cache_array[j][0] = WATCH_HELDACTOR_INDEX;
									watch_cache_array[j][1] = -1;
								};
							};
						}
						break;
					case WATCH_ISG_INDEX:
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
							_isgmins = (int)(float)(_isgsecs / HERTZ);
							_isgsecs = _isgsecs - (60 * _isgmins);
							if ((watch_cache_array[j][1] != ISGTimer) || (watch_cache_array[j][0] != WATCH_ISG_INDEX)) {
								if (_isgsecs >= 10) {
									dk_strFormat((char *)WatchTextSpace[j], "ISG TIME: %d:%f",_isgmins,_isgsecs);
								} else {
									dk_strFormat((char *)WatchTextSpace[j], "ISG TIME: %d:0%f",_isgmins,_isgsecs);
								}
							}
							watch_cache_array[j][0] = WATCH_ISG_INDEX;
							watch_cache_array[j][1] = ISGTimer;
						}
						break;
					case WATCH_POSITION_INDEX:
						{
							int _x = 0;
							int _y = 0;
							int _z = 0;
							if (Player) {
								_x = Player->xPos;
								_y = Player->yPos;
								_z = Player->zPos;
							}
							if (((watch_cache_array[j][1] != _x) || (watch_cache_array[j][2] != _y) || (watch_cache_array[j][3] != _z)) || (watch_cache_array[j][0] != WATCH_POSITION_INDEX)) {
								// intToStr(_x,float_str,0);
								// stringConcat((char*)WatchTextSpace[j],"POSITION",float_str);
								// intToStr(_y,float_str,0);
								// stringConcat((char*)WatchTextSpace[j],(char*)WatchTextSpace[j],float_str);
								// intToStr(_z,float_str,0);
								// stringConcat((char*)WatchTextSpace[j],(char*)WatchTextSpace[j],float_str);
								dk_strFormat((char *)WatchTextSpace[j], "POSITION: %d, %d, %d",_x,_y,_z);
							}
							watch_cache_array[j][0] = WATCH_POSITION_INDEX;
							watch_cache_array[j][1] = _x;
							watch_cache_array[j][2] = _y;
							watch_cache_array[j][3] = _z;
						}
						break;
					case WATCH_STOREDPOSITION1_INDEX:
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
							if (((watch_cache_array[j][1] != xStored) || (watch_cache_array[j][2] != yStored) || (watch_cache_array[j][3] != zStored)) || (watch_cache_array[j][0] != WATCH_STOREDPOSITION1_INDEX)) {
								dk_strFormat((char *)WatchTextSpace[j], "STORED POSITION 1: %d, %d, %d",xStored,yStored,zStored);
							}
							watch_cache_array[j][0] = WATCH_STOREDPOSITION1_INDEX;
							watch_cache_array[j][1] = xStored;
							watch_cache_array[j][2] = yStored;
							watch_cache_array[j][3] = zStored;
						}
						break;
					case WATCH_STOREDPOSITION2_INDEX:
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
							if (((watch_cache_array[j][1] != xStored) || (watch_cache_array[j][2] != yStored) || (watch_cache_array[j][3] != zStored)) || (watch_cache_array[j][0] != WATCH_STOREDPOSITION2_INDEX)) {
								dk_strFormat((char *)WatchTextSpace[j], "STORED POSITION 2: %d, %d, %d",xStored,yStored,zStored);
							}
							watch_cache_array[j][0] = WATCH_STOREDPOSITION2_INDEX;
							watch_cache_array[j][1] = xStored;
							watch_cache_array[j][2] = yStored;
							watch_cache_array[j][3] = zStored;
						}
						break;
					case WATCH_FLOOR_INDEX:
						{
							float _floor = 0;
							if (Player) {
								_floor = Player->floor;
							}
							if ((watch_cache_slotf[j] != _floor) || (watch_cache_array[j][0] != WATCH_FLOOR_INDEX)) {
								headerFormatter("FLOOR: ",_floor,0,FLOAT_TYPE,j);
							}
							watch_cache_array[j][0] = WATCH_FLOOR_INDEX;
							watch_cache_slotf[j] = _floor;
						}
						break;
					case WATCH_SPAWNSNAG_INDEX:
						// Snag Watches
						{
							int snag_list_index = ViewedSnagWatches[j];
							int _map = snag_data[snag_list_index].map;
							int _id = snag_data[snag_list_index].om2_id;
							int* m2location = (int*)ObjectModel2Pointer;
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
							if (((watch_cache_array[j][1] != snag_list_index) || (watch_cache_array[j][2] != CurrentMap) || (watch_cache_array[j][3] != snag_state.data)) || (watch_cache_array[j][0] != WATCH_SPAWNSNAG_INDEX)) {
								if (CurrentMap == _map) {
									if (_m2_index > -1) {
										if (snag_state.state) {
											stringConcat((char *)WatchTextSpace[j],(char*)snagwatch_names_array[j],": UNCOLLECTABLE");
										} else {
											stringConcat((char *)WatchTextSpace[j],(char*)snagwatch_names_array[j],": COLLECTABLE");
										}
									} else {
										stringConcat((char *)WatchTextSpace[j],(char*)snagwatch_names_array[j],": NOT SPAWNED");
									}
								} else {
									stringConcat((char *)WatchTextSpace[j],(char*)snagwatch_names_array[j],": WRONG MAP");
									colorWatch(0xFF,0xFF,0xFF,j);
								}
							}
							colorWatch(0xFF,0xFF,0xFF,j);
							if ((_m2_index > -1) && (CurrentMap == _map)) {
								if (snag_state.check != 0) {
									colorWatch(0xFF,0x45,0x00,j);
								}
							}
							watch_cache_array[j][0] = WATCH_SPAWNSNAG_INDEX;
							watch_cache_array[j][1] = snag_list_index;
							watch_cache_array[j][2] = CurrentMap;
							watch_cache_array[j][3] = snag_state.data;
						}
						break;
					case WATCH_PHASEASSISTANT_INDEX:
						// Phasewalk Assistant
						{
							if ((watch_cache_array[j][1] != PhaseChecker.reason_code) || (watch_cache_array[j][0] != WATCH_PHASEASSISTANT_INDEX)) {
								stringConcat((char *)WatchTextSpace[j],"PWALK: ",(char*)phasereason_list[(int)PhaseChecker.reason_code]);
							}
							watch_cache_array[j][0] = WATCH_PHASEASSISTANT_INDEX;
							watch_cache_array[j][1] = PhaseChecker.reason_code;
						}
						break;
					case WATCH_AVGSPD_INDEX:
						// Avg Speed
						{
							int _spdsum = 0;
							float _avgspd = 0;
							for (int k = 0; k < 64; k++) {
								_spdsum += past_speeds[k];
							}
							_avgspd = (float)(_spdsum) / 64;
							if ((watch_cache_array[j][1] != _spdsum) || (watch_cache_array[j][0] != WATCH_AVGSPD_INDEX)) {
								headerFormatter("AVERAGE SPEED: ",_avgspd,0,FLOAT_TYPE,j);
							}
							watch_cache_array[j][0] = WATCH_AVGSPD_INDEX;
							watch_cache_array[j][1] = _spdsum;
						}
						break;
					case WATCH_IGT_INDEX:
						// IGT
						{
							int state = IGT_STATE_LOCKED;
							int igt_secs = 0;
							if (player_count == 1) {
								int _ingameover = DetectGameOver();
								int _inadventure = DetectAdventure();
								if ((_ingameover) || (_inadventure)) {
									state = IGT_STATE_CANSAVE;
								}
							}
							if (state == IGT_STATE_CANSAVE) {
								igt_secs = getNewSaveTime();
							} else {
								igt_secs = IGT;
							}
							if ((watch_cache_array[j][1] != igt_secs) || (watch_cache_array[j][0] != WATCH_IGT_INDEX)) {
								int igt_split_secs = igt_secs % HERTZ;
								int igt_split_mins = ((igt_secs % 3600) - igt_split_secs) / 60;
								int igt_split_hours = (igt_secs - (60 * igt_split_mins) - igt_split_secs) / 3600;
								dk_strFormat((char *)WatchTextSpace[j], "IGT: %d:%02d:%02d",igt_split_hours,igt_split_mins,igt_split_secs);
							}
							watch_cache_array[j][0] = WATCH_IGT_INDEX;
							watch_cache_array[j][1] = igt_secs;
						}
						break;
					case WATCH_ANGLEPOINT_INDEX:
						// Point Angle
						{
							if (player_ref_bool) {
								float angle = 0;
								if (Player) {
									float px = Player->xPos;
									float pz = Player->zPos;
									float dx = player_ref_x - px;
									float dz = player_ref_z - pz;
									if ((dx != 0) && (dz != 0)) {
										angle = (arctan2(dz,dx) * (180 / 3.14159f)) + 360;
									}
								}
								if (angle >= 360) {
									angle -= 360;
								}
								// angle = angle * (4096 / 360);
								// int angle_units = angle;
								// angle_units = angle_units % 4096;
								// float angle_units_f = angle_units;
								// float angle_rounded = angle_units_f * (360 / 4096);
								if ((watch_cache_slotf[j] != angle) || (watch_cache_array[j][0] != WATCH_ANGLEPOINT_INDEX)) {
									headerFormatter("ANGLE TO POINT: ",angle,0,FLOAT_TYPE,j);
								}
								watch_cache_slotf[j] = angle;
							} else {
								stringConcat((char *)WatchTextSpace[j],"ANGLE TO POINT: UNDEFINED","");
							}
							watch_cache_array[j][0] = WATCH_ANGLEPOINT_INDEX;
						}
						break;
					case WATCH_FAKEKEY_INDEX:
						// Fake Key
						{
							/*
								0 = Wrong Map
								1 = Not Loaded
								2 = Loaded
								3 = Key Obtained
								4 = Unknown
							*/
							int fakekey_status = getFakeKeyStatus(); 
							if ((watch_cache_array[j][1] != fakekey_status) || (watch_cache_array[j][0] != WATCH_FAKEKEY_INDEX)) {
								if (fakekey_status > 5) {
									fakekey_status = 4; // Unknown
								}
								stringConcat((char *)WatchTextSpace[j],"KEY 8: ",(char*)fakekey_list[fakekey_status]);
							}
							watch_cache_array[j][0] = WATCH_FAKEKEY_INDEX;
							watch_cache_array[j][1] = fakekey_status;
						}
						break;
					case WATCH_PRODROOM_INDEX:
						// Fake Production Room
						{
							/*
								0 = Wrong Map
								1 = Production Room Off
								2 = Unknown
								3 = Not Loaded
								4 = Preparing to be fake
								5 = Fake
								6 = Real
							*/
							int fakeprod_status = getFakeProdRoomStatus(); 
							if (fakeprod_status != 2) {
								if ((watch_cache_array[j][1] != fakeprod_status) || (watch_cache_array[j][0] != WATCH_PRODROOM_INDEX)) {
									if (fakeprod_status > 6) {
										fakeprod_status = 2; // Unknown
									}
									stringConcat((char *)WatchTextSpace[j],"PROD ROOM: ",(char*)fakeprodroom_list[fakeprod_status]);
								}
								watch_cache_array[j][0] = WATCH_PRODROOM_INDEX;
								watch_cache_array[j][1] = fakeprod_status;
							}
						}
						break;
					case WATCH_OBJSIGNALS_INDEX:
						// Object Signals Count
						if ((watch_cache_array[j][1] != objectSignalsCountCopy) || (watch_cache_array[j][0] != WATCH_OBJSIGNALS_INDEX)) {
							headerFormatter("OBJECT SIGNALS COUNT: ",0,objectSignalsCountCopy,INT_TYPE,j);
						}
						watch_cache_array[j][0] = WATCH_OBJSIGNALS_INDEX;
						watch_cache_array[j][1] = objectSignalsCountCopy;
						break;
					case WATCH_DELAYEDKILLS_INDEX:
						// Delayed Kills Count
						if ((watch_cache_array[j][1] != delayedKillsCountCopy) || (watch_cache_array[j][0] != WATCH_DELAYEDKILLS_INDEX)) {
							headerFormatter("DELAYED KILLS COUNT: ",0,delayedKillsCountCopy,INT_TYPE,j);
						}
						watch_cache_array[j][0] = WATCH_DELAYEDKILLS_INDEX;
						watch_cache_array[j][1] = delayedKillsCountCopy;
						break;
					case WATCH_LOCKSTACK_INDEX:
						// Lock Stack Count
						if ((watch_cache_array[j][1] != lockStackCountCopy) || (watch_cache_array[j][0] != WATCH_LOCKSTACK_INDEX)) {
							headerFormatter("LOCK STACK COUNT: ",0,lockStackCountCopy,INT_TYPE,j);
						}
						watch_cache_array[j][0] = WATCH_LOCKSTACK_INDEX;
						watch_cache_array[j][1] = lockStackCountCopy;
						break;
					case WATCH_SCRIPTRUN_INDEX:
						// Scripts Running Count
						if (
							(watch_cache_array[j][1] != scriptsRunningCount) || 
							(watch_cache_array[j][2] != scriptsAttemptLoadCount) || 
							(watch_cache_array[j][0] != WATCH_SCRIPTRUN_INDEX)
						) {
							dk_strFormat((char *)WatchTextSpace[j], "SCRIPTS RUNNING: %d (%d)",scriptsRunningCount,scriptsAttemptLoadCount);
						}
						watch_cache_array[j][0] = WATCH_SCRIPTRUN_INDEX;
						watch_cache_array[j][1] = scriptsRunningCount;
						watch_cache_array[j][2] = scriptsAttemptLoadCount;
						break;
					case WATCH_LOADEDACTORCOUNT_INDEX:
						// Loaded Actor Count
						if ((watch_cache_array[j][1] != LoadedActorCount) || (watch_cache_array[j][0] != WATCH_LOADEDACTORCOUNT_INDEX)) {
							headerFormatter("ACTORS LOADED: ",0,LoadedActorCount,INT_TYPE,j);
						}
						watch_cache_array[j][0] = WATCH_LOADEDACTORCOUNT_INDEX;
						watch_cache_array[j][1] = LoadedActorCount;
						break;
					case WATCH_DYNWATCH_INDEX:
						// Dynamic Watches
						{
							int dyn_index = -1;
							int k = 0;
							while (k < 4) {
								if (dynamic_watches[k].used) {
									if (dynamic_watches[k].watch_index == j) {
										dyn_index = k;
										break;
									}
								}
								k++;
							}
							if (dyn_index > -1) {
								int hex_value = 0;
								int sizes[] = {1,1,1,2,2,2,4,4,4,4};
								int types[] = {0,1,2,0,1,2,0,1,2,3};
								int size = sizes[(int)dynamic_watches[dyn_index].size];
								int _type = types[(int)dynamic_watches[dyn_index].size];
								int s_val = 0;
								float f_val = 0;
								unsigned int u_val = 0;
								if (size == 1) {
									hex_value = *(unsigned char*)(dynamic_watches[dyn_index].address);
									u_val = hex_value;
									s_val = *(char*)(dynamic_watches[dyn_index].address);
								} else if (size == 2) {
									hex_value = *(unsigned short*)(dynamic_watches[dyn_index].address);
									u_val = hex_value;
									s_val = *(short*)(dynamic_watches[dyn_index].address);
								} else if (size == 4) {
									hex_value = *(unsigned int*)(dynamic_watches[dyn_index].address);
									u_val = hex_value;
									s_val = *(int*)(dynamic_watches[dyn_index].address);
									if (_type == 3) {
										f_val = *(float*)(dynamic_watches[dyn_index].address);
									}
								}
								if ((watch_cache_array[j][1] != hex_value)
									|| (watch_cache_array[j][2] != dynamic_watches[dyn_index].size)
									|| (watch_cache_array[j][3] != (int)dynamic_watches[dyn_index].address)
									|| (watch_cache_array[j][0] != WATCH_DYNWATCH_INDEX)) {
									if (_type == 0) {
										dk_strFormat((char *)WatchTextSpace[j], "0X%X:%u",dynamic_watches[dyn_index].address,u_val);
									} else if (_type == 1) {
										dk_strFormat((char *)WatchTextSpace[j], "0X%X:%d",dynamic_watches[dyn_index].address,s_val);
									} else if (_type == 2) {
										dk_strFormat((char *)WatchTextSpace[j], "0X%X:%X",dynamic_watches[dyn_index].address,u_val);
									} else if (_type == 3) {
										dk_strFormat((char *)WatchTextSpace[j], "0X%X:%f",dynamic_watches[dyn_index].address,f_val);
									}
								}
								watch_cache_array[j][0] = WATCH_DYNWATCH_INDEX;
								watch_cache_array[j][1] = hex_value;
								watch_cache_array[j][2] = dynamic_watches[dyn_index].size;
								watch_cache_array[j][3] = (int)dynamic_watches[dyn_index].address;
							}
						}
						break;
					case WATCH_2015FILE_INDEX:
						// 2015 MMM File Watch
						{
							int file_slot_index = 0;
							if (CurrentMap == 0x50) {
								file_slot_index = File;
							} else {
								for (int k = 0; k < 4; k++) {
									if (EEPROMSlots[k] == File) {
										file_slot_index = k;
									}
								}
							}
							file_slot_index += 1;
							if ((watch_cache_array[j][1] != file_slot_index) || (watch_cache_array[j][0] != WATCH_2015FILE_INDEX)) {
								headerFormatter("2015 MMM FILE: ",0,file_slot_index,INT_TYPE,j);
							}
							watch_cache_array[j][0] = WATCH_2015FILE_INDEX;
							watch_cache_array[j][1] = file_slot_index;
						}
					case WATCH_TAGKICKOUT_INDEX:
						// Lowest Tag Kickout Timer
						{
							int lowest_kickout = 9999;
							int found_tag = 0;
							for (int k = 0; k < LoadedActorCount; k++) {
								actorData* actor = LoadedActorArray[k].actor;
								if (actor) {
									int actorType = actor->actorType;
									if ((actorType == 98) || (actorType == 136) || (actorType == 137)) {
										tag_paad* paad = actor->paad;
										int kickout = 9000 - paad->kickout_timer;
										if (lowest_kickout > kickout) {
											lowest_kickout = kickout;
											found_tag = 1;
										}
									}
								}
							}
							if (!found_tag) {
								lowest_kickout = 9000;
							}
							if ((watch_cache_array[j][1] != lowest_kickout) || (watch_cache_array[j][0] != WATCH_TAGKICKOUT_INDEX)) {
								headerFormatter("TAG KICKOUT TIMER: ",0,lowest_kickout,INT_TYPE,j);
							}
							watch_cache_array[j][0] = WATCH_TAGKICKOUT_INDEX;
							watch_cache_array[j][1] = lowest_kickout;
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