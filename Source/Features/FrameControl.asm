FrameControl_Toggle:
	SW 		ra, @ReturnAddress4
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
		JAL 	@GetTimestamp
		NOP
		LI 		a0, @PauseTimestamp
		SW 		v0, 0x0 (a0)
		SW 		v1, 0x4 (a0)
		B 		FrameControl_Toggle_Finish
		NOP

	FrameControl_Toggle_Play:
		SB 		r0, @FrameAdvancing
		LBU 	a1, @TBVoidByte
		ANDI 	a1, a1, 0xFD
		SB 		a1, @TBVoidByte
		SB 		r0, @ArtificialPauseOn
		LBU 	a0, @HelmTimerShown
		BEQZ  	a0, FrameControl_Toggle_Play_ResetTimestamp
		NOP
		JAL 	@GetTimestamp
		NOP
		LI 		a0, @TempTimestampStorage
		SW 		v0, 0x0 (a0)
		SW 		v1, 0x4 (a0)
		LD 		a1, 0x0 (a0)
		LD 		a2, @PauseTimestamp
		BEQZ 	a2, FrameControl_Toggle_Play_ResetTimestamp
		NOP
		DSUBU 	a1, a1, a2
		LD 		a2, @HelmStartTimestamp
		DADDU 	a2, a1, a2
		SD 		a2, @HelmStartTimestamp
	FrameControl_Toggle_Play_ResetTimestamp:
		LI 		a0, @PauseTimestamp
		SW 		r0, 0x0 (a0)
		SW 		r0, 0x4 (a0)

	FrameControl_Toggle_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

FrameControl_FrameAdvanceInit:
	SW 		ra, @ReturnAddress4
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
	LBU 	a0, @FrameAdvancing
	BNEZ 	a0, FrameControl_FrameAdvanceInit_SetVars
	NOP
	LHU 	a1, @ControllerInput
	SH 		a1, @PreviousFrameButtons

	FrameControl_FrameAdvanceInit_SetVars:
		LI 		a0, 1
		SB 		a0, @FrameAdvancing
		LW 		a0, @FrameLag
		SW 		a0, @FrameAdvanceStart
		LBU 	a1, @TBVoidByte
		ANDI 	a1, a1, 0xFD
		SB 		a1, @TBVoidByte
		SB 		r0, @ArtificialPauseOn
		LHU 	a0, @BackgroundHeldInput
		LHU 	a1, @PreviousFrameButtons
		ORI 	a1, a1, 0x0F00
		AND 	a0, a0, a1 // Reset non DPad buttons
		SH 		a0, @BackgroundHeldInput
		LBU 	a0, @HelmTimerShown
		BEQZ  	a0, FrameControl_FrameAdvanceInit_ResetTimestamp
		NOP
		JAL 	@GetTimestamp
		NOP
		LI 		a0, @TempTimestampStorage
		SW 		v0, 0x0 (a0)
		SW 		v1, 0x4 (a0)
		LD 		a1, 0x0 (a0)
		LD 		a2, @PauseTimestamp
		BEQZ 	a2, FrameControl_FrameAdvanceInit_ResetTimestamp
		NOP
		DSUBU 	a1, a1, a2
		LD 		a2, @HelmStartTimestamp
		DADDU 	a2, a1, a2
		SD 		a2, @HelmStartTimestamp

	FrameControl_FrameAdvanceInit_ResetTimestamp:
		LI 		a0, @PauseTimestamp
		SW 		r0, 0x0 (a0)
		SW 		r0, 0x4 (a0)

	FrameControl_FrameAdvanceInit_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

FrameControl_FrameAdvanceExit:
	SW 		ra, @ReturnAddress4
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
	JAL 	@GetTimestamp
	NOP
	LI 		a0, @PauseTimestamp
	SW 		v0, 0x0 (a0)
	SW 		v1, 0x4 (a0)

	FrameControl_FrameAdvanceExit_Repause:
		ORI 	a1, a1, 2
		SB 		a1, @TBVoidByte
		LI 		a2, 1
		SB 		a2, @ArtificialPauseOn

	FrameControl_FrameAdvanceExit_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP