START_HOOK:
	updateLag:
		LW 		a0, FrameReal
		LW 		a1, FrameLag
		SUBU 	a1, a0, a1
		SH 		a1, StoredLag
		LUI 	t6, 0x8077
		J 		0x8060067C
		LBU 	t6, 0xAF14 (t6)

.align 0x10
END_HOOK: