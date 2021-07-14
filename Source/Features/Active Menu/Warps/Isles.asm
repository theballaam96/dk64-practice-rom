.align
Maps_Isles_DestMap:
	.byte 0x0 // Null for main
	.byte 0xBD
	.byte 0x61
	.byte 0x0 // Null for lobbies
	.byte 0xC3
	.byte 0xB0
	.byte 0xAB

.align
Maps_Isles_DestExit:
	.byte 0x0 // Null for main
	.byte 0
	.byte 0
	.byte 0x0 // Null for lobbies
	.byte 0
	.byte 1
	.byte 2

.align
Maps_Isles_Struct:
	.word Maps_Isles_DestMap // Map
	.word Maps_Isles_DestExit // Exit
	.byte 10 // Screen

.align
Maps_IslesMain_DestMap:
	.byte 0x22
	.byte 0x22
	.byte 0x22
	.byte 0x22
	.byte 0x22

.align
Maps_IslesMain_DestExit:
	.byte 0x0
	.byte 0x8
	.byte 0xC
	.byte 0x4
	.byte 0x6

.align
Maps_IslesMain_Struct:
	.word Maps_IslesMain_DestMap // Map
	.word Maps_IslesMain_DestExit // Exit
	.byte 25 // Screen

.align
Maps_IslesLobbies_DestMap:
	.byte 0xA9
	.byte 0xAD
	.byte 0xAF
	.byte 0xAE
	.byte 0xB2
	.byte 0xC2
	.byte 0xC1
	.byte 0xAA

.align
Maps_IslesLobbies_DestExit:
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_IslesLobbies_Struct:
	.word Maps_IslesLobbies_DestMap // Map
	.word Maps_IslesLobbies_DestExit // Exit
	.byte 26 // Screen

.align
Menu_Maps_Isles_Overworld:	
	.asciiz "OVERWORLD"
Menu_Maps_Isles_BFIInterior:	
	.asciiz "BANANA FAIRY ISLAND"
Menu_Maps_Isles_KLumsy:	
	.asciiz "K. LUMSY"
Menu_Maps_Isles_Lobbies:	
	.asciiz "LOBBIES"
Menu_Maps_Isles_Snides:	
	.asciiz "SNIDE'S ROOM"
Menu_Maps_Isles_TGrounds:	
	.asciiz "TRAINING GROUNDS"
Menu_Maps_Isles_Treehouse:	
	.asciiz "TREEHOUSE"

.align
Menu_MapIsles_Array:
	.word Menu_Maps_Isles_Overworld
	.word Menu_Maps_Isles_BFIInterior
	.word Menu_Maps_Isles_KLumsy
	.word Menu_Maps_Isles_Lobbies
	.word Menu_Maps_Isles_Snides
	.word Menu_Maps_Isles_TGrounds
	.word Menu_Maps_Isles_Treehouse
	.word Menu_Return

.align
Menu_MapIsles_Functions:
	.word ActiveMenu_OpenMapWarper_IslesMain // Open Main
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_OpenMapWarper_IslesLobbies // Open Lobbies
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapIsles_Struct:
	.word Menu_MapIsles_Array // Text Array
	.word Menu_MapIsles_Functions // Function Array
	.byte 8 // Array Items
	.byte 1 // Parent Screen

.align
Menu_Maps_Isles_Escape:	
	.asciiz "ESCAPE"
Menu_Maps_Isles_BFIExterior:	
	.asciiz "BFI"
Menu_Maps_Isles_W3:	
	.asciiz "WARP 3"
Menu_Maps_Isles_KrocIsle:	
	.asciiz "KROC ISLE"
Menu_Maps_Isles_TopOfDKIsle:	
	.asciiz "TOP OF DK ISLE"

.align
Menu_MapIslesMain_Array:
	.word Menu_Maps_Isles_Escape
	.word Menu_Maps_Isles_BFIExterior
	.word Menu_Maps_Isles_W3
	.word Menu_Maps_Isles_KrocIsle
	.word Menu_Maps_Isles_TopOfDKIsle
	.word Menu_Return

.align
Menu_MapIslesMain_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapIslesMain_Struct:
	.word Menu_MapIslesMain_Array // Text Array
	.word Menu_MapIslesMain_Functions // Function Array
	.byte 6 // Array Items
	.byte 10 // Parent Screen

.align
Menu_Maps_Isles_LobbyJapes:	
	.asciiz "JUNGLE JAPES LOBBY"
Menu_Maps_Isles_LobbyAztec:	
	.asciiz "ANGRY AZTEC LOBBY"
Menu_Maps_Isles_LobbyFactory:	
	.asciiz "FRANTIC FACTORY LOBBY"
Menu_Maps_Isles_LobbyGalleon:	
	.asciiz "GLOOMY GALLEON LOBBY"
Menu_Maps_Isles_LobbyFungi:	
	.asciiz "FUNGI FOREST LOBBY"
Menu_Maps_Isles_LobbyCaves:	
	.asciiz "CRYSTAL CAVES LOBBY"
Menu_Maps_Isles_LobbyCastle:	
	.asciiz "CREEPY CASTLE LOBBY"
Menu_Maps_Isles_LobbyHelm:	
	.asciiz "HIDEOUT HELM LOBBY"

.align
Menu_MapIslesLobbies_Array:
	.word Menu_Maps_Isles_LobbyJapes
	.word Menu_Maps_Isles_LobbyAztec
	.word Menu_Maps_Isles_LobbyFactory
	.word Menu_Maps_Isles_LobbyGalleon
	.word Menu_Maps_Isles_LobbyFungi
	.word Menu_Maps_Isles_LobbyCaves
	.word Menu_Maps_Isles_LobbyCastle
	.word Menu_Maps_Isles_LobbyHelm
	.word Menu_Return

.align
Menu_MapIslesLobbies_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapIslesLobbies_Struct:
	.word Menu_MapIslesLobbies_Array // Text Array
	.word Menu_MapIslesLobbies_Functions // Function Array
	.byte 9 // Array Items
	.byte 10 // Parent Screen