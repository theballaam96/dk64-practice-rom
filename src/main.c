#include "../include/common.h"

void cFuncLoop(void) {
	ClosingMenu = 0;
	IsPauseMenuOpen = 0;
	if ((PausePointer) && isAddressActor(PausePointer)) {
		int pause_type = PausePointer->actorType;
		if ((pause_type == 95) || (pause_type == 343)) {
			IsPauseMenuOpen = 1;
		}
	}
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
			if (ActiveMenu.screenIndex == ACTIVEMENU_SCREEN_DEBUG_ACTORDETAILS) {
				updateActorScreen();
			}
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
			customHideHUD();
			handleTimer(); // Constant
			hideRacePosition(0);
		}
		toggleMenu(); // Constant
	}
	if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
		closeMenuOnTransition(); // Into Transition
		closeInputOnTransition(); // Into Transition
		if (voidPointer) {
			complexFree(voidPointer);
			voidPointer = 0;
		}
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
		if (voidMapOn) {
			preload_map_voids();
		}
	}
	if (stateLoadTimer > 0) {
		stateLoadTimer--;
	}
	if (NoVacantWatchTimer > 0) {
		NoVacantWatchTimer--;
	}
	disableVoid();
	DiddyMoonMoves();
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
	handleInfinites();
	fileInit(); // File Init
	analyzeInputs(); // PhaseChecker.assistant_on
	writeFlagsToLog(); // Constant
	changeTimer_spawnTimer(); // ConvertTimerCountdown > 0
	controlFairyViewer(); // FairyViewerOpen
};

void arcadeFuncLoop(void) {
	autoCloseArcadeMenu();
	controlArcadeMenuActions();
	toggleArcadeMenu();
	finishLoadingArcadeState();
};

void jetpacFuncLoop(void) {
	autoCloseJetpacMenu();
	controlJetpacMenuActions();
	toggleJetpacMenu();
}

static char stateLoadstr[15] = "";
#define ACTOR_MAINMENUCONTROLLER 0x146

int* displayListModifiers(int* dl) {
	if (CurrentMap == 0x50) {
		int i = 0;
		while (i < LoadedActorCount) {
			if (LoadedActorArray[i].actor) {
				if (LoadedActorArray[i].actor->actorType == ACTOR_MAINMENUCONTROLLER) {
					int screen = *(char*)((int)(LoadedActorArray[i].actor) + 0x18A);
					//int next_screen = *(char*)((int)(LoadedActorArray[i].actor) + 0x18B);
					if (screen < 2) {
						dl = displayInfo(dl);
					}
					break;
				}
			}
			i++;
		}
	}
	if (stateLoadTimer > 0) {
		dk_strFormat((char *)stateLoadstr, "STATE %d LOADED", FocusedSavestate + 1);
		dl = drawPixelTextContainer(dl, 185, 207, (char *)stateLoadstr, 0xFF, 0xFF, 0xFF, 0xFF, 1);
	}
	dl = displaySavePrompt(dl);
	if (NoVacantWatchTimer > 0) {
		dl = drawPixelTextContainer(dl, 130, 207, "NO VACANT WATCH SLOTS", 0xFF, 0xFF, 0xFF, 0xFF, 1);
	}
	if ((!IsPauseMenuOpen) && (CurrentMap != 0x51)) {
		dl = displayMenu(dl);
		if ((!ActiveMenu.isOpen) && (!RAMDisplayOpen)) {
			dl = displayWatches(dl);
			dl = displaySimpleInput(dl);
			if (TransitionSpeed <= 0) {
				dl = displayVoid(dl);
			}
		}
		dl = displayMemory(dl);
		if (CurrentMap != 0x50) {
			dl = displayFairy(dl);
		}
		//dl = drawTri(dl, 100, 100, 300, 500, 500, 300);
		//dl = displayFloors(dl);
	}
	return dl;
};