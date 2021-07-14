FrameControl_Toggle:
	LBU 	a0, @ArtificialPauseOn
	BNEZ 	a0, FrameControl_CheckOtherInputs
	NOP
	SH 		r0, @PreviousFrameButtons

	FrameControl_CheckOtherInputs:
		LBU 	a0, @DisablePositionButtons
		LI 		a1, 1
		BNE 	a0, a1, FrameControl_Toggle_Finish
		NOP
		LBU 	a0, @NewMenuOpen
		BNEZ 	a0, FrameControl_Toggle_Finish
		NOP
		LBU 	a0, @IsPauseMenuOpen
		BNEZ 	a0, FrameControl_Toggle_Finish
		NOP
		LH 		a0, @NewlyPressedControllerInput
		ANDI 	a0, a0, @D_Right
		BEQZ 	a0, FrameControl_Toggle_Finish
		NOP
		LBU 	a0, @ArtificialPauseOn
		BNEZ 	a0, FrameControl_Toggle_Play
		NOP

	FrameControl_Toggle_Pause:
		LHU 	a1, @ControllerInput
		SH 		a1, @PreviousFrameButtons
		LBU 	a1, @TBVoidByte
		ORI 	a1, a1, 2
		SB 		a1, @TBVoidByte
		LI 		a2, 1
		SB 		a2, @ArtificialPauseOn
		B 		FrameControl_Toggle_Finish
		NOP

	FrameControl_Toggle_Play:
		SB 		r0, @FrameAdvancing
		LBU 	a1, @TBVoidByte
		ANDI 	a1, a1, 0xFD
		SB 		a1, @TBVoidByte
		SB 		r0, @ArtificialPauseOn

	FrameControl_Toggle_Finish:
		JR 		ra
		NOP

FrameControl_FrameAdvanceInit:
	LBU 	a0, @DisablePositionButtons
	LI 		a1, 1
	BNE 	a0, a1, FrameControl_FrameAdvanceInit_Finish
	NOP
	LBU 	a0, @IsPauseMenuOpen
	BNEZ 	a0, FrameControl_FrameAdvanceInit_Finish
	NOP
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, FrameControl_FrameAdvanceInit_Finish
	NOP
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @D_Left
	BEQZ 	a0, FrameControl_FrameAdvanceInit_Finish
	NOP
	LI 		a0, 1
	SB 		a0, @FrameAdvancing
	LW 		a0, @FrameLag
	SW 		a0, @FrameAdvanceStart
	LBU 	a1, @TBVoidByte
	ANDI 	a1, a1, 0xFD
	SB 		a1, @TBVoidByte
	SB 		r0, @ArtificialPauseOn

	FrameControl_FrameAdvanceInit_Finish:
		JR 		ra
		NOP

FrameControl_FrameAdvanceExit:
	LBU 	a0, @FrameAdvancing
	BEQZ 	a0, FrameControl_FrameAdvanceExit_Finish
	NOP
	LBU 	a0, @IsPauseMenuOpen
	BNEZ 	a0, FrameControl_FrameAdvanceExit_Finish
	NOP
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, FrameControl_FrameAdvanceExit_Finish
	NOP
	LW 		a0, @FrameLag
	LW 		a1, @FrameAdvanceStart
	SUBU 	a0, a0, a1
	BEQZ 	a0, FrameControl_FrameAdvanceExit_Finish
	NOP
	LBU 	a1, @TBVoidByte
	ANDI 	a2, a1, 2
	BNEZ 	a2, FrameControl_FrameAdvanceExit_Repause
	NOP
	LHU 	a2, @ControllerInput
	SH 		a2, @PreviousFrameButtons

	FrameControl_FrameAdvanceExit_Repause:
		ORI 	a1, a1, 2
		SB 		a1, @TBVoidByte
		LI 		a2, 1
		SB 		a2, @ArtificialPauseOn

	FrameControl_FrameAdvanceExit_Finish:
		JR 		ra
		NOP