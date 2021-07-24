.align
Maps_FungiForest_DestMap:
	.byte 0x0 // Null for Main
	.byte 0x53
	.byte 0x34
	.byte 0xBC
	.byte 0x3B
	.byte 0x38
	.byte 0x0 // Null for GMush
	.byte 0x3A
	.byte 0x0 // Null for Mills
	.byte 0x37
	.byte 0x39

.align
Maps_FungiForest_DestExit:
	.byte 0x0 // Null for Main
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0x0 // Null for GMush
	.byte 0
	.byte 0x0 // Null for Mills
	.byte 0
	.byte 0

.align
Maps_FungiForest_Struct:
	.word Maps_FungiForest_DestMap // Map
	.word Maps_FungiForest_DestExit // Exit
	.byte 6 // Screen

.align
Maps_FungiForestMain_DestMap:
	.byte 0x30
	.byte 0x30
	.byte 0x30
	.byte 0x30
	.byte 0x30
	.byte 0x30

.align
Maps_FungiForestMain_DestExit:
	.byte 0x0
	.byte 0x12
	.byte 0x6
	.byte 0x8
	.byte 0x17
	.byte 0x18

.align
Maps_FungiForestMain_Struct:
	.word Maps_FungiForestMain_DestMap // Map
	.word Maps_FungiForestMain_DestExit // Exit
	.byte 17 // Screen

.align
Maps_FungiForestGiantMushroom_DestMap:
	.byte 0x40
	.byte 0x40
	.byte 0x40
	.byte 0x3F
	.byte 0x46
	.byte 0x47

.align
Maps_FungiForestGiantMushroom_DestExit:
	.byte 0x0
	.byte 0x1
	.byte 0x4
	.byte 0x0
	.byte 0x0

.align
Maps_FungiForestGiantMushroom_Struct:
	.word Maps_FungiForestGiantMushroom_DestMap // Map
	.word Maps_FungiForestGiantMushroom_DestExit // Exit
	.byte 18 // Screen

.align
Maps_FungiForestMills_DestMap:
	.byte 0x3D
	.byte 0x3E
	.byte 0x3C

.align
Maps_FungiForestMills_DestExit:
	.byte 0
	.byte 0
	.byte 0

.align
Maps_FungiForestMills_Struct:
	.word Maps_FungiForestMills_DestMap // Map
	.word Maps_FungiForestMills_DestExit // Exit
	.byte 55 // Screen

.align
Menu_Maps_Fungi_Main:	
	.asciiz "MAIN MAP"
Menu_Maps_Fungi_Anthill:	
	.asciiz "ANTHILL"
Menu_Maps_Fungi_BBlast:	
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Fungi_Barn:	
	.asciiz "BARN"
Menu_Maps_Fungi_DarkAttic:	
	.asciiz "DARK ATTIC"
Menu_Maps_Fungi_GiantMushroom:	
	.asciiz "GIANT MUSHROOM"
Menu_Maps_Fungi_LankyAttic:	
	.asciiz "LANKY'S ATTIC"
Menu_Maps_Fungi_Mills:
	.asciiz "MILLS"
Menu_Maps_Fungi_Minecart:	
	.asciiz "MINECART"
Menu_Maps_Fungi_Winch:	
	.asciiz "WINCH ROOM"
Menu_Maps_Fungi_Dogadon:
	.asciiz "DOGADON 2"

.align
Menu_MapFungi_Array:
	.word Menu_Maps_Fungi_Main
	.word Menu_Maps_Fungi_Dogadon
	.word Menu_Maps_Fungi_Anthill
	.word Menu_Maps_Fungi_BBlast
	.word Menu_Maps_Fungi_Barn
	.word Menu_Maps_Fungi_DarkAttic
	.word Menu_Maps_Fungi_GiantMushroom
	.word Menu_Maps_Fungi_LankyAttic
	.word Menu_Maps_Fungi_Mills
	.word Menu_Maps_Fungi_Minecart
	.word Menu_Maps_Fungi_Winch
	.word Menu_Return

.align
Menu_MapFungi_Functions:
	.word ActiveMenu_OpenMapWarper_FungiMain
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_FungiGMush
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_FungiMills
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapFungi_Struct:
	.word Menu_MapFungi_Array // Text Array
	.word Menu_MapFungi_Functions // Function Array
	.byte 12 // Array Items
	.byte 1 // Parent Screen
	.byte 4 // Parent Position

.align
Menu_Maps_Fungi_Portal:	
	.asciiz "FROM PORTAL"
Menu_Maps_Fungi_Apple:	
	.asciiz "APPLE SIDE"
Menu_Maps_Fungi_MillArea:	
	.asciiz "MILL SIDE"
Menu_Maps_Fungi_MushroomArea:	
	.asciiz "MUSHROOM SIDE"
Menu_Maps_Fungi_Owl:	
	.asciiz "OWL TREE"
Menu_Maps_Fungi_TopOfMushroom:	
	.asciiz "TOP OF MUSHROOM"

.align
Menu_MapFungiMain_Array:
	.word Menu_Maps_Fungi_Portal
	.word Menu_Maps_Fungi_Apple
	.word Menu_Maps_Fungi_MillArea
	.word Menu_Maps_Fungi_MushroomArea
	.word Menu_Maps_Fungi_Owl
	.word Menu_Maps_Fungi_TopOfMushroom
	.word Menu_Return

.align
Menu_MapFungiMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapFungiMain_Struct:
	.word Menu_MapFungiMain_Array // Text Array
	.word Menu_MapFungiMain_Functions // Function Array
	.byte 7 // Array Items
	.byte 6 // Parent Screen
	.byte 0 // Parent Position

.align
Menu_Maps_Fungi_MushBottom:	
	.asciiz "GIANT MUSHROOM - BOTTOM"
Menu_Maps_Fungi_MushMiddle:	
	.asciiz "GIANT MUSHROOM - MIDDLE"
Menu_Maps_Fungi_MushTop:	
	.asciiz "GIANT MUSHROOM - TOP"
Menu_Maps_Fungi_LightRoom:	
	.asciiz "MUSHROOM TOP - LIGHT ROOM"
Menu_Maps_Fungi_DarkRoom:	
	.asciiz "MUSHROOM TOP - DARK ROOM"
Menu_Maps_Fungi_FacePuzzle:	
	.asciiz "FACE PUZZLE"

.align
Menu_MapFungiGMush_Array:
	.word Menu_Maps_Fungi_MushBottom
	.word Menu_Maps_Fungi_MushMiddle
	.word Menu_Maps_Fungi_MushTop
	.word Menu_Maps_Fungi_LightRoom
	.word Menu_Maps_Fungi_DarkRoom
	.word Menu_Maps_Fungi_FacePuzzle
	.word Menu_Return

.align
Menu_MapFungiGMush_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapFungiGMush_Struct:
	.word Menu_MapFungiGMush_Array // Text Array
	.word Menu_MapFungiGMush_Functions // Function Array
	.byte 7 // Array Items
	.byte 6 // Parent Screen
	.byte 6 // Parent Position

.align
Menu_Maps_Fungi_MillFront:	
	.asciiz "MILL - FRONT" // Crusher Side
Menu_Maps_Fungi_MillRear:	
	.asciiz "MILL - REAR" // Spider Side
Menu_Maps_Fungi_Spider:	
	.asciiz "SPIDER BOSS"

.align
Menu_MapFungiMills_Array:
	.word Menu_Maps_Fungi_MillFront
	.word Menu_Maps_Fungi_MillRear
	.word Menu_Maps_Fungi_Spider
	.word Menu_Return

.align
Menu_MapFungiMills_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapFungiMills_Struct:
	.word Menu_MapFungiMills_Array // Text Array
	.word Menu_MapFungiMills_Functions // Function Array
	.byte 4 // Array Items
	.byte 6 // Parent Screen
	.byte 8 // Parent Position