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

.align
ViewHeldObject_NoneText:
	.asciiz "NO ACTOR HELD"
ViewHeldObject_Header:
	.asciiz "HELD ACTOR"