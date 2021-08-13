#include "../include/common.h"

void cFuncLoop(void) {
	endClose();
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
	patchHooks();
	hideInputDisplay();
	savestateHandler();
	shorthandSavestate();
}
