Watch_SpawnWatch:
	SW 		ra, @ReturnAddress2
	LI 		a0, 0
	LI 		a1, 100
	LI 		a2, 200
	LA 		a3, Display_Calibrating
	JAL 	@SpawnTextOverlay
	NOP
	LW 		a0, @CurrentActorPointer
	BEQZ 	a0, Watch_SpawnWatch_Finish
	NOP
	SW 		a0, @WatchActor
	LI 		a1, @WatchTextSpace
	SW 		a1, 0x178 (a0)
	LI 		a1, 0xFF
	SB 		a1, 0x15F (a0) // Opacity

	Watch_SpawnWatch_Finish:
		LW 		ra, @ReturnAddress2
		JR 		ra
		NOP

Watch_DestroyWatch:
	SW 		ra, @ReturnAddress2
	LW 		a0, @WatchActor
	BEQZ 	a0, Watch_DestroyWatch_Finish
	NOP
	JAL 	@DeleteActor
	NOP
	SW 		r0, @WatchActor

	Watch_DestroyWatch_Finish:
		LW 		ra, @ReturnAddress2
		JR 		ra
		NOP

Watch_ColourWatch:
	// a0 = Colour (u24)
	LW 		a1, @WatchActor
	BEQZ 	a1, Watch_ColourWatch_Finish
	NOP
	// RGB = 0x16A > 0x16C
	ANDI 	a2, a0, 0xFF
	SB 		a2, 0x16C (a1)
	SRA 	a0, a0, 8
	ANDI 	a2, a0, 0xFF
	SB 		a2, 0x16B (a1)
	SRA 	a0, a0, 8
	ANDI 	a2, a0, 0xFF
	SB 		a2, 0x16A (a1)

	Watch_ColourWatch_Finish:
		JR 		ra
		NOP

Watch_CloseOnTransition:
	SW 		ra, @ReturnAddress
	LW 		a0, @WatchActor
	BEQZ 	a0, Watch_CloseOnTransition_Finish
	NOP
	LBU 	a0, @TransitionSpeed
	ANDI 	a0, a0, 0x80
	BNEZ 	a0, Watch_CloseOnTransition_CheckZipper // Non-negative
	NOP
	LW 		a0, @TransitionSpeed // Non-zero
	BEQZ 	a0, Watch_CloseOnTransition_CheckZipper
	NOP
	B 		Watch_CloseOnTransition_Close
	NOP

	Watch_CloseOnTransition_CheckZipper:
		LBU 	a0, @CutsceneActive
		LI 		a1, 6
		BNE 	a0, a1, Watch_CloseOnTransition_Finish
		NOP

	Watch_CloseOnTransition_Close:
		JAL 	Watch_DestroyWatch
		NOP

	Watch_CloseOnTransition_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

Watch_OpenOnTransition:
	SW 		ra, @ReturnAddress
	LBU 	a0, @VariableDisplayOn
	BEQZ 	a0, Watch_OpenOnTransition_Finish
	NOP
	LW 		a0, @WatchActor
	BNEZ 	a0, Watch_OpenOnTransition_Finish
	NOP
	LBU 	a0, @TransitionSpeed
	ANDI 	a0, a0, 0x80
	BEQZ 	a0, Watch_OpenOnTransition_Finish // Negative
	NOP
	LW 		a0, @TransitionSpeed // Non-zero
	BEQZ 	a0, Watch_OpenOnTransition_Finish
	NOP
	JAL 	Watch_SpawnWatch
	NOP

	Watch_OpenOnTransition_Finish:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP