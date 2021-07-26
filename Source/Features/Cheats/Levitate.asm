LToLevitate:
	LBU 	a0, @LToLevitateOn
	BEQZ 	a0, LToLevitate_Finish
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, LToLevitate_Finish // Pause Menu
	NOP
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, LToLevitate_Finish
	NOP
	LH 		a0, @ControllerInput
	ANDI 	a0, a0, @L_Button
	BEQZ 	a0, LToLevitate_Finish
	NOP
	LW 		a0, @Player
	BEQZ 	a0, LToLevitate_Finish
	NOP
	LH 		a1, @ControllerInput
	ANDI 	a1, a1, @R_Button
	BNEZ 	a1, FastLevitate
	NOP
	LH 		a1, @ControllerInput
	ANDI 	a1, a1, @Z_Button
	BNEZ 	a1, SlowLevitate
	NOP
	B 		NormalLevitate
	NOP

	FastLevitate:
		B 		IncrementHeight
		LUI 	a1, 0x41A0 // 20 as float

	SlowLevitate:
		B 		IncrementHeight
		LUI 	a1, 0x40A0 // 5 as float

	NormalLevitate:
		LUI 	a1, 0x4120 // 10 as float

	IncrementHeight:
		MTC1 	a1, f2
		SW 		r0, 0xC0 (a0) // Set Y Veloc
		LW 		a1, 0x80 (a0)
		MTC1 	a1, f0
		ADD.S 	f0, f0, f2
		MFC1 	a1, f0
		SW 		a1, 0x80 (a0)

	LToLevitate_Finish:
		JR 		ra
		NOP