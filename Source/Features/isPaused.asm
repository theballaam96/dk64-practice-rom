IsPaused:
	LI 		a0, @ActorArray
	LHU 	a1, @ActorCount
	SB 		r0, @IsPauseMenuOpen

	IsPaused_Loop:
		LW 		t0, 0x0 (a0)
		BEQZ 	t0, IsPaused_Increment
		NOP
		SRA 	t3, t0, 16
		SLTIU 	t3, t3, 0x8000
		BNEZ 	t3, IsPaused_Increment
		NOP
		SRA 	t3, t0, 16
		SLTIU 	t3, t3, 0x8080
		BEQZ 	t3, IsPaused_Increment
		NOP
		LW 		t3, 0x58 (t0)
		LI 		t6, 95 // Game pause menu
		BEQ 	t3, t6, IsPaused_SetPause
		LI 		t6, 343 // Mystery Menu Pause Menu
		BEQ 	t3, t6, IsPaused_SetPause
		LI 		t6, 342 // Try Again Dialog
		BEQ 	t3, t6, IsPaused_SetPause
		NOP

	IsPaused_Increment:
		ADDI 	a1, a1, -1
		BEQZ  	a1, IsPaused_Finish
		ADDIU 	a0, a0, 4
		B 		IsPaused_Loop
		NOP

	IsPaused_SetPause:
		LI 		a0, 1
		SB 		a0, @IsPauseMenuOpen

	IsPaused_Finish:
		JR 		ra
		NOP