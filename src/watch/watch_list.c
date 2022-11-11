/*
	This is an automatically generated file.
	Please don't make edits to this file directly as they will be overwritten at next build.
	To make amendments, see include/watches.json and build/watch_generator.py.
	Thanks.
*/

#include "../../include/common.h"

// player
static const char viewed_position[] = "} POSITION";
static const char change_position[] = "{ POSITION";
static const char viewed_speed[] = "} SPEED";
static const char change_speed[] = "{ SPEED";
static const char viewed_avgspd[] = "} AVERAGE SPEED";
static const char change_avgspd[] = "{ AVERAGE SPEED";
static const char viewed_angle[] = "} ANGLE";
static const char change_angle[] = "{ ANGLE";
static const char viewed_anglepoint[] = "} ANGLE TO POINT";
static const char change_anglepoint[] = "{ ANGLE TO POINT";
static const char viewed_floor[] = "} FLOOR";
static const char change_floor[] = "{ FLOOR";
static const char viewed_movement[] = "} MOVEMENT STATE";
static const char change_movement[] = "{ MOVEMENT STATE";
static const char viewed_heldactor[] = "} HELD ACTOR";
static const char change_heldactor[] = "{ HELD ACTOR";
static const char viewed_storedposition1[] = "} STORED POSITION 1";
static const char change_storedposition1[] = "{ STORED POSITION 1";
static const char viewed_storedposition2[] = "} STORED POSITION 2";
static const char change_storedposition2[] = "{ STORED POSITION 2";
const char watches_player_indexes[] = {1,2,3,4,5,6,7,8,9,10};

// sysenv
static const char viewed_lag[] = "} LAG";
static const char change_lag[] = "{ LAG";
static const char viewed_avglag[] = "} AVERAGE LAG";
static const char change_avglag[] = "{ AVERAGE LAG";
static const char viewed_input[] = "} INPUT";
static const char change_input[] = "{ INPUT";
static const char viewed_objsignals[] = "} OBJECT SIGNALS COUNT";
static const char change_objsignals[] = "{ OBJECT SIGNALS COUNT";
static const char viewed_delayedkills[] = "} DELAYED KILLS COUNT";
static const char change_delayedkills[] = "{ DELAYED KILLS COUNT";
static const char viewed_lockStack[] = "} LOCK STACK COUNT";
static const char change_lockStack[] = "{ LOCK STACK COUNT";
static const char viewed_scriptRun[] = "} SCRIPTS RUNNING COUNT";
static const char change_scriptRun[] = "{ SCRIPTS RUNNING COUNT";
static const char viewed_loadedActorCount[] = "} LOADED ACTOR COUNT";
static const char change_loadedActorCount[] = "{ LOADED ACTOR COUNT";
static const char viewed_2015file[] = "} 2015 MMM FILE";
static const char change_2015file[] = "{ 2015 MMM FILE";
const char watches_sysenv_indexes[] = {11,12,13,14,15,16,17,18,19};

// timers
static const char viewed_timer[] = "} TIMER";
static const char change_timer[] = "{ TIMER";
static const char viewed_gktimer[] = "} GIANT KOSHA TIMER";
static const char change_gktimer[] = "{ GIANT KOSHA TIMER";
static const char viewed_isg[] = "} INTRO STORY TIMER";
static const char change_isg[] = "{ INTRO STORY TIMER";
static const char viewed_tagkickout[] = "} TAG KICKOUT TIMER";
static const char change_tagkickout[] = "{ TAG KICKOUT TIMER";
static const char viewed_igt[] = "} IN-GAME TIME";
static const char change_igt[] = "{ IN-GAME TIME";
const char watches_timers_indexes[] = {20,21,22,23,24};

// assist
static const char viewed_phaseassistant[] = "} PHASEWALK ASSISTANT";
static const char change_phaseassistant[] = "{ PHASEWALK ASSISTANT";
static const char viewed_fairy[] = "} FAIRY VIEWER";
static const char change_fairy[] = "{ FAIRY VIEWER";
const char watches_assist_indexes[] = {25,-1};

// fake
static const char viewed_fakekey[] = "} KEY 8";
static const char change_fakekey[] = "{ KEY 8";
static const char viewed_prodroom[] = "} PRODUCTION ROOM";
static const char change_prodroom[] = "{ PRODUCTION ROOM";
const char watches_fake_indexes[] = {27,28};

