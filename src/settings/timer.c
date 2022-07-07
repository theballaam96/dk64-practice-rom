#include "../include/common.h"

static const char timerstart_default[] = "START ON:L PRESS";
static const char timerstart_mapload[] = "START ON:MAP LOAD";
static const char timerstart_input[] = "START ON:INPUT";

static const char timerpause_off[] = "PAUSE TIMER ON PAUSE MENU:NO";
static const char timerpause_on[] = "PAUSE TIMER ON PAUSE MENU:YES";

static const char timerfinish_default[] = "END ON:L PRESS";
static const char timerfinish_transition[] = "END ON:TRANSITION";
static const char timerfinish_cutscene[] = "END ON:CUTSCENE";
static const char timerfinish_gb[] = "END ON:GB COLLECTION";
static const char timerfinish_endtransition[] = "END ON:END TRANSITION";

static const char* start_modes[] = {
	timerstart_default,
	timerstart_mapload,
	timerstart_input
};

static const char* pause_modes[] = {
	timerpause_off,
	timerpause_on
};

static const char* finish_modes[] = {
	timerfinish_default,
	timerfinish_transition,
	timerfinish_cutscene,
	timerfinish_gb,
	timerfinish_endtransition
};

static const char* timersettings_array[] = {
	timerstart_default,
	timerpause_off,
	timerfinish_default
};

void openTimerSettingsMenu(void) {
	timersettings_array[0] = start_modes[(int)TimerData.StartMode];
	timersettings_array[1] = pause_modes[(int)TimerData.PauseMode];
	timersettings_array[2] = finish_modes[(int)TimerData.FinishMode];
	changeMenu(ACTIVEMENU_SCREEN_TIMERSETTINGS);
}


void toggleStartCondition(void) {
	int _new_mode = TimerData.StartMode + 1;
	if (_new_mode > 2) {
		_new_mode = 0;
	};
	TimerData.StartMode = _new_mode;
	openTimerSettingsMenu();
}

void togglePauseCondition(void) {
	TimerData.PauseMode = 1 ^ TimerData.PauseMode;
	openTimerSettingsMenu();
}

void toggleFinishCondition(void) {
	int _new_mode = TimerData.FinishMode + 1;
	if (_new_mode > 4) {
		_new_mode = 0;
	};
	TimerData.FinishMode = _new_mode;
	openTimerSettingsMenu();
}

static const int timersettings_functions[] = {
	(int)&toggleStartCondition,
	(int)&togglePauseCondition,
	(int)&toggleFinishCondition
};

const Screen timersettings_struct = {
	.TextArray = (int*)timersettings_array,
	.FunctionArray = timersettings_functions,
	.ArrayItems = 3,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 6
};