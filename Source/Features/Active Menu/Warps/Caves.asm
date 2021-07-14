.align
Maps_CrystalCaves_DestMap:
	.byte 0x0 // Null for main
	.byte 0xC4
	.byte 0xBA
	.byte 0x52
	.byte 0x0 // Null for 5DCs
	.byte 0x0 // Null for 5DIs
	.byte 0x62
	.byte 0x59
	.byte 0x5E

.align
Maps_CrystalCaves_DestExit:
	.byte 0x0 // Null for Main
	.byte 0
	.byte 0
	.byte 0
	.byte 0x0 // Null for 5DCs
	.byte 0x0 // Null for 5DIs
	.byte 0
	.byte 0
	.byte 0

.align
Maps_CrystalCaves_Struct:
	.word Maps_CrystalCaves_DestMap // Map
	.word Maps_CrystalCaves_DestExit // Exit
	.byte 7 // Screen

.align
Maps_CrystalCavesMain_DestMap:
	.byte 0x48
	.byte 0x48
	.byte 0x48
	.byte 0x48
	.byte 0x48
	.byte 0x48

.align
Maps_CrystalCavesMain_DestExit:
	.byte 0x0
	.byte 0x9
	.byte 0x1A
	.byte 0x6
	.byte 0xB
	.byte 0x14

.align
Maps_CrystalCavesMain_Struct:
	.word Maps_CrystalCavesMain_DestMap // Map
	.word Maps_CrystalCavesMain_DestExit // Exit
	.byte 19 // Screen

.align
Maps_CrystalCaves5DC_DestMap:
	.byte 0x5B
	.byte 0xC8
	.byte 0x5C
	.byte 0x5D
	.byte 0x5A

.align
Maps_CrystalCaves5DC_DestExit:
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_CrystalCaves5DC_Struct:
	.word Maps_CrystalCaves5DC_DestMap // Map
	.word Maps_CrystalCaves5DC_DestExit // Exit
	.byte 20 // Screen

.align
Maps_CrystalCaves5DI_DestMap:
	.byte 0x56
	.byte 0x64
	.byte 0x55
	.byte 0x54
	.byte 0x5F

.align
Maps_CrystalCaves5DI_DestExit:
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_CrystalCaves5DI_Struct:
	.word Maps_CrystalCaves5DI_DestMap // Map
	.word Maps_CrystalCaves5DI_DestExit // Exit
	.byte 21 // Screen

.align
Menu_Maps_Caves_Main:	
	.asciiz "MAIN MAP"
Menu_Maps_Caves_BBlast:	
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Caves_Beetle:	
	.asciiz "BEETLE RACE"
Menu_Maps_Caves_5DCs:	
	.asciiz "FIVE DOOR CABINS"
Menu_Maps_Caves_5DIs:	
	.asciiz "FIVE DOOR IGLOOS"
Menu_Maps_Caves_IceCastleMap:	
	.asciiz "ICE CASTLE"
Menu_Maps_Caves_RotatingRoom:	
	.asciiz "ROTATING ROOM"
Menu_Maps_Caves_1DC:	
	.asciiz "SPRINT CABIN"
Menu_Maps_Caves_AD2:
	.asciiz "ARMY DILLO 2"

.align
Menu_MapCaves_Array:
	.word Menu_Maps_Caves_Main
	.word Menu_Maps_Caves_AD2
	.word Menu_Maps_Caves_BBlast
	.word Menu_Maps_Caves_Beetle
	.word Menu_Maps_Caves_5DCs
	.word Menu_Maps_Caves_5DIs
	.word Menu_Maps_Caves_IceCastleMap
	.word Menu_Maps_Caves_RotatingRoom
	.word Menu_Maps_Caves_1DC
	.word Menu_Return

.align
Menu_MapCaves_Functions:
	.word ActiveMenu_OpenMapWarper_CavesMain // Open Main
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_Caves5DC // Open 5DCs
	.word ActiveMenu_OpenMapWarper_Caves5DI // Open 5DIs
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapCaves_Struct:
	.word Menu_MapCaves_Array // Text Array
	.word Menu_MapCaves_Functions // Function Array
	.byte 10 // Array Items
	.byte 1 // Parent Screen

.align
Menu_Maps_Caves_Portal:	
	.asciiz "FROM PORTAL"
Menu_Maps_Caves_CabinArea:	
	.asciiz "CABINS AREA"
Menu_Maps_Caves_Boulder:	
	.asciiz "GIANT BOULDER"
Menu_Maps_Caves_IceCastleArea:	
	.asciiz "ICE CASTLE"
Menu_Maps_Caves_IglooArea:	
	.asciiz "IGLOOS AREA"
Menu_Maps_Caves_Waterfall:	
	.asciiz "WATERFALL"

.align
Menu_MapCavesMain_Array:
	.word Menu_Maps_Caves_Portal
	.word Menu_Maps_Caves_CabinArea
	.word Menu_Maps_Caves_Boulder
	.word Menu_Maps_Caves_IceCastleArea
	.word Menu_Maps_Caves_IglooArea
	.word Menu_Maps_Caves_Waterfall
	.word Menu_Return

.align
Menu_MapCavesMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapCavesMain_Struct:
	.word Menu_MapCavesMain_Array // Text Array
	.word Menu_MapCavesMain_Functions // Function Array
	.byte 7 // Array Items
	.byte 7 // Parent Screen

.align
Menu_Maps_Caves_5DCDK:	
	.asciiz "FIVE DOOR CABIN - DK"
Menu_Maps_Caves_5DCDiddyCandle:	
	.asciiz "FIVE DOOR CABIN - DIDDY CANDLES"
Menu_Maps_Caves_5DCDiddyEnemy:	
	.asciiz "FIVE DOOR CABIN - DIDDY ENEMIES"
Menu_Maps_Caves_5DCTiny:	
	.asciiz "FIVE DOOR CABIN - TINY"
Menu_Maps_Caves_5DCChunky:	
	.asciiz "FIVE DOOR CABIN - CHUNKY"

.align
Menu_MapCaves5DC_Array:
	.word Menu_Maps_Caves_5DCDK
	.word Menu_Maps_Caves_5DCDiddyCandle
	.word Menu_Maps_Caves_5DCDiddyEnemy
	.word Menu_Maps_Caves_5DCTiny
	.word Menu_Maps_Caves_5DCChunky
	.word Menu_Return

.align
Menu_MapCaves5DC_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapCaves5DC_Struct:
	.word Menu_MapCaves5DC_Array // Text Array
	.word Menu_MapCaves5DC_Functions // Function Array
	.byte 6 // Array Items
	.byte 7 // Parent Screen

.align
Menu_Maps_Caves_5DIDK:	
	.asciiz "FIVE DOOR IGLOO - DK"
Menu_Maps_Caves_5DIDiddy:	
	.asciiz "FIVE DOOR IGLOO - DIDDY"
Menu_Maps_Caves_5DILanky:	
	.asciiz "FIVE DOOR IGLOO - LANKY"
Menu_Maps_Caves_5DITiny:	
	.asciiz "FIVE DOOR IGLOO - TINY"
Menu_Maps_Caves_5DIChunky:	
	.asciiz "FIVE DOOR IGLOO - CHUNKY"

.align
Menu_MapCaves5DI_Array:
	.word Menu_Maps_Caves_5DIDK
	.word Menu_Maps_Caves_5DIDiddy
	.word Menu_Maps_Caves_5DILanky
	.word Menu_Maps_Caves_5DITiny
	.word Menu_Maps_Caves_5DIChunky
	.word Menu_Return

.align
Menu_MapCaves5DI_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapCaves5DI_Struct:
	.word Menu_MapCaves5DI_Array // Text Array
	.word Menu_MapCaves5DI_Functions // Function Array
	.byte 6 // Array Items
	.byte 7 // Parent Screen