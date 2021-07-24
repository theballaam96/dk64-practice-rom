.align
Menu_Flags_KongFlags:
	.half 0x181 // DK Free 
	.half 0x6 // Diddy Free
	.half 0x46 // Lanky Free
	.half 0x42 // Tiny Free
	.half 0x75 // Chunky Free

.align
Menu_Flags_KongFlagType:
	.byte 0 // DK Free
	.byte 0 // Diddy Free
	.byte 0 // Lanky Free
	.byte 0 // Tiny Free
	.byte 0 // Chunky Free

.align
Menu_Flags_KongStruct:
	.word Menu_Flags_KongFlags ; Flags
	.word Menu_Flags_KongFlagType ; Flag Type
	.word Menu_Flags_Kong_TextStruct ; Text Information
	.byte 37 ; Associated Screen
	.byte 5 ; Flag Count

.align
Menu_Flags_Kong_DK_Set:
	.asciiz "DK: FREED"
Menu_Flags_Kong_DK_Clear:
	.asciiz "DK: LOCKED"
Menu_Flags_Kong_Diddy_Set:
	.asciiz "DIDDY: FREED"
Menu_Flags_Kong_Diddy_Clear:
	.asciiz "DIDDY: LOCKED"
Menu_Flags_Kong_Lanky_Set:
	.asciiz "LANKY: FREED"
Menu_Flags_Kong_Lanky_Clear:
	.asciiz "LANKY: LOCKED"
Menu_Flags_Kong_Tiny_Set:
	.asciiz "TINY: FREED"
Menu_Flags_Kong_Tiny_Clear:
	.asciiz "TINY: LOCKED"
Menu_Flags_Kong_Chunky_Set:
	.asciiz "CHUNKY: FREED"
Menu_Flags_Kong_Chunky_Clear:
	.asciiz "CHUNKY: LOCKED"

.align
Menu_Flags_Kong_DK_Struct:
	.word Menu_Flags_Kong_DK_Clear
	.word Menu_Flags_Kong_DK_Set

.align
Menu_Flags_Kong_Diddy_Struct:
	.word Menu_Flags_Kong_Diddy_Clear
	.word Menu_Flags_Kong_Diddy_Set

.align
Menu_Flags_Kong_Lanky_Struct:
	.word Menu_Flags_Kong_Lanky_Clear
	.word Menu_Flags_Kong_Lanky_Set

.align
Menu_Flags_Kong_Tiny_Struct:
	.word Menu_Flags_Kong_Tiny_Clear
	.word Menu_Flags_Kong_Tiny_Set

.align
Menu_Flags_Kong_Chunky_Struct:
	.word Menu_Flags_Kong_Chunky_Clear
	.word Menu_Flags_Kong_Chunky_Set

.align
Menu_Flags_Kong_TextStruct:
	.word Menu_Flags_Kong_DK_Struct
	.word Menu_Flags_Kong_Diddy_Struct
	.word Menu_Flags_Kong_Lanky_Struct
	.word Menu_Flags_Kong_Tiny_Struct
	.word Menu_Flags_Kong_Chunky_Struct

.align
Menu_Flags_Kong_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_Flags_Kong_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_PreviousScreen

.align
Menu_Flags_Kong_Struct:
	.word Menu_Flags_Kong_Array // Text Array
	.word Menu_Flags_Kong_Functions // Function Array
	.byte 6 // Array Items
	.byte 36 // Parent Screen
	.byte 0 // Parent Position

.align
ActiveMenu_OpenFlagMenu_Kong:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 37
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP