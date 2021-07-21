MaxFile:
	SW 		ra, @ReturnAddress4
	LA 		a0, FileCompleteFlag
	JAL 	SetAllFlags
	NOP
	LI 		a0, @MovesBase
	LI 		a2, 0 // Counter
	LI 		a3, 5 // Kong Cap

	WriteMaxGBs:
		LI 		a1, 7
		SH 		a1, 0x42 (a0) // Japes
		SH 		a1, 0x44 (a0) // Aztec
		SH 		a1, 0x46 (a0) // Factory
		SH 		a1, 0x48 (a0) // Galleon
		SH 		a1, 0x4A (a0) // Fungi
		SH 		a1, 0x4C (a0) // Caves
		SH 		a1, 0x4E (a0) // Castle
		SH 		a1, 0x50 (a0) // Isles
		ADDIU 	a2, a2, 1 // Increment counter
		BEQ 	a3, a2, MaxFile_SFX
		NOP	
		B 		WriteMaxGBs
		ADDIU 	a0, a0, 0x5E // Next kong base

	MaxFile_SFX:
		JAL 	CodedPlaySFX
		LI 		a0, @FeedMe

	MaxFile_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP
