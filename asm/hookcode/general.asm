	updateLag:
		LW 		t6, FrameReal
		LW 		a2, FrameLag
		SUBU 	a2, t6, a2
		SH 		a2, StoredLag
		LUI 	t6, hi(simpleLagCalcDisabled)
		J 		lagHookWrite+8
		LBU 	t6, lo(simpleLagCalcDisabled) (t6)

	isSaving:
		ADDIU 	t6, r0, 1
		SB 	 	t6, SavePromptIsSaving
		LUI 	t6, hi(player_count)
		J 		saveHookWrite+8
		LBU 	t6, lo(player_count) (t6)

	logSpriteAddress:
		LUI 	t6, hi(SpriteAddress)
		SW 		v0, lo(SpriteAddress) (t6)
		LUI 	v1, hi(sprite_translucency)
		J 		spriteHookWrite+8
		ADDIU 	v1, v1, lo(sprite_translucency)

	setPauseVolume:
		LUI 	a0, hi(PauseMenuMusicSetting)
		LBU 	a1, lo(PauseMenuMusicSetting) (a0)
		BEQZ 	a1, setPauseVolume_Regular
		NOP
		ADDIU 	a0, r0, 1
		BEQ 	a0, a1, setPauseVolume_Quiet
		NOP
		ADDIU 	a0, r0, 2
		BEQ 	a0, a1, setPauseVolume_Silent
		NOP

		setPauseVolume_Regular:
			B 		setPauseVolume_Finish
			LUI 	a1, 0x3F80

		setPauseVolume_Quiet:
			B 		setPauseVolume_Finish
			LUI 	a1, 0x3F00

		setPauseVolume_Silent:
			B 		setPauseVolume_Finish
			LUI 	a1, 0x0

		setPauseVolume_Finish:
			JAL 	playSong
			ADDIU 	a0, r0, 0x22
			J 		pauseHookWrite+8
			NOP

	kongCode:
		JAL 	handleAutophase
		NOP
		LW 		ra, -0x4C (sp)
		J 		kongHookWrite+8
		LW 		s0, -0x50 (sp)

	writeLastUpdatedFlags:
		ADDIU 	sp, sp, -0x30
		LUI 	t7, hi(UndoFlag)
		ADDIU 	t7, t7, lo(UndoFlag)
		ADDIU 	a3, r0, 1
		SB 		a3, 0x4 (t7)
		SB 		a3, 0x5 (t7)
		SH 		a0, 0x0 (t7)
		SB 		a1, 0x2 (t7)
		SB 		a2, 0x3 (t7)
		LUI 	t7, hi(flagLog_currentfitems)
		ADDIU	t7, t7, lo(flagLog_currentfitems)
		LUI 	a3, hi(FlagLogCurrentFCounter)
		LBU 	a3, lo(FlagLogCurrentFCounter) (a3)
		SLL 	a3, a3, 2
		ADD 	t7, t7, a3
		LW 		t7, 0x0 (t7)
		SH 		a0, 0x0 (t7)
		SB 		a1, 0x2 (t7)
		SB 		a2, 0x3 (t7)
		LUI 	a3, hi(FlagLogCurrentFCounter)
		LBU 	a3, lo(FlagLogCurrentFCounter) (a3)
		ADDIU 	t7, r0, 9
		BEQ 	a3, t7, writeLastUpdatedFlags_Finish
		ADDIU 	a3, a3, 1
		LUI 	t7, hi(FlagLogCurrentFCounter)
		SB 		a3, lo(FlagLogCurrentFCounter) (t7)

		writeLastUpdatedFlags_Finish:
			SLL 	a3, a0, 0x10
			J 		flagHookWrite+8
			NOP

	controlTimer:
		LUI 	t8, hi(ConvertTimerCountdown)
		ADDIU 	t6, r0, 2
		SB 		t6, lo(ConvertTimerCountdown) (t8)
		LW 		ra, 0x14 (sp)
		J 		spawnTimerHookWrite+8
		ADDIU 	sp, sp, 0x18

	preventPhasewalkingOverride:
		JAL 	processPhase
		SRA 	a2, t4, 0x10
		LUI 	a2, hi(AutoPhaseStateOn)
		LBU 	a2, lo(AutoPhaseStateOn) (a2)
		BEQZ 	a2, preventPhasewalkingOverride_Finish
		NOP
		LUI 	a2, hi(ControllerInput)
		LHU 	a2, lo(ControllerInput) (a2)
		ANDI 	a2, a2, 0x0800 // D_Up
		BEQZ 	a2, preventPhasewalkingOverride_Finish
		NOP
		LUI 	a2, hi(Player)
		LW 		a2, lo(Player) (a2)
		BEQZ 	a2, preventPhasewalkingOverride_Finish
		NOP
		LHU 	a3, 0xE6 (a2)
		SLTIU 	a1, a3, 2048
		BEQZ 	a1, preventPhasewalkingOverride_Finish
		ADDIU 	a3, a3, 4096
		SH 		a3, 0xE6 (a2)

		preventPhasewalkingOverride_Finish:
			J 	phaseCorrectionHookWrite+8
			NOP

	fairyDataStorageCode:
		LUI 	t2, hi(fairy_data)
		ADDIU 	t2, t2, lo(fairy_data)
		LHU 	v0, 0x0 (t2)
		LUI 	s0, hi(FairyViewerData)
		ADDIU 	s0, s0, lo(FairyViewerData)
		SH 		v0, 0x0 (s0)
		LHU 	v0, 0x2 (t2)
		SH 		v0, 0x2 (s0)
		LHU 	v0, 0x4 (t2)
		SH 		v0, 0x4 (s0)
		LUI 	t2, hi(CurrentActorPointer_0)
		LW 		t2, lo(CurrentActorPointer_0) (t2)
		LUI 	s0, hi(FairyViewerFocus)
		SW 		t2, lo(FairyViewerFocus) (s0)
		LUI 	t2, hi(SwapObject)
		J 		fairyStoreHookWrite+8
		LW 		t2, lo(SwapObject) (t2)

	arcadeTextHook:
		J 		arcadeTextLoop
		NOP
	arcadeHasControlHook:
		J 		arcadeHasControlLoop
		NOP
	arcadeHasControl2Hook:
		J 		arcadeHasControl2Loop
		NOP
	arcadeHasControl3Hook:
		J 		arcadeHasControl3Loop
		NOP
	arcadeLoopCode:
		LUI 	t3, hi(arcadeTextHook)
		LW 		t3, lo(arcadeTextHook) (t3)
		LUI 	t4, hi(arcadeTextHookWrite)
		SW 		t3, lo(arcadeTextHookWrite) (t4) // Store Hook
		SW 		r0, lo(arcadeTextHookWrite)+4 (t4) // Store NOP
		LUI 	t3, hi(arcadeHasControlHook)
		LW 		t3, lo(arcadeHasControlHook) (t3)
		LUI 	t4, hi(arcadeHasControlHookWrite)
		SW 		t3, lo(arcadeHasControlHookWrite) (t4)
		SW 		r0, lo(arcadeHasControlHookWrite)+4 (t4)
		LUI 	t3, hi(arcadeHasControl2Hook)
		LW 		t3, lo(arcadeHasControl2Hook) (t3)
		LUI 	t4, hi(arcadeHasControl2HookWrite)
		SW 		t3, lo(arcadeHasControl2HookWrite) (t4)
		SW 		r0, lo(arcadeHasControl2HookWrite)+4 (t4)
		LUI 	t3, hi(arcadeHasControl3Hook)
		LW 		t3, lo(arcadeHasControl3Hook) (t3)
		LUI 	t4, hi(arcadeHasControl3HookWrite)
		SW 		t3, lo(arcadeHasControl3HookWrite) (t4)
		SW 		r0, lo(arcadeHasControl3HookWrite)+4 (t4)
		JAL 	overlayEntryPoint
		NOP
		JAL 	arcadeFuncLoop
		NOP
		J 		arcadeHookWrite+8
		NOP

	arcadeTextLoop:
		JAL 	spawnArcadeMenu
		ADDIU 	a0, sp, 0x90
		LUI 	v0, hi(arcadeMode)
		J 		arcadeTextHookWrite+8
		LBU 	v0, lo(arcadeMode) (v0)

	arcadeHasControlLoop:
		LUI 	t6, hi(arcadeMenu)
		ADDIU 	t6, t6, lo(arcadeMenu)
		LBU 	t6, 0x0000 (t6)
		BNEZ 	t6, arcadeHasControlLoop_Finish
		NOP
		LUI 	t6, hi(arcadePause)
		J 		arcadeHasControlHookWrite+8
		LBU 	t6, lo(arcadePause) (t6)

		arcadeHasControlLoop_Finish:
			LUI 	t6, hi(arcadePause)
			J 		arcadeHasControlHookWrite+0x74
			LBU 	t6, lo(arcadePause) (t6)

	arcadeHasControl2Loop:
		LUI 	t8, hi(arcadeMenu)
		ADDIU 	t8, t8, lo(arcadeMenu)
		LBU 	t8, 0x0000 (t8)
		BNEZ 	t8, arcadeHasControl2Loop_Finish
		NOP
		LUI 	t8, hi(arcadeBonusTimer)
		J 		arcadeHasControl2HookWrite+8
		LB 		t8, lo(arcadeBonusTimer) (t8)

		arcadeHasControl2Loop_Finish:
			LUI 	t8, hi(arcadeBonusTimer)
			J 		arcadeHasControl2HookWrite+0x114
			LB 		t8, lo(arcadeBonusTimer) (t8)

	arcadeHasControl3Loop:
		LUI 	at, hi(arcadeMenu)
		ADDIU 	at, at, lo(arcadeMenu)
		LBU 	at, 0x0000 (at)
		BNEZ 	at, arcadeHasControl3Loop_Finish
		NOP
		LWC1 	f4, 0x4 (s1)
		J 		arcadeHasControl3HookWrite+8
		LWC1	f6, 0x8 (s1)

		arcadeHasControl3Loop_Finish:
			J 		arcadeHasControl3HookWrite+0x58
			NOP

	pauseMenu97Code:
		LUI 	v0, hi(PausePointer)
		LUI 	v1, hi(CurrentActorPointer_0)
		LW 		v1, lo(CurrentActorPointer_0) (v1)
		SW 		v1, lo(PausePointer) (v0)
		LUI 	v0, hi(CurrentMap)
		J 		pause97HookWrite+8
		LW 		v0, lo(CurrentMap) (v0)

	pauseMenu343Code:
		LUI 	t6, hi(PausePointer)
		LUI 	t7, hi(CurrentActorPointer_0)
		LW 		t7, lo(CurrentActorPointer_0) (t7)
		SB 		t7, lo(PausePointer) (t6)
		ADDIU 	sp, sp, -0x30
		J 		pause343HookWrite+8
		SW 		s0, 0x1C (sp)

	loadSetupCode:
		JAL 	getParentMapIndexFromCurrentMap
		LW 		a0, lo(CurrentMap) (a0)
		LI 		at, -1
		BEQ 	v0, at, loadSetupCode_Finish
		ADDIU 	t6, r0, 0xC0
		LUI 	at, hi(parentData)
		ADDIU 	at, at, lo(parentData)
		MULTU 	t6, v0
		MFLO 	t6
		ADDU 	at, at, t6
		LBU 	t6, 0x0 (at)
		ANDI 	t6, t6, 2
		BEQZ 	t6, loadSetupCode_Finish
		NOP
		LI 		v0, -1

		loadSetupCode_Finish:
			J 		loadSetupHookWrite+0xC
			LI 		at, -1

	resolveBonusBarrelCode:
		JAL 	getParentMapIndexFromCurrentMap
		SWC1 	f12, 0x4c (sp)
		LI 		at, -1
		BEQ 	v0, at, resolveBonusBarrelCode_Finish
		ADDIU 	a3, r0, 0xc0
		LUI 	at, hi(parentData)
		ADDIU 	at, at, lo(parentData)
		MULTU 	v0, a3
		MFLO 	a3
		ADDU 	at, at, a3
		LBU 	a3, 0x0 (at)
		ANDI 	a3, a3, 2
		BEQZ 	a3, resolveBonusBarrelCode_Finish
		NOP
		LI  	v0, -1

		resolveBonusBarrelCode_Finish:
			J 	resolveBarrelHookWrite+0xC
			LI  at, -1

	displayListCode:
		JAL 	displayListModifiers
		OR 		a0, s0, r0
		OR 		s0, v0, r0
		LUI 	a0, hi(DemoFadeoutTimer)
		ADDIU 	a0, a0, lo(DemoFadeoutTimer)
		LHU 	v1, 0x0 (a0)
		LUI 	v0, hi(Gamemode)
		J 		displayListHookWrite+8
		LBU 	v0, lo(Gamemode) (v0)

	jetpacTextHook:
		J 		jetpacTextCode
		NOP
	jetpacPauseHook:
		J 		jetpacPauseCode
		NOP
	jetpacTimerHook:
		J 		jetpac5000Code
		NOP

	jetpacLoopCode:
		LUI 	t3, hi(jetpacTextHook)
		LW 		t3, lo(jetpacTextHook) (t3)
		LUI 	t4, hi(jetpacTextHookWrite)
		SW 		t3, lo(jetpacTextHookWrite) (t4) // Store Hook
		SW 		r0, lo(jetpacTextHookWrite)+4 (t4) // Store NOP

		LUI 	t3, hi(jetpacPauseHook)
		LW 		t3, lo(jetpacPauseHook) (t3)
		LUI 	t4, hi(jetpacPauseHookWrite)
		SW 		t3, lo(jetpacPauseHookWrite) (t4) // Store Hook
		SW 		r0, lo(jetpacPauseHookWrite)+4 (t4) // Store NOP

		LUI 	t3, hi(jetpacTimerHook)
		LW 		t3, lo(jetpacTimerHook) (t3)
		LUI 	t4, hi(jetpac5000HookWrite)
		SW 		t3, lo(jetpac5000HookWrite) (t4) // Store Hook
		SW 		r0, lo(jetpac5000HookWrite)+4 (t4) // Store NOP

		JAL 	overlayEntryPoint
		NOP
		JAL 	jetpacFuncLoop
		NOP
		J 		jetpacHookWrite+8
		NOP

	jetpacTextCode:
		JAL 	spawnJetpacMenu
		LW 		a0, 0x20 (sp)
		LW 		ra, 0x1C (sp)
		J 		jetpacTextHookWrite+8
		LW 		s0, 0x18 (sp)

	jetpacPauseCode:
		LUI 	v0, hi(jetpacPaused)
		LBU 	v0, lo(jetpacPaused) (v0)
		BNEZ 	v0, jetpacPauseCode_Finish
		NOP
		LW 		v0, 0x1C (sp)
		JAL 	jetpacUnkFunc
		SW 		v0, 0x1C (sp)
		J 		jetpacPauseHookWrite+0xC
		NOP

		jetpacPauseCode_Finish:
			JAL 	jetpacInitDL
			LW 		a0, 0x20 (sp)
			JAL 	jetpacDrawFloors // Draw Floors
			NOP
			JAL 	jetpacDrawJetman // Draw Jetman
			NOP
			JAL 	jetpacDrawEnemies // Draw Enemies
			NOP
			JAL 	jetpacDrawRocket // Draw Rocket
			NOP
			J 		jetpacPauseHookWrite+0x90
			NOP

	jetpac5000Code:
		LW 		t2, 0x70 (sp)
		LW 		t3, 0x4 (t2)
		SLTI 	at, t3, 5000
		BNEZ 	at, jetpac5000Code_Finish
		LBU		t1, lo(jetpacStoryMode) (t1)

		jetpac5000Code_5000Hit:
			LUI 	at, hi(jetpacTimerState)
			LBU 	a0, lo(jetpacTimerState) (at)
			ADDIU 	t3, r0, 2
			BNE 	a0, t3, jetpac5000Code_Finish
			ADDIU 	a1, r0, 3
			SB 		a1, lo(jetpacTimerState) (at)

		jetpac5000Code_Finish:
			J 		jetpac5000HookWrite+8
			NOP

	vertBaseStore:
		ADDU 	t9, v0, t5
		SW 		t9, lo(MapVertsPointer) (at)
		LUI 	at, hi(vanillaVertBase)
		J 		vertBaseStoreHookWrite+8
		SW 		t9, lo(vanillaVertBase) (at)

	signalsStore:
		LH 		v1, 0x0 (s3)
		SW 		s1, 0x18 (sp)
		LUI 	t6, hi(objectSignalsCountCopy)
		J 		signalsStoreHookWrite+8
		SB 		v1, lo(objectSignalsCountCopy) (t6)

	delayedKillsStore:
		LH 		t6, 0x0 (s2)
		SW 		s0, 0x18 (sp)
		LUI 	a0, hi(delayedKillsCountCopy)
		J 		delayedKillsStoreHookWrite+8
		SB 		t6, lo(delayedKillsCountCopy) (a0)

	lockStackStore:
		LW 		v1, 0x0 (t1)
		LUI 	v0, hi(lockStackCountCopy)
		SB 		v1, lo(lockStackCountCopy) (v0)
		J 		lockStackStoreHookWrite+8
		ADDIU 	v0, r0, 1

	storeFloorPreload:
		OR 		s1, v0, r0
		ANDI	t1, t9, 2
		LUI 	a1, hi(floorsPreloadedVanilla)
		J 		storeFloorPreloadHookWrite+8
		SB 		t1, lo(floorsPreloadedVanilla) (a1)

	getGiantKoshaAddress:
		LW 		v1, 0x0 (a0)
		ADDIU 	s0, v1, 6
		SW 		r0, GiantKoshaTimerAddress
		SRA  	t8, s0, 16
		SLTIU 	t8, t8, 0x8000
		BNEZ 	t8, getGiantKoshaAddress_Finish
		SRA 	t8, s0, 16
		SLTIU 	t8, t8, 0x8080
		BEQZ 	t8, getGiantKoshaAddress_Finish
		NOP
		SW 		s0, GiantKoshaTimerAddress

		getGiantKoshaAddress_Finish:
			J 		giantKoshaHookWrite+8
			OR 		s0, a0, r0

	lockedCamCode:
		BEQZ 	t7, lockedCamCode_None
		NOP
		LUI 	t9, hi(disableLockedCam)
		LBU 	t9, lo(disableLockedCam) (t9)
		BNEZ 	t9, lockedCamCode_None
		NOP
		J 		lockedCamHookWrite+8
		NOP

		lockedCamCode_None:
			J 	lockedCamHookWrite+0x4C4
			MTC1 r0, f28

	doubleBeaverCode:
		LBU 	t1, 0x154 (t0)
		ADDIU 	t9, r0, 0x40
		BEQ 	t1, t9, doubleBeaverCode_activated
		NOP

		doubleBeaverCode_nosuccess:
			ADDIU 	t9, r0, 0x10
			SB 		t9, 0x154 (t0)
			LW 		t1, 0x0 (a3)
			J 		doubleBeaverHookWrite+0x24
			SB 		r0, 0x155 (t1)

		doubleBeaverCode_activated:
			ADDIU 	t9, r0, 0x10
			SB 		t9, 0x154 (t0)
			LW 		t1, 0x0 (a3)
			SB 		r0, 0x155 (t1)
			JAL 	playBeaverSuccessDing
			NOP
			J 		doubleBeaverHookWrite+0x24
			NOP

	GuardSphereStoreCode:
		SW 		t4, 0x28 (sp)
		SW 		t3, 0x24 (sp)
		LW 		t4, 0x0 (s0)
		LW 		t3, 0x5C (sp)
		SW 		t3, 0x1BC (t4)
		LW 		t3, 0x64 (sp)
		SW 		t3, 0x1B8 (t4)
		LW 		t4, 0x28 (sp)
		J 		guardStoreHookWrite+0x8
		LW 		t3, 0x24 (sp)

	GuardSphereLightCode:
		LUI 	t5, hi(altCollisionEnabled)
		LBU 	t5, lo(altCollisionEnabled) (t5)
		ANDI 	t5, t5, 1 // Check Snoop Spheres
		SWC1 	f18, 0x18 (sp)
		BEQZ 	t5, GuardSphereLightCode_Render
		NOP
		LUI 	t5, hi(collisiondrawmode)
		LBU 	t5, lo(collisiondrawmode) (t5)
		BNEZ 	t5, GuardSphereLightCode_Finish
		NOP

		GuardSphereLightCode_Render:
			JAL 	0x8065A708
			NOP

		GuardSphereLightCode_Finish:
			J 	guardLightHookWrite+0x8
			NOP

	ParentCheckBypass:
		LUI 	a2, hi(scriptsNotAutoloading)
		LBU 	a2, lo(scriptsNotAutoloading) (a2)
		ANDI 	a2, a2, 0x10
		BEQZ 	a2, ParentCheckBypass_Finish
		ADDIU 	v0, r0, 0
		JAL 	checkParent
		LH 		a2, 0x6 (s1)

		ParentCheckBypass_Finish:
			J 		parentCheckBypassHookWrite+0x8
			NOP
	
	initCode:
		JAL 		playSound
		SW 			r0, 0x14 (sp)
		JAL 		quickInit
		NOP
		J 			initHookWrite+0x8
		NOP
		
