Watch_Position:
	SW  	ra, @ReturnAddress4
	LW 		a0, @Player
	LI 		t0, 0
	LI 		t3, 0
	LI 		t6, 0
	BEQZ 	a0, Watch_Position_Format
	NOP
	LW 		t0, 0x7C (a0)
	LW 		t3, 0x80 (a0)
	LW 		t6, 0x84 (a0)
	MTC1 	t0, f0
	CVT.W.S f0, f0
	MFC1 	t0, f0
	MTC1 	t3, f0
	CVT.W.S f0, f0
	MFC1 	t3, f0
	MTC1 	t6, f0
	CVT.W.S f0, f0
	MFC1 	t6, f0

	Watch_Position_Format:
		LA 		a0, @WatchTextSpace
		LA 		a1, Watch_Position_Text_Format
		ADDIU 	a2, t0, 0
		SW 		t6, 0x10 (sp)
		JAL 	@StrFormat
		ADDIU 	a3, t3, 0

	Watch_Position_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

.align
Watch_Position_Text_Format:
	.asciiz "POSITION: %4d, %4d, %4d"