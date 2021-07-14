FormatTextForWatch:
	// a0 = header_pointer (Max length = 5 Chars)
	// a1 = value (u32)
	// a2 = format_type
		// 0 = int
		// 1 = float
	// a3 = header_length (u8)

	// Clear Watch Space
	SW 		ra, @ReturnAddress3
	LI 		t3, @WatchTextSpace
	SD 		r0, 0x00 (t3)
	SD 		r0, 0x08 (t3)
	SD 		r0, 0x10 (t3)
	SD 		r0, 0x18 (t3)
	SD 		r0, 0x20 (t3)
	SD 		r0, 0x28 (t3)
	ADDIU 	t9, a0, 0
	LI 		t8, 0

	FormatText_HeaderLoop:
		LBU 	t6, 0x0 (t9)
		BEQZ 	t6, FormatText_Delimiter
		SB 		t6, 0x0 (t3)
		ADDIU 	t9, t9, 1
		ADDIU 	t8, t8, 1
		B 		FormatText_HeaderLoop
		ADDIU 	t3, t3, 1

	FormatText_Delimiter:
		ADDIU 	a3, t8, 0
		LI 		t9, @WatchTextSpace
		ADD 	t9, t9, a3
		LI 		t6, 0x3A
		SB 		t6, 0x0 (t9)
		LI 		t6, 0x20
		SB 		t6, 0x1 (t9)
		BEQZ 	a2, FormatText_IsInt
		LI 		t8, 1
		LA 		t7, WatchFormat_FloatFormat_1
		BEQ 	a2, t8, FormatText_IsFloat
		NOP
		LI 		t8, 2
		LA 		t7, WatchFormat_FloatFormat_2
		BEQ 	a2, t8, FormatText_IsFloat
		NOP
		B 		FinishFormattingText
		NOP

	FormatText_IsInt:
		LI 		t8, @WatchTextSpace
		ADDIU 	t8, t8, 0x2F
		ADDIU 	t9, a1, 0 // Remaining
		LI 		t6, 0 // Length

		FormatText_IntLoop:
			LI 		t3, 10
			DDIVU 	t9, t3
			MFHI 	t3 // Remainder
			ADDIU 	t3, t3, 0x30 // ASCII
			SB 		t3, 0x0 (t8)
			ADDIU 	t6, t6, 1
			ADDI 	t8, t8, -1
			MFLO 	t9 // Copy Quotient to remaining
			BEQZ 	t9, FormatText_Int_Finish
			NOP
			SLTIU 	t3, t6, 8
			BEQZ 	t3, FormatText_Int_Finish
			NOP
			B 		FormatText_IntLoop
			NOP

		FormatText_Int_Finish:
			LI 		t3, @WatchTextSpace
			ADD 	t3, t3, a3
			ADDIU 	t3, t3, 2
			ADDIU 	t8, t8, 1
			
		FormatText_Int_FinishLoop:
			LBU 	t9, 0x0 (t8)
			SB 		t9, 0x0 (t3)
			ADDIU 	t3, t3, 1
			ADDIU 	t8, t8, 1
			ADDI 	t6, t6, -1
			BEQZ 	t6, FormatText_Int_FinishCap
			NOP
			B 		FormatText_Int_FinishLoop
			NOP

		FormatText_Int_FinishCap:
			B 		FinishFormattingText
			SB 		r0, 0x0 (t3)

	FormatText_IsFloat:
		LUI 	t6, 0x3F00 // 0.5 as float
		MTC1 	t6, f6 
		MTC1 	a1, f0
		SUB.S 	f0, f0, f6
		CVT.W.S f2, f0 // f2 = Int Portion
		CVT.S.W f4, f2
		ADD.S 	f0, f0, f6
		SUB.S 	f0, f0, f4 // f0 = Dec Portion
		LUI 	t6, 0x42C8 // 100 as float
		MTC1 	t6, f4
		MUL.S 	f0, f0, f4
		CVT.W.S f4, f0 // Dec as Int
		MFC1 	t6, f4 // Dec Portion
		MFC1 	t9, f2 // Int Portion
		LI 		a0, 100
		BNE 	t6, a0, FormatText_IsFloat_StringFormat
		NOP

		FormatText_IsFloat_Correct100Error:
			LI 		t6, 0
			ADDIU 	t9, t9, 1

		FormatText_IsFloat_StringFormat:
			LA 		a0, WatchFormat_TextSpace
			ADDIU 	a2, t9, 0
			ADDIU 	a3, t6, 0
			ADDIU 	a1, t7, 0
			SW 		t3, @VarStorage0
			JAL 	@StrFormat
			NOP
			LW 		t3, @VarStorage0
			ADDIU 	t3, t3, 1
			LA 		t6, WatchFormat_TextSpace

		FormatText_FloatLoop:
			LBU 	t9, 0x0 (t6)
			BEQZ 	t9, FinishFormattingText
			SB 		t9, 0x0 (t3)
			ADDIU 	t3, t3, 1
			B 		FormatText_FloatLoop
			ADDIU 	t6, t6, 1

	FinishFormattingText:
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
WatchFormat_FloatFormat_1:
	.asciiz "%3d.%02d"
WatchFormat_FloatFormat_2:
	.asciiz "%02d.%02d"
.align
WatchFormat_TextSpace:
	.space 0x10