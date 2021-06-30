.align
Menu_Flags_MiscFlags:
	.half 0x82 // Arcade Round 1 GB
	.half 0xF8 // Rabbit Race 1 Complete

.align
Menu_Flags_MiscFlagType:
	.byte 0 // Arcade Round 1 GB
	.byte 0 // Rabbit Race 1 Complete

.align
Menu_Flags_MiscStruct:
	.word Menu_Flags_MiscFlags ; Flags
	.word Menu_Flags_MiscFlagType ; Flag Type
	.word Menu_Flags_Misc_TextStruct ; Text Information
	.byte 45 ; Associated Screen
	.byte 2 ; Flag Count

.align
Menu_Flags_Misc_ArcadeR1_Set:
	.asciiz "ARCADE ROUND 1: BEATEN"
Menu_Flags_Misc_ArcadeR1_Clear:
	.asciiz "ARCADE ROUND 1: NOT BEATEN"
Menu_Flags_Misc_RabbitR1_Set:
	.asciiz "RABBIT RACE 1: BEATEN"
Menu_Flags_Misc_RabbitR1_Clear:
	.asciiz "RABBIT RACE 1: NOT BEATEN"

.align
Menu_Flags_Misc_ArcadeR1_Struct:
	.word Menu_Flags_Misc_ArcadeR1_Clear
	.word Menu_Flags_Misc_ArcadeR1_Set
Menu_Flags_Misc_RabbitR1_Struct:
	.word Menu_Flags_Misc_RabbitR1_Clear
	.word Menu_Flags_Misc_RabbitR1_Set

.align
Menu_Flags_Misc_TextStruct:
	.word Menu_Flags_Misc_ArcadeR1_Struct
	.word Menu_Flags_Misc_RabbitR1_Struct

.align
Menu_Flags_Misc_Array:
	.word 0
	.word 0

.align
Menu_Flags_Misc_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	
.align
Menu_Flags_Misc_Struct:
	.word Menu_Flags_Misc_Array // Text Array
	.word Menu_Flags_Misc_Functions // Function Array
	.byte 2 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_Misc:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 45
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP