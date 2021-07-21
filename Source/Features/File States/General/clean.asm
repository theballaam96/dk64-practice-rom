SetClean:
	SW 		ra, @ReturnAddress4
	JAL 	@GetFlagBlockAddress
	ADDIU 	a0, r0, 0
	LI 		a0, 0x13C
	ADDIU 	a1, v0, 0
	LA 		a2, FileState_Clean_KongBase

	SetClean_Flag_Loop:
		LW 		t0, 0x0 (a2)
		SW  	t0, 0x0 (a1)
		ADDI 	a0, a0, -4
		BEQZ 	a0, SetClean_KongBase_Define
		ADDIU 	a1, a1, 4
		B 		SetClean_Flag_Loop
		ADDIU 	a2, a2, 4

	SetClean_KongBase_Define:
		LI 		a0, 0x1D6
		LI 		a1, @MovesBase
		LA 		a2, FileState_Clean_KongBase

	SetClean_KongBase_Loop:
		LHU 	t0, 0x0 (a2)
		SH 		t0, 0x0 (a1)
		ADDI 	a0, a0, -2
		BEQZ 	a0, SetClean_SFX
		ADDIU 	a1, a1, 2
		B 		SetClean_KongBase_Loop
		ADDIU 	a2, a2, 2

	SetClean_SFX:
		JAL 	CodedPlaySFX
		LI 		a0, @UhOh

	SetClean_KongBase_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

.align
FileState_Clean_KongBase:
	.space 0x1D6

.align
FileState_Clean_FlagBlock:
	.space 0x13C

.align
FileState_Clean_Data:
	.word FileState_Clean_KongBase
	.word FileState_Clean_FlagBlock