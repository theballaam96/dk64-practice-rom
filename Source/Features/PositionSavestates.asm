// Position Savestate
PositionSavestates:
	SW 		ra, @ReturnAddress
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, FinishPositionWrite
	NOP

	CheckLeft:
		LH 		a1, @NewlyPressedControllerInput
		ANDI 	a1, a1, @D_Left
		BEQZ 	a1, CheckRight
		NOP 
		B 		LoadPosition
		NOP

	CheckRight:
		LH 		a1, @NewlyPressedControllerInput
		ANDI 	a1, a1, @D_Right
		BEQZ 	a1, FinishPositionWrite
		NOP

	SavePosition:
		LW 		a1, @Player
		// Actual Positions
		LI 		a3, @SavedPositions
		LW 		a2, 0x7C (a1) // X Position
		SW 		a2, 0x0 (a3)
		LW 		a2, 0x80 (a1) // Y Position
		SW 		a2, 0x4 (a3)
		LW 		a2, 0x84 (a1) // Z Position
		SW 		a2, 0x8 (a3)
		// Stored Position
		LW 		a2, 0x4 (a1) // Rendering Params Pointer
		LW 		a0, 0x14 (a2) // Bone Array 1
		LI 		a3, @SavedStoredPosition1
		LH 		t9, 0x58 (a0)
		SH 		t9, 0x0 (a3)
		LH 		t9, 0x5A (a0)
		SH 		t9, 0x2 (a3)
		LH 		t9, 0x5C (a0)
		SH 		t9, 0x4 (a3)
		LW 		a0, 0x18 (a2) // Bone Array 2
		LI 		a3, @SavedStoredPosition2
		LH 		t9, 0x58 (a0)
		SH 		t9, 0x0 (a3)
		LH 		t9, 0x5A (a0)
		SH 		t9, 0x2 (a3)
		LH 		t9, 0x5C (a0)
		SH 		t9, 0x4 (a3)
		// Facing Angle
		LI 		a3, @SavedRotations
		LHU		a2, 0xE6 (a1)
		SH 		a2, 0x0 (a3)
		LHU		a2, 0xE8 (a1)
		SH 		a2, 0x2 (a3)
		// Speed/Accel
		LI 		a3, @SavedHVelocity
		LW 		a2, 0xB8 (a1)
		SW 		a2, 0x0 (a3)
		LI 		a3, @SavedVerticalSpeedComponents
		LW 		a2, 0xC0 (a1)
		SW 		a2, 0x0 (a3)
		LW 		a2, 0xC4 (a1)
		SW 		a2, 0x4 (a3)
		// Floor
		LI 		a3, @SavedFloor
		LW 		a2, 0xA4 (a1)
		SW 		a2, 0x0 (a3)
		// Saved Boolean
		LW 		a1, @CurrentMap
		SB 		a1, @SavedPositionMap
		// Play Bell SFX
		JAL 	CodedPlaySFX
		LI 		a0, @Bell
		B 		FinishPositionWrite
		NOP

	LoadPosition:
		LBU 	a1, @SavedPositionMap
		LW 		a3, @CurrentMap
		BNE 	a1, a3, FinishPositionWrite // If not equal to the last stored map, prevent write
		NOP
		SW 		r0, @StoredTime
		SB 		r0, @StoredTimerMode
		LW 		a1, @Player
		// Actual Positions
		LI 		a3, @SavedPositions
		LW 		a2, 0x0 (a3) // X
		SW 		a2, 0x7C (a1)
		LW 		a2, 0x4 (a3) // Y
		SW 		a2, 0x80 (a1)
		LW 		a2, 0x8 (a3) // Z
		SW 		a2, 0x84 (a1)
		LW 		a0, @CurrentMap
		LI 		a2, 0xCC
		BEQ 	a0, a2, LoadStoredPosition
		LI 		a2, 0xCD
		BEQ 	a0, a2, LoadStoredPosition
		LI 		a2, 0xCF
		BEQ 	a0, a2, LoadStoredPosition
		NOP
		LBU 	a0, @IsAutowalking
		BEQZ 	a0, LoadStoredPosition
		NOP
		LW 		a0, @AutowalkPointer
		BEQZ 	a0, LoadStoredPosition
		NOP
		SRA 	a2, a0, 16
		SLTIU 	a2, a2, 0x8000
		BNEZ 	a2, LoadStoredPosition
		NOP
		SRA 	a2, a0, 16
		SLTIU 	a2, a2, 0x8080
		BEQZ 	a2, LoadStoredPosition
		NOP
		LW 		a2, 0x0 (a3) // X
		MTC1 	a2, f0
		CVT.W.S f0, f0
		MFC1 	a2, f0
		SH 		a2, 0x12 (a0)
		LW 		a2, 0x8 (a3) // Z
		MTC1 	a2, f0
		CVT.W.S f0, f0
		MFC1 	a2, f0
		SH 		a2, 0x16 (a0)


	LoadStoredPosition:
		// Stored Position
		LBU 	a2, 0x63 (a1)
		ANDI 	a2, a2, 4
		BNEZ 	a2, LoadSkew
		LW 		a2, 0x4 (a1) // Rendering Params Pointer
		LW 		a0, 0x14 (a2) // Bone Array 1
		LI 		a3, @SavedStoredPosition1
		LH 		t9, 0x0 (a3)
		SH 		t9, 0x58 (a0)
		LH 		t9, 0x2 (a3)
		SH 		t9, 0x5A (a0)
		LH 		t9, 0x4 (a3)
		SH 		t9, 0x5C (a0)
		LW 		a0, 0x18 (a2) // Bone Array 2
		LI 		a3, @SavedStoredPosition2
		LH 		t9, 0x0 (a3)
		SH 		t9, 0x58 (a0)
		LH 		t9, 0x2 (a3)
		SH 		t9, 0x5A (a0)
		LH 		t9, 0x4 (a3)
		SH 		t9, 0x5C (a0)


	LoadSkew:
		// Facing & Skew Angle
		LI 		a3, @SavedRotations
		LHU		a2, 0x0 (a3)
		SH 		a2, 0xE6 (a1)
		LHU		a2, 0x2 (a3)
		SH 		a2, 0xE8 (a1)
		// Speed/Accel
		LI 		a3, @SavedHVelocity
		LW 		a2, 0x0 (a3)
		SW 		a2, 0xB8 (a1)
		LI 		a3, @SavedVerticalSpeedComponents
		LW 		a2, 0x0 (a3)
		SW 		a2, 0xC0 (a1)
		LW 		a2, 0x4 (a3)
		SW 		a2, 0xC4 (a1)
		// Floor
		LI 		a3, @SavedFloor
		LW 		a2, 0x0 (a3)
		SW 		a2, 0xA4 (a1)
		// Collision
		SW 		r0, 0x13C (a1)
		SB 		r0, 0x110 (a1)

	FinishPositionWrite:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP