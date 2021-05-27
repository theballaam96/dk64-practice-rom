.align
Menu_Flags_GlobalMGFlags:
	.half 0x0F // Rambi Arena
	.half 0x10 // Enguarde Arena
	.half 0x11 // DK Arcade
	.half 0x12 // Jetpac

.align
Menu_Flags_GlobalMGFlagType:
	.byte 1 // Rambi Arena
	.byte 1 // Enguarde Arena
	.byte 1 // DK Arcade
	.byte 1 // Jetpac

.align
Menu_Flags_GlobalMGStruct:
	.word Menu_Flags_GlobalMGFlags ; Flags
	.word Menu_Flags_GlobalMGFlagType ; Flag Type
	.word Menu_Flags_GlobalMG_TextStruct ; Text Information
	.byte 49 ; Associated Screen
	.byte 4 ; Flag Count

.align
Menu_Flags_GlobalMG_Rambi_Set:
	.asciiz "RAMBI ARENA - UNLOCKED"
Menu_Flags_GlobalMG_Rambi_Clear:
	.asciiz "RAMBI ARENA - LOCKED"
Menu_Flags_GlobalMG_Enguarde_Set:
	.asciiz "ENGUARDE ARENA - UNLOCKED"
Menu_Flags_GlobalMG_Enguarde_Clear:
	.asciiz "ENGUARDE ARENA - LOCKED"
Menu_Flags_GlobalMG_Arcade_Set:
	.asciiz "DK ARCADE - UNLOCKED"
Menu_Flags_GlobalMG_Arcade_Clear:
	.asciiz "DK ARCADE - LOCKED"
Menu_Flags_GlobalMG_Jetpac_Set:
	.asciiz "JETPAC - UNLOCKED"
Menu_Flags_GlobalMG_Jetpac_Clear:
	.asciiz "JETPAC - LOCKED"

.align
Menu_Flags_GlobalMG_Rambi_Struct:
	.word Menu_Flags_GlobalMG_Rambi_Clear
	.word Menu_Flags_GlobalMG_Rambi_Set

.align
Menu_Flags_GlobalMG_Enguarde_Struct:
	.word Menu_Flags_GlobalMG_Enguarde_Clear
	.word Menu_Flags_GlobalMG_Enguarde_Set

.align
Menu_Flags_GlobalMG_Arcade_Struct:
	.word Menu_Flags_GlobalMG_Arcade_Clear
	.word Menu_Flags_GlobalMG_Arcade_Set

.align
Menu_Flags_GlobalMG_Jetpac_Struct:
	.word Menu_Flags_GlobalMG_Jetpac_Clear
	.word Menu_Flags_GlobalMG_Jetpac_Set

.align
Menu_Flags_GlobalMG_TextStruct:
	.word Menu_Flags_GlobalMG_Rambi_Struct
	.word Menu_Flags_GlobalMG_Enguarde_Struct
	.word Menu_Flags_GlobalMG_Arcade_Struct
	.word Menu_Flags_GlobalMG_Jetpac_Struct

.align
Menu_Flags_GlobalMG_Array:
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_GlobalMG_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_GlobalMG_Struct:
	.word Menu_Flags_GlobalMG_Array // Text Array
	.word Menu_Flags_GlobalMG_Functions // Function Array
	.byte 4 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_GlobalMG:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 49
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP

