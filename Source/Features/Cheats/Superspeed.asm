ControlSuperspeed:
	MUL.D 	f8, f18, f6
	NOP
	LBU 	a0, @IsSuperspeedOn
	BEQZ	a0, ControlSuperspeed_Finish
	NOP

	ControlSuperspeed_Fast:
		LUI 	a0, 0x40A0
		MTC1 	a0, f16
		CVT.D.S f16, f16
		MUL.D 	f8, f8, f16

	ControlSuperspeed_Finish:
		J 		0x8066535C
		NOP

ToggleSuperspeed:
	LI 		a1, 1
	LBU 	a0, @IsSuperspeedOn
	SUBU 	a0, a1, a0
	SB 		a0, @IsSuperspeedOn
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ToggleSuperspeed_IsOff
	NOP
	LA 		a1, Menu_Cheats_Superspeed_On
	B 		ToggleSuperspeed_Finish
	NOP

	ToggleSuperspeed_IsOff:
		LA 		a1, Menu_Cheats_Superspeed_Off

	ToggleSuperspeed_Finish:
		SW 		a1, 0x1C (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 58
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP