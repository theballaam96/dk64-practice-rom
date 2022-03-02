START_HOOK:
	updateLag:
		LW 		t6, FrameReal
		LW 		a2, FrameLag
		SUBU 	a2, t6, a2
		SH 		a2, StoredLag
		LUI 	t6, 0x8077
		J 		0x805FE02C
		LBU 	t6, 0xB104 (t6)

	isSaving:
		ADDIU 	t6, r0, 1
		SB 	 	t6, SavePromptIsSaving
		LUI 	t6, 0x8080
		J 		0x8060B8D4
		LBU 	t6, 0xCDB8 (t6)

	logSpriteAddress:
		LUI 	t6, hi(SpriteAddress)
		SW 		v0, lo(SpriteAddress) (t6)
		LUI 	v1, 0x8080
		J 		0x806A9FF0
		ADDIU 	v1, v1, 0xCC87

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
			J 		0x805FA238
			NOP

	kongCode:
		JAL 	handleAutophase
		NOP
		LW 		ra, -0x4C (sp)
		J 		0x806F2D18
		LW 		s0, -0x50 (sp)

	controlSuperspeed:
		MUL.D 	f8, f18, f6
		NOP
		LUI 	a0, hi(IsSuperspeedOn)
		LBU 	a0, lo(IsSuperspeedOn) (a0)
		BEQZ 	a0, controlSuperspeed_Finish
		NOP
		LHU 	t1, ControllerInput
		ANDI 	t1, t1, 0x0020
		BEQZ 	t1, controlSuperspeed_Finish
		NOP
		LUI		t1, hi(ActiveMenu)
		ADDIU 	t1, t1, lo(ActiveMenu)
		LBU 	t1, 0x0 (t1)
		BNEZ 	t1, controlSuperspeed_Finish
		NOP
		LBU 	t1, ClosingMenu
		BNEZ 	t1, controlSuperspeed_Finish
		NOP
		MTC1 	a0, f16
		CVT.D.W f16, f16
		MUL.D 	f8, f8, f16

		controlSuperspeed_Finish:
			J 	0x806632CC
			NOP

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
			J 		0x80730A68
			NOP

	controlTimer:
		LUI 	t8, hi(ConvertTimerCountdown)
		ADDIU 	t6, r0, 2
		SB 		t6, lo(ConvertTimerCountdown) (t8)
		LW 		ra, 0x14 (sp)
		J 		0x806A1170
		ADDIU 	sp, sp, 0x18

	preventPhasewalkingOverride:
		JAL 	0x806DE764
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
			J 	0x806DF914
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
		LUI 	t2, 0x8080
		LW 		t2, 0xBFB4 (t2)
		LUI 	s0, hi(FairyViewerFocus)
		SW 		t2, lo(FairyViewerFocus) (s0)
		LUI 	t2, 0x8080
		J 		0x806C4AB4
		LW 		t2, 0xCDB4 (t2)

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
		LUI 	t4, 0x8002
		SW 		t3, 0x49C0 (t4) // Store Hook
		SW 		r0, 0x49C4 (t4) // Store NOP
		LUI 	t3, hi(arcadeHasControlHook)
		LW 		t3, lo(arcadeHasControlHook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0x83EC (t4)
		SW 		r0, 0x83F0 (t4)
		LUI 	t3, hi(arcadeHasControl2Hook)
		LW 		t3, lo(arcadeHasControl2Hook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0x82D0 (t4)
		SW 		r0, 0x82D4 (t4)
		LUI 	t3, hi(arcadeHasControl3Hook)
		LW 		t3, lo(arcadeHasControl3Hook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0xA8F0 (t4)
		SW 		r0, 0xA8F4 (t4)
		JAL 	0x80017000
		NOP
		JAL 	arcadeFuncLoop
		NOP
		J 		0x05F99D8
		NOP

	arcadeTextLoop:
		JAL 	spawnArcadeMenu
		ADDIU 	a0, sp, 0x90
		LUI 	v0, 0x8004
		J 		0x800249C8
		LBU 	v0, 0xF4B4 (v0)

	arcadeHasControlLoop:
		LUI 	t6, hi(arcadeMenu)
		ADDIU 	t6, t6, lo(arcadeMenu)
		LBU 	t6, 0x0000 (t6)
		BNEZ 	t6, arcadeHasControlLoop_Finish
		NOP
		LUI 	t6, 0x8004
		J 		0x800183F4
		LBU 	t6, 0xF4AD (t6)

		arcadeHasControlLoop_Finish:
			LUI 	t6, 0x8004
			J 		0x80018460
			LBU 	t6, 0xF4AD (t6)

	arcadeHasControl2Loop:
		LUI 	t8, hi(arcadeMenu)
		ADDIU 	t8, t8, lo(arcadeMenu)
		LBU 	t8, 0x0000 (t8)
		BNEZ 	t8, arcadeHasControl2Loop_Finish
		NOP
		LUI 	t8, 0x8004
		J 		0x800182D8
		LB 		t8, 0xF4AE (t8)

		arcadeHasControl2Loop_Finish:
			LUI 	t8, 0x8004
			J 		0x800183E4
			LB 		t8, 0xF4AE (t8)

	arcadeHasControl3Loop:
		LUI 	at, hi(arcadeMenu)
		ADDIU 	at, at, lo(arcadeMenu)
		LBU 	at, 0x0000 (at)
		BNEZ 	at, arcadeHasControl3Loop_Finish
		NOP
		LWC1 	f4, 0x4 (s1)
		J 		0x8001A8F8
		LWC1	f6, 0x8 (s1)

		arcadeHasControl3Loop_Finish:
			J 		0x8001A948
			NOP

	pauseMenu97Code:
		LUI 	v0, hi(PausePointer)
		LUI 	v1, 0x8080
		LW 		v1, 0xBFB0 (v1)
		SW 		v1, lo(PausePointer) (v0)
		LUI 	v0, 0x8077
		J 		0x806A6930
		LW 		v0, 0xA298 (v0)

	pauseMenu343Code:
		LUI 	t6, hi(PausePointer)
		LUI 	t7, 0x8080
		LW 		t7, 0xBFB0 (t7)
		SB 		t7, lo(PausePointer) (t6)
		ADDIU 	sp, sp, -0x30
		J 		0x806ABB74
		SW 		s0, 0x1C (sp)

	loadSetupCode:
		JAL 	0x805FDA2C
		LW 		a0, 0xA298 (a0)
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
			J 		0x80686920
			LI 		at, -1

	resolveBonusBarrelCode:
		JAL 	0x805FDA2C
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
			J 	0x80686F80
			LI  at, -1

	displayListCode:
		JAL 	displayListModifiers
		OR 		a0, s0, r0
		OR 		s0, v0, r0
		LUI 	a0, 0x8075
		ADDIU 	a0, a0, 0x53DC
		LHU 	v1, 0x0 (a0)
		LUI 	v0, 0x8075
		J 		0x80713820
		LBU 	v0, 0x53D4 (v0)

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
		LUI 	t4, 0x8002
		SW 		t3, 0x8364 (t4) // Store Hook
		SW 		r0, 0x8368 (t4) // Store NOP

		LUI 	t3, hi(jetpacPauseHook)
		LW 		t3, lo(jetpacPauseHook) (t3)
		LUI 	t4, 0x8001
		SW 		t3, 0x7954 (t4) // Store Hook
		SW 		r0, 0x7958 (t4) // Store NOP

		LUI 	t3, hi(jetpacTimerHook)
		LW 		t3, lo(jetpacTimerHook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0xADC0 (t4) // Store Hook
		SW 		r0, 0xADC4 (t4) // Store NOP

		JAL 	0x80017000
		NOP
		JAL 	jetpacFuncLoop
		NOP
		J 		0x805F99E8
		NOP

	jetpacTextCode:
		JAL 	spawnJetpacMenu
		LW 		a0, 0x20 (sp)
		LW 		ra, 0x1C (sp)
		J 		0x8001836C
		LW 		s0, 0x18 (sp)

	jetpacPauseCode:
		LUI 	v0, hi(jetpacPaused)
		LBU 	v0, lo(jetpacPaused) (v0)
		BNEZ 	v0, jetpacPauseCode_Finish
		NOP
		LW 		v0, 0x1C (sp)
		JAL 	0x80019D58
		SW 		v0, 0x1C (sp)
		J 		0x80017960
		NOP

		jetpacPauseCode_Finish:
			JAL 	0x800185E4
			LW 		a0, 0x20 (sp)
			JAL 	0x8001BE98 // Draw Floors
			NOP
			JAL 	0x80019AC0 // Draw Jetman
			NOP
			JAL 	0x8001DDAC // Draw Enemies
			NOP
			JAL 	0x8001B554 // Draw Rocket
			NOP
			J 		0x800179E4
			NOP

	jetpac5000Code:
		LW 		t2, 0x70 (sp)
		LW 		t3, 0x4 (t2)
		SLTI 	at, t3, 5000
		BNEZ 	at, jetpac5000Code_Finish
		LBU		t1, 0x23D8 (t1)

		jetpac5000Code_5000Hit:
			LUI 	at, hi(jetpacTimerState)
			LBU 	a0, lo(jetpacTimerState) (at)
			ADDIU 	t3, r0, 2
			BNE 	a0, t3, jetpac5000Code_Finish
			ADDIU 	a1, r0, 3
			SB 		a1, lo(jetpacTimerState) (at)

		jetpac5000Code_Finish:
			J 		0x8001ADC8
			NOP

	vertBaseStore:
		ADDU 	t9, v0, t5
		SW 		t9, 0x6258 (at)
		LUI 	at, hi(vanillaVertBase)
		J 		0x8062CE74
		SW 		t9, lo(vanillaVertBase) (at)

	signalsStore:
		LH 		v1, 0x0 (s3)
		SW 		s1, 0x18 (sp)
		LUI 	t6, hi(objectSignalsCountCopy)
		J 		0x806774F8
		SB 		v1, lo(objectSignalsCountCopy) (t6)

	delayedKillsStore:
		LH 		t6, 0x0 (s2)
		SW 		s0, 0x18 (sp)
		LUI 	a0, hi(delayedKillsCountCopy)
		J 		0x806764B4
		SB 		t6, lo(delayedKillsCountCopy) (a0)

	lockStackStore:
		LW 		v1, 0x0 (t1)
		LUI 	v0, hi(lockStackCountCopy)
		SB 		v1, lo(lockStackCountCopy) (v0)
		J 		0x8060E468
		ADDIU 	v0, r0, 1

	storeFloorPreload:
		OR 		s1, v0, r0
		ANDI	t1, t9, 2
		LUI 	a1, hi(floorsPreloadedVanilla)
		J 		0x806640E4
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
			J 		0x80643DBC
			OR 		s0, a0, r0

.align 0x10
END_HOOK: