ActiveMenu_ToggleTBVoid:
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
		JR 		ra
		NOP

ToggleTBVoidLMode:
	LI 		a1, 1
	LBU 	a0, @LToToggleTBOn
	SUBU 	a0, a1, a0
	SB 		a0, @LToToggleTBOn
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ToggleTBVoid_IsOff
	NOP
	LA 		a1, Menu_Cheats_LToToggleTB_On
	B 		ToggleTBVoid_Finish
	NOP

	ToggleTBVoid_IsOff:
		LA 		a1, Menu_Cheats_LToToggleTB_Off

	ToggleTBVoid_Finish:
		SW 		a1, 0x24 (a2)
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

LTo_ToggleTB:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @LToToggleTBOn
	BEQZ 	a0, LTo_ToggleTB_Finish
	NOP
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, LTo_ToggleTB_Finish // Active Menu
	NOP
	LBU 	a0, @ClosingMenu
	BNEZ 	a0, LTo_ToggleTB_Finish
	NOP
	LHU 	a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @L_Button
	BEQZ 	a0, LTo_ToggleTB_Finish
	NOP
	JAL 	ActiveMenu_ToggleTBVoid
	NOP

	LTo_ToggleTB_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP