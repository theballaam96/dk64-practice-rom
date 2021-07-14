UpdateFunkyKongGun:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @NewMenu_Position
	LI 		a1, @MovesBase
	LI 		a2, 0x5E
	MULTU 	a0, a2
	MFLO	a2
	ADDU 	a1, a1, a2
	LBU 	a3, 0x2 (a1) // Weapon Bitfield Value
	ANDI 	a3, a3, 1
	LI 		t0, 1
	BEQ 	a3, t0, UpdateFunkyKongGun_Write
	LI 		t3, -1
	LI 		t3, 1

	UpdateFunkyKongGun_Write:
		LBU 	t0, 0x2 (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x2 (a1)
		JAL 	ActiveMenu_OpenFunkyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateFunkyAmmoBelt:
	SW 		ra, @ReturnAddress5
	LI 		a1, @MovesBase
	LBU 	a3, 0x3 (a1) // Ammo Belt Value
	LI 		t0, 2
	BEQ 	a3, t0, UpdateFunkyAmmoBelt_Write
	LI 		t3, 0
	ADDIU 	t3, a3, 1

	UpdateFunkyAmmoBelt_Write:
		SB 		t3, 0x3 (a1) // DK
		SB 		t3, 0x61 (a1) // Diddy
		SB 		t3, 0xBF (a1) // Lanky
		SB 		t3, 0x11D (a1) // Tiny
		SB 		t3, 0x17B (a1) // Chunky
		JAL 	ActiveMenu_OpenFunkyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateFunkyHoming:
	SW 		ra, @ReturnAddress5
	LI 		a1, @MovesBase
	LBU 	a3, 0x2 (a1) // Homing Value
	ANDI 	a3, a3, 0x2
	LI 		t0, 2
	BEQ 	a3, t0, UpdateFunkyHoming_Write
	LI 		t3, -2
	LI 		t3, 2

	UpdateFunkyHoming_Write:
		// DK
		LBU 	t0, 0x2 (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x2 (a1)
		// Diddy
		LBU 	t0, 0x60 (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x60 (a1)
		// Lanky
		LBU 	t0, 0xBE (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0xBE (a1)
		// Tiny
		LBU 	t0, 0x11C (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x11C (a1)
		// Chunky
		LBU 	t0, 0x17A (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x17A (a1)
		JAL 	ActiveMenu_OpenFunkyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateFunkySniper:
	SW 		ra, @ReturnAddress5
	LI 		a1, @MovesBase
	LBU 	a3, 0x2 (a1) // Sniper Value
	ANDI 	a3, a3, 0x4
	LI 		t0, 4
	BEQ 	a3, t0, UpdateFunkySniper_Write
	LI 		t3, -4
	LI 		t3, 4

	UpdateFunkySniper_Write:
		// DK
		LBU 	t0, 0x2 (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x2 (a1)
		// Diddy
		LBU 	t0, 0x60 (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x60 (a1)
		// Lanky
		LBU 	t0, 0xBE (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0xBE (a1)
		// Tiny
		LBU 	t0, 0x11C (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x11C (a1)
		// Chunky
		LBU 	t0, 0x17A (a1)
		ADD 	t0, t0, t3
		SB 		t0, 0x17A (a1)
		JAL 	ActiveMenu_OpenFunkyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateFunkyMenu:
	LI 		a0, @MovesBase
	LA 		a3, Menu_Funky_Array
	// Ammo Belt
	LBU 	a1, 0x3 (a0) // Ammo Level
	LA 		a2, Menu_Funky_AmmoBelt_List
	SLL 	a1, a1, 2
	ADD 	a2, a2, a1
	LW 		t0, 0x0 (a2) // Ammo Text Pointer
	SW 		t0, 0x14 (a3)
	// Homing
	LBU 	a1, 0x2 (a0)
	ANDI 	a1, a1, 0x2
	LA 		a2, Menu_Funky_Homing_List
	SLL 	a1, a1, 1
	ADD 	a2, a2, a1
	LW 		t0, 0x0 (a2) // Homing Text Pointer
	SW 		t0, 0x18 (a3)
	// Sniper
	LBU 	a1, 0x2 (a0)
	ANDI 	a1, a1, 0x4
	LA 		a2, Menu_Funky_Sniper_List
	ADD 	a2, a2, a1
	LW 		t0, 0x0 (a2) // Sniper Text Pointer
	SW 		t0, 0x1C (a3)

	UpdateFunkyMenu_DefineLoop:
		LI 		a1, 5
		LA 		a2, Menu_Funky_Kong_Lists

	UpdateFunkyMenu_Loop:
		LBU 	t0, 0x2 (a0)
		ANDI 	t0, t0, 0x1
		LW 		t3, 0x0 (a2) // Kong Text Array
		SLL 	t0, t0, 2
		ADD 	t3, t3, t0
		LW 		t3, 0x0 (t3) // Move Text Pointer
		SW 		t3, 0x0 (a3)

	UpdateFunkyMenu_Increment:
		ADDIU 	a0, a0, 0x5E
		ADDI 	a1, a1, -1
		BEQZ 	a1, UpdateFunkyMenu_Finish	
		ADDIU 	a2, a2, 4
		B 		UpdateFunkyMenu_Loop
		ADDIU 	a3, a3, 4

	UpdateFunkyMenu_Finish:
		JR 		ra
		NOP

ActiveMenu_OpenFunkyMenu:
	SW 		ra, @ReturnAddress3
	LBU 	a0, @NewMenu_Screen
	LI 		a1, 48
	BEQ 	a0, a1, ActiveMenu_OpenFunkyMenu_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenFunkyMenu_Spawn:
		JAL 	ActiveMenu_ClearMenu
		NOP
		JAL 	UpdateFunkyMenu
		NOP
		LI 		a0, 48
		SB 		a0, @NewMenu_Screen	
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
Menu_Funky_AmmoBelt_None:
	.asciiz "AMMO BELT: 0"
Menu_Funky_AmmoBelt_Regular:
	.asciiz "AMMO BELT: 1"
Menu_Funky_AmmoBelt_Super:
	.asciiz "AMMO BELT: 2"
Menu_Funky_DK_None:
	.asciiz "DK: NO GUN"
Menu_Funky_DK_Gun:
	.asciiz "DK: COCONUT GUN"
Menu_Funky_Diddy_None:
	.asciiz "DIDDY: NO GUN"
Menu_Funky_Diddy_Gun:
	.asciiz "DIDDY: PEANUT POPGUNS"
Menu_Funky_Lanky_None:
	.asciiz "LANKY: NO GUN"
Menu_Funky_Lanky_Gun:
	.asciiz "LANKY: GRAPE SHOOTER"
Menu_Funky_Tiny_None:
	.asciiz "TINY: NO GUN"
Menu_Funky_Tiny_Gun:
	.asciiz "TINY: FEATHER BOW"
Menu_Funky_Chunky_None:
	.asciiz "CHUNKY: NO GUN"
Menu_Funky_Chunky_Gun:
	.asciiz "CHUNKY: PINEAPPLE LAUNCHER"
Menu_Funky_Homing_Disabled:
	.asciiz "HOMING AMMO: DISABLED"
Menu_Funky_Homing_Enabled:
	.asciiz "HOMING AMMO: ENABLED"
Menu_Funky_Sniper_Disabled:
	.asciiz "SNIPER SCOPE: DISABLED"
Menu_Funky_Sniper_Enabled:
	.asciiz "SNIPER SCOPE: ENABLED"

.align
Menu_Funky_AmmoBelt_List:
	.word Menu_Funky_AmmoBelt_None
	.word Menu_Funky_AmmoBelt_Regular
	.word Menu_Funky_AmmoBelt_Super
Menu_Funky_DK_List:
	.word Menu_Funky_DK_None
	.word Menu_Funky_DK_Gun
Menu_Funky_Diddy_List:
	.word Menu_Funky_Diddy_None
	.word Menu_Funky_Diddy_Gun
Menu_Funky_Lanky_List:
	.word Menu_Funky_Lanky_None
	.word Menu_Funky_Lanky_Gun
Menu_Funky_Tiny_List:
	.word Menu_Funky_Tiny_None
	.word Menu_Funky_Tiny_Gun
Menu_Funky_Chunky_List:
	.word Menu_Funky_Chunky_None
	.word Menu_Funky_Chunky_Gun
Menu_Funky_Homing_List:
	.word Menu_Funky_Homing_Disabled
	.word Menu_Funky_Homing_Enabled
Menu_Funky_Sniper_List:
	.word Menu_Funky_Sniper_Disabled
	.word Menu_Funky_Sniper_Enabled

.align
Menu_Funky_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word Menu_Return

.align
Menu_Funky_Functions:
	.word UpdateFunkyKongGun
	.word UpdateFunkyKongGun
	.word UpdateFunkyKongGun
	.word UpdateFunkyKongGun
	.word UpdateFunkyKongGun
	.word UpdateFunkyAmmoBelt
	.word UpdateFunkyHoming
	.word UpdateFunkySniper
	.word ActiveMenu_PreviousScreen

.align
Menu_Funky_Kong_Lists:
	.word Menu_Funky_DK_List
	.word Menu_Funky_Diddy_List
	.word Menu_Funky_Lanky_List
	.word Menu_Funky_Tiny_List
	.word Menu_Funky_Chunky_List

.align
Menu_Funky_Struct:
	.word Menu_Funky_Array // Text Array
	.word Menu_Funky_Functions // Function Array
	.byte 9 // Array Items
	.byte 31 // Parent Screen