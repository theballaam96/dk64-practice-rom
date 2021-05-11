.align
Maps_JungleJapes_DestMap:
	.byte 0x0 // Null for Main Map
	.byte 0x25
	.byte 0x6
	.byte 0x4
	.byte 0xD
	.byte 0xC
	.byte 0x21

.align
Maps_JungleJapes_DestExit:
	.byte 0x0 // Null for Main Map
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_JungleJapes_Struct:
	.word Maps_JungleJapes_DestMap // Map
	.word Maps_JungleJapes_DestExit // Exit
	.byte 2 // Screen

.align
Maps_JungleJapesMain_DestMap:
	.byte 0x7
	.byte 0x7
	.byte 0x7
	.byte 0x7
	.byte 0x7
	.byte 0x7

.align
Maps_JungleJapesMain_DestExit:
	.byte 0xF
	.byte 0x0
	.byte 0x10
	.byte 0x2
	.byte 0x3
	.byte 0x1

.align
Maps_JungleJapesMain_Struct:
	.word Maps_JungleJapesMain_DestMap // Map
	.word Maps_JungleJapesMain_DestExit // Exit
	.byte 11 // Screen

.align
Menu_Maps_Japes_Main:
	.asciiz "MAIN MAP"
Menu_Maps_Japes_BBlast:
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Japes_Minecart:
	.asciiz "MINECART"
Menu_Maps_Japes_Mountain:
	.asciiz "MOUNTAIN"
Menu_Maps_Japes_Painting:
	.asciiz "PAINTING ROOM"
Menu_Maps_Japes_Shellhive:
	.asciiz "SHELLHIVE"
Menu_Maps_Japes_Underground:
	.asciiz "UNDERGROUND"

.align
Menu_MapJapes_Array:
	.word Menu_Maps_Japes_Main
	.word Menu_Maps_Japes_BBlast
	.word Menu_Maps_Japes_Minecart
	.word Menu_Maps_Japes_Mountain
	.word Menu_Maps_Japes_Painting
	.word Menu_Maps_Japes_Shellhive
	.word Menu_Maps_Japes_Underground

.align
Menu_MapJapes_Functions:
	.word ActiveMenu_OpenMapWarper_JapesMain
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapJapes_Struct:
	.word Menu_MapJapes_Array // Text Array
	.word Menu_MapJapes_Functions // Function Array
	.byte 7 // Array Items
	.byte 1 // Parent Screen



.align
Menu_Maps_Japes_Portal:
	.asciiz "FROM PORTAL"
Menu_Maps_Japes_Intro:
	.asciiz "INTRO"
Menu_Maps_Japes_RiverLow:
	.asciiz "LOWER RIVER"
Menu_Maps_Japes_RiverHigh:
	.asciiz "UPPER RIVER"
Menu_Maps_Japes_Storm:
	.asciiz "STORM AREA"
Menu_Maps_Japes_Zinger:
	.asciiz "ZINGER AREA"

.align
Menu_MapJapesMain_Array:
	.word Menu_Maps_Japes_Portal
	.word Menu_Maps_Japes_Intro
	.word Menu_Maps_Japes_RiverLow
	.word Menu_Maps_Japes_RiverHigh
	.word Menu_Maps_Japes_Storm
	.word Menu_Maps_Japes_Zinger

.align
Menu_MapJapesMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapJapesMain_Struct:
	.word Menu_MapJapesMain_Array // Text Array
	.word Menu_MapJapesMain_Functions // Function Array
	.byte 6 // Array Items
	.byte 2 // Parent Screen