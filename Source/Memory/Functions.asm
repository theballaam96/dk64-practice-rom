// FUNCTIONS
[SetFlag]: 0x8073129C
[CheckFlag]: 0x8073110C
[PrintText]: 0x806ABB98
// a0 = HUD Pointer?
// a1 = x
// a2 = y
// a3 = scale
// sp[0x10] = String
[Malloc]: 0x80610FE8 // a0 = size
[SetHUDPointer]: 0x806A921C // a0 = malloc outcome
[PlaySFX]: 0x80609140 // a0 = Sound Effect, a1 = 0x7FFF, a2 = 427C0000, a3 = 0x3f800000, sp+0x10 = 0, sp + 0x14 = 0
[InitiateTransition]: 0x805FF378
[GetFlagBlockAddress]: 0x8060E25C
[IsAddressActor]: 0x8067AF44 // a0 = InputAddress, v0 = Output Bool
[GetTimestamp]: 0x800060B0 // v0 = Output u64
[DMAFileTransfer]: 0x80000450
[SpawnObjectModelTwo]: 0x80632630
[PlaySong]: 0x80602A94
[DeleteActor]: 0x806785D4
[SpawnActor]: 0x80677fa8 // a0 = Actor Type
[SpawnTextOverlay]: 0x8069D0F8
// a0 = style
	// 0 = Centered
	// 1 = DK Font
	// 2 = Thick Computer
	// 3 = Timer
	// 4 = Thin Computer
	// 5 = V. Thin Computer
	// 6 = Comic Sans-Esque
	// 7 - 9 = Crash
	// 10 = K Rool Intro
// a1 = x (s16)
// a2 = y (s16)
// a3 = textpointer
[SQRT]: 0x8000AC60 // f12 = val to sqrt, return f0
[StrFormat]: 0x800031E0
[GetTimestamp]: 0x800060B0
[Multiply]: 0x80005918
[ConvertTimestamp]: 0x80005818
[ResetMap]: 0x805FFFC8
[SetCutscene]: 0x8061CC40
[IDToIndex]: 0x80659470