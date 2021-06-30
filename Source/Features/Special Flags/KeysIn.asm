.align
Menu_Flags_KeyInFlags:
	.half 0x1BB // K. Lumsy Intro
	.half 0x1BC // Key 1 Turned
	.half 0x1BD // Key 2 Turned
	.half 0x1BE // Key 3 Turned
	.half 0x1BF // Key 4 Turned
	.half 0x1C0 // Key 5 Turned
	.half 0x1C1 // Key 6 Turned
	.half 0x1C2 // Key 7 Turned
	.half 0x1C3 // Key 8 Turned

.align
Menu_Flags_KeyInFlagType:
	.byte 0 // K. Lumsy Intro
	.byte 0 // Key 1 Turned
	.byte 0 // Key 2 Turned
	.byte 0 // Key 3 Turned
	.byte 0 // Key 4 Turned
	.byte 0 // Key 5 Turned
	.byte 0 // Key 6 Turned
	.byte 0 // Key 7 Turned
	.byte 0 // Key 8 Turned

.align
Menu_Flags_KeyInStruct:
	.word Menu_Flags_KeyInFlags ; Flags
	.word Menu_Flags_KeyInFlagType ; Flag Type
	.word Menu_Flags_KeyIn_TextStruct ; Text Information
	.byte 38 ; Associated Screen
	.byte 9 ; Flag Count

.align
Menu_Flags_KeyIn_JapesOpen_Set:
	.asciiz "JAPES: OPEN"
Menu_Flags_KeyIn_JapesOpen_Clear:
	.asciiz "JAPES: NOT OPEN"
Menu_Flags_KeyIn_Key1In_Set:
	.asciiz "KEY 1: TURNED"
Menu_Flags_KeyIn_Key1In_Clear:
	.asciiz "KEY 1: NOT TURNED"
Menu_Flags_KeyIn_Key2In_Set:
	.asciiz "KEY 2: TURNED"
Menu_Flags_KeyIn_Key2In_Clear:
	.asciiz "KEY 2: NOT TURNED"
Menu_Flags_KeyIn_Key3In_Set:
	.asciiz "KEY 3: TURNED"
Menu_Flags_KeyIn_Key3In_Clear:
	.asciiz "KEY 3: NOT TURNED"
Menu_Flags_KeyIn_Key4In_Set:
	.asciiz "KEY 4: TURNED"
Menu_Flags_KeyIn_Key4In_Clear:
	.asciiz "KEY 4: NOT TURNED"
Menu_Flags_KeyIn_Key5In_Set:
	.asciiz "KEY 5: TURNED"
Menu_Flags_KeyIn_Key5In_Clear:
	.asciiz "KEY 5: NOT TURNED"
Menu_Flags_KeyIn_Key6In_Set:
	.asciiz "KEY 6: TURNED"
Menu_Flags_KeyIn_Key6In_Clear:
	.asciiz "KEY 6: NOT TURNED"
Menu_Flags_KeyIn_Key7In_Set:
	.asciiz "KEY 7: TURNED"
Menu_Flags_KeyIn_Key7In_Clear:
	.asciiz "KEY 7: NOT TURNED"
Menu_Flags_KeyIn_Key8In_Set:
	.asciiz "KEY 8: TURNED"
Menu_Flags_KeyIn_Key8In_Clear:
	.asciiz "KEY 8: NOT TURNED"

.align
Menu_Flags_KeyIn_JapesOpen_Struct:
	.word Menu_Flags_KeyIn_JapesOpen_Clear
	.word Menu_Flags_KeyIn_JapesOpen_Set

.align
Menu_Flags_KeyIn_Key1_Struct:
	.word Menu_Flags_KeyIn_Key1In_Clear
	.word Menu_Flags_KeyIn_Key1In_Set

.align
Menu_Flags_KeyIn_Key2_Struct:
	.word Menu_Flags_KeyIn_Key2In_Clear
	.word Menu_Flags_KeyIn_Key2In_Set

.align
Menu_Flags_KeyIn_Key3_Struct:
	.word Menu_Flags_KeyIn_Key3In_Clear
	.word Menu_Flags_KeyIn_Key3In_Set

.align
Menu_Flags_KeyIn_Key4_Struct:
	.word Menu_Flags_KeyIn_Key4In_Clear
	.word Menu_Flags_KeyIn_Key4In_Set

.align
Menu_Flags_KeyIn_Key5_Struct:
	.word Menu_Flags_KeyIn_Key5In_Clear
	.word Menu_Flags_KeyIn_Key5In_Set

.align
Menu_Flags_KeyIn_Key6_Struct:
	.word Menu_Flags_KeyIn_Key6In_Clear
	.word Menu_Flags_KeyIn_Key6In_Set

.align
Menu_Flags_KeyIn_Key7_Struct:
	.word Menu_Flags_KeyIn_Key7In_Clear
	.word Menu_Flags_KeyIn_Key7In_Set

.align
Menu_Flags_KeyIn_Key8_Struct:
	.word Menu_Flags_KeyIn_Key8In_Clear
	.word Menu_Flags_KeyIn_Key8In_Set

.align
Menu_Flags_KeyIn_TextStruct:
	.word Menu_Flags_KeyIn_JapesOpen_Struct
	.word Menu_Flags_KeyIn_Key1_Struct
	.word Menu_Flags_KeyIn_Key2_Struct
	.word Menu_Flags_KeyIn_Key3_Struct
	.word Menu_Flags_KeyIn_Key4_Struct
	.word Menu_Flags_KeyIn_Key5_Struct
	.word Menu_Flags_KeyIn_Key6_Struct
	.word Menu_Flags_KeyIn_Key7_Struct
	.word Menu_Flags_KeyIn_Key8_Struct

.align
Menu_Flags_KeyIn_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_KeyIn_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_KeyIn_Struct:
	.word Menu_Flags_KeyIn_Array // Text Array
	.word Menu_Flags_KeyIn_Functions // Function Array
	.byte 9 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_KeyIn:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 38
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP