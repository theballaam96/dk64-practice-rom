.align
Menu_Flags_FTTFlags:
	.half 0x16F // Diddy FTT
	.half 0x170 // Lanky FTT
	.half 0x171 // Tiny FTT
	.half 0x172 // Chunky FTT
	.half 0x17E // B. Locker FTT
	.half 0x163 // Bananaport FTT
	.half 0x166 // Crown Pad FTT
	.half 0x16B // Strong Kong FTT
	.half 0x16A // OSprint FTT
	.half 0x168 // Mini Monkey FTT
	.half 0x169 // Hunky Chunky FTT

.align
Menu_Flags_FTTFlagType:
	.byte 0 // Diddy FTT
	.byte 0 // Lanky FTT
	.byte 0 // Tiny FTT
	.byte 0 // Chunky FTT
	.byte 0 // B. Locker FTT
	.byte 0 // Bananaport FTT
	.byte 0 // Crown Pad FTT
	.byte 0 // Strong Kong FTT
	.byte 0 // OSprint FTT
	.byte 0 // Mini Monkey FTT
	.byte 0 // Hunky Chunky FTT

.align
Menu_Flags_FTTStruct:
	.word Menu_Flags_FTTFlags ; Flags
	.word Menu_Flags_FTTFlagType ; Flag Type
	.word Menu_Flags_FTT_TextStruct ; Text Information
	.byte 52 ; Associated Screen
	.byte 11 ; Flag Count

.align
Menu_Flags_FTT_BLockerFTT_Set:
	.asciiz "B LOCKER FTT: WATCHED"
Menu_Flags_FTT_BLockerFTT_Clear:
	.asciiz "B LOCKER FTT: NOT WATCHED"
Menu_Flags_FTT_DiddyFTT_Set:
	.asciiz "DIDDY FTT: WATCHED"
Menu_Flags_FTT_DiddyFTT_Clear:
	.asciiz "DIDDY FTT: NOT WATCHED"
Menu_Flags_FTT_LankyFTT_Set:
	.asciiz "LANKY FTT: WATCHED"
Menu_Flags_FTT_LankyFTT_Clear:
	.asciiz "LANKY FTT: NOT WATCHED"
Menu_Flags_FTT_TinyFTT_Set:
	.asciiz "TINY FTT: WATCHED"
Menu_Flags_FTT_TinyFTT_Clear:
	.asciiz "TINY FTT: NOT WATCHED"
Menu_Flags_FTT_ChunkyFTT_Set:
	.asciiz "CHUNKY FTT: WATCHED"
Menu_Flags_FTT_ChunkyFTT_Clear:
	.asciiz "CHUNKY FTT: NOT WATCHED"
Menu_Flags_FTT_BananaportFTT_Set:
	.asciiz "BANANAPORT FTT: WATCHED"
Menu_Flags_FTT_BananaportFTT_Clear:
	.asciiz "BANANAPORT FTT: NOT WATCHED"
Menu_Flags_FTT_CrownPadFTT_Set:
	.asciiz "CROWN PAD FTT: WATCHED"
Menu_Flags_FTT_CrownPadFTT_Clear:
	.asciiz "CROWN PAD FTT: NOT WATCHED"
Menu_Flags_FTT_StrongKongFTT_Set:
	.asciiz "STRONG KONG FTT: WATCHED"
Menu_Flags_FTT_StrongKongFTT_Clear:
	.asciiz "STRONG KONG FTT: NOT WATCHED"
Menu_Flags_FTT_OrangstandSprintFTT_Set:
	.asciiz "OSTAND SPRINT FTT: WATCHED"
Menu_Flags_FTT_OrangstandSprintFTT_Clear:
	.asciiz "OSTAND SPRINT FTT: NOT WATCHED"
Menu_Flags_FTT_MiniMonkeyFTT_Set:
	.asciiz "MINI MONKEY FTT: WATCHED"
Menu_Flags_FTT_MiniMonkeyFTT_Clear:
	.asciiz "MINI MONKEY FTT: NOT WATCHED"
Menu_Flags_FTT_HunkyChunkyFTT_Set:
	.asciiz "HUNKY CHUNKY FTT: WATCHED"
Menu_Flags_FTT_HunkyChunkyFTT_Clear:
	.asciiz "HUNKY CHUNKY FTT: NOT WATCHED"

.align
Menu_Flags_FTT_BLockerFTT_Struct:
	.word Menu_Flags_FTT_BLockerFTT_Clear
	.word Menu_Flags_FTT_BLockerFTT_Set
.align
Menu_Flags_FTT_DiddyFTT_Struct:
	.word Menu_Flags_FTT_DiddyFTT_Clear
	.word Menu_Flags_FTT_DiddyFTT_Set
.align
Menu_Flags_FTT_LankyFTT_Struct:
	.word Menu_Flags_FTT_LankyFTT_Clear
	.word Menu_Flags_FTT_LankyFTT_Set
.align
Menu_Flags_FTT_TinyFTT_Struct:
	.word Menu_Flags_FTT_TinyFTT_Clear
	.word Menu_Flags_FTT_TinyFTT_Set
.align
Menu_Flags_FTT_ChunkyFTT_Struct:
	.word Menu_Flags_FTT_ChunkyFTT_Clear
	.word Menu_Flags_FTT_ChunkyFTT_Set
.align
Menu_Flags_FTT_BananaportFTT_Struct:
	.word Menu_Flags_FTT_BananaportFTT_Clear
	.word Menu_Flags_FTT_BananaportFTT_Set
.align
Menu_Flags_FTT_CrownPadFTT_Struct:
	.word Menu_Flags_FTT_CrownPadFTT_Clear
	.word Menu_Flags_FTT_CrownPadFTT_Set
.align
Menu_Flags_FTT_StrongKongFTT_Struct:
	.word Menu_Flags_FTT_StrongKongFTT_Clear
	.word Menu_Flags_FTT_StrongKongFTT_Set
.align
Menu_Flags_FTT_OrangstandSprintFTT_Struct:
	.word Menu_Flags_FTT_OrangstandSprintFTT_Clear
	.word Menu_Flags_FTT_OrangstandSprintFTT_Set
.align
Menu_Flags_FTT_MiniMonkeyFTT_Struct:
	.word Menu_Flags_FTT_MiniMonkeyFTT_Clear
	.word Menu_Flags_FTT_MiniMonkeyFTT_Set
.align
Menu_Flags_FTT_HunkyChunkyFTT_Struct:
	.word Menu_Flags_FTT_HunkyChunkyFTT_Clear
	.word Menu_Flags_FTT_HunkyChunkyFTT_Set

.align
Menu_Flags_FTT_TextStruct:
	.word Menu_Flags_FTT_DiddyFTT_Struct
	.word Menu_Flags_FTT_LankyFTT_Struct
	.word Menu_Flags_FTT_TinyFTT_Struct
	.word Menu_Flags_FTT_ChunkyFTT_Struct
	.word Menu_Flags_FTT_BLockerFTT_Struct
	.word Menu_Flags_FTT_BananaportFTT_Struct
	.word Menu_Flags_FTT_CrownPadFTT_Struct
	.word Menu_Flags_FTT_StrongKongFTT_Struct
	.word Menu_Flags_FTT_OrangstandSprintFTT_Struct
	.word Menu_Flags_FTT_MiniMonkeyFTT_Struct
	.word Menu_Flags_FTT_HunkyChunkyFTT_Struct

.align
Menu_Flags_FTT_Array:
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
	.word Menu_Return

.align
Menu_Flags_FTT_Functions:
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
	.word ActiveMenu_PreviousScreen

.align
Menu_Flags_FTT_Struct:
	.word Menu_Flags_FTT_Array // Text Array
	.word Menu_Flags_FTT_Functions // Function Array
	.byte 12 // Array Items
	.byte 36 // Parent Screen
	.byte 8 // Parent Position

.align
ActiveMenu_OpenFlagMenu_FTT:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 52
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP