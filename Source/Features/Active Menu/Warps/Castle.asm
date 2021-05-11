.align
Maps_CreepyCastle_DestMap:
	.byte 0x0 // Null for main
	.byte 0xBB
	.byte 0x58
	.byte 0xB9
	.byte 0x0 // Null for Crypts
	.byte 0xA3
	.byte 0x0 // Null for Tunnel
	.byte 0xA8
	.byte 0x9
	.byte 0x72
	.byte 0x6A
	.byte 0x71
	.byte 0xA6
	.byte 0xA4
	.byte 0xA7
	.byte 0x69

.align
Maps_CreepyCastle_DestExit:
	.byte 0x0 // Null for main
	.byte 0
	.byte 0
	.byte 0
	.byte 0x0 // Null for Crypts
	.byte 0
	.byte 0x0 // Null for Tunnel
	.byte 0
	.byte 0
	.byte 0x1 // Library
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_CreepyCastle_Struct:
	.word Maps_CreepyCastle_DestMap // Map
	.word Maps_CreepyCastle_DestExit // Exit
	.byte 8 // Screen

.align
Maps_CreepyCastleMain_DestMap:
	.byte 0x57
	.byte 0x57
	.byte 0x57
	.byte 0x57
	.byte 0x57

.align
Maps_CreepyCastleMain_DestExit:
	.byte 0x0
	.byte 0x15
	.byte 0xE
	.byte 0x3
	.byte 0xA

.align
Maps_CreepyCastleMain_Struct:
	.word Maps_CreepyCastleMain_DestMap // Map
	.word Maps_CreepyCastleMain_DestExit // Exit
	.byte 22 // Screen

.align
Maps_CreepyCastleCrypt_DestMap:
	.byte 0x70
	.byte 0x6C
	.byte 0xB7

.align
Maps_CreepyCastleCrypt_DestExit:
	.byte 0
	.byte 0
	.byte 0

.align
Maps_CreepyCastleCrypt_Struct:
	.word Maps_CreepyCastleCrypt_DestMap // Map
	.word Maps_CreepyCastleCrypt_DestExit // Exit
	.byte 23 // Screen

.align
Maps_CreepyCastleTunnel_DestMap:
	.byte 0x97
	.byte 0x97

.align
Maps_CreepyCastleTunnel_DestExit:
	.byte 0x0
	.byte 0x2

.align
Maps_CreepyCastleTunnel_Struct:
	.word Maps_CreepyCastleTunnel_DestMap // Map
	.word Maps_CreepyCastleTunnel_DestExit // Exit
	.byte 24 // Screen

.align
Menu_Maps_Castle_Main:	
	.asciiz "MAIN MAP"
Menu_Maps_Castle_BBlast:	
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Castle_Ballrom:	
	.asciiz "BALLROOM"
Menu_Maps_Castle_Car:	
	.asciiz "CAR RACE"
Menu_Maps_Castle_Crypt:	
	.asciiz "CRYPT"
Menu_Maps_Castle_Dungeon:	
	.asciiz "DUNGEON"
Menu_Maps_Castle_Tunnel:	
	.asciiz "DUNGEON TUNNEL"
Menu_Maps_Castle_Greenhouse:	
	.asciiz "GREENHOUSE"
Menu_Maps_Castle_Jetpac:	
	.asciiz "JETPAC"
Menu_Maps_Castle_Library:	
	.asciiz "LIBRARY"
Menu_Maps_Castle_Minecart:	
	.asciiz "MINECART"
Menu_Maps_Castle_Museum:	
	.asciiz "MUSEUM"
Menu_Maps_Castle_Shed:	
	.asciiz "SHED"
Menu_Maps_Castle_Tree:	
	.asciiz "TREE"
Menu_Maps_Castle_TrashCan:	
	.asciiz "TRASH CAN"
Menu_Maps_Castle_WindTower:	
	.asciiz "WIND TOWER"

.align
Menu_MapCastle_Array:
	.word Menu_Maps_Castle_Main
	.word Menu_Maps_Castle_BBlast
	.word Menu_Maps_Castle_Ballrom
	.word Menu_Maps_Castle_Car
	.word Menu_Maps_Castle_Crypt
	.word Menu_Maps_Castle_Dungeon
	.word Menu_Maps_Castle_Tunnel
	.word Menu_Maps_Castle_Greenhouse
	.word Menu_Maps_Castle_Jetpac
	.word Menu_Maps_Castle_Library
	.word Menu_Maps_Castle_Minecart
	.word Menu_Maps_Castle_Museum
	.word Menu_Maps_Castle_Shed
	.word Menu_Maps_Castle_Tree
	.word Menu_Maps_Castle_TrashCan
	.word Menu_Maps_Castle_WindTower

.align
Menu_MapCastle_Functions:
	.word ActiveMenu_OpenMapWarper_CastleMain // Open Main
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_CastleCrypt // Open Crypt
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_CastleTunnel // Open Tunnel
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapCastle_Struct:
	.word Menu_MapCastle_Array // Text Array
	.word Menu_MapCastle_Functions // Function Array
	.byte 16 // Array Items
	.byte 1 // Parent Screen

.align
Menu_Maps_Castle_Portal:	
	.asciiz "FROM PORTAL"
Menu_Maps_Castle_Intro:	
	.asciiz "INTRO"
Menu_Maps_Castle_Top:	
	.asciiz "TOP"
Menu_Maps_Castle_Warp2:	
	.asciiz "WARP 2"
Menu_Maps_Castle_Warp4:	
	.asciiz "WARP 4"

.align
Menu_MapCastleMain_Array:
	.word Menu_Maps_Castle_Portal
	.word Menu_Maps_Castle_Intro
	.word Menu_Maps_Castle_Top
	.word Menu_Maps_Castle_Warp2
	.word Menu_Maps_Castle_Warp4

.align
Menu_MapCastleMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapCastleMain_Struct:
	.word Menu_MapCastleMain_Array // Text Array
	.word Menu_MapCastleMain_Functions // Function Array
	.byte 5 // Array Items
	.byte 8 // Parent Screen

.align
Menu_Maps_Castle_CryptDDC:	
	.asciiz "CRYPT - DK, DIDDY, CHUNKY"
Menu_Maps_Castle_CryptLT:	
	.asciiz "CRYPT - LANKY, TINY"
Menu_Maps_Castle_CryptHub:	
	.asciiz "CRYPT - HUB"

.align
Menu_MapCastleCrypt_Array:
	.word Menu_Maps_Castle_CryptDDC
	.word Menu_Maps_Castle_CryptLT
	.word Menu_Maps_Castle_CryptHub

.align
Menu_MapCastleCrypt_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapCastleCrypt_Struct:
	.word Menu_MapCastleCrypt_Array // Text Array
	.word Menu_MapCastleCrypt_Functions // Function Array
	.byte 3 // Array Items
	.byte 8 // Parent Screen

.align
Menu_Maps_Castle_TunnelNear:	
	.asciiz "DUNGEON TUNNEL - NEAR"
Menu_Maps_Castle_TunnelFar:	
	.asciiz "DUNGEON TUNNEL - FAR"

.align
Menu_MapCastleTunnel_Array:
	.word Menu_Maps_Castle_TunnelNear
	.word Menu_Maps_Castle_TunnelFar

.align
Menu_MapCastleTunnel_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapCastleTunnel_Struct:
	.word Menu_MapCastleTunnel_Array // Text Array
	.word Menu_MapCastleTunnel_Functions // Function Array
	.byte 2 // Array Items
	.byte 8 // Parent Screen