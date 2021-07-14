.align
Menu_Japes:
	.asciiz "JUNGLE JAPES"
Menu_Aztec:
	.asciiz "ANGRY AZTEC"
Menu_Factory:
	.asciiz "FRANTIC FACTORY"
Menu_Galleon:
	.asciiz "GLOOMY GALLEON"
Menu_Fungi:
	.asciiz "FUNGI FOREST"
Menu_Caves:
	.asciiz "CRYSTAL CAVES"
Menu_Castle:
	.asciiz "CREEPY CASTLE"
Menu_HelmAndKRool:
	.asciiz "HIDEOUT HELM AND K. ROOL"
Menu_Isles:
	.asciiz "DK ISLES"

.align
Menu_MapWarp_Array:
	.word Menu_Japes
	.word Menu_Aztec
	.word Menu_Factory
	.word Menu_Galleon
	.word Menu_Fungi
	.word Menu_Caves
	.word Menu_Castle
	.word Menu_HelmAndKRool
	.word Menu_Isles
	.word Menu_Return

.align
Menu_MapWarp_Functions:
	.word ActiveMenu_OpenMapWarper_Japes
	.word ActiveMenu_OpenMapWarper_Aztec
	.word ActiveMenu_OpenMapWarper_Factory
	.word ActiveMenu_OpenMapWarper_Galleon
	.word ActiveMenu_OpenMapWarper_Fungi
	.word ActiveMenu_OpenMapWarper_Caves
	.word ActiveMenu_OpenMapWarper_Castle
	.word ActiveMenu_OpenMapWarper_HelmKRool
	.word ActiveMenu_OpenMapWarper_Isles
	.word ActiveMenu_PreviousScreen

.align
Menu_MapWarp_Struct:
	.word Menu_MapWarp_Array // Text Array
	.word Menu_MapWarp_Functions // Function Array
	.byte 10 // Array Items
	.byte 0 // Parent Screen