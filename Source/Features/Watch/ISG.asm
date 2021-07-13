CalculateISGTime:
	SW 		ra, @ReturnAddress4
	LBU 	a1, @ISGActive
	LI 		t0, 0 // Float representation
	BEQZ 	a1, CalculateISGTime_Format
	LI 		a1, 0 // Default time when ISG not on
	LD 		t9, @CurrentTimestamp
	LD 		a3, @ISGTimestamp
	BEQZ 	a3, CalculateISGTime_Format
	LI 		a1, 0 // Default time when ISG timestamp is inactive
	DSUBU 	a1, t9, a3
	LI 		a3, @ISGTimer
	SD 		a1, 0x0(a3)
	LW 		a2, 0x0(a3)
	LW 		a1, 0x4(a3)
	MTC1 	a2, f0
	MTC1 	a1, f10
	CVT.S.W f0, f0 // Major as float
	CVT.S.W f10, f10 // Minor as float
	LI 		a2, 0x4F800000 // 2^32 as float
	MTC1 	a2, f6 
	LI 		a2, 0x41AA7302 // 21.306156158447265625
	MTC1 	a2, f2
	LI 		a3, 0x3089705F // 10^-9
	MTC1 	a3, f4
	LI 		a3, 0x42B704BC // Minor Overflow Addition (91.509246826171875) = (2 ^ 32) * (10 ^ -9) * scalar
	MTC1 	a3, f12
	MTC1 	r0, f8 // r0
	MUL.S 	f0, f0, f4 // Major * magnitude
	MUL.S 	f10, f10, f4 // Minor * ticks
	MUL.S 	f0, f0, f2 // Major * magnitude * ticks
	MUL.S 	f10, f10, f2 // Minor * magnitude * ticks
	MUL.S 	f0, f0, f6 // Major * magnitude * ticks * 2^32
	C.LE.S 	f10, f8
	BC1TL 	AddISGStamps
	ADD.S 	f10, f10, f12

	AddISGStamps:
		ADD.S 	f0, f0, f10 // Major + Minor
		LI 		a2, 0x40049375 // Offset for "Real time" timing method. 2.0715
		MTC1 	a2, f10
		ADD.S 	f0, f0, f10 // Time + Realtime Offset
		MFC1 	t0, f0
		LUI 	a2, 0x3EFF // f32 - 0.498 (Close to 0.5)
		MTC1 	a2, f10
		SUB.S 	f0, f0, f10
		CVT.W.S f0, f0
		MFC1 	a1, f0

	CalculateISGTime_Format:
		LI 		a2, 60
		DIVU 	a1, a2
		MFLO 	a2 // Minutes
		MTC1 	a2, f0
		CVT.S.W f0, f0
		LUI 	a3, 0x4270
		MTC1 	a3, f2
		MUL.S 	f2, f0, f2
		MTC1 	t0, f0
		SUB.S 	f0, f0, f2 // Seconds
		MFC1 	a3, f0
		SW 		a3, @VarStorage0
		LA 		a0, ISGWatch_Header_Space
		//LI 		a0, @WatchTextSpace
		LA 		a1, ISGWatch_Header_Format
		JAL 	@StrFormat
		NOP
		LW 		a1, @VarStorage0
		LA 		a0, ISGWatch_Header_Space
		LI 		a2, 2 // Display Type
		JAL 	FormatTextForWatch
		LI 		a3, 11 // Header Length
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

		// MTC1 	a1, f0
		// CVT.S.W f0, f0
		// LUI 	a2, 0x4270
		// MTC1 	a2, f2
		// DIV.S 	f0, f0, f2
		// LUI 	a3, 0x3EFF
		// MTC1 	a3, f4

GetISGTimer:
	ADDU 	a2, t9, t0
	SW 		v1, @ISGTimer
	LW 		t2, 0x0 (a2)
	J 		0x8061B568
	NOP

.align
ISGWatch_Header_Format:
	.asciiz "ISG TIME: %1d"
ISGWatch_Header_Space:
	.space 0x10