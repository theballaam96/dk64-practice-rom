.align
Maps_GloomyGalleon_DestMap:
	.byte 0x0 // Null for Main
	.byte 0x6F
	.byte 0x36
	.byte 0x0 // Null for Shipwrecks
	.byte 0x1F
	.byte 0x31
	.byte 0x2D
	.byte 0x33
	.byte 0x27
	.byte 0xB3
	.byte 0x2C

.align
Maps_GloomyGalleon_DestExit:
	.byte 0x0 // Null for Main
	.byte 0
	.byte 0
	.byte 0x0 // Null for Shipwrecks
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_GloomyGalleon_Struct:
	.word Maps_GloomyGalleon_DestMap // Map
	.word Maps_GloomyGalleon_DestExit // Exit
	.byte 5 // Screen

.align
Maps_GloomyGalleonMain_DestMap:
	.byte 0x1E
	.byte 0x1E
	.byte 0x1E
	.byte 0x1E

.align
Maps_GloomyGalleonMain_DestExit:
	.byte 0x0
	.byte 0xD
	.byte 0xB
	.byte 0x7

.align
Maps_GloomyGalleonMain_Struct:
	.word Maps_GloomyGalleonMain_DestMap // Map
	.word Maps_GloomyGalleonMain_DestExit // Exit
	.byte 15 // Screen

.align
Maps_GloomyGalleonShipwrecks_DestMap:
	.byte 0x2E // DK
	.byte 0x2B // Diddy
	.byte 0x2B // Lanky
	.byte 0x2E // Tiny
	.byte 0x2B // Chunky
	.byte 0x2F // Lanky
	.byte 0x2F // Tiny

.align
Maps_GloomyGalleonShipwrecks_DestExit:
	.byte 0x0 // DK
	.byte 0x0 // Diddy
	.byte 0x2 // Lanky
	.byte 0x1 // Tiny
	.byte 0x1 // Chunky
	.byte 0x1 // Lanky
	.byte 0x0 // Tiny

.align
Maps_GloomyGalleonShipwrecks_Struct:
	.word Maps_GloomyGalleonShipwrecks_DestMap // Map
	.word Maps_GloomyGalleonShipwrecks_DestExit // Exit
	.byte 16 // Screen

.align
Menu_Maps_Galleon_Main:	
	.asciiz "MAIN MAP"
Menu_Maps_Galleon_BBlast:	
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Galleon_Shipwrecks:	
	.asciiz "SHIPWRECKS"
Menu_Maps_Galleon_Seasick:	
	.asciiz "K. ROOL'S SHIP"
Menu_Maps_Galleon_LighthouseMap:	
	.asciiz "LIGHTHOUSE"
Menu_Maps_Galleon_Mermaid:	
	.asciiz "MERMAID PALACE"
Menu_Maps_Galleon_MechFish:	
	.asciiz "MECHANICAL FISH"
Menu_Maps_Galleon_Seal:	
	.asciiz "SEAL RACE"
Menu_Maps_Galleon_Submarine:	
	.asciiz "SUBMARINE"
Menu_Maps_Galleon_TreasureChest:	
	.asciiz "TREASURE CHEST"
Menu_Maps_Galleon_Pufftoss:
	.asciiz "PUFFTOSS"

.align
Menu_MapGalleon_Array:
	.word Menu_Maps_Galleon_Main
	.word Menu_Maps_Galleon_Pufftoss
	.word Menu_Maps_Galleon_BBlast
	.word Menu_Maps_Galleon_Shipwrecks
	.word Menu_Maps_Galleon_Seasick
	.word Menu_Maps_Galleon_LighthouseMap
	.word Menu_Maps_Galleon_Mermaid
	.word Menu_Maps_Galleon_MechFish
	.word Menu_Maps_Galleon_Seal
	.word Menu_Maps_Galleon_Submarine
	.word Menu_Maps_Galleon_TreasureChest
	.word Menu_Return

.align
Menu_MapGalleon_Functions:
	.word ActiveMenu_OpenMapWarper_GalleonMain // Open Main Menu
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_GalleonShipwrecks // Open Shipwrecks Menu
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapGalleon_Struct:
	.word Menu_MapGalleon_Array // Text Array
	.word Menu_MapGalleon_Functions // Function Array
	.byte 12 // Array Items
	.byte 1 // Parent Screen
	.byte 3 // Parent Position

.align
Menu_Maps_Galleon_Portal:	
	.asciiz "MAIN - PORTAL"
Menu_Maps_Galleon_Cranky:	
	.asciiz "MAIN - CRANKY AREA"
Menu_Maps_Galleon_LighthouseArea:	
	.asciiz "MAIN - LIGHTHOUSE SIDE"
Menu_Maps_Galleon_Shipwreck:	
	.asciiz "MAIN - SHIPWRECK SIDE"

.align
Menu_MapGalleonMain_Array:
	.word Menu_Maps_Galleon_Portal
	.word Menu_Maps_Galleon_Cranky
	.word Menu_Maps_Galleon_LighthouseArea
	.word Menu_Maps_Galleon_Shipwreck
	.word Menu_Return

.align
Menu_MapGalleonMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapGalleonMain_Struct:
	.word Menu_MapGalleonMain_Array // Text Array
	.word Menu_MapGalleonMain_Functions // Function Array
	.byte 5 // Array Items
	.byte 5 // Parent Screen
	.byte 0 // Parent Position

.align
Menu_Maps_Galleon_5DSDK:	
	.asciiz "FIVE DOOR SHIP - DK"
Menu_Maps_Galleon_5DSDiddy:	
	.asciiz "FIVE DOOR SHIP - DIDDY"
Menu_Maps_Galleon_5DSLanky:	
	.asciiz "FIVE DOOR SHIP - LANKY"
Menu_Maps_Galleon_5DSTiny:	
	.asciiz "FIVE DOOR SHIP - TINY"
Menu_Maps_Galleon_5DSChunky:	
	.asciiz "FIVE DOOR SHIP - CHUNKY"
Menu_Maps_Galleon_2DSLanky:	
	.asciiz "TWO DOOR SHIP - LANKY"
Menu_Maps_Galleon_2DSTiny:	
	.asciiz "TWO DOOR SHIP - TINY"

.align
Menu_MapGalleonShipwrecks_Array:
	.word Menu_Maps_Galleon_5DSDK
	.word Menu_Maps_Galleon_5DSDiddy
	.word Menu_Maps_Galleon_5DSLanky
	.word Menu_Maps_Galleon_5DSTiny
	.word Menu_Maps_Galleon_5DSChunky
	.word Menu_Maps_Galleon_2DSLanky
	.word Menu_Maps_Galleon_2DSTiny
	.word Menu_Return

.align
Menu_MapGalleonShipwrecks_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapGalleonShipwrecks_Struct:
	.word Menu_MapGalleonShipwrecks_Array // Text Array
	.word Menu_MapGalleonShipwrecks_Functions // Function Array
	.byte 8 // Array Items
	.byte 5 // Parent Screen
	.byte 3 // Parent Position