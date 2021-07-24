.align
Maps_AngryAztec_DestMap:
	.byte 0x0 // Null for main
	.byte 0xC5
	.byte 0x29
	.byte 0xE
	.byte 0x0 // Null for 5DTs
	.byte 0x14
	.byte 0x10

.align
Maps_AngryAztec_DestExit:
	.byte 0x0 // Null for main
	.byte 0
	.byte 0
	.byte 0
	.byte 0x0 // Null for 5DTS
	.byte 0
	.byte 0

.align
Maps_AngryAztec_Struct:
	.word Maps_AngryAztec_DestMap // Map
	.word Maps_AngryAztec_DestExit // Exit
	.byte 3 // Screen

.align
Maps_AngryAztecMain_DestMap:
	.byte 0x26
	.byte 0x26
	.byte 0x26
	.byte 0x26

.align
Maps_AngryAztecMain_DestExit:
	.byte 0x0
	.byte 0x12
	.byte 0x8
	.byte 0xA

.align
Maps_AngryAztecMain_Struct:
	.word Maps_AngryAztecMain_DestMap // Map
	.word Maps_AngryAztecMain_DestExit // Exit
	.byte 12 // Screen

.align
Maps_AngryAztec5DT_DestMap:
	.byte 0x13
	.byte 0x15
	.byte 0x17
	.byte 0x16
	.byte 0x18

.align
Maps_AngryAztec5DT_DestExit:
	.byte 0x0
	.byte 0x0
	.byte 0x0
	.byte 0x0
	.byte 0x0

.align
Maps_AngryAztec5DT_Struct:
	.word Maps_AngryAztec5DT_DestMap // Map
	.word Maps_AngryAztec5DT_DestExit // Exit
	.byte 13 // Screen

.align
Menu_Maps_Aztec_Main:	
	.asciiz "MAIN MAP"
Menu_Maps_Aztec_BBlast:	
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Aztec_Beetle:	
	.asciiz "BEETLE RACE"
Menu_Maps_Aztec_5DTs:	
	.asciiz "FIVE DOOR TEMPLES"
Menu_Maps_Aztec_LlamaTemple:	
	.asciiz "LLAMA TEMPLE"
Menu_Maps_Aztec_TinyTemple:	
	.asciiz "TINY TEMPLE"
Menu_Maps_Aztec_Dogadon:
	.asciiz "DOGADON 1"

.align
Menu_MapAztec_Array:
	.word Menu_Maps_Aztec_Main
	.word Menu_Maps_Aztec_Dogadon
	.word Menu_Maps_Aztec_BBlast
	.word Menu_Maps_Aztec_Beetle
	.word Menu_Maps_Aztec_5DTs
	.word Menu_Maps_Aztec_LlamaTemple
	.word Menu_Maps_Aztec_TinyTemple
	.word Menu_Return

.align
Menu_MapAztec_Functions:
	.word ActiveMenu_OpenMapWarper_AztecMain // Open Main
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_Aztec5DT // Open 5DT
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapAztec_Struct:
	.word Menu_MapAztec_Array // Text Array
	.word Menu_MapAztec_Functions // Function Array
	.byte 8 // Array Items
	.byte 1 // Parent Screen
	.byte 1 // Parent Position

.align
Menu_Maps_Aztec_Portal:	
	.asciiz "FROM PORTAL"
Menu_Maps_Aztec_Totem:	
	.asciiz "FEED ME TOTEM"
Menu_Maps_Aztec_Oasis:	
	.asciiz "OASIS"
Menu_Maps_Aztec_Snake:	
	.asciiz "SNAKE ROAD"

.align
Menu_MapAztecMain_Array:
	.word Menu_Maps_Aztec_Portal
	.word Menu_Maps_Aztec_Totem
	.word Menu_Maps_Aztec_Oasis
	.word Menu_Maps_Aztec_Snake
	.word Menu_Return

.align
Menu_MapAztecMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapAztecMain_Struct:
	.word Menu_MapAztecMain_Array // Text Array
	.word Menu_MapAztecMain_Functions // Function Array
	.byte 5 // Array Items
	.byte 3 // Parent Screen
	.byte 0 // Parent Position

.align
Menu_Maps_Aztec_5DTDK:	
	.asciiz "FIVE DOOR TEMPLE - DK"
Menu_Maps_Aztec_5DTDiddy:	
	.asciiz "FIVE DOOR TEMPLE - DIDDY"
Menu_Maps_Aztec_5DTLanky:	
	.asciiz "FIVE DOOR TEMPLE - LANKY"
Menu_Maps_Aztec_5DTTiny:	
	.asciiz "FIVE DOOR TEMPLE - TINY"
Menu_Maps_Aztec_5DTChunky:	
	.asciiz "FIVE DOOR TEMPLE - CHUNKY"

.align
Menu_MapAztec5DTs_Array:
	.word Menu_Maps_Aztec_5DTDK
	.word Menu_Maps_Aztec_5DTDiddy
	.word Menu_Maps_Aztec_5DTLanky
	.word Menu_Maps_Aztec_5DTTiny
	.word Menu_Maps_Aztec_5DTChunky
	.word Menu_Return

.align
Menu_MapAztec5DTs_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapAztec5DTs_Struct:
	.word Menu_MapAztec5DTs_Array // Text Array
	.word Menu_MapAztec5DTs_Functions // Function Array
	.byte 6 // Array Items
	.byte 3 // Parent Screen
	.byte 4 // Parent Position