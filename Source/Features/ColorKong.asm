// Who says it's only Link's tunic which can change colour
ChangeColour:
	SW 		ra, @ReturnAddress
	LUI 	a0, 0x8069	
	SB 		r0, 0xA62F(a0) // 0x8068A62F // Enable colouring for 1-player gameplay
	SW 		r0, 0xA450(a0) // 0x8068A450 // Disable shading
	JAL 	0x8068A508
	// NOP
	SW 		r0, 0xA458(a0) // 0x8068A458 // Turn off low poly models
	LA 		a0, KongColours
	LBU 	a1, @Character
	ADD 	a0, a0, a1
	LBU 	a1, 0x0 (a0)
	SW 		a1, @PlayerOneColour

	FinishColourChange:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

.align
KongColours:
	.byte 0x02 // DK - Green Body
	.byte 0x02 // Diddy - Yellow Cap
	.byte 0x01 // Lanky - Green Straps
	.byte 0x02 // Tiny - Purple Suit
	.byte 0x01 // Chunky - Red Suit