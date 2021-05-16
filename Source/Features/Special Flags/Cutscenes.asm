.align
Menu_Flags_CutscenesFlags:
	.half 0x17E // B. Locker FTT
	.half 0x2A // Diddy Help Me CS
	.half 0x5C // Llama CS
	.half 0x12B // Kosha Cutscene

.align
Menu_Flags_CutscenesFlagType:
	.byte 0 // B. Locker FTT
	.byte 0 // Diddy Help Me CS
	.byte 0 // Llama CS
	.byte 0 // Kosha Cutscene

.align
Menu_Flags_CutscenesStruct:
	.word Menu_Flags_CutscenesFlags ; Flags
	.word Menu_Flags_CutscenesFlagType ; Flag Type
	.word Menu_Flags_Cutscenes_TextStruct ; Text Information
	.byte 43 ; Associated Screen
	.byte 4 ; Flag Count

.align
Menu_Flags_Cutscenes_BLockerFTT_Set:
	.asciiz "B LOCKER FIRST TIME TEXT - WATCHED"
Menu_Flags_Cutscenes_BLockerFTT_Clear:
	.asciiz "B LOCKER FIRST TIME TEXT - NOT WATCHED"
Menu_Flags_Cutscenes_DiddyHelpMe_Set:
	.asciiz "DIDDY HELP ME CUTSCENE - WATCHED"
Menu_Flags_Cutscenes_DiddyHelpMe_Clear:
	.asciiz "DIDDY HELP ME CUTSCENE - NOT WATCHED"
Menu_Flags_Cutscenes_LlamaCS_Set:
	.asciiz "LLAMA CUTSCENE - WATCHED"
Menu_Flags_Cutscenes_LlamaCS_Clear:
	.asciiz "LLAMA CUTSCENE - NOT WATCHED"
Menu_Flags_Cutscenes_Kosha_Set:
	.asciiz "GIANT KOSHA CUTSCENE - WATCHED"
Menu_Flags_Cutscenes_Kosha_Clear:
	.asciiz "GIANT KOSHA CUTSCENE - NOT WATCHED"

.align
Menu_Flags_Cutscenes_BLockerFTT_Struct:
	.word Menu_Flags_Cutscenes_BLockerFTT_Clear
	.word Menu_Flags_Cutscenes_BLockerFTT_Set
.align
Menu_Flags_Cutscenes_DiddyHelpMe_Struct:
	.word Menu_Flags_Cutscenes_DiddyHelpMe_Clear
	.word Menu_Flags_Cutscenes_DiddyHelpMe_Set
.align
Menu_Flags_Cutscenes_LlamaCS_Struct:
	.word Menu_Flags_Cutscenes_LlamaCS_Clear
	.word Menu_Flags_Cutscenes_LlamaCS_Set
.align
Menu_Flags_Cutscenes_Kosha_Struct:
	.word Menu_Flags_Cutscenes_Kosha_Clear
	.word Menu_Flags_Cutscenes_Kosha_Set

.align
Menu_Flags_Cutscenes_TextStruct:
	.word Menu_Flags_Cutscenes_BLockerFTT_Struct
	.word Menu_Flags_Cutscenes_DiddyHelpMe_Struct
	.word Menu_Flags_Cutscenes_LlamaCS_Struct
	.word Menu_Flags_Cutscenes_Kosha_Struct

.align
Menu_Flags_Cutscenes_Array:
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_Cutscenes_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_Cutscenes_Struct:
	.word Menu_Flags_Cutscenes_Array // Text Array
	.word Menu_Flags_Cutscenes_Functions // Function Array
	.byte 4 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_Cutscenes:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 43
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP