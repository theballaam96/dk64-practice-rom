#include "../include/common.h"

void cFuncLoop(void) {
	endClose();
	changeCustomFlagVariable();
	isPaused();
	checkMapType();
	handleTimer();
	toggleMenu();
	moveSlot();
	colorMenuSky();
	colorKong();
	levitate();
	closeMenuOnTransition();
	emergencyClose();
	confirmOption();
	menuShortcutButtons();
	startupSkip();
	closeWatchesOnTransition();
	openWatchesOnTransition();
	handleWatch();
	clampWatchFloats();
	tagAnywhere();
	initHack();
	savestateHandler();
	shorthandSavestate();
	ramViewUpdate();
	savestateLoadMapLoadVars();
	LToCancelCS();
	displaySavePrompt();
	clearSavePromptFlag();
	openInputOnTransition();
	closeInputOnTransition();
	displayInput();
	handlePositionSavestates();
	toggleFrameAdvanceState();
	initFrameAdvance();
	exitFrameAdvance();
	LToEndMinigame();
	forceStorySkip();
	setKRoolRound();
	handleAutomoonkick();
	getSandstormAddress();
	handleSpawnPrevention();
	handleLToTBV();
	infiniteHealth();
	fileInit();
}
