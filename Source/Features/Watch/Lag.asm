UpdateLag:
	// Our Code
	LW 		a0, @FrameReal
	LW 		a1, @FrameLag
	SUBU 	a1, a0, a1
	SW 		a1, @StoredLag
	// Run code we replaced
	LUI 	t6, 0x8077
	J 		0x8060067C
	LBU 	t6, 0xAF14(t6)