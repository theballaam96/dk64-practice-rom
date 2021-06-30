ClearMoves:
	LI 		a0, 4
	LI 		a1, @MovesBase

	ClearMoves_WriteMoves:
		SH 		r0, 0x0 (a1) // Special | Slam Level | Guns | Ammo Belt
		SH 		r0, 0x2 (a1) // Gun Bitfield, Ammo belt
		SB 		r0, 0x4 (a1) // Instrument
		BEQZ 	a0, ClearMoves_WriteMoveFlags
		ADDI 	a0, a0, -1 // Decrement Value for next kong
		B 		ClearMoves_WriteMoves
		ADDIU 	a1, a1, 0x5E // Next kong base
	
	ClearMoves_WriteMoveFlags:
		SW 		ra, @ReturnAddress4
		LI 		a0, @CollectableBase
		// Melons
		LI 		a1, 1
		SB 		a1, 0xC(a0)
		// Health
		LI 		a1, 4
		SB 		a1, 0xB(a0)
		// How were your trading barrels this run?
		LA 		a0, MoveFlags
		JAL 	ClearAllFlags
		NOP
		LA 		a0, Menu_MovesMaster_CameraOff
		LA 		a1, Menu_MovesMaster_Array
		SW 		a0, 0x18 (a1)
		LBU 	a1, @NewMenuOpen
		BEQZ 	a1, ClearMoves_PlaySFX
		LI 		a0, 31
		LBU 	a1, @NewMenu_Screen
		BNE 	a0, a1, ClearMoves_PlaySFX
		NOP
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 31
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP

	ClearMoves_PlaySFX:
		// Sound Effect
		JAL 	CodedPlaySFX
		LI 		a0, @MatchingSound
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP