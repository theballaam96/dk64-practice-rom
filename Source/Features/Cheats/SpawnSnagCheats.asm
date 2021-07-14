VisifySnagGBs:
	LW 		a0, @ObjectModel2Pointer
	BEQZ 	a0, VisifySnagGBs_Finish
	NOP
	LW 		a1, @ObjectModel2Count
	BEQZ 	a1, VisifySnagGBs_Finish
	NOP

	VisifySnagGBs_Loop:
		LHU 	t0, 0x84 (a0)
		LI 		t3, 0x74 // GB
		BEQ 	t0, t3, VisifySnagGBs_Visify
		LI 		t3, 0x90 // Medal
		BNE 	t0, t3, VisifySnagGBs_Increment
		NOP

	VisifySnagGBs_Visify:
		LW 		t0, 0x7C (a0)
		BEQZ 	t0, VisifySnagGBs_Increment
		NOP
		LI 		t3, 2
		SB 		t3, 0x54 (t0)
		SB 		r0, 0x60 (t0)

	VisifySnagGBs_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, VisifySnagGBs_Finish
		ADDIU 	a0, a0, 0x90
		B 		VisifySnagGBs_Loop
		NOP

	VisifySnagGBs_Finish:
		JR 		ra
		NOP

ResetSnagGBs:
	LW 		a0, @ObjectModel2Pointer
	BEQZ 	a0, ResetSnagGBs_Finish
	NOP
	LW 		a1, @ObjectModel2Count
	BEQZ 	a1, ResetSnagGBs_Finish
	NOP

	ResetSnagGBs_Loop:
		LHU 	t0, 0x84 (a0)
		LI 		t3, 0x74
		BEQ 	t0, t3, ResetSnagGBs_Reset
		LI 		t3, 0x90 // Medal
		BNE 	t0, t3, ResetSnagGBs_Increment
		NOP

	ResetSnagGBs_Reset:
		LW 		t0, 0x7C (a0)
		BEQZ 	t0, ResetSnagGBs_Increment
		NOP
		SB 		r0, 0x48 (t0)
		SB 		r0, 0x54 (t0)
		SB 		r0, 0x60 (t0)

	ResetSnagGBs_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, ResetSnagGBs_Finish
		ADDIU 	a0, a0, 0x90
		B 		ResetSnagGBs_Loop
		NOP

	ResetSnagGBs_Finish:
		JR 		ra
		NOP