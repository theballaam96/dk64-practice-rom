GrabSandstormAddress:
	LW 		a0, @CurrentMap
	LI 		a1, 0x26 // Aztec
	BNE 	a0, a1, FinishGrabbingSandstorm
	NOP
	LW 		a0, @ObjectModel2Timer
	LI 		a1, 1
	BNE 	a0, a1, FinishGrabbingSandstorm // Only grab address on frame 1 of loading a map
	NOP
	LW 		a0, @ObjectModel2Pointer
	LW 		a1, @ObjectModel2Count

	CheckThroughObjects:
		LHU 	a2, 0x8A (a0)
		LI 		a3, 0xC1
		BEQ 	a2, a3, SetSandstormAddress
		NOP
		ADDI 	a1, a1, -1
		BEQZ 	a1, FinishGrabbingSandstorm
		ADDIU 	a0, a0, 0x90
		B 		CheckThroughObjects
		NOP

	SetSandstormAddress:
		LW 		a2, 0x7C (a0)
		ADDIU 	a2, a2, 0x54
		SW 		a2, @SandstormAddress

	FinishGrabbingSandstorm:
		JR 		ra
		NOP

ToggleAztecSandstorm:
	SW 		ra, @ReturnAddress
	LW 		a0, @CurrentMap
	LI 		a1, 0x26 // Aztec
	BNE 	a0, a1, ToggleSandstorm_NotAztec
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, FinishTogglingSandstorm // Pause Menu
	NOP
	LW 		a0, @SandstormAddress
	BEQZ 	a0, FinishTogglingSandstorm
	NOP
	// Toggle Sandstorm
	LBU 	a1, 0x0 (a0)
	LI 		a2, 1
	SUBU 	a1, a2, a1
	SB 		a1, 0x0 (a0)
	JAL 	ActiveMenu_OpenCheatsTogglesMenu
	NOP

	ToggleSandstorm_NotAztec:

	FinishTogglingSandstorm:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

.align
Sandstorm_TextPointers:
	.word Menu_Cheats_SandstormUnknown
	.word Menu_Cheats_SandstormOff
	.word Menu_Cheats_SandstormOn