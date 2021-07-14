CalculateISGTime:
	SW 		ra, @ReturnAddress4
	JAL 	GetISGTimer
	NOP
	LBU 	a1, @ISGActive
	BEQZ 	a1, CalculateISGTime_Format
	LI 		a1, 0 // Default time when ISG not on
	LW 		a1, @ISGTimer
	ADDIU 	a1, a1, 200

	CalculateISGTime_Format:
		LI 		a2, 6000
		DIVU 	a1, a2
		MFLO 	a2 // Minutes
		MFHI 	a1 // Seconds
		MTC1 	a1, f0
		CVT.S.W f0, f0
		LUI 	a3, 0x42C8 // 100
		MTC1 	a3, f2
		DIV.S 	f0, f0, f2
		MFC1 	a3, f0
		SW 		a3, @VarStorage0
		LA 		a0, ISGWatch_Header_Space
		LA 		a1, ISGWatch_Header_Format
		JAL 	@StrFormat
		NOP
		LW 		a1, @VarStorage0
		LA 		a0, ISGWatch_Header_Space
		LI 		a2, 2 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 11 // Header Length
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

GetISGTimer:
	SW 		ra, @ReturnAddress3
	LBU	 	a1, @ISGActive
	SW 		r0, @ISGTimer
	BEQZ 	a1, GetISGTimer_Finish
	NOP
	JAL 	@GetTimestamp
	NOP
	LI 		t6, @ISGTimestamp
	LW 		t7, 0x4 (t6)
	LW 		t6, 0x0 (t6)
	LI 		a2, 0
	SLTU 	at, v1, t7
	SUBU 	a0, v0, t6
	SUBU 	a0, a0, at
	LI 		a3, 0x40
	JAL 	@Multiply
	SUBU 	a1, v1, t7
	OR 		a0, v0, r0
	OR 		a1, v1, r0
	LI 		a2, 0
	JAL 	@ConvertTimestamp
	LI 		a3, 3000
	OR 		a0, v0, r0
	OR 		a1, v1, r0
	LI 		a2, 0
	JAL 	@ConvertTimestamp
	LI 		a3, 10000
	SW 		v1, @ISGTimer

	GetISGTimer_Finish:
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ColourISGTimer:
	SW 		ra, @ReturnAddress4
	LI 		a0, 0xFFFFFF // Default Colour
	LBU 	a1, @ISGActive
	BEQZ 	a1, ColourISGTimer_Finish
	NOP
	LW 		t6, @ISGTimer
	LI 		t3, @ISGFadeoutArray
	SB 		r0, @ISGStage
	LI 		t0, 0

	ColourISGTimer_Loop:
		LwU 	t8, 0x0 (t3)
		SLTU 	t8, t6, t8
		BEQZ 	t8, ColourISGTimer_Increment
		NOP

	ColourISGTimer_SetStage:
		SB 		t0, @ISGStage
		BEQZ 	t0, ColourISGTimer_DetectFade
		NOP
		LBU 	a1, @ISGPreviousFadeout
		BEQ 	t0, a1, ColourISGTimer_Finish
		NOP
		LI 		a0, @ISGRGB_FadeoutPending
		B  		ColourISGTimer_DetectFade
		NOP

	ColourISGTimer_Increment:
		ADDIU 	t0, t0, 1
		LI 		t8, 7
		BEQ 	t0, t8, ColourISGTimer_Finish
		ADDIU 	t3, t3, 8
		B 		ColourISGTimer_Loop
		NOP

	ColourISGTimer_DetectFade:
		LBU 	t8, 0x4 (t3) // Expected Destination Map
		LW 		t0, @DestMap
		BNE 	t0, t8, ColourISGTimer_Finish
		NOP
		LI 		a0, @ISGRGB_Fading

	ColourISGTimer_Finish:
		JAL 	Watch_ColourWatch
		NOP
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP
		
.align
ISGWatch_Header_Format:
	.asciiz "ISG TIME: %1d"
ISGWatch_Header_Space:
	.space 0x10