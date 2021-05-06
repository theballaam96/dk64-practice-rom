GetGKTimer:
	LW 		a0, @CurrentMap
	LI 		a1, 0x48 // Caves
	BNE 	a0, a1, FinishGettingGKTimer
	NOP
	LW 		a0, @ObjectModel2Timer
	BEQZ 	a0, FinishGettingGKTimer
	NOP
	LW 		a0, @GiantKoshaTimerAddress
	BEQZ 	a0, FinishGettingGKTimer
	NOP
	SRA 	a1, a0, 16
	SLTIU 	a2, a1, 0x8000
	BNEZ 	a2, FinishGettingGKTimer
	NOP
	SLTIU 	a2, a1, 0x8080
	BEQZ 	a2, FinishGettingGKTimer
	NOP
	LHU 	a0, 0x0(a0)
	SH 		a0, @GiantKoshaTimerValue

	FinishGettingGKTimer:
		JR 		ra
		NOP


GrabGKTimerAddress:
	LW 		v1, 0x0 (a0)	
	ADDIU 	s0, v1, 6
	SW 		s0, @GiantKoshaTimerAddress
	OR 		s0, a0, r0
	J 		0x8064607C
	NOP