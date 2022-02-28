START:
	displacedBootCode:
		LUI v0, 0x8001
		ADDIU v0, v0, 0xDCC4

		// Bypass Setup Checks
		LUI t3, 0x8075
		ADDIU t4, r0, 1
		SB t4, 0x00B0 (t3)
		LUI t3, 0x8074
		SB t4, 0x7D78 (t3)
		LUI t3, hi(bootSpeedupFunc)
		LW t3, lo(bootSpeedupFunc) (t3)
		LUI t4, 0x8060
		SW t3, 0xEB00 (t4)

		//write heap size
		LUI t3, hi(heapEndWrite)
		ADDIU t4, r0, 0x805D
		SH t4, lo(heapEndWrite) (t3)

		//write file start stuff
		LUI t3, hi(fileStartMap)
		ADDIU t4, r0, 0x22
		SB t4, lo(fileStartMap) (t3)
		LUI t3, hi(fileStartExit)
		SB r0, lo(fileStartExit) (t3)

		// write kong color stuff
		LUI t3, hi(kongColor1)
		SB r0, lo(kongColor1) (t3)
		LUI t3, hi(kongColor1)
		SW r0, lo(kongColor2) (t3)
		LUI t3, hi(kongColor1)
		SW r0, lo(kongColor3) (t3)

		// Write EEPROM patch
		LUI t3, hi(eepromPatch)
		SW r0, lo(eepromPatch) (t3)

		//write per frame hook
		//
		LUI t3, hi(mainASMFunctionJump)
		LW t3, lo(mainASMFunctionJump) (t3)
		LUI t4, 0x8060
		SW t3, 0xC164 (t4) //store per frame hook
		LUI t3, 0
		LUI t4, 1
		LUI t5, 1
		LUI t9, 0xD
		LUI t8, 0xD
		J 0x80000784
		LUI t6, 0x000D
		//end of boot code
		/////////////////////////////////////////////////////

mainASMFunction:
	JAL	0x805FC2B0
	NOP
	JAL cFuncLoop
	NOP
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

getOtherSpritePointer:
	JR 		ra
	OR 		v0, a1, r0

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

timestampAdd:
	// a0 = Timestamp 1 double
	// a1 = Timestamp 2 double
	LD		t0, 0x0 (a0)
	LD 		t3, 0x0 (a1)
	DADDU 	t0, t0, t3
	LUI	 	t6, hi(TempTimestampStorageMajor)
	JR 		ra
	SD 		t0, lo(TempTimestampStorageMajor) (t6)

bootSpeedupFunc:
	JAL bootSpeedup
	NOP

pauseHook:
	J 	setPauseVolume
	NOP
kongHook:
	J 	kongCode
	NOP
flagHook:
	J 	writeLastUpdatedFlags
	NOP
TextResizeHook:
	J 	resizeActiveMenuFont
	NOP
DefineAMFontHook:
	J 	defineActiveMenuOtherParams
	NOP
SpawnTimerHook:
	J 	controlTimer
	NOP
PhaseCorrectionHook:
	J 	preventPhasewalkingOverride
	NOP
FairyStoreHook:
	J 	fairyDataStorageCode
	NOP
ArcadeHook:
	J 	arcadeLoopCode
	NOP
Pause97Hook:
	J 	pauseMenu97Code
	NOP
Pause343Hook:
	J 	pauseMenu343Code
	NOP
LoadSetupHook:
	J 	loadSetupCode
	NOP
ResolveBarrelHook:
	J 	resolveBonusBarrelCode
	NOP
DisplayListHook:
	J 	displayListCode
	NOP
mapDLHook:
	J 	mapDLCode
	NOP
JetpacHook:
	J 	jetpacLoopCode
	NOP
vertBaseStoreHook:
	J 	vertBaseStore
	NOP
signalsStoreHook:
	J 	signalsStore
	NOP
delayedKillsStoreHook:
	J 	delayedKillsStore
	NOP
lockStackStoreHook:
	J 	lockStackStore
	NOP
storeFloorPreloadHook:
	J 	storeFloorPreload
	NOP