const char* watch_viewed_array[] = {
	viewed_position,
	viewed_speed,
	viewed_avgspd,
	viewed_angle,
	viewed_anglepoint,
	viewed_floor,
	viewed_movement,
	viewed_heldactor,
	viewed_storedposition1,
	viewed_storedposition2,
	viewed_lag,
	viewed_avglag,
	viewed_input,
	viewed_objsignals,
	viewed_delayedkills,
	viewed_lockStack,
	viewed_scriptRun,
	viewed_loadedActorCount,
	viewed_2015file,
	viewed_timer,
	viewed_gktimer,
	viewed_isg,
	viewed_tagkickout,
	viewed_igt,
	viewed_phaseassistant,
	viewed_fairy,
	viewed_fakekey,
	viewed_prodroom,
	0,
	0,
};

const char* watch_listed_array[] = {
	change_position,
	change_speed,
	change_avgspd,
	change_angle,
	change_anglepoint,
	change_floor,
	change_movement,
	change_heldactor,
	change_storedposition1,
	change_storedposition2,
	change_lag,
	change_avglag,
	change_input,
	change_objsignals,
	change_delayedkills,
	change_lockStack,
	change_scriptRun,
	change_loadedActorCount,
	change_2015file,
	change_timer,
	change_gktimer,
	change_isg,
	change_tagkickout,
	change_igt,
	change_phaseassistant,
	change_fairy,
	change_fakekey,
	change_prodroom,
	0,
	0,
};

const char* watch_change_array[] = {
	change_position,
	change_speed,
	change_avgspd,
	change_angle,
	change_anglepoint,
	change_floor,
	change_movement,
	change_heldactor,
	change_storedposition1,
	change_storedposition2,
	change_lag,
	change_avglag,
	change_input,
	change_objsignals,
	change_delayedkills,
	change_lockStack,
	change_scriptRun,
	change_loadedActorCount,
	change_2015file,
	change_timer,
	change_gktimer,
	change_isg,
	change_tagkickout,
	change_igt,
	change_phaseassistant,
	change_fairy,
	change_fakekey,
	change_prodroom,
	0,
	0,
};

const char* watch_player_array[] = {
	change_position,
	change_speed,
	change_avgspd,
	change_angle,
	change_anglepoint,
	change_floor,
	change_movement,
	change_heldactor,
	change_storedposition1,
	change_storedposition2,
};

const int watch_player_functions[] = {
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
};

const Screen watch_player_struct = {
	.TextArray = (int*)watch_player_array,
	.FunctionArray = watch_player_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 0,
};

const char* watch_sysenv_array[] = {
	change_lag,
	change_avglag,
	change_input,
	change_objsignals,
	change_delayedkills,
	change_lockStack,
	change_scriptRun,
	change_loadedActorCount,
	change_2015file,
};

const int watch_sysenv_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&toggleInputDisplay,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
};

const Screen watch_sysenv_struct = {
	.TextArray = (int*)watch_sysenv_array,
	.FunctionArray = watch_sysenv_functions,
	.ArrayItems = 9,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 2,
};

const char* watch_timers_array[] = {
	change_timer,
	change_gktimer,
	change_isg,
	change_tagkickout,
	change_igt,
};

const int watch_timers_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
	(int)&setWatch,
};

const Screen watch_timers_struct = {
	.TextArray = (int*)watch_timers_array,
	.FunctionArray = watch_timers_functions,
	.ArrayItems = 5,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 1,
};

const char* watch_assist_array[] = {
	change_phaseassistant,
	change_fairy,
};

const int watch_assist_functions[] = {
	(int)&togglePhaseAssistant,
	(int)&fairyViewerContainerToggle,
};

const Screen watch_assist_struct = {
	.TextArray = (int*)watch_assist_array,
	.FunctionArray = watch_assist_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 4,
	.hasAccessArray = 1,
	.AccessArray = watch_assist_access,
};

const char* watch_fake_array[] = {
	change_fakekey,
	change_prodroom,
};

const int watch_fake_functions[] = {
	(int)&setWatch,
	(int)&setWatch,
};

const Screen watch_fake_struct = {
	.TextArray = (int*)watch_fake_array,
	.FunctionArray = watch_fake_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 5,
};
