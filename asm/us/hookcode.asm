START_HOOK:
	updateLag:
		LW 		a0, FrameReal
		LW 		a1, FrameLag
		SUBU 	a1, a0, a1
		SH 		a1, StoredLag
		LUI 	t6, 0x8077
		J 		0x8060067C
		LBU 	t6, 0xAF14 (t6)

	isSaving:
		ADDIU 	t6, r0, 1
		SB 	 	t6, SavePromptIsSaving
		LUI 	t6, 0x8080
		J 		0x8060DED4
		LBU 	t6, 0xC928 (t6)

	logSpriteAddress:
		LUI 	t6, hi(SpriteAddress)
		SW 		v0, lo(SpriteAddress) (t6)
		LUI 	v1, 0x8080
		J 		0x806AB7D8
		ADDIU 	v1, v1, 0xC80F

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
			J 		0x805FC898
			NOP

	kongCode:
		JAL 	handleAutophase
		NOP
		LW 		ra, -0x4C (sp)
		J 		0x806F3758
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
		LBU 	t1, 0x2 (t1)
		BNEZ 	t1, controlSuperspeed_Finish
		NOP
		LBU 	t1, ClosingMenu
		BNEZ 	t1, controlSuperspeed_Finish
		NOP
		MTC1 	a0, f16
		CVT.D.W f16, f16
		MUL.D 	f8, f8, f16

		controlSuperspeed_Finish:
			J 	0x8066535C
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
			J 		0x807312A4
			NOP

	resizeActiveMenuFont:
		LUI 	a3, 0x3F4C
		ORI 	a3, a3, 0xCCCD
		BEQ 	t0, at, resizeActiveMenuFont_NormalStyle10
		NOP
		LUI 	a3, 0x3F99
		ORI 	a3, a3, 0x999A
		ADDI 	t0, t0, -5
		BEQZ 	t0, resizeActiveMenuFont_NormalStyle10
		ADDIU 	t0, t0, 5
		LUI 	a3, 0x3F66 // Groovy Font Size
		ORI 	a3, a3, 0x6666

		resizeActiveMenuFont_NormalStyle10:
			J 	0x8069D898
			SB 	t0, 0x0056 (sp)

	defineActiveMenuOtherParams:
		LBU 	t0, 0x0056 (sp)
		ADDIU 	a2, r0, 10
		BEQ 	t0, a2, defineActiveMenuOtherParams_Finish
		ADDIU 	a3, r0, 6
		ADDIU 	a2, r0, 5
		BEQ 	t0, a2, defineActiveMenuOtherParams_Finish
		ADDIU 	a3, r0, 2
		ADDIU 	a3, r0, 0

		defineActiveMenuOtherParams_Finish:
			ADDIU a2, r0, 6
			SB 	a2, 0x0056 (sp)
			OR 	a2, r0, r0
			OR 	t0, a3, r0
			J 	0x8069D8BC
			OR 	a3, r0, r0

	controlTimer:
		LUI 	t8, hi(ConvertTimerCountdown)
		ADDIU 	t6, r0, 2
		SB 		t6, lo(ConvertTimerCountdown) (t8)
		LW 		ra, 0x14 (sp)
		J 		0x806A2B00
		ADDIU 	sp, sp, 0x18

	preventPhasewalkingOverride:
		JAL 	0x806DF494
		SRA 	a2, t4, 0x10
		LUI 	a2, hi(AutoPhaseStateOn)
		LBU 	a2, lo(AutoPhaseStateOn) (a2)
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
			J 	0x806E0644
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
		LW 		t2, 0xBB40 (t2)
		LUI 	s0, hi(FairyViewerFocus)
		SW 		t2, lo(FairyViewerFocus) (s0)
		LUI 	t2, 0x8080
		J 		0x806C5DA4
		LW 		t2, 0xC924 (t2)

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
		LUI 	t4, 0x8003
		SW 		t3, 0x1C30 (t4) // Store Hook
		SW 		r0, 0x1C34 (t4) // Store NOP
		LUI 	t3, hi(arcadeHasControlHook)
		LW 		t3, lo(arcadeHasControlHook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0x5410 (t4)
		SW 		r0, 0x5414 (t4)
		LUI 	t3, hi(arcadeHasControl2Hook)
		LW 		t3, lo(arcadeHasControl2Hook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0x52F4 (t4)
		SW 		r0, 0x52F8 (t4)
		LUI 	t3, hi(arcadeHasControl3Hook)
		LW 		t3, lo(arcadeHasControl3Hook) (t3)
		LUI 	t4, 0x8002
		SW 		t3, 0x7914 (t4)
		SW 		r0, 0x7918 (t4)
		JAL 	0x80024000
		NOP
		JAL 	arcadeFuncLoop
		NOP
		J 		0x805FC14C
		NOP

	arcadeTextLoop:
		JAL 	spawnArcadeMenu
		ADDIU 	a0, sp, 0x90
		LUI 	v0, 0x8005
		J 		0x80031C38
		LBU 	v0, 0xC724 (v0)

	arcadeHasControlLoop:
		LUI 	t6, hi(arcadeMenu)
		ADDIU 	t6, t6, lo(arcadeMenu)
		LBU 	t6, 0x0002 (t6)
		BNEZ 	t6, arcadeHasControlLoop_Finish
		NOP
		LUI 	t6, 0x8005
		J 		0x80025418
		LBU 	t6, 0xC71D (t6)

		arcadeHasControlLoop_Finish:
			LUI 	t6, 0x8005
			J 		0x80025484
			LBU 	t6, 0xC71D (t6)

	arcadeHasControl2Loop:
		LUI 	t8, hi(arcadeMenu)
		ADDIU 	t8, t8, lo(arcadeMenu)
		LBU 	t8, 0x0002 (t8)
		BNEZ 	t8, arcadeHasControl2Loop_Finish
		NOP
		LUI 	t8, 0x8005
		J 		0x800252FC
		LB 		t8, 0xC71E (t8)

		arcadeHasControl2Loop_Finish:
			LUI 	t8, 0x8005
			J 		0x80025408
			LB 		t8, 0xC71E (t8)

	arcadeHasControl3Loop:
		LUI 	at, hi(arcadeMenu)
		ADDIU 	at, at, lo(arcadeMenu)
		LBU 	at, 0x0002 (at)
		BNEZ 	at, arcadeHasControl3Loop_Finish
		NOP
		LWC1 	f4, 0x4 (s1)
		J 		0x8002791C
		LWC1	f6, 0x8 (s1)

		arcadeHasControl3Loop_Finish:
			J 		0x8002796C
			NOP

	pauseMenu97Code:
		LUI 	v0, hi(IsPauseMenuOpen)
		ADDIU 	v1, r0, 1
		SB 		v1, lo(IsPauseMenuOpen) (v0)
		LUI 	v0, 0x8077
		J 		0x806A8160
		LW 		v0, 0xA0A8 (v0)

	pauseMenu343Code:
		LUI 	t6, hi(IsPauseMenuOpen)
		ADDIU 	t7, r0, 1
		SB 		t7, lo(IsPauseMenuOpen) (t6)
		ADDIU 	sp, sp, -0x30
		J 		0x806AD004
		SW 		s0, 0x1C (sp)

	loadSetupCode:
		JAL 	0x80600080
		LW 		a0, 0xA0A8 (a0)
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
			J 		0x80688720
			LI 		at, -1

	resolveBonusBarrelCode:
		JAL 	0x80600080
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
			J 	0x80688D70
			LI  at, -1

	displayListCode:
		JAL 	displayListModifiers
		OR 		a0, s0, r0
		OR 		s0, v0, r0
		LUI 	a0, 0x8075
		ADDIU 	a0, a0, 0x531C
		LHU 	v1, 0x0 (a0)
		LUI 	v0, 0x8075
		J 		0x80714184
		LBU 	v0, 0x5314 (v0)

.align 0x10
END_HOOK: