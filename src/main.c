#include "../include/common.h"

void cFuncLoop(void) {
	ClosingMenu = 0;
	if (CurrentMap == 0x51) {
		CutsceneActive = 0;
		spawnConsoleMenu();
		controlConsoleMenu();
	} else {
		if (ActiveMenu.isOpen) {
			changeCustomFlagVariable(); // Active Menu Open
			moveSlot(); // Active Menu Open
			confirmOption(); // Active Menu Open
			menuShortcutButtons(); // Active Menu Open
			shouldRefreshTOMenu(); // Active Menu Open
			runTest(); // Active Menu Open
			toggleSelectedActor(); // Active Menu Open
			customHideHUD();
			hideRacePosition(0);
		} else {
			if (ClosingMenu == 0) {
				levitate(); // Active Menu Closed
				LToCancelCS(); // Active Menu Closed
				handlePositionSavestates(); // Active Menu Closed, RAM Viewer Closed, PosButtons == 0
				LToEndMinigame(); // Active Menu Closed
				handleLToTBV(); // Active Menu Closed
			}
		}
		watchActive = 0;
		int i = 0;
		while (i < 4) {
			if (WatchIndex[i++]) {
				watchActive = 1;
				break;
			}
		}
		if (watchActive) {
			handleWatch(); // Active Menu Closed, Watch Present
			clampWatchFloats(); // Active Menu Closed, Watch Present
			controlWatchView(); // Watches Open
			customHideHUD();
			handleTimer(); // Constant
			hideRacePosition(0);
		}
		toggleMenu(); // Constant
	}
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		closeMenuOnTransition(); // Into Transition
		closeInputOnTransition(); // Into Transition
		destroyViewerOnTransition(); // Into Transition
	}
	if ((TransitionSpeed < 0) || ((CutsceneActive == 6) && (CurrentMap != 0x50))) {
		checkMapType(); // Out of Transition
		openInputOnTransition(); // Out of Transition
		getSandstormAddress(); // Out of Transition, CurrentMap == 0x26
		handleSpawnPrevention(); // Out of Transition, EnemySpawnOff
		if (CurrentMap == 0x28) {
			for (int i = 0; i < 0x10; i++) {
				TempFlagBlock[i] = 0;
			}
		}
	}
	if (stateLoadTimer > 0) {
		stateLoadTimer -= 1;
	}
	startupSkip();
	colorKong(); // Constant
	tagAnywhere(); // Constant
	//correctTagCode();
	initHack(); // Map == 0x28
	shorthandSavestate(); // Constant
	ramViewUpdate(); // RAM Viewer Open
	if (TransitionSpeed < 0) {
		savestateLoadMapLoadVars(); // LoadVarsOnMapLoad
		fileStateMapLoadVars();
		loadMapVars_0();
	}
	if (ShowSavePrompts) {
		displaySavePrompt(); // ShowSavePrompts
	}
	SavePromptIsSaving = 0;
	displayInput(); // Constant
	if (DisablePositionButtons == 1) {
		toggleFrameAdvanceState(); // DisablePositionButtons == 1
		initFrameAdvance(); // DisablePositionButtons == 1
		exitFrameAdvance(); // DisablePositionButtons == 1
	}
	if (DisableForcedStorySkip == 0) {
		StorySkip = 1;
	}
	setKRoolRound(); // Constant
	handleAutomoonkick(); // AutoMoonkickOn
	infiniteHealth(); // InfiniteHealthCheatOn
	fileInit(); // File Init
	analyzeInputs(); // PhaseChecker.assistant_on
	writeFlagsToLog(); // Constant
	changeTimer_spawnTimer(); // ConvertTimerCountdown > 0
	controlFairyViewer(); // FairyViewerOpen
};

void arcadeFuncLoop(void) {
	controlArcadeMenuActions();
	toggleArcadeMenu();
	finishLoadingArcadeState();
};

static char stateLoadstr[15] = "";

int* displayListModifiers(int* dl) {
	if ((CurrentMap == 0x50) && (!watchActive)) {
		dl = drawTextContainer(dl, 1, 25, 525, "DK64 PRACTICE ROM", 0xFF, 0xFF, 0xFF, 0xFF, 0);
		dl = drawTextContainer(dl, 1, 25, 550, "VERSION 1.4.2", 0xFF, 0xFF, 0xFF, 0xFF, 0);
	}
	if (stateLoadTimer > 0) {
		dk_strFormat((char *)stateLoadstr, "State %d Loaded", FocusedSavestate + 1);
		dl = drawTextContainer(dl, 128, 200, 290, (char *)stateLoadstr, 0xFF, 0xFF, 0xFF, 0xFF, 1);
	}
	dl = displayMenu(dl);
	dl = displayWatches(dl);
	dl = displayMemory(dl);
	dl = displayFairy(dl);
	// int dl0 = displayListVar[0];
	// int dl1 = displayListVar[2];
	// *(unsigned int*)(dl + 0x00) = 0xE200001C;
	// *(unsigned int*)(dl + 0x04) = 0x00504240;
	// *(unsigned int*)(dl + 0x08) = 0xFA000000;
	// *(unsigned int*)(dl + 0x0C) = 0xFFFFFFFF;
	// *(unsigned int*)(dl + 0x10) = 0xFCFF97FF;
	// *(unsigned int*)(dl + 0x14) = 0xFF2CFE7F;
	// *(unsigned int*)(dl + 0x18) = 0xE3001201;
	// *(unsigned int*)(dl + 0x1C) = 0x00000000;
	return dl;
};