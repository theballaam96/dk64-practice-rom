SkewCheat:
	LW 		a0, @Player
	BEQZ 	a0, SkewCheat_Finish
	NOP
	LI 		a1, 0xC00
	SH 		a1, 0xE8 (a0)

	SkewCheat_Finish:
		JR 		ra
		NOP