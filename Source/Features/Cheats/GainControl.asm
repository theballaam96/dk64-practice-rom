GainControl:
	LW 		a0, @Player
	BEQZ 	a0, GainControl_Finish
	NOP
	// Make kong visible
	LBU 	t0, 0x63 (a0)
	ORI 	t0, t0, 8
	SB 		t0, 0x63 (a0)
	// Force into Idle state
	LI 		t0, 0xC // Idle state
	SB 		t0, 0x154 (a0)
	// Buttons Enabled
	LI 		t0, 0xFFFF
	SH 		t0, @ButtonsEnabledBitfield
	LI 		t0, 0xFF
	SB 		t0, @JoystickEnabledX
	SB 		t0, @JoystickEnabledY
	LI 		t0, 8
	SB 		t0, @MapState
	// Vehicle Stuff
	LW 		a1, 0x208 (a0) // Vehicle Actor Pointer
	BEQZ 	a1, GainControl_Finish
	NOP
	SW 		a0, 0x208 (a0)


	GainControl_Finish:
		JR 		ra
		NOP