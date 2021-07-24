.align
Menu_Flags_LevelIntroFlags:
	.half 0x1B // Japes Intro
	.half 0x5F // Aztec Intro
	.half 0x8C // Factory Intro
	.half 0xC2 // Galleon Intro
	.half 0x101 // Fungi Intro
	.half 0x11A // Caves Intro
	.half 0x15D // Castle Intro

.align
Menu_Flags_LevelIntroFlagType:
	.byte 0 // Japes Intro
	.byte 0 // Aztec Intro
	.byte 0 // Factory Intro
	.byte 0 // Galleon Intro
	.byte 0 // Fungi Intro
	.byte 0 // Caves Intro
	.byte 0 // Castle Intro

.align
Menu_Flags_LevelIntroStruct:
	.word Menu_Flags_LevelIntroFlags ; Flags
	.word Menu_Flags_LevelIntroFlagType ; Flag Type
	.word Menu_Flags_LevelIntro_TextStruct ; Text Information
	.byte 40 ; Associated Screen
	.byte 7 ; Flag Count

.align
Menu_Flags_LevelIntro_Japes_Set:
	.asciiz "JAPES INTRO: WATCHED"
Menu_Flags_LevelIntro_Japes_Clear:
	.asciiz "JAPES INTRO: NOT WATCHED"
Menu_Flags_LevelIntro_Aztec_Set:
	.asciiz "AZTEC INTRO: WATCHED"
Menu_Flags_LevelIntro_Aztec_Clear:
	.asciiz "AZTEC INTRO: NOT WATCHED"
Menu_Flags_LevelIntro_Factory_Set:
	.asciiz "FACTORY INTRO: WATCHED"
Menu_Flags_LevelIntro_Factory_Clear:
	.asciiz "FACTORY INTRO: NOT WATCHED"
Menu_Flags_LevelIntro_Galleon_Set:
	.asciiz "GALLEON INTRO: WATCHED"
Menu_Flags_LevelIntro_Galleon_Clear:
	.asciiz "GALLEON INTRO: NOT WATCHED"
Menu_Flags_LevelIntro_Fungi_Set:
	.asciiz "FUNGI INTRO: WATCHED"
Menu_Flags_LevelIntro_Fungi_Clear:
	.asciiz "FUNGI INTRO: NOT WATCHED"
Menu_Flags_LevelIntro_Caves_Set:
	.asciiz "CAVES INTRO: WATCHED"
Menu_Flags_LevelIntro_Caves_Clear:
	.asciiz "CAVES INTRO: NOT WATCHED"
Menu_Flags_LevelIntro_Castle_Set:
	.asciiz "CASTLE INTRO: WATCHED"
Menu_Flags_LevelIntro_Castle_Clear:
	.asciiz "CASTLE INTRO: NOT WATCHED"

.align
Menu_Flags_LevelIntro_Japes_Struct:
	.word Menu_Flags_LevelIntro_Japes_Clear
	.word Menu_Flags_LevelIntro_Japes_Set
.align
Menu_Flags_LevelIntro_Aztec_Struct:
	.word Menu_Flags_LevelIntro_Aztec_Clear
	.word Menu_Flags_LevelIntro_Aztec_Set
.align
Menu_Flags_LevelIntro_Factory_Struct:
	.word Menu_Flags_LevelIntro_Factory_Clear
	.word Menu_Flags_LevelIntro_Factory_Set
.align
Menu_Flags_LevelIntro_Galleon_Struct:
	.word Menu_Flags_LevelIntro_Galleon_Clear
	.word Menu_Flags_LevelIntro_Galleon_Set
.align
Menu_Flags_LevelIntro_Fungi_Struct:
	.word Menu_Flags_LevelIntro_Fungi_Clear
	.word Menu_Flags_LevelIntro_Fungi_Set
.align
Menu_Flags_LevelIntro_Caves_Struct:
	.word Menu_Flags_LevelIntro_Caves_Clear
	.word Menu_Flags_LevelIntro_Caves_Set
.align
Menu_Flags_LevelIntro_Castle_Struct:
	.word Menu_Flags_LevelIntro_Castle_Clear
	.word Menu_Flags_LevelIntro_Castle_Set

.align
Menu_Flags_LevelIntro_TextStruct:
	.word Menu_Flags_LevelIntro_Japes_Struct
	.word Menu_Flags_LevelIntro_Aztec_Struct
	.word Menu_Flags_LevelIntro_Factory_Struct
	.word Menu_Flags_LevelIntro_Galleon_Struct
	.word Menu_Flags_LevelIntro_Fungi_Struct
	.word Menu_Flags_LevelIntro_Caves_Struct
	.word Menu_Flags_LevelIntro_Castle_Struct

.align
Menu_Flags_LevelIntro_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_Flags_LevelIntro_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_PreviousScreen

.align
Menu_Flags_LevelIntro_Struct:
	.word Menu_Flags_LevelIntro_Array // Text Array
	.word Menu_Flags_LevelIntro_Functions // Function Array
	.byte 8 // Array Items
	.byte 36 // Parent Screen
	.byte 3 // Parent Position

.align
ActiveMenu_OpenFlagMenu_LevelIntro:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 40
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP