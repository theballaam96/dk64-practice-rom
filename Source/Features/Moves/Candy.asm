UpdateCandyKongInstrument:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @NewMenu_Position
	LI 		a1, @MovesBase
	LI 		a2, 0x5E
	MULTU 	a0, a2
	MFLO	a2
	ADDU 	a1, a1, a2
	LBU 	a3, 0x4 (a1) // Instrument Bitfield Value
	ANDI 	a3, a3, 1
	LI 		t0, 1
	BEQ 	a3, t0, UpdateCandyKongInstrument_Write
	LI 		t3, -1
	LI 		t3, 1

	UpdateCandyKongInstrument_Write:
		LBU 	t0, 0x4 (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x4 (a1)
		JAL 	ActiveMenu_OpenCandyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateCandyMelons:
	SW 		ra, @ReturnAddress5
	LI 		a1, @CollectableBase
	LBU 	a3, 0xC (a1) // Melons
	LI 		t0, 3
	BEQ 	a3, t0, UpdateCandyMelons_Write
	LI 		t3, 1
	ADDIU 	t3, a3, 1

	UpdateCandyMelons_Write:
		SB 		t3, 0xC (a1) // Melons
		JAL 	ActiveMenu_OpenCandyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateCandyUpgrade:
	SW 		ra, @ReturnAddress5
	LI 		a1, @MovesBase
	LBU 	a3, 0x4 (a1) // Homing Value
	ANDI 	t0, a3, 0x2
	BEQZ 	t0, UpdateCandyUpgrade_Write
	LI 		t3, 2 // 0010
	ANDI 	t0, a3, 0x4
	BEQZ 	t0, UpdateCandyUpgrade_Write
	LI 		t3, 6 // 0110
	ANDI 	t0, a3, 0x8
	BEQZ 	t0, UpdateCandyUpgrade_Write
	LI 		t3, 14 // 1110
	LI 		t3, 0 // 0000

	UpdateCandyUpgrade_Write:
		// DK
		LBU 	t0, 0x4 (a1)
		ANDI 	t0, t0, 1
		OR 		t0, t0, t3
		SB 		t0, 0x4 (a1)
		// Diddy
		LBU 	t0, 0x62 (a1)
		ANDI 	t0, t0, 1
		OR 		t0, t0, t3
		SB 		t0, 0x62 (a1)
		// Lanky
		LBU 	t0, 0xC0 (a1)
		ANDI 	t0, t0, 1
		OR 		t0, t0, t3
		SB 		t0, 0xC0 (a1)
		// Tiny
		LBU 	t0, 0x11E (a1)
		ANDI 	t0, t0, 1
		OR 		t0, t0, t3
		SB 		t0, 0x11E (a1)
		// Chunky
		LBU 	t0, 0x17C (a1)
		ANDI 	t0, t0, 1
		OR 		t0, t0, t3
		SB 		t0, 0x17C (a1)
		JAL 	ActiveMenu_OpenCandyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateCandyMenu:
	LI 		a0, @CollectableBase
	LA 		a3, Menu_Candy_Array
	// Melons
	LBU 	a1, 0xC (a0) // Melon Count
	LA 		a2, Menu_Candy_Melons_List
	ADDI 	a1, a1, -1
	SLL 	a1, a1, 2
	ADD 	a2, a2, a1
	LW 		t0, 0x0 (a2) // Melon Text Pointer
	SW 		t0, 0x18 (a3)
	// Upgrade
	LI 		a0, @MovesBase
	LBU 	a1, 0x4 (a0)
	ANDI 	t0, a1, 2
	BEQZ 	t0, UpdateCandyMenu_WriteUpgrade
	LI 		t3, 0
	ANDI 	t0, a1, 4
	BEQZ 	t0, UpdateCandyMenu_WriteUpgrade
	LI 		t3, 4
	ANDI 	t0, a1, 8
	BEQZ 	t0, UpdateCandyMenu_WriteUpgrade
	LI 		t3, 8
	LI 		t3, 12

	UpdateCandyMenu_WriteUpgrade:
		LA 		a2, Menu_Candy_Upgrade_List
		ADD 	a2, a2, t3
		LW 		t0, 0x0 (a2) // Upgrade Text Pointer
		SW 		t0, 0x14 (a3)

	UpdateCandyMenu_DefineLoop:
		LI 		a1, 5
		LA 		a2, Menu_Candy_Kong_Lists

	UpdateCandyMenu_Loop:
		LBU 	t0, 0x4 (a0)
		ANDI 	t0, t0, 0x1
		LW 		t3, 0x0 (a2) // Kong Text Array
		SLL 	t0, t0, 2
		ADD 	t3, t3, t0
		LW 		t3, 0x0 (t3) // Move Text Pointer
		SW 		t3, 0x0 (a3)

	UpdateCandyMenu_Increment:
		ADDIU 	a0, a0, 0x5E
		ADDI 	a1, a1, -1
		BEQZ 	a1, UpdateCandyMenu_Finish	
		ADDIU 	a2, a2, 4
		B 		UpdateCandyMenu_Loop
		ADDIU 	a3, a3, 4

	UpdateCandyMenu_Finish:
		JR 		ra
		NOP

ActiveMenu_OpenCandyMenu:
	SW 		ra, @ReturnAddress3
	LBU 	a0, @NewMenu_Screen
	LI 		a1, 49
	BEQ 	a0, a1, ActiveMenu_OpenCandyMenu_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenCandyMenu_Spawn:
		JAL 	ActiveMenu_ClearMenu
		NOP
		JAL 	UpdateCandyMenu
		NOP
		LI 		a0, 49
		SB 		a0, @NewMenu_Screen	
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
Menu_Candy_Melons_Level1:
	.asciiz "MELONS: 1"
Menu_Candy_Melons_Level2:
	.asciiz "MELONS: 2"
Menu_Candy_Melons_Level3:
	.asciiz "MELONS: 3"
Menu_Candy_DK_None:
	.asciiz "DK: NO INSTRUMENT"
Menu_Candy_DK_Instrument:
	.asciiz "DK: BONGO BLAST"
Menu_Candy_Diddy_None:
	.asciiz "DIDDY: NO INSTRUMENT"
Menu_Candy_Diddy_Instrument:
	.asciiz "DIDDY: GUITAR GAZUMP"
Menu_Candy_Lanky_None:
	.asciiz "LANKY: NO INSTRUMENT"
Menu_Candy_Lanky_Instrument:
	.asciiz "LANKY: TROMBONE TREMOR"
Menu_Candy_Tiny_None:
	.asciiz "TINY: NO INSTRUMENT"
Menu_Candy_Tiny_Instrument:
	.asciiz "TINY: SAXOPHONE SLAM"
Menu_Candy_Chunky_None:
	.asciiz "CHUNKY: NO INSTRUMENT"
Menu_Candy_Chunky_Instrument:
	.asciiz "CHUNKY: TRIANGLE TRAMPLE"
Menu_Candy_Upgrade_Level0:
	.asciiz "UPGRADE LEVEL: 0"
Menu_Candy_Upgrade_Level1:
	.asciiz "UPGRADE LEVEL: 1"
Menu_Candy_Upgrade_Level2:
	.asciiz "UPGRADE LEVEL: 2"
Menu_Candy_Upgrade_Level3:
	.asciiz "UPGRADE LEVEL: 3"

.align
Menu_Candy_Melons_List:
	.word Menu_Candy_Melons_Level1
	.word Menu_Candy_Melons_Level2
	.word Menu_Candy_Melons_Level3
Menu_Candy_DK_List:
	.word Menu_Candy_DK_None
	.word Menu_Candy_DK_Instrument
Menu_Candy_Diddy_List:
	.word Menu_Candy_Diddy_None
	.word Menu_Candy_Diddy_Instrument
Menu_Candy_Lanky_List:
	.word Menu_Candy_Lanky_None
	.word Menu_Candy_Lanky_Instrument
Menu_Candy_Tiny_List:
	.word Menu_Candy_Tiny_None
	.word Menu_Candy_Tiny_Instrument
Menu_Candy_Chunky_List:
	.word Menu_Candy_Chunky_None
	.word Menu_Candy_Chunky_Instrument
Menu_Candy_Upgrade_List:
	.word Menu_Candy_Upgrade_Level0
	.word Menu_Candy_Upgrade_Level1
	.word Menu_Candy_Upgrade_Level2
	.word Menu_Candy_Upgrade_Level3

.align
Menu_Candy_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_Candy_Functions:
	.word UpdateCandyKongInstrument
	.word UpdateCandyKongInstrument
	.word UpdateCandyKongInstrument
	.word UpdateCandyKongInstrument
	.word UpdateCandyKongInstrument
	.word UpdateCandyUpgrade
	.word UpdateCandyMelons
	.word ActiveMenu_PreviousScreen

.align
Menu_Candy_Kong_Lists:
	.word Menu_Candy_DK_List
	.word Menu_Candy_Diddy_List
	.word Menu_Candy_Lanky_List
	.word Menu_Candy_Tiny_List
	.word Menu_Candy_Chunky_List

.align
Menu_Candy_Struct:
	.word Menu_Candy_Array // Text Array
	.word Menu_Candy_Functions // Function Array
	.byte 8 // Array Items
	.byte 31 // Parent Screen