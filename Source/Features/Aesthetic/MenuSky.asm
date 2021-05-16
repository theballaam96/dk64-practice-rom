ColourSky:
	LI 		a0, @MenuSkyTopRGB
	LI 		a1, 0xFF
	SB 		r0, 0x0 (a0)
	SB 		r0, 0x1 (a0)
	SB 		a1, 0x2 (a0)
	LI 		a0, @MenuSkyRGB
	SB 		r0, 0x0 (a0)
	SB 		r0, 0x1 (a0)
	JR 		ra
	SB 		r0, 0x2 (a0) 		