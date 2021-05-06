[JOY_DEADZONE]: 5
[JOY_CHANGE]: 14
[JOY_MAX]: 70

GetStickMagnitude:
	// Return a0 = magnitude
	SW 		ra, @ReturnAddress4
	LI 		a0, @ControllerInput
	LB 		a1, 0x2 (a0)
	LB 		a2, 0x3 (a0)
	MTC1 	a1, f0
	MTC1 	a2, f2
	CVT.S.W f0, f0
	CVT.S.W f2, f2
	MUL.S 	f4, f0, f0
	MUL.S 	f6, f0, f0
	JAL 	@SQRT
	ADD.S 	f12, f4, f6
	CVT.W.S f0, f0
	MFC1 	a0, f0 // Stick Magnitude
	LW 		ra, @ReturnAddress4
	JR  	ra
	NOP

CheckStickMagnitudeRule:
	// v0 = is magnitude rule successful
	SW 		ra, @ReturnAddress3
	JAL 	GetStickMagnitude
	NOP
	SLTIU 	a1, a0, @JOY_MAX
	BNEZ 	a1, CheckStickMagnitudeRule_CheckDeadzone
	NOP
	LI 		a0, 70

	CheckStickMagnitudeRule_CheckDeadzone:
		SLTIU 	a1, a0, @JOY_DEADZONE
		BEQZ 	a1, CheckStickMagnitudeRule_GetDifference
		NOP
		LI 		a0, 0

	CheckStickMagnitudeRule_GetDifference:
		LBU 	a1, @PhaseChecker_PreviousMagnitude
		SUBU 	a0, a1, a0
		MTC1 	a0, f0
		CVT.S.W f0, f0
		ABS.S 	f0, f0
		CVT.W.S f0, f0
		MFC1 	a0, f0 // Absolute difference
		SLTIU 	a1, a0, @JOY_CHANGE
		BNEZ 	a1, CheckStickMagnitudeRule_Finish
		ADDIU 	v0, r0, 0
		ADDIU 	v0, r0, 1

	CheckStickMagnitudeRule_Finish:
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP