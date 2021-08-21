#include "../include/common.h"

void cFuncLoop(void) {
	endClose();
	changeCustomFlagVariable();
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
	hideInputDisplay();
	savestateHandler();
	shorthandSavestate();
	ramViewUpdate();
	savestateLoadMapLoadVars();
	LToCancelCS();
	displaySavePrompt();
	clearSavePromptFlag();
}
