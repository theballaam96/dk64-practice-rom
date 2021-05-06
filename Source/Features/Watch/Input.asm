Input_HandleString:
	SW 		ra, @ReturnAddress4
	LA 		a0, Input_String
	JAL 	CopyTextToWatch
	NOP
	LI 		a0, @WatchTextSpace // Write Space
	LH 		a1, @ControllerInput // Controller Input
	LI 		a2, 0x20 // Replace Character

	Input_HandleString_CheckA:
		// A
		ANDI 	a3, a1, @A_Button
		BNEZ 	a3, Input_HandleString_CheckB
		NOP
		SB 		a2, 0x0 (a0)

	Input_HandleString_CheckB:
		// B
		ANDI 	a3, a1, @B_Button
		BNEZ 	a3, Input_HandleString_CheckZ
		NOP
		SB 		a2, 0x1 (a0)

	Input_HandleString_CheckZ:
		// Z
		ANDI 	a3, a1, @Z_Button
		BNEZ 	a3, Input_HandleString_CheckS
		NOP
		SB 		a2, 0x2 (a0)

	Input_HandleString_CheckS:
		// Start
		ANDI 	a3, a1, @Start_Button
		BNEZ 	a3, Input_HandleString_CheckL
		NOP
		SB 		a2, 0x3 (a0)

	Input_HandleString_CheckL:
		// L
		ANDI 	a3, a1, @L_Button
		BNEZ 	a3, Input_HandleString_CheckR
		NOP
		SB 		a2, 0x4 (a0)

	Input_HandleString_CheckR:
		// R
		ANDI 	a3, a1, @R_Button
		BNEZ 	a3, Input_HandleString_CheckDU
		NOP
		SB 		a2, 0x5 (a0)

	Input_HandleString_CheckDU:
		// D-Up
		ANDI 	a3, a1, @D_Up
		BNEZ 	a3, Input_HandleString_CheckDD
		NOP
		SB 		a2, 0x9 (a0)

	Input_HandleString_CheckDD:
		// D-Down
		ANDI 	a3, a1, @D_Down
		BNEZ 	a3, Input_HandleString_CheckDL
		NOP
		SB 		a2, 0xA (a0)

	Input_HandleString_CheckDL:
		// D-Left
		ANDI 	a3, a1, @D_Left
		BNEZ 	a3, Input_HandleString_CheckDR
		NOP
		SB 		a2, 0xB (a0)

	Input_HandleString_CheckDR:
		// D-Right
		ANDI 	a3, a1, @D_Right
		BNEZ 	a3, Input_HandleString_CheckCU
		NOP
		SB 		a2, 0xC (a0)

	Input_HandleString_CheckCU:
		// C-Up
		ANDI 	a3, a1, @C_Up
		BNEZ 	a3, Input_HandleString_CheckCD
		NOP
		SB 		a2, 0x10 (a0)

	Input_HandleString_CheckCD:
		// C-Down
		ANDI 	a3, a1, @C_Down
		BNEZ 	a3, Input_HandleString_CheckCL
		NOP
		SB 		a2, 0x11 (a0)

	Input_HandleString_CheckCL:
		// C-Left
		ANDI 	a3, a1, @C_Left
		BNEZ 	a3, Input_HandleString_CheckCR
		NOP
		SB 		a2, 0x12 (a0)

	Input_HandleString_CheckCR:
		// C-Right
		ANDI 	a3, a1, @C_Right
		BNEZ 	a3, Input_HandleString_X
		NOP
		SB 		a2, 0x13 (a0)

	Input_HandleString_X:
		LI 		a1, @ControllerInput
		LB 		t9, 0x2 (a1) // X Direction, Signed
		ANDI 	a3, t9, 0x80
		ANDI 	t9, t9, 0x7F // Get size of x
		BEQZ 	a3, Input_HandleString_XMag
		LI 		t0, 0x0 // Character 0 - ""
		LI 		t0, 128
		SUBU 	t9, t0, t9
		LI 		t0, 0x2D // Character 0 - "-"

	Input_HandleString_XMag:
		// Reset Defaults
		LI 		t8, 0
		LI 		t6, 0
		LI 		t3, 0
		// Convert
		LI 		a3, 10
		DIVU 	t9, a3
		MFHI 	t8
		ADDIU 	t8, t8, 0x30 // Character 3
		MFLO 	t9
		BEQZ 	t9, Input_HandleString_XConcat
		NOP
		DIVU 	t9, a3
		MFHI 	t6
		ADDIU 	t6, t6, 0x30 // Character 2
		MFLO 	t9
		BEQZ 	t9, Input_HandleString_XConcat
		NOP
		MFLO 	t3
		ADDIU 	t3, t3, 0x30 // Character 1

	Input_HandleString_XConcat:
		// t0, t3, t6, t8 - Suppress 0s, Pad with 0x20
		ADDIU 	a3, a0, 0x17
		BEQZ 	t0, Input_HandleString_XConcat0
		NOP
		SB 		t0, 0x0 (a3)
		ADDIU 	a3, a3, 1
		LI 		t0, 1

	Input_HandleString_XConcat0:
		BEQZ 	t3, Input_HandleString_XConcat1
		NOP
		SB 		t3, 0x0 (a3)
		ADDIU 	a3, a3, 1
		ADDIU 	t0, t0, 1

	Input_HandleString_XConcat1:
		BEQZ 	t6, Input_HandleString_XConcat2
		NOP
		SB 		t6, 0x0 (a3)
		ADDIU 	a3, a3, 1
		ADDIU 	t0, t0, 1

	Input_HandleString_XConcat2:
		BEQZ 	t8, Input_HandleString_XPad
		NOP
		SB 		t8, 0x0 (a3)
		ADDIU 	a3, a3, 1
		ADDIU 	t0, t0, 1

	Input_HandleString_XPad:
		LI 		t3, 4
		BEQ 	t0, t3, Input_HandleString_Y
		NOP

	Input_HandleString_XPadLoop:
		ADDIU 	t0, t0, 1
		BEQ 	t0, t3, Input_HandleString_Y
		SB 		a2, 0x0 (a3)
		B 		Input_HandleString_XPadLoop
		ADDIU 	a3, a3, 1

	Input_HandleString_Y:
		LI 		a1, @ControllerInput
		LB 		t9, 0x3 (a1) // Y Direction, Signed
		ANDI 	a3, t9, 0x80
		ANDI 	t9, t9, 0x7F // Get size of y
		BEQZ 	a3, Input_HandleString_YMag
		LI 		t0, 0x0 // Character 0 - ""
		LI 		t0, 128
		SUBU 	t9, t0, t9
		LI 		t0, 0x2D // Character 0 - "-"

	Input_HandleString_YMag:
		// Reset Defaults
		LI 		t8, 0
		LI 		t6, 0
		LI 		t3, 0
		// Convert
		LI 		a3, 10
		DIVU 	t9, a3
		MFHI 	t8
		ADDIU 	t8, t8, 0x30 // Character 3
		MFLO 	t9
		BEQZ 	t9, Input_HandleString_YConcat
		NOP
		DIVU 	t9, a3
		MFHI 	t6
		ADDIU 	t6, t6, 0x30 // Character 2
		MFLO 	t9
		BEQZ 	t9, Input_HandleString_YConcat
		NOP
		MFLO 	t3
		ADDIU 	t3, t3, 0x30 // Character 1

	Input_HandleString_YConcat:
		// t0, t3, t6, t8 - Suppress 0s, Pad with 0x20
		ADDIU 	a3, a0, 0x1E
		BEQZ 	t0, Input_HandleString_YConcat0
		NOP
		SB 		t0, 0x0 (a3)
		ADDIU 	a3, a3, 1
		LI 		t0, 1

	Input_HandleString_YConcat0:
		BEQZ 	t3, Input_HandleString_YConcat1
		NOP
		SB 		t3, 0x0 (a3)
		ADDIU 	a3, a3, 1
		ADDIU 	t0, t0, 1

	Input_HandleString_YConcat1:
		BEQZ 	t6, Input_HandleString_YConcat2
		NOP
		SB 		t6, 0x0 (a3)
		ADDIU 	a3, a3, 1
		ADDIU 	t0, t0, 1

	Input_HandleString_YConcat2:
		BEQZ 	t8, Input_HandleString_YPad
		NOP
		SB 		t8, 0x0 (a3)
		ADDIU 	a3, a3, 1
		ADDIU 	t0, t0, 1

	Input_HandleString_YPad:
		LI 		t3, 4
		BEQ 	t0, t3, Input_HandleString_Finish
		NOP

	Input_HandleString_YPadLoop:
		ADDIU 	t0, t0, 1
		BEQ 	t0, t3, Input_HandleString_Finish
		SB 		a2, 0x0 (a3)
		B 		Input_HandleString_YPadLoop
		ADDIU 	a3, a3, 1

	Input_HandleString_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

.align
Input_String:
	.asciiz "ABZSLR D:UDLR C:UDLR X:0000 Y:0000"