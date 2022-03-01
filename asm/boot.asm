START:
	displacedBootCode:
		LUI v0, boot_lui1
		ADDIU v0, v0, boot_lui2

		// Bypass Setup Checks
		LUI t3, hi(SetupCheck1)
		ADDIU t4, r0, 1
		SB t4, lo(SetupCheck1) (t3)
		LUI t3, hi(SetupCheck2)
		SB t4, lo(SetupCheck2) (t3)
		LUI t3, hi(bootSpeedupFunc)
		LW t3, lo(bootSpeedupFunc) (t3)
		LUI t4, hi(setupCheckOverwrite)
		SW t3, lo(setupCheckOverwrite) (t4)

		//write heap size
		LUI t3, hi(heapEndWrite)
		ADDIU t4, r0, customCodeUpper
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
		LUI t4, hi(frameHookLocation)
		SW t3, lo(frameHookLocation) (t4) //store per frame hook
		LUI t3, 0
		LUI t4, 1
		LUI t5, 1
		LUI t9, 0xD
		LUI t8, 0xD
		J bootJumpReturn
		LUI t6, 0x000D
		//end of boot code
		/////////////////////////////////////////////////////

mainASMFunction:
	JAL	frameLoop
	NOP
	JAL cFuncLoop
	NOP
	NOP
	J customLoopReturn
	NOP

mainASMFunctionJump:
	J mainASMFunction //instruction copied and used as a hook
	NOP

mainASMFunctionVanilla:
	JAL	frameLoop
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
giantKoshaHook:
	J 	getGiantKoshaAddress
	NOP
lagHook:
	J 	updateLag
	NOP
saveHook:
	J 	isSaving
	NOP
spriteHook:
	J 	logSpriteAddress
	NOP
speedHook:
	J 	controlSuperspeed
	NOP

loadExtraHooks:
	LUI t3, hi(pauseHook)
	LW t3, lo(pauseHook) (t3)
	LUI t4, hi(pauseHookWrite)
	SW t3, lo(pauseHookWrite) (t4) // Store Hook

	LUI t3, hi(flagHook)
	LW t3, lo(flagHook) (t3)
	LUI t4, hi(flagHookWrite)
	SW t3, lo(flagHookWrite) (t4) // Store Hook

	LUI t3, hi(SpawnTimerHook)
	LW t3, lo(SpawnTimerHook) (t3)
	LUI t4, hi(spawnTimerHookWrite)
	SW 	t3, lo(spawnTimerHookWrite) (t4) // Store Hook
	SW 	r0, lo(spawnTimerHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(PhaseCorrectionHook)
	LW t3, lo(PhaseCorrectionHook) (t3)
	LUI t4, hi(phaseCorrectionHookWrite)
	SW 	t3, lo(phaseCorrectionHookWrite) (t4) // Store Hook

	LUI t3, hi(ArcadeHook)
	LW t3, lo(ArcadeHook) (t3)
	LUI t4, hi(arcadeHookWrite)
	SW 	t3, lo(arcadeHookWrite) (t4) // Store Hook

	LUI t3, hi(JetpacHook)
	LW t3, lo(JetpacHook) (t3)
	LUI t4, hi(jetpacHookWrite)
	SW 	t3, lo(jetpacHookWrite) (t4) // Store Hook

	LUI t3, hi(Pause97Hook)
	LW t3, lo(Pause97Hook) (t3)
	LUI t4, hi(pause97HookWrite)
	SW 	t3, lo(pause97HookWrite) (t4) // Store Hook
	SW 	r0, lo(pause97HookWrite)+4 (t4) // Store NOP

	LUI t3, hi(Pause343Hook)
	LW t3, lo(Pause343Hook) (t3)
	LUI t4, hi(pause343HookWrite)
	SW 	t3, lo(pause343HookWrite) (t4) // Store Hook
	SW 	r0, lo(pause343HookWrite)+4 (t4) // Store NOP 

	LUI t3, hi(LoadSetupHook)
	LW t3, lo(LoadSetupHook) (t3)
	LUI t4, hi(loadSetupHookWrite)
	SW 	t3, lo(loadSetupHookWrite) (t4) // Store Hook
	SW 	r0, lo(loadSetupHookWrite)+4 (t4) // Store NOP 

	LUI t3, hi(ResolveBarrelHook)
	LW t3, lo(ResolveBarrelHook) (t3)
	LUI t4, hi(resolveBarrelHookWrite)
	SW t3, lo(resolveBarrelHookWrite) (t4) // Store Hook
	SW r0, lo(resolveBarrelHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(FairyStoreHook)
	LW t3, lo(FairyStoreHook) (t3)
	LUI t4, hi(fairyStoreHookWrite)
	SW 	t3, lo(fairyStoreHookWrite) (t4) // Store Hook
	SW 	r0, lo(fairyStoreHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(DisplayListHook)
	LW t3, lo(DisplayListHook) (t3)
	LUI t4, hi(displayListHookWrite)
	SW t3, lo(displayListHookWrite) (t4) // Store Hook
	SW r0, lo(displayListHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(vertBaseStoreHook)
	LW t3, lo(vertBaseStoreHook) (t3)
	LUI t4, hi(vertBaseStoreHookWrite)
	SW t3, lo(vertBaseStoreHookWrite) (t4) // Store Hook
	SW r0, lo(vertBaseStoreHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(signalsStoreHook)
	LW t3, lo(signalsStoreHook) (t3)
	LUI t4, hi(signalsStoreHookWrite)
	SW t3, lo(signalsStoreHookWrite) (t4) // Store Hook
	SW r0, lo(signalsStoreHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(delayedKillsStoreHook)
	LW t3, lo(delayedKillsStoreHook) (t3)
	LUI t4, hi(delayedKillsStoreHookWrite)
	SW t3, lo(delayedKillsStoreHookWrite) (t4) // Store Hook
	SW r0, lo(delayedKillsStoreHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(lockStackStoreHook)
	LW t3, lo(lockStackStoreHook) (t3)
	LUI t4, hi(lockStackStoreHookWrite)
	SW t3, lo(lockStackStoreHookWrite) (t4) // Store Hook
	SW r0, lo(lockStackStoreHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(storeFloorPreloadHook)
	LW t3, lo(storeFloorPreloadHook) (t3)
	LUI t4, hi(storeFloorPreloadHookWrite)
	SW t3, lo(storeFloorPreloadHookWrite) (t4) // Store Hook
	SW r0, lo(storeFloorPreloadHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(giantKoshaHook)
	LW t3, lo(giantKoshaHook) (t3)
	LUI t4, hi(giantKoshaHookWrite)
	SW t3, lo(giantKoshaHookWrite) (t4) // Store Hook
	SW r0, lo(giantKoshaHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(lagHook)
	LW t3, lo(lagHook) (t3)
	LUI t4, hi(lagHookWrite)
	SW t3, lo(lagHookWrite) (t4) // Store Hook
	SW r0, lo(lagHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(saveHook)
	LW t3, lo(saveHook) (t3)
	LUI t4, hi(saveHookWrite)
	SW t3, lo(saveHookWrite) (t4) // Store Hook
	SW r0, lo(saveHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(spriteHook)
	LW t3, lo(spriteHook) (t3)
	LUI t4, hi(spriteHookWrite)
	SW t3, lo(spriteHookWrite) (t4) // Store Hook
	SW r0, lo(spriteHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(speedHook)
	LW t3, lo(speedHook) (t3)
	LUI t4, hi(speedHookWrite)
	SW t3, lo(speedHookWrite) (t4) // Store Hook
	SW r0, lo(speedHookWrite)+4 (t4) // Store NOP

	LUI t3, hi(kongHook)
	LW t3, lo(kongHook) (t3)
	LUI t4, hi(kongHookWrite)
	JR 	ra
	SW t3, lo(kongHookWrite) (t4) // Store Hook

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