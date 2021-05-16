.align
Menu_Flags_BossIntroFlags:
	.half 0x68 // AD1 Intro
	.half 0x67 // Dog1 Intro
	.half 0x6A // MJ Intro
	.half 0x6B // Puff Intro
	.half 0x69 // Dog2 Intro
	.half 0x6D // AD2 Intro
	.half 0x6C // Kut Out Intro

.align
Menu_Flags_BossIntroFlagType:
	.byte 2 // AD1 Intro
	.byte 2 // Dog1 Intro
	.byte 2 // MJ Intro
	.byte 2 // Puff Intro
	.byte 2 // Dog2 Intro
	.byte 2 // AD2 Intro
	.byte 2 // Kut Out Intro

.align
Menu_Flags_BossIntroStruct:
	.word Menu_Flags_BossIntroFlags ; Flags
	.word Menu_Flags_BossIntroFlagType ; Flag Type
	.word Menu_Flags_BossIntro_TextStruct ; Text Information
	.byte 42 ; Associated Screen
	.byte 7 ; Flag Count

.align
Menu_Flags_BossIntro_Japes_Set:
	.asciiz "ARMY DILLO 1 INTRO - WATCHED"
Menu_Flags_BossIntro_Japes_Clear:
	.asciiz "ARMY DILLO 1 INTRO - NOT WATCHED"
Menu_Flags_BossIntro_Aztec_Set:
	.asciiz "DOGADON 1 INTRO - WATCHED"
Menu_Flags_BossIntro_Aztec_Clear:
	.asciiz "DOGADON 1 INTRO - NOT WATCHED"
Menu_Flags_BossIntro_Factory_Set:
	.asciiz "MAD JACK INTRO - WATCHED"
Menu_Flags_BossIntro_Factory_Clear:
	.asciiz "MAD JACK INTRO - NOT WATCHED"
Menu_Flags_BossIntro_Galleon_Set:
	.asciiz "PUFFTOSS INTRO - WATCHED"
Menu_Flags_BossIntro_Galleon_Clear:
	.asciiz "PUFFTOSS INTRO - NOT WATCHED"
Menu_Flags_BossIntro_Fungi_Set:
	.asciiz "DOGADON 2 INTRO - WATCHED"
Menu_Flags_BossIntro_Fungi_Clear:
	.asciiz "DOGADON 2 INTRO - NOT WATCHED"
Menu_Flags_BossIntro_Caves_Set:
	.asciiz "ARMY DILLO 2 INTRO - WATCHED"
Menu_Flags_BossIntro_Caves_Clear:
	.asciiz "ARMY DILLO 2 INTRO - NOT WATCHED"
Menu_Flags_BossIntro_Castle_Set:
	.asciiz "KUT OUT INTRO - WATCHED"
Menu_Flags_BossIntro_Castle_Clear:
	.asciiz "KUT OUT INTRO - NOT WATCHED"

.align
Menu_Flags_BossIntro_Japes_Struct:
	.word Menu_Flags_BossIntro_Japes_Clear
	.word Menu_Flags_BossIntro_Japes_Set
.align
Menu_Flags_BossIntro_Aztec_Struct:
	.word Menu_Flags_BossIntro_Aztec_Clear
	.word Menu_Flags_BossIntro_Aztec_Set
.align
Menu_Flags_BossIntro_Factory_Struct:
	.word Menu_Flags_BossIntro_Factory_Clear
	.word Menu_Flags_BossIntro_Factory_Set
.align
Menu_Flags_BossIntro_Galleon_Struct:
	.word Menu_Flags_BossIntro_Galleon_Clear
	.word Menu_Flags_BossIntro_Galleon_Set
.align
Menu_Flags_BossIntro_Fungi_Struct:
	.word Menu_Flags_BossIntro_Fungi_Clear
	.word Menu_Flags_BossIntro_Fungi_Set
.align
Menu_Flags_BossIntro_Caves_Struct:
	.word Menu_Flags_BossIntro_Caves_Clear
	.word Menu_Flags_BossIntro_Caves_Set
.align
Menu_Flags_BossIntro_Castle_Struct:
	.word Menu_Flags_BossIntro_Castle_Clear
	.word Menu_Flags_BossIntro_Castle_Set

.align
Menu_Flags_BossIntro_TextStruct:
	.word Menu_Flags_BossIntro_Japes_Struct
	.word Menu_Flags_BossIntro_Aztec_Struct
	.word Menu_Flags_BossIntro_Factory_Struct
	.word Menu_Flags_BossIntro_Galleon_Struct
	.word Menu_Flags_BossIntro_Fungi_Struct
	.word Menu_Flags_BossIntro_Caves_Struct
	.word Menu_Flags_BossIntro_Castle_Struct

.align
Menu_Flags_BossIntro_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_BossIntro_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_BossIntro_Struct:
	.word Menu_Flags_BossIntro_Array // Text Array
	.word Menu_Flags_BossIntro_Functions // Function Array
	.byte 7 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_BossIntro:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 42
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP