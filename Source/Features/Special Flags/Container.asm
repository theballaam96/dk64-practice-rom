.align
Menu_Flags_Kongs:
	.asciiz "KONGS FREED"
Menu_Flags_KeysIn:
	.asciiz "KEYS TURNED IN"
Menu_Flags_KeysHave:
	.asciiz "KEYS IN POSSESSION"
Menu_Flags_LevelIntros:
	.asciiz "LEVEL INTROS"
Menu_Flags_LevelTnS:
	.asciiz "LEVEL TROFF N SCOFF"
Menu_Flags_LevelBoss:
	.asciiz "LEVEL BOSS INTROS"
Menu_Flags_Cutscenes:
	.asciiz "CUTSCENES"
Menu_Flags_Modifiers:
	.asciiz "LEVEL MODIFIERS"
Menu_Flags_Misc:
	.asciiz "MISCELLANEOUS"
Menu_Flags_Custom:
	.asciiz "CUSTOM"

.align
Menu_Flags_Array:
	.word Menu_Flags_Kongs
	.word Menu_Flags_KeysIn
	.word Menu_Flags_KeysHave
	.word Menu_Flags_LevelIntros
	.word Menu_Flags_LevelTnS
	.word Menu_Flags_LevelBoss
	.word Menu_Flags_Cutscenes
	.word Menu_Flags_Modifiers
	.word Menu_Flags_Misc
	.word Menu_Flags_Custom

.align
Menu_Flags_Functions:
	.word ActiveMenu_OpenFlagMenu_Kong
	.word ActiveMenu_OpenFlagMenu_KeyIn
	.word ActiveMenu_OpenFlagMenu_KeyHave
	.word ActiveMenu_OpenFlagMenu_LevelIntro
	.word ActiveMenu_OpenFlagMenu_LevelTnS
	.word ActiveMenu_OpenFlagMenu_BossIntro
	.word ActiveMenu_OpenFlagMenu_Cutscenes
	.word ActiveMenu_OpenFlagMenu_Modifiers
	.word ActiveMenu_OpenFlagMenu_Misc
	.word ActiveMenu_OpenFlagMenu_Custom

.align
Menu_Flags_Struct:
	.word Menu_Flags_Array ; Text Array
	.word Menu_Flags_Functions ; Function Array
	.byte 10 ; Array Items
	.byte 0 ; Parent Screen

.align
Menu_Flags_DataStruct:
	.word Menu_Flags_KongStruct
	.word Menu_Flags_KeyInStruct
	.word Menu_Flags_KeyHaveStruct
	.word Menu_Flags_LevelIntroStruct
	.word Menu_Flags_LevelTnSStruct
	.word Menu_Flags_BossIntroStruct
	.word Menu_Flags_CutscenesStruct
	.word Menu_Flags_ModifiersStruct
	.word Menu_Flags_MiscStruct
	.word Menu_Flags_TrainingStruct

.align
ActiveMenu_OpenFlagMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 36
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenFlagsSubmenu:
	; a0 = Menu Screen Index
	; a1 = Reset Menu Position
	SW 		ra, @ReturnAddress3
	SW 		a0, @VarStorage3
	SW 		a1, @VarStorage5
	JAL 	ActiveMenu_ClearMenu
	NOP
	LW 		a0, @VarStorage3
	LA 		a1, Menu_Flags_DataStruct
	LI 		a2, @SpecialFlagCategories ; Special Flag Subcategories
	
	ActiveMenu_OpenFlagsSubmenu_Loop:
		LW 		t0, 0x0 (a1) ; Flag Data Struct
		LBU 	t3, 0xC (t0) ; Associated Screen
		BNE 	t3, a0, ActiveMenu_OpenFlagsSubmenu_Increment
		NOP
		LI 		t9, 0
		SW 		t0, @VarStorage2
		SW 		t9, @VarStorage1
		
		ActiveMenu_OpenFlagsSubmenu_FlagLoop:
			LW 		t0, @VarStorage2
			LW 		t9, @VarStorage1
			LW 		t6, 0x0 (t0) ; Flags
			LW 		t7, 0x4 (t0) ; Flag Types
			SLL 	t8, t9, 1
			ADD  	t6, t6, t8
			ADD 	t7, t7, t9
			LHU 	a0, 0x0 (t6)
			JAL 	@CheckFlag
			LBU 	a1, 0x0 (t7)
			ADDIU 	a0, v0, 0
			LW 		t0, @VarStorage2
			LW 		t9, @VarStorage1
			LW 		t3, 0x8 (t0) ; Text Struct
			SLL 	t8, t9, 2
			ADD 	t3, t3, t8
			LW 		t3, 0x0 (t3) ; Focused Text Info
			SLL 	a0, a0, 2
			ADD 	t3, t3, a0
			LW 		t3, 0x0 (t3) ; Focused Text Pointer
			LW 		a0, @VarStorage3
			LA 		a1, Menu_Screens
			SLL 	a0, a0, 2
			ADD 	a1, a1, a0
			LW 		a1, 0x0 (a1) ; Focused Menu Screen Struct
			LW 		a1, 0x0 (a1) ; Focused Text Array
			ADD 	a1, a1, t8 ; Focused Text Item
			SW 		t3, 0x0 (a1)
			LBU 	t8, 0xD (t0) ; Flag Count
			ADDIU 	t9, t9, 1
			SW 		t9, @VarStorage1
			BEQ 	t9, t8, ActiveMenu_OpenFlagsSubmenu_FinishSpawn
			NOP
			B 		ActiveMenu_OpenFlagsSubmenu_FlagLoop
			NOP

	ActiveMenu_OpenFlagsSubmenu_Increment:
		ADDI 	a2, a2, -1
		BEQZ 	a2, ActiveMenu_OpenFlagsSubmenu_FinishSpawn
		NOP
		B 		ActiveMenu_OpenFlagsSubmenu_Loop
		ADDIU 	a1, a1, 4

	ActiveMenu_OpenFlagsSubmenu_FinishSpawn:
		LW 		a0, @VarStorage3
		SB 		a0, @NewMenu_Screen
		LW 		a1, @VarStorage5
		BEQZ 	a1, ActiveMenu_OpenFlagsSubmenu_Spawn
		NOP
		SB 		r0, @NewMenu_Position

	ActiveMenu_OpenFlagsSubmenu_Spawn:
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ToggleFlag:
	SW 		ra, @ReturnAddress5
	LBU	 	a0, @NewMenu_Screen
	LA 		a1, Menu_Flags_DataStruct
	LI 		a2, @SpecialFlagCategories

	ActiveMenu_ToggleFlag_Loop:
		LW 		t0, 0x0 (a1) ; Focused Data Struct
		LBU 	t3, 0xC (t0) ; Associated Screen
		BNE 	a0, t3, ActiveMenu_ToggleFlag_Increment
		NOP
		LBU 	a3, @NewMenu_Position
		LW 		t6, 0x0 (t0)
		LW 		t8, 0x4 (t0)
		SLL 	t9, a3, 1
		ADD 	t6, t6, t9
		ADD 	t8, t8, a3
		LHU 	a0, 0x0 (t6)
		LBU 	a1, 0x0 (t8)
		SW 		a0, @VarStorage0
		SW 		a1, @VarStorage1
		JAL 	@CheckFlag
		NOP
		ADDIU 	a1, v0, 0
		LI 		t0, 1
		LW 		a2, @VarStorage1
		LW 		a0, @VarStorage0
		JAL 	@SetFlag
		SUBU 	a1, t0, a1
		B 		ActiveMenu_ToggleFlag_Finish
		NOP

	ActiveMenu_ToggleFlag_Increment:
		ADDI 	a2, a2, -1
		BEQZ 	a2, ActiveMenu_ToggleFlag_Finish
		NOP
		B 		ActiveMenu_ToggleFlag_Loop
		ADDIU 	a1, a1, 4

	ActiveMenu_ToggleFlag_Finish:
		LBU 	a0, @NewMenu_Screen
		LI 		a1, 0
		JAL 	ActiveMenu_OpenFlagsSubmenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP