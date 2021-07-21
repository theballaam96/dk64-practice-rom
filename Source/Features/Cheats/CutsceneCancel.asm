CancelCutscene:
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, CancelCutscene_Finish // Pause Menu
	NOP
	LBU 	a0, @CutsceneActive
	BEQZ 	a0, CancelCutscene_Finish
	NOP
	LH 		a0, @CutsceneIndex
	LW 		a1, @CutsceneTypePointer
	BEQZ 	a1, CancelCutscene_Finish
	NOP
	LW  	a1, 0xD0 (a1) // Cutscene Databank
	BEQZ 	a1, CancelCutscene_Finish
	NOP
	LI 		a2, 0xC
	MULTU 	a0, a2
	MFLO 	a2
	ADD 	a1, a1, a2
	LH 		a1, 0x0 (a1) // Required Cam State
	SH 		a1, @CurrentCameraState
	SH 		a1, @PreviousCameraState
	ADDI 	a1, a1, -1
	SH 		r0, @CameraStateChangeTimer
	LW 		a0, @Player
	BEQZ 	a0, CancelCutscene_Finish
	NOP
	LI 		a1, 0xC
	SB 		a1, 0x154 (a0)

	CancelCutscene_Finish:
		JR 		ra
		NOP

ToggleCSCancelLMode:
	LI 		a1, 1
	LBU 	a0, @LToCancelCSOn
	SUBU 	a0, a1, a0
	SB 		a0, @LToCancelCSOn
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ToggleCSCancel_IsOff
	NOP
	LA 		a1, Menu_Cheats_LToCancelCS_On
	B 		ToggleCSCancel_Finish
	NOP

	ToggleCSCancel_IsOff:
		LA 		a1, Menu_Cheats_LToCancelCS_Off

	ToggleCSCancel_Finish:
		SW 		a1, 0x20 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 58
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

LTo_CancelCS:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @LToCancelCSOn
	BEQZ 	a0, LTo_CancelCS_Finish
	NOP
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, LTo_CancelCS_Finish // Active Menu
	NOP
	LBU 	a0, @ClosingMenu
	BNEZ 	a0, LTo_CancelCS_Finish
	NOP
	LHU 	a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @L_Button
	BEQZ 	a0, LTo_CancelCS_Finish
	NOP
	JAL 	CancelCutscene
	NOP

	LTo_CancelCS_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP