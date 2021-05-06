HandleTimer:
	// Timer Modes
		// 0 - Reset, 1 - Go, 2 - Finish
	// Start Modes
		// 0 - L, 1 - Load, 2 - Input
	// Finish Modes
		// 0 - L, 1 - Transition, 2 - CS, 3 - GB
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BEQZ 	a0, HandleTimer_TimerModes // Pause Menu
	NOP
	LBU 	a0, @TimerPauseMode
	BEQZ 	a0, HandleTimer_Finish
	NOP
	LBU 	a0, @StoredTimerMode
	LI 		a1, 1
	BNE 	a0, a1, HandleTimer_Finish
	NOP
	LW 		a0, @StoredLag
	LW 		a1, @TimerReduction
	ADD 	a1, a1, a0
	SW 		a1, @TimerReduction
	LW 		a1, @FrameReal
	LW 		a2, @StoredStart
	SUBU 	a1, a1, a2
	SW 		a1, @StoredTime
	B 		HandleTimer_Finish
	NOP

	HandleTimer_TimerModes:
		LBU 	a0, @StoredTimerMode
		BEQZ 	a0, HandleTimer_Ready
		NOP
		LI 		a1, 1
		BEQ 	a0, a1, HandleTimer_Running
		NOP
		LI 		a1, 2
		BEQ 	a0, a1, HandleTimer_Stopped
		NOP
		B 		HandleTimer_Finish
		NOP

	HandleTimer_Ready:
		LH 		a0, @NewlyPressedControllerInput
		ANDI 	a0, a0, @L_Button
		BNEZ 	a0, HandleTimer_ReadyTick
		NOP
		LBU 	a0, @TimerStartMode
		BEQZ 	a0, HandleTimer_Ready_L
		NOP
		LI 		a1, 1
		BEQ 	a0, a1, HandleTimer_Ready_MapLoad
		NOP
		LI 		a1, 2
		BEQ 	a0, a1, HandleTimer_Ready_Input
		NOP
		B 		HandleTimer_Finish
		NOP

		HandleTimer_Ready_L:
			LH 		a0, @NewlyPressedControllerInput
			ANDI 	a0, a0, @L_Button
			BNEZ 	a0, HandleTimer_ReadyTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_Ready_MapLoad:
			LW 		a0, @ObjectModel2Timer
			LI 		a1, 1
			BEQ 	a0, a1, HandleTimer_ReadyTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_Ready_Input:
			LW 		a0, @ControllerInput
			BNEZ 	a0, HandleTimer_ReadyTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_ReadyTick:
			LI 		a1, 1
			SB 		a1, @StoredTimerMode
			B 		HandleTimer_Finish
			NOP

	HandleTimer_Running:
		LW 		a1, @FrameReal
		LW 		a2, @StoredStart
		BNEZ 	a2, HandleTimer_Running2
		NOP
		SW 		a1, @StoredStart
		
	HandleTimer_Running2:
		SUBU 	a1, a1, a2
		SW 		a1, @StoredTime
		LH 		a0, @NewlyPressedControllerInput
		ANDI 	a0, a0, @L_Button
		BNEZ 	a0, HandleTimer_RunningTick
		NOP
		LBU 	a0, @TimerFinishMode
		BEQZ 	a0, HandleTimer_Running_L
		NOP
		LI 		a1, 1
		BEQ 	a0, a1, HandleTimer_Running_Transition
		NOP
		LI 		a1, 2
		BEQ 	a0, a1, HandleTimer_Running_Cutscene
		NOP
		LI 		a1, 3
		BEQ 	a0, a1, HandleTimer_Running_GB
		NOP
		B 		HandleTimer_Finish
		NOP

		HandleTimer_Running_L:
			LH 		a0, @NewlyPressedControllerInput
			ANDI 	a0, a0, @L_Button
			BNEZ 	a0, HandleTimer_RunningTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_Running_Transition:
			LW 		a0, @TransitionSpeed
			LUI 	a1, 0x3F80 // f32 = 1
			BEQ 	a0, a1, HandleTimer_RunningTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_Running_Cutscene:
			LBU 	a0, @InCutscene
			LI 		a1, 1
			BEQ 	a0, a1, HandleTimer_RunningTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_Running_GB:
			LW 		a0, @Player
			BEQZ  	a0, HandleTimer_Finish
			NOP
			LBU 	a1, 0x154 (a0)
			LI 		a2, 0x70
			BEQ 	a1, a2, HandleTimer_RunningTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_RunningTick:
			LI 		a1, 2
			SB 		a1, @StoredTimerMode
			B 		HandleTimer_Finish
			NOP

	HandleTimer_Stopped:
		LH 		a0, @NewlyPressedControllerInput
		ANDI 	a0, a0, @L_Button
		BEQZ 	a0, HandleTimer_Finish
		NOP
		SB 		r0, @StoredTimerMode
		SW 		r0, @StoredTime
		SW 		r0, @StoredStart
		SW 		r0, @TimerReduction
		SW 		r0, @TimerAfterReduction
		B 		HandleTimer_Finish
		NOP

	HandleTimer_Finish:
		LW 		a0, @StoredTime
		LW 		a1, @TimerReduction
		SUBU 	a0, a0, a1
		SW 		a0, @TimerAfterReduction
		JR 		ra
		NOP