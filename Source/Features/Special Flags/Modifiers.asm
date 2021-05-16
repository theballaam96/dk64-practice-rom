.align
Menu_Flags_ModifiersFlags:
	.half 0x6F // Prod Room
	.half 0xA0 // Galleon Water
	.half 0x9C // Galleon Ship
	.half 0xCE // Fungi Nighttime
	.half 0x12C // Giant Kosha
	.half 0x302 // BoM Off

.align
Menu_Flags_ModifiersFlagType:
	.byte 0 // Prod Room
	.byte 0 // Galleon Water
	.byte 0 // Galleon Ship
	.byte 0 // Nighttime
	.byte 0 // Giant Kosha
	.byte 0 // BoM off

.align
Menu_Flags_ModifiersStruct:
	.word Menu_Flags_ModifiersFlags ; Flags
	.word Menu_Flags_ModifiersFlagType ; Flag Type
	.word Menu_Flags_Modifiers_TextStruct ; Text Information
	.byte 44 ; Associated Screen
	.byte 6 ; Flag Count

.align
Menu_Flags_Modifiers_ProdRoom_Set:
	.asciiz "PRODUCTION ROOM - ON"
Menu_Flags_Modifiers_ProdRoom_Clear:
	.asciiz "PRODUCTION ROOM - OFF"
Menu_Flags_Modifiers_GalleonWater_Set:
	.asciiz "GALLEON WATER LEVEL - RAISED"
Menu_Flags_Modifiers_GalleonWater_Clear:
	.asciiz "GALLEON WATER LEVEL - LOWERED"
Menu_Flags_Modifiers_GalleonShip_Set:
	.asciiz "GALLEON SHIP - SPAWNED"
Menu_Flags_Modifiers_GalleonShip_Clear:
	.asciiz "GALLEON SHIP - NOT SPAWNED"
Menu_Flags_Modifiers_FungiNighttime_Set:
	.asciiz "FUNGI TIME OF DAY - NIGHT"
Menu_Flags_Modifiers_FungiNighttime_Clear:
	.asciiz "FUNGI TIME OF DAY - DAY"
Menu_Flags_Modifiers_KoshaDead_Set:
	.asciiz "GIANT KOSHA - DEAD"
Menu_Flags_Modifiers_KoshaDead_Clear:
	.asciiz "GIANT KOSHA - ALIVE"
Menu_Flags_Modifiers_BoMOff_Set:
	.asciiz "BLAST O MATIC - OFF"
Menu_Flags_Modifiers_BoMOff_Clear:
	.asciiz "BLAST O MATIC - ON"

.align
Menu_Flags_Modifiers_ProdRoom_Struct:
	.word Menu_Flags_Modifiers_ProdRoom_Clear
	.word Menu_Flags_Modifiers_ProdRoom_Set
Menu_Flags_Modifiers_GalleonWater_Struct:
	.word Menu_Flags_Modifiers_GalleonWater_Clear
	.word Menu_Flags_Modifiers_GalleonWater_Set
Menu_Flags_Modifiers_GalleonShip_Struct:
	.word Menu_Flags_Modifiers_GalleonShip_Clear
	.word Menu_Flags_Modifiers_GalleonShip_Set
Menu_Flags_Modifiers_FungiNighttime_Struct:
	.word Menu_Flags_Modifiers_FungiNighttime_Clear
	.word Menu_Flags_Modifiers_FungiNighttime_Set
Menu_Flags_Modifiers_KoshaDead_Struct:
	.word Menu_Flags_Modifiers_KoshaDead_Clear
	.word Menu_Flags_Modifiers_KoshaDead_Set
Menu_Flags_Modifiers_BoMOff_Struct:
	.word Menu_Flags_Modifiers_BoMOff_Clear
	.word Menu_Flags_Modifiers_BoMOff_Set

.align
Menu_Flags_Modifiers_TextStruct:
	.word Menu_Flags_Modifiers_ProdRoom_Struct
	.word Menu_Flags_Modifiers_GalleonWater_Struct
	.word Menu_Flags_Modifiers_GalleonShip_Struct
	.word Menu_Flags_Modifiers_FungiNighttime_Struct
	.word Menu_Flags_Modifiers_KoshaDead_Struct
	.word Menu_Flags_Modifiers_BoMOff_Struct

.align
Menu_Flags_Modifiers_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Flags_Modifiers_Functions:
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag
	.word ActiveMenu_ToggleFlag

.align
Menu_Flags_Modifiers_Struct:
	.word Menu_Flags_Modifiers_Array // Text Array
	.word Menu_Flags_Modifiers_Functions // Function Array
	.byte 6 // Array Items
	.byte 36 // Parent Screen

.align
ActiveMenu_OpenFlagMenu_Modifiers:
	SW 		ra, @ReturnAddress5
	LI 		a1, 1
	JAL 	ActiveMenu_OpenFlagsSubmenu
	LI 		a0, 44
	LW 		ra, @ReturnAddress5
	JR 		ra
	NOP