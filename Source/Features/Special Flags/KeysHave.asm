.align
Menu_Flags_KeyHaveFlags:
	.half 0x1A // Key 1
	.half 0x4A // Key 2
	.half 0x8A // Key 3
	.half 0xA8 // Key 4
	.half 0xEC // Key 5
	.half 0x124 // Key 6
	.half 0x13D // Key 7
	.half 0x17C // Key 8

.align
Menu_Flags_KeyHaveFlagType:
	.byte 0 // Key 1
	.byte 0 // Key 2
	.byte 0 // Key 3
	.byte 0 // Key 4
	.byte 0 // Key 5
	.byte 0 // Key 6
	.byte 0 // Key 7
	.byte 0 // Key 8

.align
Menu_Flags_KeyHaveStruct:
	.word Menu_Flags_KeyHaveFlags ; Flags
	.word Menu_Flags_KeyHaveFlagType ; Flag Type
	.word Menu_Flags_KeyHave_TextStruct ; Text Information
	.byte 39 ; Associated Screen
	.byte 8 ; Flag Count

.align
Menu_Flags_KeyHave_Key1_Set:
	.asciiz "KEY 1: OBTAINED"
Menu_Flags_KeyHave_Key1_Clear:
	.asciiz "KEY 1: NOT OBTAINED"
Menu_Flags_KeyHave_Key2_Set:
	.asciiz "KEY 2: OBTAINED"
Menu_Flags_KeyHave_Key2_Clear:
	.asciiz "KEY 2: NOT OBTAINED"
Menu_Flags_KeyHave_Key3_Set:
	.asciiz "KEY 3: OBTAINED"
Menu_Flags_KeyHave_Key3_Clear:
	.asciiz "KEY 3: NOT OBTAINED"
Menu_Flags_KeyHave_Key4_Set:
	.asciiz "KEY 4: OBTAINED"
Menu_Flags_KeyHave_Key4_Clear:
	.asciiz "KEY 4: NOT OBTAINED"
Menu_Flags_KeyHave_Key5_Set:
	.asciiz "KEY 5: OBTAINED"
Menu_Flags_KeyHave_Key5_Clear:
	.asciiz "KEY 5: NOT OBTAINED"
Menu_Flags_KeyHave_Key6_Set:
	.asciiz "KEY 6: OBTAINED"
Menu_Flags_KeyHave_Key6_Clear:
	.asciiz "KEY 6: NOT OBTAINED"
Menu_Flags_KeyHave_Key7_Set:
	.asciiz "KEY 7: OBTAINED"
Menu_Flags_KeyHave_Key7_Clear:
	.asciiz "KEY 7: NOT OBTAINED"
Menu_Flags_KeyHave_Key8_Set:
	.asciiz "KEY 8: OBTAINED"
Menu_Flags_KeyHave_Key8_Clear:
	.asciiz "KEY 8: NOT OBTAINED"

.align
Menu_Flags_KeyHave_Key1_Struct:
	.word Menu_Flags_KeyHave_Key1_Clear
	.word Menu_Flags_KeyHave_Key1_Set

.align
Menu_Flags_KeyHave_Key2_Struct:
	.word Menu_Flags_KeyHave_Key2_Clear
	.word Menu_Flags_KeyHave_Key2_Set

.align
Menu_Flags_KeyHave_Key3_Struct:
	.word Menu_Flags_KeyHave_Key3_Clear
	.word Menu_Flags_KeyHave_Key3_Set

.align
Menu_Flags_KeyHave_Key4_Struct:
	.word Menu_Flags_KeyHave_Key4_Clear
	.word Menu_Flags_KeyHave_Key4_Set

.align
Menu_Flags_KeyHave_Key5_Struct:
	.word Menu_Flags_KeyHave_Key5_Clear
	.word Menu_Flags_KeyHave_Key5_Set

.align
Menu_Flags_KeyHave_Key6_Struct:
	.word Menu_Flags_KeyHave_Key6_Clear
	.word Menu_Flags_KeyHave_Key6_Set

.align
Menu_Flags_KeyHave_Key7_Struct:
	.word Menu_Flags_KeyHave_Key7_Clear
	.word Menu_Flags_KeyHave_Key7_Set

.align
Menu_Flags_KeyHave_Key8_Struct:
	.word Menu_Flags_KeyHave_Key8_Clear
	.word Menu_Flags_KeyHave_Key8_Set

.align
Menu_Flags_KeyHave_TextStruct:
	.word Menu_Flags_KeyHave_Key1_Struct
	.word Menu_Flags_KeyHave_Key2_Struct
	.word Menu_Flags_KeyHave_Key3_Struct
	.word Menu_Flags_KeyHave_Key4_Struct
	.word Menu_Flags_KeyHave_Key5_Struct
	.word Menu_Flags_KeyHave_Key6_Struct
	.word Menu_Flags_KeyHave_Key7_Struct
	.word Menu_Flags_KeyHave_Key8_Struct

.align
Menu_Flags_KeyHave_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_KeyHave_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_KeyHave_Struct:
	.word Menu_Flags_KeyHave_Array // Text Array
	.word Menu_Flags_KeyHave_Functions // Function Array
	.byte 8 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_KeyHave:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 39
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP