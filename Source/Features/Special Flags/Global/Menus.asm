.align
Menu_Flags_GlobalMysteryFlags:
	.half 0x00 // Mystery Menu Unlocked
	.half 0x01 // CS Menu Unlocked
	.half 0x0E // Minigame Menu Unlocked
	.half 0x13 // Bosses Menu Unlocked
	.half 0x21 // Krusha Menu Unlocked
	.half 0x22 // Cheats Menu Unlocked
	.half 0x1C // Multi Unlocked

.align
Menu_Flags_GlobalMysteryFlagType:
	.byte 1 // Mystery Menu Unlocked
	.byte 1 // CS Menu Unlocked
	.byte 1 // Minigame Menu Unlocked
	.byte 1 // Bosses Menu Unlocked
	.byte 1 // Krusha Menu Unlocked
	.byte 1 // Cheats Menu Unlocked
	.byte 1 // Multi Unlocked

.align
Menu_Flags_GlobalMysteryStruct:
	.word Menu_Flags_GlobalMysteryFlags ; Flags
	.word Menu_Flags_GlobalMysteryFlagType ; Flag Type
	.word Menu_Flags_GlobalMystery_TextStruct ; Text Information
	.byte 47 ; Associated Screen
	.byte 7 ; Flag Count

.align
Menu_Flags_GlobalMystery_Mystery_Set:
	.asciiz "MYSTERY MENU: UNLOCKED"
Menu_Flags_GlobalMystery_Mystery_Clear:
	.asciiz "MYSTERY MENU: LOCKED"
Menu_Flags_GlobalMystery_CSMenu_Set:
	.asciiz "CUTSCENE MENU: UNLOCKED"
Menu_Flags_GlobalMystery_CSMenu_Clear:
	.asciiz "CUTSCENE MENU: LOCKED"
Menu_Flags_GlobalMystery_MgMenu_Set:
	.asciiz "MINIGAME MENU: UNLOCKED"
Menu_Flags_GlobalMystery_MgMenu_Clear:
	.asciiz "MINIGAME MENU: LOCKED"
Menu_Flags_GlobalMystery_BossMenu_Set:
	.asciiz "BOSSES MENU: UNLOCKED"
Menu_Flags_GlobalMystery_BossMenu_Clear:
	.asciiz "BOSSES MENU: LOCKED"
Menu_Flags_GlobalMystery_KrushaMenu_Set:
	.asciiz "KRUSHA MENU: UNLOCKED"
Menu_Flags_GlobalMystery_KrushaMenu_Clear:
	.asciiz "KRUSHA MENU: LOCKED"
Menu_Flags_GlobalMystery_CheatMenu_Set:
	.asciiz "CHEAT MENU: UNLOCKED"
Menu_Flags_GlobalMystery_CheatMenu_Clear:
	.asciiz "CHEAT MENU: LOCKED"
Menu_Flags_GlobalMystery_MultiMenu_Set:
	.asciiz "MULTIPLAYER MENU: UNLOCKED"
Menu_Flags_GlobalMystery_MultiMenu_Clear:
	.asciiz "MULTIPLAYER MENU: LOCKED"

.align
Menu_Flags_GlobalMystery_Mystery_Struct:
	.word Menu_Flags_GlobalMystery_Mystery_Clear
	.word Menu_Flags_GlobalMystery_Mystery_Set

.align
Menu_Flags_GlobalMystery_CSMenu_Struct:
	.word Menu_Flags_GlobalMystery_CSMenu_Clear
	.word Menu_Flags_GlobalMystery_CSMenu_Set
.align
Menu_Flags_GlobalMystery_MgMenu_Struct:
	.word Menu_Flags_GlobalMystery_MgMenu_Clear
	.word Menu_Flags_GlobalMystery_MgMenu_Set
.align
Menu_Flags_GlobalMystery_BossMenu_Struct:
	.word Menu_Flags_GlobalMystery_BossMenu_Clear
	.word Menu_Flags_GlobalMystery_BossMenu_Set
.align
Menu_Flags_GlobalMystery_KrushaMenu_Struct:
	.word Menu_Flags_GlobalMystery_KrushaMenu_Clear
	.word Menu_Flags_GlobalMystery_KrushaMenu_Set
.align
Menu_Flags_GlobalMystery_CheatMenu_Struct:
	.word Menu_Flags_GlobalMystery_CheatMenu_Clear
	.word Menu_Flags_GlobalMystery_CheatMenu_Set
.align
Menu_Flags_GlobalMystery_MultiMenu_Struct:
	.word Menu_Flags_GlobalMystery_MultiMenu_Clear
	.word Menu_Flags_GlobalMystery_MultiMenu_Set

.align
Menu_Flags_GlobalMystery_TextStruct:
	.word Menu_Flags_GlobalMystery_Mystery_Struct
	.word Menu_Flags_GlobalMystery_CSMenu_Struct
	.word Menu_Flags_GlobalMystery_MgMenu_Struct
	.word Menu_Flags_GlobalMystery_BossMenu_Struct
	.word Menu_Flags_GlobalMystery_KrushaMenu_Struct
	.word Menu_Flags_GlobalMystery_CheatMenu_Struct
	.word Menu_Flags_GlobalMystery_MultiMenu_Struct

.align
Menu_Flags_GlobalMystery_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_GlobalMystery_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	
.align
Menu_Flags_GlobalMystery_Struct:
	.word Menu_Flags_GlobalMystery_Array // Text Array
	.word Menu_Flags_GlobalMystery_Functions // Function Array
	.byte 7 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_GlobalMystery:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 47
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP