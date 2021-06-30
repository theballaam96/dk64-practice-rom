VariableDisplay:
	SW 		ra, @ReturnAddress
	LBU 	a0, @VariableDisplayOn
	BEQZ 	a0, HandleKRoolTimer
	LUI 	a3, 0x42FA // K Rool Timer X (125)
	// Change Helm Timer Format
	LI 		a2, 8
	BEQ 	a0, a2, VDispInput
	LI 		a1, 7
	BEQ 	a0, a1, VDispAngle
	LI 		a2, @MovementStateIndex
	BEQ 	a0, a2, UpdateVDispText // Movement
	LI 		a1, 5
	BEQ 	a0, a1, VDispGKTimer
	LI 		a2, 4
	BEQ 	a0, a2, VDispTimer
	LI 		a1, 3
	BEQ 	a0, a1, VDispSpd
	LI 		a2, 2
	BEQ 	a0, a2, VDispCLag
	NOP

	VDispLag:
		LI 		a1, @WatchTextSpace
		JAL 	ConvertCodePointerForWatchText
		NOP
		LA 		a0, Watch_Header_Lag
		LW 		a1, @StoredLag // Value
		LI 		a2, 0 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 3 // Header Length
		LI 		a0, 0
		B 		UpdateVDispText
		LI 		a1, 0

	VDispSpd:
		LI 		a1, @WatchTextSpace
		JAL 	ConvertCodePointerForWatchText
		NOP
		LW 		a0, @Player // Player pointer
		BEQZ 	a0, VDispSpdFormat // Player pointer null
		LI 		a1, 0
		LW 		a1, 0xB8 (a0) // Grab velocity hex
	
	VDispSpdFormat:
		LA 		a0, Watch_Header_Speed
		// a1 carried from prior
		LI 		a2, 1 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 5 // Header Length
		LI 		a0, 0
		B 		UpdateVDispText
		LI 		a1, 0

	VDispCLag:
		LI 		a1, @WatchTextSpace
		JAL 	ConvertCodePointerForWatchText
		NOP
		LW 		a1, @StoredLag
		LW 		a2, @CumulativeLag
		ADD 	a1, a1, a2 // Lag + Old Lag
		SW 		a1, @CumulativeLag
		LA 		a0, Watch_Header_CumulativeLag
		// a1 carried from prior
		LI 		a2, 0 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 14 // Header Length
		LI 		a1, 0
		LI 		a0, 0
		B 		UpdateVDispText
		LI 		a2, 0 // ""

	VDispTimer:
		LI 		a1, @WatchTextSpace
		JAL 	ConvertCodePointerForWatchText
		NOP
		LWU 	a1, @TimerAfterReduction
		MTC1 	a1, f0
		LUI 	t6, 0x4270 // 60 as float
		MTC1 	t6, f2
		CVT.S.W f4, f0
		DIV.S 	f0, f4, f2
		MFC1 	a1, f0
		LA 		a0, Watch_Header_Timer
		LI 		a2, 1 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 5 // Header Length
		LI 		a1, 0
		LI 		a0, 0
		B 		UpdateVDispText
		NOP

	VDispGKTimer:
		LW 		a0, @CurrentMap
		LI 		a3, 0x48
		BNE 	a0, a3, VDispGKTimer_NotCaves
		NOP

		VDispGKTimer_IsCaves:
			LI 		a1, @WatchTextSpace
			LH 		a1, @GiantKoshaTimerValue
			LA 		a0, Watch_Header_GKTimer
			LI 		a2, 0 // Display Type
			JAL 	FormatTextForWatch
			LI 		a3, 11 // Header Length
			LH 		a1, @GiantKoshaTimerValue
			SLTIU 	a2, a1, 51
			BNEZ 	a2, VDispGKTimer_IsCaves_Tantrum
			SLTIU 	a3, a1, 101
			BNEZ 	a3, VDispGKTimer_IsCaves_Music
			SLTIU 	a2, a1, 201
			BNEZ 	a2, VDispGKTimer_IsCaves_CancelRange
			NOP
			LW 		a0, @Player
			BEQZ 	a0, UpdateVDispText
			NOP
			LH 		a1, 0x12C (a0)
			BEQZ 	a1, VDispGKTimer_IsCaves_Frozen
			LI 		a2, 2
			BEQ 	a1, a2, VDispGKTimer_IsCaves_Frozen
			LI 		a3, 3
			BEQ 	a1, a3, VDispGKTimer_IsCaves_Frozen
			LI 		a2, 7
			BEQ 	a1, a2, VDispGKTimer_IsCaves_Frozen
			NOP
			LI 		a0, 0xFFFFFF
			JAL 	Watch_ColourWatch
			NOP
			B 		UpdateVDispText
			NOP

		VDispGKTimer_IsCaves_Frozen:
			LI 		a0, @KoshaRGB_Frozen
			JAL 	Watch_ColourWatch
			NOP
			B 		UpdateVDispText
			NOP

		VDispGKTimer_IsCaves_CancelRange:
			LI 		a0, @KoshaRGB_CancelRange
			JAL 	Watch_ColourWatch
			NOP
			B 		UpdateVDispText
			NOP

		VDispGKTimer_IsCaves_Music:
			LI 		a0, @KoshaRGB_Music
			JAL 	Watch_ColourWatch
			NOP
			B 		UpdateVDispText
			NOP

		VDispGKTimer_IsCaves_Tantrum:
			LI 		a0, @KoshaRGB_Tantrum
			JAL 	Watch_ColourWatch
			NOP
			B 		UpdateVDispText
			NOP

		VDispGKTimer_NotCaves:
			LA 		a0, OutOfCavesText
			JAL 	CopyTextToWatch
			NOP
			LI 		a0, 0xFFFFFF
			JAL 	Watch_ColourWatch
			NOP
			B 		UpdateVDispText
			NOP

	VDispAngle:
		LW 		a0, @Player
		BEQZ 	a0, VDispAngle_Text
		LI 		a1, 0
		LH 		a1, 0xE6 (a0)
		SLTIU 	t0, a1, 4096
		MTC1 	a1, f6
		CVT.S.W f0, f6 // f0 = angle
		LUI		t6, 0x4580
		MTC1 	t6, f2 // 4096
		LUI 	t6, 0x43B4
		MTC1 	t6, f4 // 360
		DIV.S 	f0, f0, f2
		MUL.S 	f0, f0, f4
		MFC1 	a1, f0
		LI 		a0, 0xFFFFFF
		SW 		a1, @VarStorage0
		BNEZ 	t0, VDispAngle_TextColourWrite
		NOP
		LI 		a0, @KoshaRGB_Frozen


	VDispAngle_TextColourWrite:
		JAL 	Watch_ColourWatch
		NOP
		LW 		a1, @VarStorage0

	VDispAngle_Text:
		LA 		a0, Watch_Header_Angle
		LI 		a2, 1 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 5 // Header Length
		LI 		a1, 0
		LI 		a0, 0
		B 		UpdateVDispText
		LI 		a2, 0

	VDispInput:
		JAL 	Input_HandleString
		NOP
		B 		UpdateVDispText
		NOP

	UpdateVDispText:
		LUI 	a3, 0x435C // K Rool Timer X (220)

	HandleKRoolTimer:
		// K Rool Check
		LW 		a0, @CurrentMap
		SLTI 	a1, a0, 0xCB
		BNEZ 	a1, FinishVDisplay
		SLTI 	a2, a0, 0xD0
		BEQZ 	a2, FinishVDisplay
		NOP
		LW 		a0, @Player
		BEQZ 	a0, FinishVDisplay
		LW 		a1, 0x328(a0)
		BEQZ 	a1, FinishVDisplay
		NOP
		SW 		a3, 0x7C(a1)

	FinishVDisplay:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

.align
Watch_Header_Lag:
	.asciiz "LAG"
Watch_Header_CumulativeLag:
	.asciiz "CUMULATIVE LAG"
Watch_Header_Speed:
	.asciiz "SPEED"
Watch_Header_Timer:
	.asciiz "TIMER"
Watch_Header_GKTimer:
	.asciiz "KOSHA TIMER"
Watch_Header_Angle:
	.asciiz "ANGLE"