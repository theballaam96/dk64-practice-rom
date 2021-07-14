ActiveMenu_ToggleTBVoid:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @TBVoidByte
	ANDI 	a1, a0, 0x30
	BNEZ  	a1, ActiveMenu_ToggleTBVoid_TurnOff
	NOP

	ActiveMenu_ToggleTBVoid_TurnOn:
		B 		ActiveMenu_ToggleTBVoid_Finish
		ORI 	a1, a0, 0x30

	ActiveMenu_ToggleTBVoid_TurnOff:
		ANDI 	a1, a0, 0xCF

	ActiveMenu_ToggleTBVoid_Finish:
		SB 		a1, @TBVoidByte
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP