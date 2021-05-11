.align
Maps_FranticFactory_DestMap:
	.byte 0x0 // Null for Main
	.byte 0x2
	.byte 0x6E
	.byte 0x1B
	.byte 0x24
	.byte 0x1D

.align
Maps_FranticFactory_DestExit:
	.byte 0x0 // Null for Main
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_FranticFactory_Struct:
	.word Maps_FranticFactory_DestMap // Map
	.word Maps_FranticFactory_DestExit // Exit
	.byte 4 // Screen

.align
Maps_FranticFactoryMain_DestMap:
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A
	.byte 0x1A

.align
Maps_FranticFactoryMain_DestExit:
	.byte 0x0
	.byte 0xA
	.byte 0x9
	.byte 0x11
	.byte 0x6
	.byte 0xC
	.byte 0xB
	.byte 0x5
	.byte 0x4

.align
Maps_FranticFactoryMain_Struct:
	.word Maps_FranticFactoryMain_DestMap // Map
	.word Maps_FranticFactoryMain_DestExit // Exit
	.byte 14 // Screen

.align
Menu_Maps_Factory_Main:	
	.asciiz "MAIN MAP"
Menu_Maps_Factory_ArcadeMap:	
	.asciiz "ARCADE"
Menu_Maps_Factory_BBlast:	
	.asciiz "BABOON BLAST COURSE"
Menu_Maps_Factory_Car:	
	.asciiz "CAR RACE"
Menu_Maps_Factory_Crusher:	
	.asciiz "CRUSHER ROOM"
Menu_Maps_Factory_PowerShed:	
	.asciiz "POWER SHED"

.align
Menu_MapFactory_Array:
	.word Menu_Maps_Factory_Main
	.word Menu_Maps_Factory_ArcadeMap
	.word Menu_Maps_Factory_BBlast
	.word Menu_Maps_Factory_Car
	.word Menu_Maps_Factory_Crusher
	.word Menu_Maps_Factory_PowerShed

.align
Menu_MapFactory_Functions:
	.word ActiveMenu_OpenMapWarper_FactoryMain // Open Main
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap

.align
Menu_MapFactory_Struct:
	.word Menu_MapFactory_Array // Text Array
	.word Menu_MapFactory_Functions // Function Array
	.byte 6 // Array Items
	.byte 1 // Parent Screen

.align
Menu_Maps_Factory_Portal:	
	.asciiz "FROM PORTAL"
Menu_Maps_Factory_ArcadeRoom:	
	.asciiz "ARCADE ROOM"
Menu_Maps_Factory_Block:	
	.asciiz "BLOCK TOWER"
Menu_Maps_Factory_Candy:	
	.asciiz "CANDY AREA"
Menu_Maps_Factory_Funky:	
	.asciiz "FUNKY ROOM"
Menu_Maps_Factory_Production:	
	.asciiz "PRODUCTION ROOM"
Menu_Maps_Factory_RnD:	
	.asciiz "RESEARCH AND DEV"
Menu_Maps_Factory_Snides:	
	.asciiz "SNIDES ROOM"
Menu_Maps_Factory_Storage:	
	.asciiz "STORAGE ROOM"

.align
Menu_MapFactoryMain_Array:
	.word Menu_Maps_Factory_Portal
	.word Menu_Maps_Factory_ArcadeRoom
	.word Menu_Maps_Factory_Block
	.word Menu_Maps_Factory_Candy
	.word Menu_Maps_Factory_Funky
	.word Menu_Maps_Factory_Production
	.word Menu_Maps_Factory_RnD
	.word Menu_Maps_Factory_Snides
	.word Menu_Maps_Factory_Storage

.align
Menu_MapFactoryMain_Functions:
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
Menu_MapFactoryMain_Struct:
	.word Menu_MapFactoryMain_Array // Text Array
	.word Menu_MapFactoryMain_Functions // Function Array
	.byte 9 // Array Items
	.byte 4 // Parent Screen