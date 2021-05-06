FormatTextForWatch:
	// a0 = header_pointer (Max length = 5 Chars)
	// a1 = value (u32)
	// a2 = format_type
		// 0 = int
	// a3 = header_length (u8)

	// Clear Watch Space
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
		SW 		t6, @VarStorage1
		SW 		t9, @VarStorage0
		LI 		t8, @WatchTextSpace
		ADDIU 	t8, t8, 0x2C
		// t9 = remaining
		LI 		t6, 0 // Length

		FormatText_FloatLoop_Int:
			LI 		t3, 10
			DDIVU 	t9, t3
			MFHI 	t3 // Remainder
			ADDIU 	t3, t3, 0x30 // ASCII
			SB 		t3, 0x0 (t8)
			ADDIU 	t6, t6, 1
			ADDI 	t8, t8, -1
			MFLO 	t9 // Copy Quotient to remaining
			BEQZ 	t9, FormatText_FloatInt_Finish
			NOP
			SLTIU 	t3, t6, 5
			BEQZ 	t3, FormatText_FloatInt_Finish
			NOP
			B 		FormatText_FloatLoop_Int
			NOP

		FormatText_FloatInt_Finish:
			LI 		t8, @WatchTextSpace
			LI 		t9, 0x2E // "."
			SB 		t9, 0xD (t8)
			LW 		t9, @VarStorage1
			LI 		t3, 10
			DDIVU 	t9, t3
			MFLO 	t3 // 10th
			LI 		t9, 10
			BEQ 	t3, t9, FormatText_FloatInt_99
			ADDIU 	t3, t3, 0x30
			SB 		t3, 0xE (t8)
			MFHI 	t3 // 100th
			ADDIU 	t3, t3, 0x30
			B 		FormatText_FloatInt_GetRewriteAddresses
			SB 		t3, 0xF (t8)

		FormatText_FloatInt_99:
			LI 		t3, 0x39
			SB 		t3, 0xE (t8)
			SB 		t3, 0xF (t8)
			
		FormatText_FloatInt_GetRewriteAddresses:
			ADDIU 	t6, t6, 3 // Length
			LI 		t3, @WatchTextSpace
			ADD 	t3, t3, a3
			ADDIU 	t9, t3, 2 // Start of text area to write
			LI 		t3, @WatchTextSpace
			LI 		t8, 0x30
			ADD 	t8, t8, t3
			SUBU 	t8, t8, t6 // Start of written text area

		FormatText_FloatInt_FinishLoop:
			LBU 	t3, 0x0 (t8)
			SB 		t3, 0x0 (t9)
			ADDIU 	t9, t9, 1
			ADDIU 	t8, t8, 1
			ADDI 	t6, t6, -1
			BEQZ 	t6, FormatText_FloatInt_FinishCap
			NOP
			B 		FormatText_FloatInt_FinishLoop
			NOP

		FormatText_FloatInt_FinishCap:
			B 		FinishFormattingText
			SB 		r0, 0x0 (t9)

	FinishFormattingText:
		JR 		ra
		NOP