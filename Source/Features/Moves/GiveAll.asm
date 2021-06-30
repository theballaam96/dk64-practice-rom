GiveMoves:
	LI 		a0, 4
	LI 		a1, @MovesBase

	GiveMoves_WriteMoves:
		LI 		t3, 0x0303
		SH 		t3, 0x0 (a1) // Special | Slam Level | Guns | Ammo Belt
		LI 		t3, 0x0702
		SH 		t3, 0x2 (a1) // Gun Bitfield, Ammo belt
		LI 		t3, 15
		SB 		t3, 0x4 (a1) // Instrument
		BEQZ 	a0, GiveMoves_WriteMoveFlags
		ADDI 	a0, a0, -1 // Decrement Value for next kong
		B 		GiveMoves_WriteMoves
		ADDIU 	a1, a1, 0x5E // Next kong base
	
	GiveMoves_WriteMoveFlags:
		SW 		ra, @ReturnAddress4
		LI 		a0, @CollectableBase
		// Melons
		LI 		a1, 3
		SB 		a1, 0xC(a0)
		// Health
		LI 		a1, 12
		SB 		a1, 0xB(a0)
		// How were your trading barrels this run?
		LA 		a0, MoveFlags
		JAL 	SetAllFlags
		NOP
		LA 		a0, Menu_MovesMaster_CameraOn
		LA 		a1, Menu_MovesMaster_Array
		SW 		a0, 0x18 (a1)
		LBU 	a1, @NewMenuOpen
		BEQZ 	a1, GiveMoves_PlaySFX
		LI 		a0, 31
		LBU 	a1, @NewMenu_Screen
		BNE 	a0, a1, GiveMoves_PlaySFX
		NOP
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 31
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP

	GiveMoves_PlaySFX:
		// Sound Effect
		JAL 	CodedPlaySFX
		LI 		a0, @Potion
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP