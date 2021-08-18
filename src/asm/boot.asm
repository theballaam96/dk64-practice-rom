START:
	displacedBootCode:
		LUI v0, 0x8001
		ADDIU v0, v0, 0xDCC4
		//set story skip to always be on
		ORI t3, r0, 0x0001
		LUI t4, 0x8074
		SB t3, 0x452C (t4) //set story skip to 1
		//write per frame hook
		//
		LUI t3, hi(mainASMFunctionJump)
		LW t3, lo(mainASMFunctionJump) (t3)
		LUI t4, 0x8060
		SW t3, 0xC164 (t4) //store per frame hook
		J 0x80000784
		LUI t6, 0x000D
		//end of boot code
		/////////////////////////////////////////////////////

mainASMFunction:
	JAL	0x805FC2B0
	NOP
	JAL cFuncLoop
	NOP
	J 0x805FC16C
	NOP

mainASMFunctionJump:
	J mainASMFunction //instruction copied and used as a hook
	NOP

mainASMFunctionVanilla:
	JAL	0x805FC2B0
	NOP

callFunc:
	// a0 = function addr
	ADDI 	sp, sp, -8
	SW 		ra, 0x4 (sp)
	JALR 	a0
	NOP
	LW 		ra, 0x4 (sp)
	JR 		ra
	ADDIU 	sp, sp, 8

getTimestampDiff:
	// a0 = major timestamp
	// a1 = minor timestamp
	ADDIU 	sp, sp, -0xA8
	SW 		ra, 0x4C (sp)
	SW 		a0, 0x40 (sp)
	JAL 	getTimestamp
	SW 		a1, 0x44 (sp)
	LW 		t6, 0x40 (sp)
	LW 		t7, 0x44 (sp)
	ADDIU 	a2, r0, 0
	SLTU 	at, v1, t7
	SUBU 	a0, v0, t6
	SUBU 	a0, a0, at
	ADDIU 	a3, r0, 0x40
	JAL 	dk_multiply
	SUBU 	a1, v1, t7
	OR 		a0, v0, r0
	OR 		a1, v1, r0
	ADDIU 	a2, r0, 0
	JAL 	convertTimestamp
	ADDIU 	a3, r0, 3000
	OR 		a0, v0, r0
	OR 		a1, v1, r0
	ADDIU 	a2, r0, 0
	JAL 	convertTimestamp
	ADDIU 	a3, r0, 10000
	LW 		ra, 0x4C (sp)
	ADDIU 	sp, sp, 0xA8
	JR 		ra
	ADDIU 	v0, v1, 0

getTimestampDiffInTicks:
	// a0 = major timestamp
	// a1 = minor timestamp
	ADDIU 	sp, sp, -0xA8
	SW 		ra, 0x4C (sp)
	SW 		a0, 0x40 (sp)
	JAL 	getTimestamp
	SW 		a1, 0x44 (sp)
	LW 		t6, 0x40 (sp)
	LW 		t7, 0x44 (sp)
	SLTU 	at, v1, t7
	SUBU 	a0, v0, t6
	SUBU 	a0, a0, at
	SUBU 	a1, v1, t7
	SW 		a0, TempTimestampStorageMajor
	SW 		a1, TempTimestampStorageMinor
	LW 		ra, 0x4C (SP)
	JR 		ra
	ADDIU 	sp, sp, 0xA8

timestampDiffToMilliseconds:
	// a0 = major timestamp
	// a1 = minor timestamp
	ADDIU 	sp, sp, -0xA8
	SW 		ra, 0x4C (sp)
	ADDIU 	a3, r0, 0x40
	JAL 	dk_multiply
	ADDIU 	a2, r0, 0
	OR 		a0, v0, r0
	OR 		a1, v1, r0
	ADDIU 	a2, r0, 0
	JAL 	convertTimestamp
	ADDIU 	a3, r0, 3000
	OR 		a0, v0, r0
	OR 		a1, v1, r0
	ADDIU 	a2, r0, 0
	JAL 	convertTimestamp
	ADDIU 	a3, r0, 10000
	LW 		ra, 0x4C (sp)
	ADDIU 	sp, sp, 0xA8
	JR 		ra
	ADDIU 	v0, v1, 0

getGiantKoshaAddress:
	LW 		v1, 0x0 (a0)
	ADDIU 	s0, v1, 6
	SW 		r0, GiantKoshaTimerAddress
	SRA  	t8, s0, 16
	SLTIU 	t8, t8, 0x8000
	BNEZ 	t8, getGiantKoshaAddress_Finish
	SRA 	t8, s0, 16
	SLTIU 	t8, t8, 0x8080
	BEQZ 	t8, getGiantKoshaAddress_Finish
	NOP
	SW 		s0, GiantKoshaTimerAddress

	getGiantKoshaAddress_Finish:
		J 		0x8064607c
		OR 		s0, a0, r0

updateLag:
	LW 		a0, FrameReal
	LW 		a1, FrameLag
	SUBU 	a1, a0, a1
	SH 		a1, StoredLag
	LUI 	t6, 0x8077
	J 		0x8060067C
	LBU 	t6, 0xAF14 (t6)

patchHook:
	// a0 = Hook Location
	// a1 = Offset in hook list
	// a2 = hook_size_in_bytes
	ADDIU sp, sp, -0x38
	SW 	ra, 0x1C (sp)
	SW 	a2, 0x20 (sp)
	ADDIU a2, a0, 0 // RDRAM location
	LUI a0, 0x01FF //start of ROM copy
	ORI a0, a0, 0xF000
	LW 	a1, 0x20 (sp)
	JAL dmaFileTransfer
	ADDU a1, a0, a1
	LW 	ra, 0x1C (sp)
	JR 	ra
	ADDIU sp, sp, 0x38

.align 0x10
END: