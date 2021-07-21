// Setup Takeoff Skip Flags
TakeoffSkip:
	SW 		ra, @ReturnAddress
	// Set all relevant flags
	LA 		a0, TakeoffSkipSetFlags
	JAL 	SetAllFlags
	NOP
	// Clear key 3 & 8 turned in
	LI      a0, 446 // Key 3 Turned In
	LI      a1, 0
	JAL     @SetFlag
	LI      a2, 0
	LI      a0, 451 // Key 8 Turned In
	LI      a1, 0
	JAL     @SetFlag
	LI      a2, 0
	// Clear Rainbow Coin FTT
	LI      a0, 364
	LI      a1, 0
	JAL     @SetFlag
	LI      a2, 0
	// Clear K. Lumsy Patch
	LI 		a0, 718
	LI 		a1, 0
	JAL 	@SetFlag
	LI 		a2, 0
	JAL 	CodedPlaySFX
	LI 		a0, @KLumsy
	LW 		ra, @ReturnAddress
	JR 		ra
	NOP

.align
TakeoffSkipSetFlags:
	.half 444 // Key 1 Turned In
	.half 445 // Key 2 Turned In
	.half 447 // Key 4 Turned In
	.half 448 // Key 5 Turned In
	.half 449 // Key 6 Turned In
	.half 450 // Key 7 Turned In
	.half 443 // Japes Rock Destroyed
	.half 138 // Key 3
	.half 380 // Key 8
	.half 0 // Terminator