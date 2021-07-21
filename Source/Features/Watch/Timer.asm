HandleTimer:
	// Timer Modes
		// 0 - Reset, 1 - Go, 2 - Finish
	// Start Modes
		// 0 - L, 1 - Load, 2 - Input
	// Finish Modes
		// 0 - L, 1 - Transition, 2 - CS, 3 - GB
	SW 		ra, @ReturnAddress5
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, HandleTimer_CheckRunning // Active Menu
	NOP
	LBU 	a0, @ClosingMenu
	BNEZ 	a0, HandleTimer_CheckRunning
	NOP
	LBU 	a0, @VariableDisplayOn
	LI 		a1, 4 // Timer Watch Index
	BNE 	a0, a1, HandleTimer_Finish
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BEQZ 	a0, HandleTimer_TimerModes // Pause Menu or frame advance
	NOP
	LBU 	a0, @TimerPauseMode
	BNEZ 	a0, HandleTimer_CheckMode
	NOP
	LBU 	a0, @ArtificialPauseOn
	BEQZ 	a0, HandleTimer_Finish
	NOP

	HandleTimer_CheckMode:
		LBU 	a0, @StoredTimerMode
		LI 		a1, 1
		BNE 	a0, a1, HandleTimer_Finish
		NOP

	HandleTimer_Pause:
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

	HandleTimer_CheckRunning:
		LBU 	a0, @StoredTimerMode
		LI 		a1, 1
		BEQ 	a0, a1, HandleTimer_Running
		NOP
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
			LHU		a0, @NewlyPressedControllerInput
			BNEZ 	a0, HandleTimer_ReadyTick
			NOP
			LI 		a0, @ControllerInput
			LHU 	a1, 0x2 (a0)
			BNEZ 	a1, HandleTimer_Ready_Input_NonNeutral
			NOP
			LI 		a1, 1
			SB 		a1, @HasNeutralStickInput
			B 		HandleTimer_Finish
			NOP

			HandleTimer_Ready_Input_NonNeutral:
				LBU 	a0, @HasNeutralStickInput
				BNEZ 	a0, HandleTimer_ReadyTick
				NOP
				B 		HandleTimer_Finish
				NOP

		HandleTimer_ReadyTick:
			LI 		a1, 1
			SB 		a1, @StoredTimerMode
			LW 		a1, @FrameReal
			SW 		a1, @StoredStart
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
		LBU 	a0, @NewMenuOpen
		BNEZ 	a0, HandleTimer_Finish // Active Menu
		NOP
		LBU 	a0, @ClosingMenu
		BNEZ 	a0, HandleTimer_Finish
		NOP
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
		LI 		a1, 4
		BEQ 	a0, a1, HandleTimer_Running_EndTransition
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
			JAL 	TimerControl_IsTouchingGB
			NOP
			LBU 	a0, @TouchingGB
			BNEZ 	a0, HandleTimer_RunningTick
			NOP
			B 		HandleTimer_Finish
			NOP

		HandleTimer_Running_EndTransition:
			LW 		a0, @TransitionSpeed
			LUI 	a1, 0x3F80
			BNE 	a0, a1, HandleTimer_Finish
			NOP
			LBU 	a0, @TransitionProgress
			BEQZ 	a0, HandleTimer_RunningTick
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
		SB 		r0, @HasNeutralStickInput
		B 		HandleTimer_Finish
		NOP

	HandleTimer_Finish:
		LW 		a0, @StoredTime
		LW 		a1, @TimerReduction
		SUBU 	a0, a0, a1
		SW 		a0, @TimerAfterReduction
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

TimerControl_IsTouchingGB:
	// Actors = 45
	SW 		ra, @ReturnAddress3
	SB 		r0, @TouchingGB
	LBU 	a0, @ModelTwoTouchCount
	BEQZ 	a0, TimerControl_IsTouchingGB_Actor_Check
	NOP
	LI 		a1, @ModelTwoTouchArray

	TimerControl_IsTouchingGB_ModelTwo_Loop:
		LHU 	t0, 0x0 (a1)
		SW 		a0, @VarStorage0
		SW 		a1, @VarStorage1
		JAL 	ConvertIDToIndex
		ADDIU 	a0, t0, 0
		ADDIU 	t6, v0, 0
		LW 		a0, @VarStorage0
		LW 		a1, @VarStorage1
		LW 		t0, @ObjectModel2Pointer
		LI 		t3, 0x90
		MULT 	t3, t6
		MFLO 	t3
		ADD 	t0, t0, t3
		LHU 	t0, 0x84 (t0) // Model Two Type
		LI 		t3, 0x74
		BNE 	t0, t3, TimerControl_IsTouchingGB_ModelTwo_Increment
		NOP
		B 		TimerControl_IsTouchingGB_Set
		NOP

	TimerControl_IsTouchingGB_ModelTwo_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, TimerControl_IsTouchingGB_Actor_Check
		ADDIU 	a0, a0, 2
		B 		TimerControl_IsTouchingGB_ModelTwo_Loop
		NOP

	TimerControl_IsTouchingGB_Actor_Check:
		// Checks for movement, try to check for collision in future
		LW 		a0, @Player
		BEQZ  	a0, TimerControl_IsTouchingGB_Finish
		NOP
		LBU 	a1, 0x154 (a0)
		LI 		a2, 0x70
		BNE 	a1, a2, TimerControl_IsTouchingGB_Finish
		NOP

	TimerControl_IsTouchingGB_Set:
		LI 		t6, 1
		SB 		t6, @TouchingGB

	TimerControl_IsTouchingGB_Finish:
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ConvertIDToIndex:
	// a0 = ID
	LW 		t0, @ObjectModel2Pointer
	LW 		t3, @ObjectModel2Count
	LI 		t9, 0

	ConvertIDToIndex_Loop:
		LHU 	t7, 0x8A (t0)
		BEQ 	t7, a0, ConvertIDToIndex_GrabIndex
		NOP
		ADDI 	t3, t3, -1
		BEQZ 	t3, ConvertIDToIndex_GrabIndex
		ADDIU 	t0, t0, 0x90
		B 		ConvertIDToIndex_Loop
		ADDIU 	t9, t9, 1

	ConvertIDToIndex_GrabIndex:
		B 		ConvertIDToIndex_Finish
		ADDIU 	v0, t9, 0

	ConvertIDToIndex_Finish:
		JR 		ra
		NOP


TimerControl_ToggleStartCondition:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @TimerStartMode
	ADDIU 	a0, a0, 1
	LI 		a1, 3
	BNE 	a0, a1, TimerControl_ToggleStartCondition_Finish
	NOP
	LI 		a0, 0

	TimerControl_ToggleStartCondition_Finish:
		SB 		a0, @TimerStartMode
		JAL 	ActiveMenu_OpenTimerSettingsMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

TimerControl_TogglePauseCondition:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @TimerPauseMode
	ADDIU 	a0, a0, 1
	LI 		a1, 2
	BNE 	a0, a1, TimerControl_TogglePauseCondition_Finish
	NOP
	LI 		a0, 0

	TimerControl_TogglePauseCondition_Finish:
		SB 		a0, @TimerPauseMode
		JAL 	ActiveMenu_OpenTimerSettingsMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

TimerControl_ToggleFinishCondition:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @TimerFinishMode
	ADDIU 	a0, a0, 1
	LI 		a1, 5
	BNE 	a0, a1, TimerControl_ToggleFinishCondition_Finish
	NOP
	LI 		a0, 0

	TimerControl_ToggleFinishCondition_Finish:
		SB 		a0, @TimerFinishMode
		JAL 	ActiveMenu_OpenTimerSettingsMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

ActiveMenu_OpenTimerSettingsMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LA 		a0, Menu_TimerSettings_Array
	// Start Mode
	LA 		a1, Menu_Timer_StartMode_List
	LBU 	a2, @TimerStartMode
	SLL 	a2, a2, 2
	ADD 	a1, a1, a2
	LW 		a1, 0x0 (a1)
	SW 		a1, 0x0 (a0)
	// Pause Mode
	LA 		a1, Menu_Timer_PauseMode_List
	LBU 	a2, @TimerPauseMode
	SLL 	a2, a2, 2
	ADD 	a1, a1, a2
	LW 		a1, 0x0 (a1)
	SW 		a1, 0x4 (a0)
	// Finish Mode
	LA 		a1, Menu_Timer_FinishMode_List
	LBU 	a2, @TimerFinishMode
	SLL 	a2, a2, 2
	ADD 	a1, a1, a2
	LW 		a1, 0x0 (a1)
	SW 		a1, 0x8 (a0)
	// Spawn
	LI 		a0, 60
	LBU 	a1, @NewMenu_Screen
	BEQ 	a0, a1, ActiveMenu_OpenTimerSettingsMenu_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenTimerSettingsMenu_Spawn:
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
Menu_Timer_StartMode_LPress:
	.asciiz "START ON: L PRESS"
Menu_Timer_StartMode_MapLoad:
	.asciiz "START ON: MAP LOAD"
Menu_Timer_StartMode_Input:
	.asciiz "START ON: INPUT"

Menu_Timer_PauseMode_Off:
	.asciiz "PAUSE TIMER ON PAUSE MENU: NO"
Menu_Timer_PauseMode_On:
	.asciiz "PAUSE TIMER ON PAUSE MENU: YES"

Menu_Timer_FinishMode_LPress:
	.asciiz "END ON: L PRESS"
Menu_Timer_FinishMode_Transition:
	.asciiz "END ON: TRANSITION"
Menu_Timer_FinishMode_Cutscene:
	.asciiz "END ON: CUTSCENE"
Menu_Timer_FinishMode_GB:
	.asciiz "END ON: GB COLLECTION"
Menu_Timer_FinishMode_EndTransition:
	.asciiz "END ON: TRANSITION COMPLETE"

.align
Menu_Timer_StartMode_List:
	.word Menu_Timer_StartMode_LPress
	.word Menu_Timer_StartMode_MapLoad
	.word Menu_Timer_StartMode_Input
Menu_Timer_PauseMode_List:
	.word Menu_Timer_PauseMode_Off
	.word Menu_Timer_PauseMode_On
Menu_Timer_FinishMode_List:
	.word Menu_Timer_FinishMode_LPress
	.word Menu_Timer_FinishMode_Transition
	.word Menu_Timer_FinishMode_Cutscene
	.word Menu_Timer_FinishMode_GB
	.word Menu_Timer_FinishMode_EndTransition

.align
Menu_TimerSettings_Array:
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_TimerSettings_Functions:
	.word TimerControl_ToggleStartCondition
	.word TimerControl_TogglePauseCondition
	.word TimerControl_ToggleFinishCondition
	.word ActiveMenu_PreviousScreen

.align
Menu_TimerSettings_Struct:
	.word Menu_TimerSettings_Array // Text Array
	.word Menu_TimerSettings_Functions // Function Array
	.byte 4 // Array Items
	.byte 0 // Parent Screen
