.align
Menu_Flags_TrainingFlags:
	.half 0x182 // Dive
	.half 0x184 // Orange
	.half 0x185 // Barrel
	.half 0x183 // Vine

.align
Menu_Flags_TrainingFlagType:
	.byte 0 // Dive
	.byte 0 // Orange
	.byte 0 // Barrel
	.byte 0 // Vine

.align
Menu_Flags_TrainingStruct:
	.word Menu_Flags_TrainingFlags ; Flags
	.word Menu_Flags_TrainingFlagType ; Flag Type
	.word Menu_Flags_Training_TextStruct ; Text Information
	.byte 50 ; Associated Screen
	.byte 4 ; Flag Count

.align
Menu_Flags_Training_Dive_Set:
	.asciiz "DIVE BARREL: COMPLETE"
Menu_Flags_Training_Dive_Clear:
	.asciiz "DIVE BARREL: INCOMPLETE"
Menu_Flags_Training_Orange_Set:
	.asciiz "ORANGE BARREL: COMPLETE"
Menu_Flags_Training_Orange_Clear:
	.asciiz "ORANGE BARREL: INCOMPLETE"
Menu_Flags_Training_Barrel_Set:
	.asciiz "BARREL BARREL: COMPLETE"
Menu_Flags_Training_Barrel_Clear:
	.asciiz "BARREL BARREL: INCOMPLETE"
Menu_Flags_Training_Vine_Set:
	.asciiz "VINE BARREL: COMPLETE"
Menu_Flags_Training_Vine_Clear:
	.asciiz "VINE BARREL: INCOMPLETE"

.align
Menu_Flags_Training_Dive_Struct:
	.word Menu_Flags_Training_Dive_Clear
	.word Menu_Flags_Training_Dive_Set

.align
Menu_Flags_Training_Orange_Struct:
	.word Menu_Flags_Training_Orange_Clear
	.word Menu_Flags_Training_Orange_Set

.align
Menu_Flags_Training_Barrel_Struct:
	.word Menu_Flags_Training_Barrel_Clear
	.word Menu_Flags_Training_Barrel_Set

.align
Menu_Flags_Training_Vine_Struct:
	.word Menu_Flags_Training_Vine_Clear
	.word Menu_Flags_Training_Vine_Set

.align
Menu_Flags_Training_TextStruct:
	.word Menu_Flags_Training_Dive_Struct
	.word Menu_Flags_Training_Orange_Struct
	.word Menu_Flags_Training_Barrel_Struct
	.word Menu_Flags_Training_Vine_Struct

.align
Menu_Flags_Training_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_Flags_Training_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_PreviousScreen

.align
Menu_Flags_Training_Struct:
	.word Menu_Flags_Training_Array // Text Array
	.word Menu_Flags_Training_Functions // Function Array
	.byte 5 // Array Items
	.byte 31 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_Training:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 50
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP