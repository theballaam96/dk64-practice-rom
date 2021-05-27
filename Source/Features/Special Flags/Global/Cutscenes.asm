.align
Menu_Flags_GlobalCSFlags:
	.half 0x02 // Japes Intro
	.half 0x03 // Aztec Intro
	.half 0x04 // Factory Intro
	.half 0x05 // Galleon Intro
	.half 0x06 // Fungi Intro
	.half 0x07 // Caves Intro
	.half 0x08 // Castle Intro
	.half 0x09 // Enter Hideout
	.half 0x0A // K Rool Press Button
	.half 0x0B // K Rool Takeoff
	.half 0x0C // Game Over
	.half 0x0D // End Seq

.align
Menu_Flags_GlobalCSFlagType:
	.byte 1 // Japes Intro
	.byte 1 // Aztec Intro
	.byte 1 // Factory Intro
	.byte 1 // Galleon Intro
	.byte 1 // Fungi Intro
	.byte 1 // Caves Intro
	.byte 1 // Castle Intro
	.byte 1 // Enter Hideout
	.byte 1 // K Rool Press Button
	.byte 1 // K Rool Takeoff
	.byte 1 // Game Over
	.byte 1 // End Seq

.align
Menu_Flags_GlobalCSStruct:
	.word Menu_Flags_GlobalCSFlags ; Flags
	.word Menu_Flags_GlobalCSFlagType ; Flag Type
	.word Menu_Flags_GlobalCS_TextStruct ; Text Information
	.byte 48 ; Associated Screen
	.byte 12 ; Flag Count

.align
Menu_Flags_GlobalCS_Japes_Set:
	.asciiz "JAPES INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Japes_Clear:
	.asciiz "JAPES INTRO - LOCKED"
Menu_Flags_GlobalCS_Aztec_Set:
	.asciiz "AZTEC INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Aztec_Clear:
	.asciiz "AZTEC INTRO - LOCKED"
Menu_Flags_GlobalCS_Factory_Set:
	.asciiz "FACTORY INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Factory_Clear:
	.asciiz "FACTORY INTRO - LOCKED"
Menu_Flags_GlobalCS_Galleon_Set:
	.asciiz "GALLEON INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Galleon_Clear:
	.asciiz "GALLEON INTRO - LOCKED"
Menu_Flags_GlobalCS_Fungi_Set:
	.asciiz "FUNGI INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Fungi_Clear:
	.asciiz "FUNGI INTRO - LOCKED"
Menu_Flags_GlobalCS_Caves_Set:
	.asciiz "CAVES INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Caves_Clear:
	.asciiz "CAVES INTRO - LOCKED"
Menu_Flags_GlobalCS_Castle_Set:
	.asciiz "CASTLE INTRO - UNLOCKED"
Menu_Flags_GlobalCS_Castle_Clear:
	.asciiz "CASTLE INTRO - LOCKED"
Menu_Flags_GlobalCS_Hideout_Set:
	.asciiz "ENTER HIDEOUT - UNLOCKED"
Menu_Flags_GlobalCS_Hideout_Clear:
	.asciiz "ENTER HIDEOUT - LOCKED"
Menu_Flags_GlobalCS_KRPB_Set:
	.asciiz "PRESS BUTTON - UNLOCKED"
Menu_Flags_GlobalCS_KRPB_Clear:
	.asciiz "PRESS BUTTON - LOCKED"
Menu_Flags_GlobalCS_Takeoff_Set:
	.asciiz "TAKEOFF - UNLOCKED"
Menu_Flags_GlobalCS_Takeoff_Clear:
	.asciiz "TAKEOFF - LOCKED"
Menu_Flags_GlobalCS_Muahaha_Set:
	.asciiz "GAME OVER - UNLOCKED"
Menu_Flags_GlobalCS_Muahaha_Clear:
	.asciiz "GAME OVER - LOCKED"
Menu_Flags_GlobalCS_EndSeq_Set:
	.asciiz "END SEQUENCE - UNLOCKED"
Menu_Flags_GlobalCS_EndSeq_Clear:
	.asciiz "END SEQUENCE - LOCKED"

.align
Menu_Flags_GlobalCS_Japes_Struct:
	.word Menu_Flags_GlobalCS_Japes_Clear
	.word Menu_Flags_GlobalCS_Japes_Set

.align
Menu_Flags_GlobalCS_Aztec_Struct:
	.word Menu_Flags_GlobalCS_Aztec_Clear
	.word Menu_Flags_GlobalCS_Aztec_Set

.align
Menu_Flags_GlobalCS_Factory_Struct:
	.word Menu_Flags_GlobalCS_Factory_Clear
	.word Menu_Flags_GlobalCS_Factory_Set

.align
Menu_Flags_GlobalCS_Galleon_Struct:
	.word Menu_Flags_GlobalCS_Galleon_Clear
	.word Menu_Flags_GlobalCS_Galleon_Set

.align
Menu_Flags_GlobalCS_Fungi_Struct:
	.word Menu_Flags_GlobalCS_Fungi_Clear
	.word Menu_Flags_GlobalCS_Fungi_Set

.align
Menu_Flags_GlobalCS_Caves_Struct:
	.word Menu_Flags_GlobalCS_Caves_Clear
	.word Menu_Flags_GlobalCS_Caves_Set

.align
Menu_Flags_GlobalCS_Castle_Struct:
	.word Menu_Flags_GlobalCS_Castle_Clear
	.word Menu_Flags_GlobalCS_Castle_Set

.align
Menu_Flags_GlobalCS_Hideout_Struct:
	.word Menu_Flags_GlobalCS_Hideout_Clear
	.word Menu_Flags_GlobalCS_Hideout_Set

.align
Menu_Flags_GlobalCS_KRPB_Struct:
	.word Menu_Flags_GlobalCS_KRPB_Clear
	.word Menu_Flags_GlobalCS_KRPB_Set

.align
Menu_Flags_GlobalCS_Takeoff_Struct:
	.word Menu_Flags_GlobalCS_Takeoff_Clear
	.word Menu_Flags_GlobalCS_Takeoff_Set

.align
Menu_Flags_GlobalCS_Muahaha_Struct:
	.word Menu_Flags_GlobalCS_Muahaha_Clear
	.word Menu_Flags_GlobalCS_Muahaha_Set

.align
Menu_Flags_GlobalCS_EndSeq_Struct:
	.word Menu_Flags_GlobalCS_EndSeq_Clear
	.word Menu_Flags_GlobalCS_EndSeq_Set


.align
Menu_Flags_GlobalCS_TextStruct:
	.word Menu_Flags_GlobalCS_Japes_Struct
	.word Menu_Flags_GlobalCS_Aztec_Struct
	.word Menu_Flags_GlobalCS_Factory_Struct
	.word Menu_Flags_GlobalCS_Galleon_Struct
	.word Menu_Flags_GlobalCS_Fungi_Struct
	.word Menu_Flags_GlobalCS_Caves_Struct
	.word Menu_Flags_GlobalCS_Castle_Struct
	.word Menu_Flags_GlobalCS_Hideout_Struct
	.word Menu_Flags_GlobalCS_KRPB_Struct
	.word Menu_Flags_GlobalCS_Takeoff_Struct
	.word Menu_Flags_GlobalCS_Muahaha_Struct
	.word Menu_Flags_GlobalCS_EndSeq_Struct

.align
Menu_Flags_GlobalCS_Array:
	.word 0
	.word 0
	.word 0
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
Menu_Flags_GlobalCS_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
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
Menu_Flags_GlobalCS_Struct:
	.word Menu_Flags_GlobalCS_Array // Text Array
	.word Menu_Flags_GlobalCS_Functions // Function Array
	.byte 12 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_GlobalCS:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 48
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP

