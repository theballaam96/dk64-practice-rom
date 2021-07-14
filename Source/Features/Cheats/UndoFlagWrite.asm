WriteLastUpdatedFlags:
	ADDIU 	sp, sp, -0x30
	LI 		a3, 1
	SB 		a3, @UndoFlag_FlagStored
	SLL 	a3, a0, 0x10
	SH 		a0, @UndoFlag_EncodedFlag
	SB 		a1, @UndoFlag_OutputBool
	SB 		a2, @UndoFlag_FlagType
	J 		0x807312A4
	NOP

UndoLastFlagWrite:
	SW 		ra, @ReturnAddress4
	LBU 	t0, @UndoFlag_FlagStored
	BEQZ 	t0, UndoLastFlagWrite_Finish
	NOP
	LHU	 	a0, @UndoFlag_EncodedFlag
	LBU 	a1, @UndoFlag_OutputBool
	LI 		t0, 1
	SUBU 	a1, t0, a1
	LBU 	a2, @UndoFlag_FlagType
	JAL 	@SetFlag
	NOP

	UndoLastFlagWrite_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP