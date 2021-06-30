// Tag Anywhere
TagAnywhere:
	LBU 	a1, @TBVoidByte
	ANDI 	a1, a1, 2
	BNEZ 	a1, TagAnywhere_Finish // Pause Menu
	NOP
	LBU 	a1, @NewMenuOpen
	BEQZ 	a1, TagAnywhere_CheckDDown // If menu is open, require L as an input
	NOP
	LH 		a1, @ControllerInput
	ANDI 	a1, a1, @L_Button
	BEQZ 	a1, TagAnywhere_Finish
	NOP

	TagAnywhere_CheckDDown:
		LBU 	a1, @Character
	    SLTIU   a1, a1, 5
	    BEQZ    a1, TagAnywhere_Finish
	    NOP
		LH 		a1, @NewlyPressedControllerInput
		ANDI 	a1, a1, @D_Down
		BEQZ 	a1, TagAnywhere_Finish // Not Pressing DDown
		NOP
		LBU 	a2, @Character
		ADDIU 	a2, a2, 1 // New Character Value
		LI 		a1, 5
		BNE 	a1, a2, GunCheck // If Character + 1 != 5, Don't wrap around to 0
		NOP

	WrapAround:
		LI 	a2, 0

	GunCheck:
		LW 		a1, @Player
		BEQZ 	a1, TagAnywhere_Finish // If player isn't in RDRAM, cancel
		NOP
		LA 		a3, GunBitfields
		SLL 	t3, a2, 2 // new_kong x 4
		ADD 	a3, t3, a3
		LW 		a3, 0x0 (a3)
		LBU 	t9, 0x0 (a3) // Get gun bitfield for kong
		ANDI 	t9, t9, 1 // Has gun
		BEQZ 	t9, RetractGun
		NOP
		LBU 	t9, 0x20C(a1) // Was gun out
		BEQZ 	t9, RetractGun
		NOP

	PullOutGun:
		LA 		t9, HandStatesGun
		ADD 	t9, t9, a2
		LBU 	t9, 0x0 (t9)
		SB 		t9, 0x147 (a1) // Set Hand State
		LI 		t9, 1
		B 		ChangeCharacter
		SB 		t9, 0x20C (a1) // Set Gun State

	RetractGun:
		LA 		t9, HandStatesNoGun
		ADD 	t9, t9, a2
		LBU 	t9, 0x0 (t9)
		SB 		t9, 0x147 (a1) // Set Hand State
		SB 		r0, 0x20C (a1) // Set Gun State

	ChangeCharacter:
		LW 		a1, @Player
		BEQZ 	a1, TagAnywhere_Finish // If player isn't in RDRAM, cancel
		ADDIU	a2, a2, 2
		SB 		a2, 0x36F (a1)
		LW 		a1, @SwapObject
		BEQZ 	a1, TagAnywhere_Finish // If swap object isn't in RDRAM, cancel
		LI 		a2, 0x3B
		SH 		a2, 0x29C (a1) // Initiate Swap

	TagAnywhere_Finish:
		JR 		ra
		NOP

.align
GunBitfields:
	.word 0x807FC952 // DK
	.word 0x807FC9B0 // Diddy
	.word 0x807FCA0E // Lanky
	.word 0x807FCA6C // Tiny
	.word 0x807FCACA // Chunky

.align
HandStatesNoGun:
	.byte 1 // DK
	.byte 0 // Diddy
	.byte 1 // Lanky
	.byte 1 // Tiny
	.byte 1 // Chunky

.align
HandStatesGun:
	.byte 2 // DK
	.byte 3 // Diddy
	.byte 2 // Lanky
	.byte 2 // Tiny
	.byte 2 // Chunky