FrameControl_Toggle:
	LBU 	a0, @DisablePositionButtons
	LI 		a1, 1
	BNE 	a0, a1, FrameControl_Toggle_Finish
	NOP
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @D_Right
	BEQZ 	a0, FrameControl_Toggle_Finish
	NOP
	LBU 	a0, @ArtificialPauseOn
	BNEZ 	a0, FrameControl_Toggle_Play
	NOP

	FrameControl_Toggle_Pause:
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
	BNE 	a0, a1, FrameControl_Toggle_Finish
	NOP
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @D_Left
	BEQZ 	a0, FrameControl_Toggle_Finish
	NOP
	LI 		a0, 1
	SB 		a0, @FrameAdvancing
	LW 		a0, @FrameLag
	SW 		a0, @FrameAdvanceStart
	LBU 	a1, @TBVoidByte
	ANDI 	a1, a1, 0xFD
	SB 		a1, @TBVoidByte
	SB 		r0, @ArtificialPauseOn
	JR 		ra
	NOP

FrameControl_FrameAdvanceExit:
	LBU 	a0, @FrameAdvancing
	BEQZ 	a0, FrameControl_FrameAdvanceExit_Finish
	NOP
	LW 		a0, @FrameLag
	LW 		a1, @FrameAdvanceStart
	SUBU 	a0, a0, a1
	BEQZ 	a0, FrameControl_FrameAdvanceExit_Finish
	NOP
	LBU 	a1, @TBVoidByte
	ORI 	a1, a1, 2
	SB 		a1, @TBVoidByte
	LI 		a2, 1
	SB 		a2, @ArtificialPauseOn

	FrameControl_FrameAdvanceExit_Finish:
		JR 		ra
		NOP