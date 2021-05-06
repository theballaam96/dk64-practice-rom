CompleteFile:
	SW 		ra, @ReturnAddress4
	LA 		a0, FileCompleteFlag
	JAL 	SetAllFlags
	NOP
	LI 		a0, @MovesBase
	LI 		a2, 0 // Counter
	LI 		a3, 6 // Tiny Isles Count
	LI 		t3, 3 // Tiny Index

	WriteGBs:
		LI 		a1, 5
		SH 		a1, 0x42 (a0) // Japes
		SH 		a1, 0x44 (a0) // Aztec
		SH 		a1, 0x46 (a0) // Factory
		SH 		a1, 0x48 (a0) // Galleon
		SH 		a1, 0x4A (a0) // Fungi
		SH 		a1, 0x4C (a0) // Caves
		SH 		a1, 0x4E (a0) // Castle
		SH 		a1, 0x50 (a0) // Isles
		BNE 	a2, t3, CompleteFile_Increment
		NOP
		SH 		a3, 0x50 (a0) // Tiny Isles

	CompleteFile_Increment:
		ADDIU 	a2, a2, 1 // Increment counter
		BEQ 	a1, a2, CompleteFile_Finish
		NOP	
		B 		WriteGBs
		ADDIU 	a0, a0, 0x5E // Next kong base

	CompleteFile_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

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
		BEQ 	a3, a2, MaxFile_Finish
		NOP	
		B 		WriteMaxGBs
		ADDIU 	a0, a0, 0x5E // Next kong base

	MaxFile_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

.align
FileCompleteFlag:
	.half 0x84 // Nintendo Coin
	.half 0x17B // Rareware Coin
	.half 0x1A // Key 1
	.half 0x4A // Key 2
	.half 0x8A // Key 3
	.half 0xA8 // Key 4
	.half 0xEC // Key 5
	.half 0x124 // Key 6
	.half 0x13D // Key 7
	.half 0x17C // Key 8
	// MEDALS
	.half 0x225 // Japes
	.half 0x226
	.half 0x227
	.half 0x228
	.half 0x229
	.half 0x22A // Aztec
	.half 0x22B
	.half 0x22C
	.half 0x22D
	.half 0x22E
	.half 0x22F // Factory
	.half 0x230
	.half 0x231
	.half 0x232
	.half 0x233
	.half 0x234 // Galleon
	.half 0x235
	.half 0x236
	.half 0x237
	.half 0x238
	.half 0x239 // Fungi
	.half 0x23A
	.half 0x23B
	.half 0x23C
	.half 0x23D
	.half 0x23E // Caves
	.half 0x23F
	.half 0x240
	.half 0x241
	.half 0x242
	.half 0x243 // Castle
	.half 0x244
	.half 0x245
	.half 0x246
	.half 0x247
	.half 0x248 // Helm
	.half 0x249
	.half 0x24A
	.half 0x24B
	.half 0x24C
	// Fairy
	.half 0x24D
	.half 0x24E
	.half 0x24F
	.half 0x250
	.half 0x251 // 5
	.half 0x252
	.half 0x253
	.half 0x254
	.half 0x255
	.half 0x256 // 10
	.half 0x257
	.half 0x258
	.half 0x259
	.half 0x25A
	.half 0x25B // 15
	.half 0x25C
	.half 0x25D
	.half 0x25E
	.half 0x25F
	.half 0x260 // 20
	// Crown
	.half 0x261
	.half 0x262
	.half 0x263
	.half 0x264
	.half 0x265 // 5
	.half 0x266
	.half 0x267
	.half 0x268
	.half 0x269
	.half 0x26A // 10
	.half 0 // Terminator