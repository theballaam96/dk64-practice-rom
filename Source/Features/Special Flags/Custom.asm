ChangeEncodedFlag:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @NewMenuOpen
	BEQZ 	a0, ChangeEncodedFlag_Finish
	NOP
	LBU 	a0, @NewMenu_Screen
	LI 		a1, 51
	BNE 	a0, a1, ChangeEncodedFlag_Finish
	NOP
	LHU 	a0, @NewlyPressedControllerInput
	ANDI 	t0, a0, @L_Button
	BNEZ 	t0, ChangeEncodedFlag_Finish
	NOP
	ANDI 	t0, a0, @D_Left
	BNEZ 	t0, ChangeEncodedFlag_GetType
	LI 		t3, -1
	ANDI 	t0, a0, @D_Right
	BNEZ 	t0, ChangeEncodedFlag_GetType
	LI 		t3, 1
	B 		ChangeEncodedFlag_Finish
	NOP

	ChangeEncodedFlag_GetType:
		LBU 	a0, @NewMenu_Position
		BEQZ 	a0, ChangeEncodedFlag_ByteWrite
		NOP
		LI 		a1, 1
		BEQ 	a0, a1, ChangeEncodedFlag_BitWrite
		NOP
		LI 		a1, 2
		BEQ 	a0, a1, ChangeEncodedFlag_TypeWrite
		NOP
		B 		ChangeEncodedFlag_Finish
		NOP

	ChangeEncodedFlag_ByteWrite:
		LHU 	a0, @CustomFlagByte
		ADD 	a0, a0, t3
		LBU 	a1, @CustomFlagType
		SLL 	a1, a1, 1
		LA 		a2, CustomFlag_MaxFlagByteValues
		ADD 	a2, a2, a1
		LHU 	a2, 0x0 (a2)
		ADDIU 	a2, a2, 1
		SLTU 	a3, a0, a2
		BEQZ 	a3, ChangeEncodedFlag_ByteWriteToMax
		NOP
		SH 		a0, @CustomFlagByte
		B 		ChangeEncodedFlag_Update
		NOP

	ChangeEncodedFlag_ByteWriteToMax:
		LI 		t6, 1
		BEQ 	t3, t6, ChangeEncodedFlag_ByteWriteToMem
		LI 		t7, 0
		ADDI 	t7, a2, -1

	ChangeEncodedFlag_ByteWriteToMem:
		SH 		t7, @CustomFlagByte
		B 		ChangeEncodedFlag_Update
		NOP

	ChangeEncodedFlag_BitWrite:
		LBU 	a0, @CustomFlagBit
		ADD 	a0, a0, t3
		LI 		a1, 8
		BEQ 	a0, a1, ChangeEncodedFlag_BitWriteToMem
		LI 		t7, 0
		LI  	a1, -1
		BEQ 	a0, a1, ChangeEncodedFlag_BitWriteToMem
		LI 		t7, 7
		ADDIU 	t7, a0, 0

	ChangeEncodedFlag_BitWriteToMem:
		SB 		t7, @CustomFlagBit
		B 		ChangeEncodedFlag_Update
		NOP

	ChangeEncodedFlag_TypeWrite:
		LBU 	a0, @CustomFlagType
		LI 		t7, -1
		BNE 	t3, t7, CustomEncodedFlag_TypeWrite_Standard
		NOP
		LI 		t7, 1
		BNE 	a0, t7, ChangeEncodedFlag_TypeWrite_CheckTemp
		NOP
		B 		ChangeEncodedFlag_TypeWriteToMem
		LI 		t7, 0

	ChangeEncodedFlag_TypeWrite_CheckTemp:
		LI 		t7, 2
		BNE 	a0, t7, CustomEncodedFlag_TypeWrite_Standard
		NOP
		B 		ChangeEncodedFlag_TypeWriteToMem
		LI 		t7, 1

	CustomEncodedFlag_TypeWrite_Standard:
		ADD 	a0, a0, t3
		LI 		a1, 3
		BEQ 	a0, a1, ChangeEncodedFlag_TypeWriteToMem
		LI 		t7, 0
		LI  	a1, -1
		BEQ 	a0, a1, ChangeEncodedFlag_TypeWriteToMem
		LI 		t7, 2
		ADDIU 	t7, a0, 0

	ChangeEncodedFlag_TypeWriteToMem:
		SB 		t7, @CustomFlagType
		B 		ChangeEncodedFlag_Update
		NOP

	ChangeEncodedFlag_Update:
		LA 		a0, CustomFlag_MaxFlagByteValues
		LBU 	t7, @CustomFlagType
		SLL 	t7, t7, 1
		ADD 	a0, a0, t7
		LHU 	a0, 0x0 (a0) // Max Flag Cap
		LHU 	t7, @CustomFlagByte
		SLTU 	a1, t7, a0
		BNEZ 	a1, ChangeEncodedFlag_Update_Spawn
		NOP
		SH 		a0, @CustomFlagByte

	ChangeEncodedFlag_Update_Spawn:
		JAL 	ActiveMenu_OpenFlagMenu_Custom
		NOP

	ChangeEncodedFlag_Finish:
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

.align
CustomFlag_MaxFlagByteValues:
	.half 0x013B
	.half 0x0007
	.half 0x000F

.align
CustomFlag_Type0:
	.asciiz "TYPE: PERMANENT"
CustomFlag_Type1:
	.asciiz "TYPE: GLOBAL"
CustomFlag_Type2:
	.asciiz "TYPE: TEMPORARY"
CustomFlag_Set:
	.asciiz "SET"
CustomFlag_Clear:
	.asciiz "CLEAR"
CustomFlag_CurrentState_Set:
	.asciiz "CURRENT STATE: SET"
CustomFlag_CurrentState_Clear:
	.asciiz "CURRENT STATE: CLEARED"
CustomFlag_Byte:
	.asciiz "BYTE: 0x%04X"
CustomFlag_Bit:
	.asciiz "BIT: %1d"
CustomFlag_ByteText:
	.space 0x10
CustomFlag_BitText:
	.space 0x10
.align
CustomFlag_Types:
	.word CustomFlag_Type0
	.word CustomFlag_Type1
	.word CustomFlag_Type2
CustomFlag_Values:
	.word CustomFlag_CurrentState_Clear
	.word CustomFlag_CurrentState_Set
	.word CustomFlag_Set
	.word CustomFlag_Clear

.align
Menu_Flags_Custom_Array:
	.word 0
	.word 0
	.word CustomFlag_Type0
	.word CustomFlag_CurrentState_Clear
	.word CustomFlag_Set
	.word Menu_Return

.align
Menu_Flags_Custom_Functions:
	.word CustomFlag_Change
	.word CustomFlag_Change
	.word CustomFlag_Change
	.word 0
	.word CustomFlag_Change
	.word ActiveMenu_PreviousScreen

.align
Menu_Flags_Custom_Struct:
	.word Menu_Flags_Custom_Array // Text Array
	.word Menu_Flags_Custom_Functions // Function Array
	.byte 6 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_Custom:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	JAL 	CustomFlag_UpdateText
	NOP
	// Redefine
	LI 		a0, 51
	LBU 	a1, @NewMenu_Screen
	BEQ 	a0, a1, ActiveMenu_OpenFlagMenu_Custom_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenFlagMenu_Custom_Spawn:
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

CustomFlag_UpdateText:
	SW 		ra, @ReturnAddress2
	// Update Byte Text
	LA 		a0, CustomFlag_ByteText
	LA 		a1, CustomFlag_Byte
	LHU 	a2, @CustomFlagByte
	JAL 	@StrFormat
	NOP
	LA 		a3, Menu_Flags_Custom_Array
	LA 		a1, CustomFlag_ByteText
	SW 		a1, 0x0 (a3)
	// Update Bit Text
	LA 		a0, CustomFlag_BitText
	LA 		a1, CustomFlag_Bit
	LBU 	a2, @CustomFlagBit
	JAL 	@StrFormat
	NOP
	LA 		a3, Menu_Flags_Custom_Array
	LA 		a1, CustomFlag_BitText
	SW 		a1, 0x4 (a3)
	// Update Type
	LBU 	a0, @CustomFlagType
	SLL 	a0, a0, 2
	LA 		a1, CustomFlag_Types
	ADD 	a1, a1, a0
	LW 		a1, 0x0 (a1)
	SW 		a1, 0x8 (a3)
	// Update States
	LHU 	a0, @CustomFlagByte
	SLL 	a0, a0, 3
	LBU 	a1, @CustomFlagBit
	ADD 	a0, a0, a1
	LBU 	a1, @CustomFlagType
	JAL 	@CheckFlag
	NOP
	LA 		a3, Menu_Flags_Custom_Array
	ADDIU 	a0, v0, 0
	LI 		a1, 1
	SUBU 	a1, a1, a0
	SB 		a1, @CustomFlagSet
	SLL 	a0, a0, 2
	LA 		a1, CustomFlag_Values
	ADD 	a1, a1, a0
	LW 		a2, 0x0 (a1)
	SW 		a2, 0xC (a3)
	LW 		a2, 0x8 (a1)
	SW 		a2, 0x10 (a3)
	// Return
	LW 		ra, @ReturnAddress2
	JR 		ra
	NOP

CustomFlag_Change:
	SW 		ra, @ReturnAddress
	LHU 	a0, @CustomFlagByte
	LBU 	a1, @CustomFlagBit
	SLL 	a0, a0, 3
	ADD 	a0, a0, a1
	LBU 	a1, @CustomFlagSet
	LBU 	a2, @CustomFlagType
	JAL 	@SetFlag
	NOP
	LI 		a0, @BeepHigh
	JAL 	CodedPlaySFX
	NOP
	JAL 	ActiveMenu_OpenFlagMenu_Custom
	NOP
	LW 		ra, @ReturnAddress
	JR 		ra
	NOP