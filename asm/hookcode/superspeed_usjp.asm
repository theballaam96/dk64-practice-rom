controlSuperspeed:
		MUL.D 	f8, f18, f6
		NOP
		LUI 	a0, hi(IsSuperspeedOn)
		LBU 	a0, lo(IsSuperspeedOn) (a0)
		BEQZ 	a0, controlSuperspeed_Finish
		NOP
		LHU 	t1, ControllerInput
		ANDI 	t1, t1, 0x0020
		BEQZ 	t1, controlSuperspeed_Finish
		NOP
		LUI		t1, hi(ActiveMenu)
		ADDIU 	t1, t1, lo(ActiveMenu)
		LBU 	t1, 0x0 (t1)
		BNEZ 	t1, controlSuperspeed_Finish
		NOP
		LBU 	t1, ClosingMenu
		BNEZ 	t1, controlSuperspeed_Finish
		NOP
		MTC1 	a0, f16
		CVT.D.W f16, f16
		MUL.D 	f8, f8, f16

		controlSuperspeed_Finish:
			J 	speedHookWrite+8
			NOP