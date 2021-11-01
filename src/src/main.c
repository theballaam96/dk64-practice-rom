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
			updateLoadedActorNoTextOverlayList(0); // Active Menu Open
			moveSlot(); // Active Menu Open
			confirmOption(); // Active Menu Open
			menuShortcutButtons(); // Active Menu Open
			shouldRefreshTOMenu(); // Active Menu Open
			runTest(); // Active Menu Open
			toggleSelectedActor(); // Active Menu Open
			hideHUD();
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
		int _watch_present = 0;
		int i = 0;
		while (i < 4) {
			if (WatchIndex[i++]) {
				_watch_present = 1;
				break;
			}
		}
		if (_watch_present) {
			handleWatch(); // Active Menu Closed, Watch Present
			clampWatchFloats(); // Active Menu Closed, Watch Present
			controlWatchView(); // Watches Open
			hideHUD();
			handleTimer(); // Constant
			hideRacePosition(0);
		}
		toggleMenu(); // Constant
	}
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		closeMenuOnTransition(); // Into Transition
		closeInputOnTransition(); // Into Transition
		destroyViewerOnTransition(); // Into Transition
		closeWatchesOnTransition(); // Into Transition
	}
	if ((TransitionSpeed < 0) || ((CutsceneActive == 6) && (CurrentMap != 0x50))) {
		checkMapType(); // Out of Transition
		openWatchesOnTransition(); // Out of Transition
		openInputOnTransition(); // Out of Transition
		getSandstormAddress(); // Out of Transition, CurrentMap == 0x26
		handleSpawnPrevention(); // Out of Transition, EnemySpawnOff
		if (CurrentMap == 0x28) {
			for (int i = 0; i < 0x10; i++) {
				TempFlagBlock[i] = 0;
			}
		}
	}
	startupSkip();
	colorKong(); // Constant
	emergencyClose(); // Constant
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
	//controlFairyViewer(); // FairyViewerOpen
}

void arcadeFuncLoop(void) {
	controlArcadeMenuActions();
	toggleArcadeMenu();
	finishLoadingArcadeState();
}