loadExtraHooks:
	ADDIU t3, r0, 0x1000
	LUI t4, 0x806A
	SH 	t3, 0xD738 (t4)

	LUI t3, hi(pauseHook)
	LW t3, lo(pauseHook) (t3)
	LUI t4, 0x8060
	SW t3, 0xC890 (t4) // Store Hook

	LUI t3, hi(flagHook)
	LW t3, lo(flagHook) (t3)
	LUI t4, 0x8073
	SW t3, 0x129C (t4) // Store Hook

	LUI t3, hi(TextResizeHook)
	LW t3, lo(TextResizeHook) (t3)
	LUI t4, 0x806A
	SW 	t3, 0xD88C (t4) // Store Hook

	LUI t3, hi(DefineAMFontHook)
	LW t3, lo(DefineAMFontHook) (t3)
	LUI t4, 0x806A
	SW 	t3, 0xD8B0 (t4) // Store Hook

	LUI t3, hi(SpawnTimerHook)
	LW t3, lo(SpawnTimerHook) (t3)
	LUI t4, 0x806A
	SW 	t3, 0x2AF8 (t4) // Store Hook
	SW 	r0, 0x2AFC (t4) // Store NOP

	LUI t3, hi(PhaseCorrectionHook)
	LW t3, lo(PhaseCorrectionHook) (t3)
	LUI t4, 0x806E
	SW 	t3, 0x063C (t4) // Store Hook

	LUI t3, hi(ArcadeHook)
	LW t3, lo(ArcadeHook) (t3)
	LUI t4, 0x8060
	SW 	t3, 0xC144 (t4) // Store Hook

	LUI t3, hi(JetpacHook)
	LW t3, lo(JetpacHook) (t3)
	LUI t4, 0x8060
	SW 	t3, 0xC154 (t4) // Store Hook

	LUI t3, hi(Pause97Hook)
	LW t3, lo(Pause97Hook) (t3)
	LUI t4, 0x806B
	SW 	t3, 0x8158 (t4) // Store Hook
	SW 	r0, 0x815C (t4) // Store NOP

	LUI t3, hi(Pause343Hook)
	LW t3, lo(Pause343Hook) (t3)
	LUI t4, 0x806B
	SW 	t3, 0xCFFC (t4) // Store Hook
	SW 	r0, 0xD000 (t4) // Store NOP 

	LUI t3, hi(LoadSetupHook)
	LW t3, lo(LoadSetupHook) (t3)
	LUI t4, 0x8069
	SW 	t3, 0x8714 (t4) // Store Hook
	SW 	r0, 0x8718 (t4) // Store NOP 

	LUI t3, hi(ResolveBarrelHook)
	LW t3, lo(ResolveBarrelHook) (t3)
	LUI t4, 0x8069
	SW t3, 0x8D64 (t4) // Store Hook
	SW r0, 0x8D68 (t4) // Store NOP

	LUI t3, hi(FairyStoreHook)
	LW t3, lo(FairyStoreHook) (t3)
	LUI t4, 0x806C
	SW 	t3, 0x5D9C (t4) // Store Hook
	SW 	r0, 0x5DA0 (t4) // Store NOP

	LUI t3, hi(DisplayListHook)
	LW t3, lo(DisplayListHook) (t3)
	LUI t4, 0x8071
	SW t3, 0x417C (t4) // Store Hook
	SW r0, 0x4180 (t4) // Store NOP

	LUI t3, hi(vertBaseStoreHook)
	LW t3, lo(vertBaseStoreHook) (t3)
	LUI t4, 0x8063
	SW t3, 0xF200 (t4) // Store Hook
	SW r0, 0xF204 (t4) // Store NOP

	LUI t3, hi(signalsStoreHook)
	LW t3, lo(signalsStoreHook) (t3)
	LUI t4, 0x8068
	SW t3, 0x9344 (t4) // Store Hook
	SW r0, 0x9348 (t4) // Store NOP

	LUI t3, hi(delayedKillsStoreHook)
	LW t3, lo(delayedKillsStoreHook) (t3)
	LUI t4, 0x8068
	SW t3, 0x83CC (t4) // Store Hook
	SW r0, 0x83D0 (t4) // Store NOP

	LUI t3, hi(lockStackStoreHook)
	LW t3, lo(lockStackStoreHook) (t3)
	LUI t4, 0x8061
	SW t3, 0x09F4 (t4) // Store Hook
	SW r0, 0x09F8 (t4) // Store NOP

	LUI t3, hi(storeFloorPreloadHook)
	LW t3, lo(storeFloorPreloadHook) (t3)
	LUI t4, 0x8066
	SW t3, 0x610C (t4) // Store Hook
	SW r0, 0x6110 (t4) // Store NOP

	//LUI t3, hi(mapDLHook)
	//LW t3, lo(mapDLHook) (t3)
	//LUI t4, 0x8060
	//SW t3, 0xC544 (t4) // Store Hook
	//SW r0, 0xC548 (t4) // Store NOP

	// Negative Kerning
	LUI t3, 0x8070
	ADDIU t4, r0, 0x81
	SB t4, 0xCB10 (t3)
	SB t4, 0xCACC (t3)

	LUI t3, 0x8070
	ADDIU t4, r0, 0x50
	SB t4, 0xCA68 (t3)

	LUI t3, hi(kongHook)
	LW t3, lo(kongHook) (t3)
	LUI t4, 0x806F
	JR 	ra
	SW t3, 0x3750 (t4) // Store Hook

getObjectArrayAddr:
	// a0 = initial address
	// a1 = common object size
	// a2 = index
	MULTU 	a1, a2
	MFLO	a1
	JR 		ra
	ADD 	v0, a0, a1

drawJetpacPixelFont:
	ADDIU 	sp, sp, -0x28
	SW 		ra, 0x24 (sp)
	SW 		s0, 0x20 (sp)
	SW 		a0, 0x28 (sp)
	SW 		a1, 0x2C (sp)
	SW 		a2, 0x30 (sp)
	SW 		a3, 0x34 (sp)
	LW 		s0, 0x0 (a0)
	OR 		v0, s0, r0
	LUI 	t8, 0xFA00
	SW 		t8, 0x0 (v0)
	LW 		t0, 0x38 (sp)
	SLL 	t0, t0, 24
	OR 		t8, t0, r0
	LW 		t0, 0x3C (sp)
	SLL 	t0, t0, 16
	OR 		t8, t8, t0
	LW 		t0, 0x40 (sp)
	SLL 	t0, t0, 8
	OR 		t8, t8, t0
	LW 		t0, 0x44 (sp)
	OR 		t8, t8, t0
	SW 		t8, 0x4 (v0)
	LUI 	t8, 0xFB00
	SW 		t8, 0x8 (v0)
	ADDIU 	t8, r0, 0xFF
	SW 		t8, 0xC (v0)
	ADDIU 	s0, s0, 16
	LW 		t8, 0x2C (sp)
	OR 		a0, s0, r0
	ADDIU 	a1, r0, 2
	LH 		a2, 0x32 (sp)
	LH 		a3, 0x36 (sp)
	JAL 	textDraw
	SW 		t8, 0x10 (sp)
	LW 		t2, 0x28 (sp)
	SW 		v0, 0x0 (t2)
	LW 		ra, 0x24 (sp)
	LW 		s0, 0x20 (sp)
	JR 		ra
	ADDIU 	sp, sp, 0x28

	
.align 0x10
END: