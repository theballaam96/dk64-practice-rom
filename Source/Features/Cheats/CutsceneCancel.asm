CancelCutscene:
	SW 		ra, @ReturnAddress4
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
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP