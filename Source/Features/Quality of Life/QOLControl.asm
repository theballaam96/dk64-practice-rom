.align
Menu_QOL_Addresses:
	.word @DisableStartupSkip // Startup
	.word @DisableForcedStorySkip // Story Skip
	.word @PauseMenuMusicSetting // Pause Volume

.align
Menu_QOL_ControlStruct:
	.word Menu_QOL_Addresses ; Addresses
	.word Menu_QOL_Control_TextStruct ; Text Information
	.byte 46 ; Associated Screen
	.byte 3 ; Flag Count

.align
Menu_QOL_Control_Startup_Set:
	.asciiz "QUICK STARTUP: OFF"
Menu_QOL_Control_Startup_Clear:
	.asciiz "QUICK STARTUP: ON"
Menu_QOL_Control_Story_Set:
	.asciiz "FORCED STORY SKIP: OFF"
Menu_QOL_Control_Story_Clear:
	.asciiz "FORCED STORY SKIP: ON"
Menu_QOL_Control_PauseVolume_Normal:
	.asciiz "PAUSE VOLUME: NORMAL"
Menu_QOL_Control_PauseVolume_Quiet:
	.asciiz "PAUSE VOLUME: QUIET"
Menu_QOL_Control_PauseVolume_Silent:
	.asciiz "PAUSE VOLUME: SILENT"

.align
Menu_QOL_Control_Startup_Struct:
	.word Menu_QOL_Control_Startup_Clear
	.word Menu_QOL_Control_Startup_Set
Menu_QOL_Control_Story_Struct:
	.word Menu_QOL_Control_Story_Clear
	.word Menu_QOL_Control_Story_Set
Menu_QOL_Control_PauseVolume_Struct:
	.word Menu_QOL_Control_PauseVolume_Normal
	.word Menu_QOL_Control_PauseVolume_Quiet
	.word Menu_QOL_Control_PauseVolume_Silent

.align
Menu_QOL_Control_TextStruct:
	.word Menu_QOL_Control_Startup_Struct
	.word Menu_QOL_Control_Story_Struct
	.word Menu_QOL_Control_PauseVolume_Struct

.align
Menu_QOL_Control_Array:
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_QOL_Control_Functions:
	.word ActiveMenu_ToggleAddress
	.word ActiveMenu_ToggleAddress
	.word ActiveMenu_TogglePauseSound
	.word ActiveMenu_PreviousScreen
	
.align
Menu_QOL_Control_Struct:
	.word Menu_QOL_Control_Array // Text Array
	.word Menu_QOL_Control_Functions // Function Array
	.byte 4 // Array Items
	.byte 34 // Parent Screen

.align
ActiveMenu_OpenQOLMenu:
	SW 		ra, @ReturnAddress5
	JAL 	ActiveMenu_RefreshQOLMenu
	LI 		a1, 1
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP

ActiveMenu_RefreshQOLMenu:
	; a1 = Reset Menu Position
	SW 		ra, @ReturnAddress3
	SW 		a1, @VarStorage5
	JAL 	ActiveMenu_ClearMenu
	NOP
	LA 		t0, Menu_QOL_ControlStruct
	LI 		t9, 0
		
	ActiveMenu_RefreshQOLMenu_AddressLoop:
		LW 		t6, 0x0 (t0) ; Addresses
		SLL 	t8, t9, 2
		ADD  	t6, t6, t8
		LW  	a0, 0x0 (t6) ; Found Address
		LW 		t3, 0x4 (t0) ; Text Struct
		ADD 	t3, t3, t8
		LW 		t3, 0x0 (t3) ; Focused Text Info
		LBU 	a0, 0x0 (a0) ; Address Value
		SLL 	a0, a0, 2
		ADD 	t3, t3, a0
		LW 		t3, 0x0 (t3) ; Focused Text Pointer
		LI 		a0, 46 ; QOL Menu Screen
		LA 		a1, Menu_Screens
		SLL 	a0, a0, 2
		ADD 	a1, a1, a0
		LW 		a1, 0x0 (a1) ; Focused Menu Screen Struct
		LW 		a1, 0x0 (a1) ; Focused Text Array
		ADD 	a1, a1, t8 ; Focused Text Item
		SW 		t3, 0x0 (a1)
		LBU 	t8, 0x9 (t0) ; Flag Count
		ADDIU 	t9, t9, 1
		BEQ 	t9, t8, ActiveMenu_RefreshQOLMenu_FinishSpawn
		NOP
		B 		ActiveMenu_RefreshQOLMenu_AddressLoop
		NOP

	ActiveMenu_RefreshQOLMenu_FinishSpawn:
		LI 		a0, 46 ; QOL Menu Screen
		SB 		a0, @NewMenu_Screen
		LW 		a1, @VarStorage5
		BEQZ 	a1, ActiveMenu_RefreshQOLMenu_Spawn
		NOP
		SB 		r0, @NewMenu_Position

	ActiveMenu_RefreshQOLMenu_Spawn:
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ToggleAddress:
	SW 		ra, @ReturnAddress5
	LA 		t0, Menu_QOL_ControlStruct
	LBU 	a3, @NewMenu_Position
	LW 		t6, 0x0 (t0) ; Addresses
	SLL 	t9, a3, 2
	ADD 	t6, t6, t9 ; Focused Address
	LW		a0, 0x0 (t6)
	LI 		t0, 1
	LBU		a1, 0x0 (a0)
	SUBU 	a1, t0, a1
	SB 		a1, 0x0 (a0)
	LI 		a1, 0
	JAL 	ActiveMenu_RefreshQOLMenu
	NOP
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP

ActiveMenu_TogglePauseSound:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @PauseMenuMusicSetting
	ADDIU 	a0, a0, 1
	LI 		a1, 3
	BNE 	a0, a1, ActiveMenu_TogglePauseSound_Write
	NOP
	LI 		a0, 0

	ActiveMenu_TogglePauseSound_Write:
		SB 		a0, @PauseMenuMusicSetting
		JAL 	ActiveMenu_RefreshQOLMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP