ActiveMenu_Open:
	SW 		ra, @ReturnAddress
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, ActiveMenu_Open_Finish
	NOP
	LW 		a0, @CurrentMap
	LI 		a1, 0x50
	BEQ 	a0, a1, ActiveMenu_Open_Finish // Can't open in main menu
	NOP
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a1, a0, @D_Up
	BEQZ 	a1, ActiveMenu_Open_Finish
	NOP
	LH 		a0, @ControllerInput
	ANDI 	a1, a0, @L_Button
	BEQZ 	a1, ActiveMenu_Open_Finish
	NOP
	SB 		r0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	LBU		a0, @NewMenuOpen
	BNEZ	a0, ActiveMenu_Open_ActorExist
	NOP
	JAL 	ActiveMenu_SpawnMenu
	LI 		a0, 0
	B 		ActiveMenu_Open_Finish
	NOP

	ActiveMenu_Open_ActorExist:
		JAL 	ActiveMenu_ClearMenu
		NOP

	ActiveMenu_Open_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

ActiveMenu_MoveSlot:
	LBU 	a0, @NewMenuOpen
	BEQZ 	a0, ActiveMenu_MoveSlot_Finish
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, ActiveMenu_MoveSlot_Finish
	NOP
	LH 		a0, @ControllerInput
	ANDI 	a0, a0, @L_Button
	BNEZ 	a0, ActiveMenu_MoveSlot_Finish
	NOP
	LA 		t9, Menu_Screens
	LBU 	t8, @NewMenu_Screen
	SLL 	t8, t8, 2
	ADD 	t8, t9, t8
	LW 		t8, 0x0 (t8) // Screen Struct
	LBU 	t3, 0x8 (t8) // Cap
	LBU 	a2, @NewMenu_Position
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a1, a0, @D_Up
	BNEZ 	a1, ActiveMenu_MoveSlot_MoveUp
	NOP
	ANDI 	a1, a0, @D_Down
	BNEZ 	a1, ActiveMenu_MoveSlot_MoveDown
	NOP
	B 		ActiveMenu_MoveSlot_Finish
	NOP

	ActiveMenu_MoveSlot_MoveUp:
		BNEZ 	a2, ActiveMenu_MoveSlot_MoveUp_0
		NOP
		ADDIU 	a2, t3, 0

	ActiveMenu_MoveSlot_MoveUp_0:
		ADDIU 	a2, a2, -1
		B 		ActiveMenu_MoveSlot_UpdateColouring
		NOP

	ActiveMenu_MoveSlot_MoveDown:
		ADDIU 	a2, a2, 1
		BNE 	a2, t3, ActiveMenu_MoveSlot_UpdateColouring
		NOP
		LI 		a2, 0

	ActiveMenu_MoveSlot_UpdateColouring:
		SB 		a2, @NewMenu_Position
		LI 		a0, 0
		LI 		a1, @ActiveToolsMenu

	ActiveMenu_MoveSlot_UpdateColouring_Loop:
		LW 		a3, 0x0 (a1) // Text Overlay Object
		BEQZ 	a3, ActiveMenu_MoveSlot_UpdateColouring_LoopEnumerate
		NOP
		LBU 	a2, @NewMenu_Position
		BNE 	a0, a2, ActiveMenu_MoveSlot_UpdateColouring_LoopWhite
		NOP
		LI 		a2, @SelectedRGB
		ANDI 	a2, a2, 0xFF
		SB 		a2, 0x16C (a3)
		LI 		a2, @SelectedRGB
		SRA 	a2, a2, 8
		ANDI 	a2, a2, 0xFF
		SB 		a2, 0x16B (a3)
		LI 		a2, @SelectedRGB
		SRA 	a2, a2, 16
		ANDI 	a2, a2, 0xFF
		B 		ActiveMenu_MoveSlot_UpdateColouring_LoopEnumerate
		SB 		a2, 0x16A (a3)

	ActiveMenu_MoveSlot_UpdateColouring_LoopWhite:
		LI 		a2, 0xFF
		SB 		a2, 0x16A (a3)
		SB 		a2, 0x16B (a3)
		SB 		a2, 0x16C (a3)

	ActiveMenu_MoveSlot_UpdateColouring_LoopEnumerate:
		ADDIU 	a0, a0, 1
		BEQ 	a0, t3, ActiveMenu_MoveSlot_Finish
		ADDIU 	a1, a1, 4
		B 		ActiveMenu_MoveSlot_UpdateColouring_Loop
		NOP

	ActiveMenu_MoveSlot_Finish:
		JR 		ra
		NOP

ActiveMenu_ClearMenu:
	SW 		ra, @ReturnAddress2
	LI 		t9, @MaxMenuItems
	LI 		t6, @ActiveToolsMenu

	ActiveMenu_ClearMenu_Loop:
		SW 		t6, @VarStorage0
		SW 		t9, @VarStorage1
		LW 		a0, 0x0 (t6)
		BEQZ 	a0, ActiveMenu_ClearMenu_Loop_0
		NOP
		JAL 	@DeleteActor
		NOP
		LW 		t9, @VarStorage1
		LW 		t6, @VarStorage0

	ActiveMenu_ClearMenu_Loop_0:
		SW 		r0, 0x0 (t6)
		ADDIU 	t6, t6, 4
		ADDI 	t9, t9, -1
		BEQZ 	t9, ActiveMenu_ClearMenu_Finish
		NOP
		B 		ActiveMenu_ClearMenu_Loop
		NOP

	ActiveMenu_ClearMenu_Finish:
		SB 		r0, @NewMenuOpen
		LW 		ra, @ReturnAddress2
		JR 		ra
		NOP

ActiveMenu_CloseOnTransition:
	SW 		ra, @ReturnAddress
	LBU 	a0, @NewMenuOpen
	BEQZ 	a0, ActiveMenu_CloseOnTransition_Finish
	NOP
	LBU 	a0, @TransitionSpeed
	ANDI 	a0, a0, 0x80
	BNEZ 	a0, ActiveMenu_CloseOnTransition_CheckZipper // Non-negative
	NOP
	LW 		a0, @TransitionSpeed // Non-zero
	BEQZ 	a0, ActiveMenu_CloseOnTransition_CheckZipper
	NOP
	B 		ActiveMenu_CloseOnTransition_Close
	NOP

	ActiveMenu_CloseOnTransition_CheckZipper:
		LBU 	a0, @CutsceneActive
		LI 		a1, 6
		BNE 	a0, a1, ActiveMenu_CloseOnTransition_Finish
		NOP

	ActiveMenu_CloseOnTransition_Close:
		JAL 	ActiveMenu_ClearMenu
		NOP

	ActiveMenu_CloseOnTransition_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

ActiveMenu_SpawnMenu:
	// a0 = ScreenIndex
	SW 		ra, @ReturnAddress2
	LI 		t6, @ActiveToolsMenu
	LA 		t3, Menu_Screens
	SLL 	a0, a0, 2
	ADD 	t9, t3, a0
	LW 		t3, 0x0 (t9) // Screen Struct
	LBU 	t9, 0x8 (t3)
	LI 		t7, 0 // Index
	LI 		a2, 25 // Y
	LW 		t8, 0x0 (t3)

	ActiveMenu_SpawnMenu_Loop:
		SW 		a2, @VarStorage0
		SW 		t6, @VarStorage1
		SW 		t3, @VarStorage2
		SW 		t9, @VarStorage3
		SW 		t8, @VarStorage4
		LI 		a0, 10 // 0 = Center, 10 = Use X Value
		LI 		a1, 25
		LW 		a3, 0x0 (t8)
		JAL 	@SpawnTextOverlay
		NOP
		LW 		a0, @CurrentActorPointer
		BEQZ 	a0, ActiveMenu_SpawnMenu_NextActor
		NOP
		LW 		t8, @VarStorage4
		LW 		t9, @VarStorage3
		LW 		t3, @VarStorage2
		LW 		t6, @VarStorage1
		LW 		a2, @VarStorage0
		SW 		a0, 0x0 (t6) // Tools Menu Slot
		LI 		a1, 0xFF
		SB 		a1, 0x15F (a0) // Opacity
		LBU 	a1, 0x8 (t3) // Cap
		SUBU 	a1, a1, t9
		LBU 	t7, @NewMenu_Position
		BNE 	t7, a1, ActiveMenu_SpawnMenu_NextActor
		NOP
		LI 		t7, @SelectedRGB
		ANDI 	a1, t7, 0xFF
		SB 		a1, 0x16C (a0)
		SRA 	t7, t7, 8
		ANDI 	a1, t7, 0xFF
		SB 		a1, 0x16B (a0)
		SRA 	t7, t7, 8
		ANDI 	a1, t7, 0xFF
		SB 		a1, 0x16A (a0)

	ActiveMenu_SpawnMenu_NextActor:
		ADDIU 	a2, a2, 10 // y = y + 40
		ADDIU 	t6, t6, 4
		ADDIU 	t8, t8, 4
		ADDI 	t9, t9, -1
		BEQZ 	t9, ActiveMenu_SpawnMenu_Finish
		NOP
		B 		ActiveMenu_SpawnMenu_Loop
		NOP

	ActiveMenu_SpawnMenu_Finish:	
		LI 		a0, 1
		SB 		a0, @NewMenuOpen
		LW 		ra, @ReturnAddress2
		JR 		ra
		NOP

ActiveMenu_EmergencyClose:
	SW 		ra, @ReturnAddress
	LW 		a0, @NewMenu_ErrorStart
	BEQZ 	a0, ActiveMenu_EmergencyClose_NewError
	NOP
	LW 		a1, @FrameReal
	SUBU 	a1, a1, a0
	SLTI 	a2, a1, @ErrorLength
	BNEZ 	a2, ActiveMenu_EmergencyClose_Finish
	NOP
	LW 		a0, @ActiveTools_Error
	JAL 	@DeleteActor
	NOP
	SW 		r0, @NewMenu_ErrorStart
	B 		ActiveMenu_EmergencyClose_Finish
	NOP

	ActiveMenu_EmergencyClose_NewError:
		LBU 	a0, @LoadedActorCount
		SLTIU 	a1, a0, @EmergencyCloseLoadedAmount
		BNEZ 	a1, ActiveMenu_EmergencyClose_Finish
		NOP
		LBU 	a0, @NewMenuOpen
		BEQZ 	a0, ActiveMenu_EmergencyClose_Finish
		NOP
		LW 		a0, @FrameReal
		SW 		a0, @NewMenu_ErrorStart
		LI 		a0, 10 // 0 = Center, 10 = Use X Value
		LI 		a1, 100
		LI 		a2, 200
		LA 		a3, Menu_ForceClose
		JAL 	@SpawnTextOverlay
		NOP
		LW 		a0, @CurrentActorPointer
		BEQZ 	a0, ActiveMenu_EmergencyClose_Finish
		NOP
		SW 		a0, @ActiveTools_Error // Error Actor Slot
		LI 		a1, 0xFF
		SB 		a1, 0x15F (a0) // Opacity
		LI  	a1, 0xFF
		SB 		a1, 0x16A (a0)
		SB 		r0, 0x16B (a0)
		SB 		r0, 0x16C (a0)
		JAL 	ActiveMenu_ClearMenu
		NOP

	ActiveMenu_EmergencyClose_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

ActiveMenu_PressA:
	SW 		ra, @ReturnAddress
	LBU 	a0, @NewMenuOpen
	BEQZ 	a0, ActiveMenu_PressA_Finish
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, ActiveMenu_PressA_Finish
	NOP
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @A_Button
	BEQZ 	a0, ActiveMenu_PressA_Finish
	NOP
	LA 		a0, Menu_Screens
	LBU 	a1, @NewMenu_Screen
	SLL 	a1, a1, 2
	ADD 	a0, a0, a1
	LW 		a0, 0x0 (a0) // Screen Struct
	LW 		a0, 0x4 (a0) // Function Array
	LBU 	a1, @NewMenu_Position
	SLL 	a1, a1, 2
	ADD 	a0, a0, a1
	LW 		a0, 0x0 (a0) // Selected Function
	BEQZ 	a0, ActiveMenu_PressA_Finish
	NOP
	JALR 	a0
	NOP

	ActiveMenu_PressA_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

ActiveMenu_PressB:
	SW 		ra, @ReturnAddress
	LBU 	a0, @NewMenuOpen
	BEQZ 	a0, ActiveMenu_PressB_Finish
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, ActiveMenu_PressB_Finish
	NOP
	LH 		a0, @NewlyPressedControllerInput
	ANDI 	a1, a0, @B_Button
	BEQZ 	a1, ActiveMenu_PressB_Finish
	ANDI 	a1, a0, @A_Button
	BNEZ 	a1, ActiveMenu_PressB_Finish
	NOP
	LBU 	a1, @NewMenu_Screen
	BEQZ 	a1, ActiveMenu_PressB_IsHome
	NOP
	LA 		a0, Menu_Screens
	SLL 	a1, a1, 2
	ADD 	a0, a0, a1
	LW 		a0, 0x0 (a0) // Screen Struct
	LBU 	a0, 0x9 (a0) // Parent Screen
	SW 		a0, @VarStorage2
	JAL 	ActiveMenu_ClearMenu
	NOP
	LW 		a0, @VarStorage2
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	B 		ActiveMenu_PressB_Finish
	NOP

	ActiveMenu_PressB_IsHome:
		JAL 	ActiveMenu_ClearMenu
		NOP

	ActiveMenu_PressB_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP