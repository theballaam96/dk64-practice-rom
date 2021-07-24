ViewHeldObject:
	SW 		ra, @ReturnAddress4
	LW 		a0, @Player
	BEQZ 	a0, ViewHeldObject_Finish
	NOP
	LW 		a1, 0x32C (a0) // Grab Pointer
	BEQZ 	a1, ViewHeldObject_NoHeld
	NOP
	LHU 	a1, 0x5A (a1) // Value
	LA 		a0, ViewHeldObject_Header
	LI 		a2, 0 // Display Type
	JAL 	FormatTextForWatch
	LI 		a3, 10 // Header Length
	B 		ViewHeldObject_Finish
	NOP


	ViewHeldObject_NoHeld:
		LA 		a0, ViewHeldObject_NoneText
		JAL 	CopyTextToWatch
		NOP

	ViewHeldObject_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

ColourHeldObject:
	SW 	 	ra, @ReturnAddress4
	LI 		a0, 0xFFFFFF
	LW 		a1, @Player
	BEQZ 	a1, ColourHeldObject_Colour
	NOP
	LW 		a1, 0x32C (a1) // Grab Pointer
	BEQZ 	a1, ColourHeldObject_Colour
	NOP
	LI 		t0, @ActorArray
	LHU 	t3, @ActorCount

	ColourHeldObject_Loop:
		LW 		t6, 0x0 (t0)
		BEQ 	t6, a1, ColourHeldObject_Found
		ADDI 	t3, t3, -1
		BEQZ 	t3, ColourHeldObject_Colour
		ADDIU 	t0, t0, 4
		B 		ColourHeldObject_Loop
		NOP

	ColourHeldObject_Found:
		LI 		a0, @HeldObject_ObjectExists

	ColourHeldObject_Colour:
		JAL 	Watch_ColourWatch
		NOP

	ColourHeldObject_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

.align
ViewHeldObject_NoneText:
	.asciiz "NO ACTOR HELD"
ViewHeldObject_Header:
	.asciiz "HELD ACTOR"