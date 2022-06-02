#include "../../include/common.h"

void writeTimer(void) {
	int _time = TimerData.Timer;
	int _reduction = TimerData.Reduction;
	TimerData.TimerPostReduction = _time - _reduction;
}

void tickTimerRunning(void) {
	TimerData.Mode = 2;
}

void tickTimerReady(void) {
	TimerData.Mode = 1;
	TimerData.Start = FrameReal;
}

void checkTouchingGB(void) {
	unsigned short _touch_id;
	short _touch_index;
	int* m2location = ObjectModel2Pointer;
	TouchingGB = 0;
	if (ModelTwoTouchCount) {
		for (int i = 0; i < ModelTwoTouchCount; i++) {
			_touch_id = ModelTwoTouchArray[i];
			_touch_index = convertIDToIndex(_touch_id);
			if (_touch_index > -1) {
				ModelTwoData* _object = getObjectArrayAddr(m2location,0x90,_touch_index);
				if (_object->object_type == 0x74) {
					TouchingGB = 1;
					return;
				}
			}
		}
	}
	if (Player) {
		// Checks for movement, check for collision once I figure a quick way to do this. Collision Queue?
		if (Player->control_state == 0x70) {
			TouchingGB = 1;
		}
	}

}

void timerRunning(void) {
	if (TimerData.Start == 0) {
		TimerData.Start = FrameReal;
		TimerData.Timer = 0;
	} else {
		TimerData.Timer = FrameReal - TimerData.Start;
	};
	if ((ActiveMenu.isOpen == 0) && (ClosingMenu == 0)) {
		if (NewlyPressedControllerInput.Buttons & L_Button && ((ControllerInput.Buttons & R_Button) == 0)) {
			// Running Tick
			tickTimerRunning();
		} else {
			switch(TimerData.FinishMode) {
				case 1:
					// Transition
					if (TransitionSpeed > 0) {
						tickTimerRunning();
					}
					break;
				case 2:
					// Cutscene
					if (CutsceneActive == 1) {
						tickTimerRunning();
					}
					break;
				case 3:
					// GB
					checkTouchingGB();
					if (TouchingGB) {
						tickTimerRunning();
					}
					break;
				case 4:
					// End Transition
					if (TransitionSpeed > 0) {
						if (TransitionProgress == 0) {
							tickTimerRunning();
						}
					}
				break;
			}
		}
	}
	writeTimer();
}

void timerReady(void) {
	if (NewlyPressedControllerInput.Buttons & L_Button && ((ControllerInput.Buttons & R_Button) == 0)) {
		tickTimerReady();
	} else {
		switch(TimerData.StartMode) {
			case 1:
				// Map Load
				if (ObjectModel2Timer == 1) {
					tickTimerReady();
				}
				break;
			case 2:
				// Input
				if (NewlyPressedControllerInput.Buttons) {
					tickTimerReady();
				} else {
					if ((ControllerInput.stickX) || (ControllerInput.stickY)) {
						if (HasNeutralStickInput) {
							tickTimerReady();
						}
					} else {
						HasNeutralStickInput = 1;
					}
				}
			break;
		}
	}
	writeTimer();
}

void handleTimer(void) {
	char _contains_timer = 0;
	for (int i = 0; i < WatchCount; i++) {
		if (WatchIndex[i] == WATCH_TIMER_INDEX) { // 4 = Timer Watch "Watch index"
			_contains_timer = 1;
		}
	};
	if (_contains_timer) {
		if ((ActiveMenu.isOpen == 0) && (ClosingMenu == 0)) {
			if ((TBVoidByte & 2) == 0) {
				if (TimerData.Mode == 0) {
					// Ready
					timerReady();
					return;
				} else {
					if (TimerData.Mode == 1) {
						timerRunning();
						return;
					} else {
						if (TimerData.Mode == 2) {
							if ((NewlyPressedControllerInput.Buttons & L_Button) && ((ControllerInput.Buttons & R_Button) == 0)) {
								TimerData.Mode = 0;
								TimerData.Timer = 0;
								TimerData.Start = 0;
								TimerData.Reduction = 0;
								TimerData.TimerPostReduction = 0;
								HasNeutralStickInput = 0;
							}
							writeTimer();
							return;
						} else {
							writeTimer();
							return;
						}
					}
				}
			} else {
				if (TimerData.PauseMode == 0) {
					if (ArtificialPauseOn == 0) {
						writeTimer();
						return;
					}
				}
				if (TimerData.Mode == 1) {
					// Pause
					TimerData.Reduction = TimerData.Reduction + StoredLag;
					TimerData.Timer = FrameReal - TimerData.Start;
				}
				writeTimer();
				return;
			}
		} else {
			if (TimerData.Mode == 1) {
				timerRunning();
				return;
			}
		}
	}
}