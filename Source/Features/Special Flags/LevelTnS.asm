.align
Menu_Flags_LevelTnSFlags:
	.half 0x2E // Japes T&S Clear
	.half 0x6C // Aztec T&S Clear
	.half 0x98 // Factory T&S Clear
	.half 0xCB // Galleon T&S Clear
	.half 0x102 // Fungi T&S Clear
	.half 0x12E // Caves T&S Clear
	.half 0x160 // Castle T&S Clear

.align
Menu_Flags_LevelTnSFlagType:
	.byte 0 // Japes T&S Clear
	.byte 0 // Aztec T&S Clear
	.byte 0 // Factory T&S Clear
	.byte 0 // Galleon T&S Clear
	.byte 0 // Fungi T&S Clear
	.byte 0 // Caves T&S Clear
	.byte 0 // Castle T&S Clear

.align
Menu_Flags_LevelTnSStruct:
	.word Menu_Flags_LevelTnSFlags ; Flags
	.word Menu_Flags_LevelTnSFlagType ; Flag Type
	.word Menu_Flags_LevelTnS_TextStruct ; Text Information
	.byte 41 ; Associated Screen
	.byte 7 ; Flag Count

.align
Menu_Flags_LevelTnS_Japes_Set:
	.asciiz "JAPES TNS: CLEAR"
Menu_Flags_LevelTnS_Japes_Clear:
	.asciiz "JAPES TNS: SPAWNED"
Menu_Flags_LevelTnS_Aztec_Set:
	.asciiz "AZTEC TNS: CLEAR"
Menu_Flags_LevelTnS_Aztec_Clear:
	.asciiz "AZTEC TNS: SPAWNED"
Menu_Flags_LevelTnS_Factory_Set:
	.asciiz "FACTORY TNS: CLEAR"
Menu_Flags_LevelTnS_Factory_Clear:
	.asciiz "FACTORY TNS: SPAWNED"
Menu_Flags_LevelTnS_Galleon_Set:
	.asciiz "GALLEON TNS: CLEAR"
Menu_Flags_LevelTnS_Galleon_Clear:
	.asciiz "GALLEON TNS: SPAWNED"
Menu_Flags_LevelTnS_Fungi_Set:
	.asciiz "FUNGI TNS: CLEAR"
Menu_Flags_LevelTnS_Fungi_Clear:
	.asciiz "FUNGI TNS: SPAWNED"
Menu_Flags_LevelTnS_Caves_Set:
	.asciiz "CAVES TNS: CLEAR"
Menu_Flags_LevelTnS_Caves_Clear:
	.asciiz "CAVES TNS: SPAWNED"
Menu_Flags_LevelTnS_Castle_Set:
	.asciiz "CASTLE TNS: CLEAR"
Menu_Flags_LevelTnS_Castle_Clear:
	.asciiz "CASTLE TNS: SPAWNED"

.align
Menu_Flags_LevelTnS_Japes_Struct:
	.word Menu_Flags_LevelTnS_Japes_Clear
	.word Menu_Flags_LevelTnS_Japes_Set
.align
Menu_Flags_LevelTnS_Aztec_Struct:
	.word Menu_Flags_LevelTnS_Aztec_Clear
	.word Menu_Flags_LevelTnS_Aztec_Set
.align
Menu_Flags_LevelTnS_Factory_Struct:
	.word Menu_Flags_LevelTnS_Factory_Clear
	.word Menu_Flags_LevelTnS_Factory_Set
.align
Menu_Flags_LevelTnS_Galleon_Struct:
	.word Menu_Flags_LevelTnS_Galleon_Clear
	.word Menu_Flags_LevelTnS_Galleon_Set
.align
Menu_Flags_LevelTnS_Fungi_Struct:
	.word Menu_Flags_LevelTnS_Fungi_Clear
	.word Menu_Flags_LevelTnS_Fungi_Set
.align
Menu_Flags_LevelTnS_Caves_Struct:
	.word Menu_Flags_LevelTnS_Caves_Clear
	.word Menu_Flags_LevelTnS_Caves_Set
.align
Menu_Flags_LevelTnS_Castle_Struct:
	.word Menu_Flags_LevelTnS_Castle_Clear
	.word Menu_Flags_LevelTnS_Castle_Set

.align
Menu_Flags_LevelTnS_TextStruct:
	.word Menu_Flags_LevelTnS_Japes_Struct
	.word Menu_Flags_LevelTnS_Aztec_Struct
	.word Menu_Flags_LevelTnS_Factory_Struct
	.word Menu_Flags_LevelTnS_Galleon_Struct
	.word Menu_Flags_LevelTnS_Fungi_Struct
	.word Menu_Flags_LevelTnS_Caves_Struct
	.word Menu_Flags_LevelTnS_Castle_Struct

.align
Menu_Flags_LevelTnS_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_LevelTnS_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_LevelTnS_Struct:
	.word Menu_Flags_LevelTnS_Array // Text Array
	.word Menu_Flags_LevelTnS_Functions // Function Array
	.byte 7 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_LevelTnS:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 41
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP