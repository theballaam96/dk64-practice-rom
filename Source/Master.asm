// Donkey Kong 64 - Practice ROM
// By theballaam96
// http://www.twitter.com/tjballaam

[InCutscene]: 0x807444EC
[TransitionSpeed]: 0x807FD88C
[CutsceneWillPlay]: 0x8075533B
[MysteryWriteOffset]: 0x29C
[CurrentCharacter]: 0x36F
[KRoolRound]: 0x80750AD4
[MovesBase]:  0x807FC950 // End: 0x807FCB28
[MovesBaseSize]: 0x1D8
[PlayerOneColour]: 0x807552F4
[Mode]: 0x80755318
[TBVoidByte]: 0x807FBB63
[CurrentMap]: 0x8076A0A8
[DestMap]: 0x807444E4
[DestExit]: 0x807444E8
[StorySkip]: 0x8074452C
[HelmTimerDisplay]: 0x80755348 // u32
[HelmTimerShown]: 0x80755350 // u8
[TempFlagBlock]: 0x807FDD90
[InSubmap]: 0x8076A170
[ParentMap]: 0x8076A172
[ParentExit]: 0x8076A174
[HelmTimer]: 0x80755348 // u32
[HelmTimerPaused]: 0x80713C9B // u8
[Lag]: 0x80744478 // u32
[KRoolTimerText]: 0x80754AD0
[FrameLag]: 0x8076AF10
[FrameReal]: 0x80767CC4
[RNG]: 0x80746A40 // u32
[BetaNinRWSkip]: 0x80755324 // u8
[Gamemode]: 0x80755314 // u8
[ObjectModel2Pointer]: 0x807F6000
[ObjectModel2Timer]: 0x8076A064
[ObjectModel2Count]: 0x807F6004
[ObjectModel2Count_Dupe]: 0x80747D70
[LoadingZoneArray]: 0x807FDCB4
[LoadingZoneArraySize]: 0x807FDCB0
[CutsceneIndex]: 0x807476F4
[CutsceneActive]: 0x807444EC
[CutsceneTypePointer]: 0x807476FC
[PreviousCameraState]: 0x807F5CF0
[CurrentCameraState]: 0x807F5CF2
[CameraStateChangeTimer]: 0x807F5CEC
[AutowalkPointer]: 0x807FD70C
[IsAutowalking]: 0x807463B8
[PositionWarpInfo]: 0x807FC918
[PositionWarpBitfield]: 0x8076AEE2
[PositionFloatWarps]: 0x8076AEE4 // f32 x 3
[SFXVolume]: 0x8074583C
[MusicVolume]: 0x80745840
[ChimpyCam]: 0x80744530
[ScreenRatio]: 0x807444C0
[CurrentActorPointer]: 0x807FBB44
[LoadedActorCount]: 0x807FBB35
[SpawnerArray]: 0x807FDC8C
[SpawnerCount]: 0x807FDC88
[MenuSkyTopRGB]: 0x80754F4C
[MenuSkyRGB]: 0x80754F4F

// Buttons
[L_Button]: 0x0020
[D_Up]: 0x0800
[D_Down]: 0x0400
[D_Left]: 0x0200
[D_Right]: 0x0100
[B_Button]: 0x4000
[A_Button]: 0x8000
[Z_Button]: 0x2000
[R_Button]: 0x0010
[Start_Button]: 0x1000
[C_Up]: 0x0008
[C_Down]: 0x0004
[C_Left]: 0x0002
[C_Right]: 0x0001

// MIPS ASM
[ReturnAddress]: 0x807FFFB0
[ReturnAddress2]: 0x807FFFB4
[ReturnAddress3]: 0x807FFFB8 // Compact Functions
[ReturnAddress4]: 0x807FFFBC
[ReturnAddress5]: 0x807FFFC0

[VarStorage0]: 0x807FF5E0
[VarStorage1]: 0x807FF5E4
[VarStorage2]: 0x807FF5E8
[VarStorage3]: 0x807FF5EC
[VarStorage4]: 0x807FF5F0
[VarStorage5]: 0x807FF5F4

// OSD
[WriteTextZone]: 0x807FCAA0
[ControllerInput]: 0x80014DC4
[NewlyPressedControllerInput]: 0x807ECD66
[WarpY]: 69
[WipeY]: 117
[PauseMenuTextPointer]: 0x807FC7E0
[PauseMenuPointer]: 0x807FC640
[MaxCooldown]: 6
[MinCooldown]: 2
[SpecialFlagCategories]: 9

// ISG
[ISGActive]: 0x80755070
[ISGTimestamp]: 0x807F5CE0
[ISGPreviousFadeout]: 0x807F5D14
[CurrentTimestamp]: 0x80014FE0

// Tag Anywhere
[Player]: 0x807FBB4C
[SwapObject]: 0x807FC924
[Character]: 0x8074E77C
[Camera]: 0x807FB968
[StaticCamera]: 0x80764EBC // Is this in the stack?

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
[SpawnTextOverlay]: 0x8069D0F8 // a0 = z?, a1 = x (s16), a2 = y (s16), a3 = textpointer
[SQRT]: 0x8000AC60 // f12 = val to sqrt, return f0

// Sound Effects
[Banana]: 0x2A0
[Okay]: 0x23C
[UhOh]: 0x150
[Bell]: 0x1F
[KLumsy]: 0x31C
[Wrong]: 0x98
[Potion]: 0x214
[AmmoPickup]: 0x157
[Coin]: 0x1D1
[BeepHigh]: 116
[BeepLow]: 117
[FeedMe]: 601
[Bounce]: 458
[TimerTock]: 143
[ChunkyFallTooFar]: 197
[Fire]: 234
[MatchingSound]: 171
[CameraPull]: 441

// Variables
[MasterLevelCount]: 25
[SlideCap]: 4
[SpecialFlagsCount]: 52
[Slot3OptionCount]: 13
[DisplayTypeCount]: 8
[MovementStateIndex]: 6
[LoadingZoneTypesCount]: 5
[LoadingZoneMassCount]: 2
[FileStatusCount]: 3
[IndependentCheatCount]: 2
[LModesCount]: 4
[SongsCount]: 117
[TimerStartCount]: 3
[TimerFinishCount]: 4
[WarpMasterCount]: 12
[SelectedRGB]: 0x2E8B57 // CSS SeaGreen
[MaxMenuItems]: 23 // 32 (practice rom cap) - 8 (normal cap) - 1 (watch)
[EmergencyCloseLoadedAmount]: 60
[ErrorLength]: 180
[KoshaRGB_Frozen]: 0x008B8B // CSS DarkCyan
[KoshaRGB_CancelRange]: 0xFFD700 // CSS Gold
[KoshaRGB_Music]: 0xD2691E // CSS Chocolate
[KoshaRGB_Tantrum]: 0x8B0000 // CSS DarkRed

// Savestate Struct
[SavestateStruct_CollectableBase]: 0x0
[SavestateStruct_PositionTuple]: 0x10
[SavestateStruct_Map]: 0x1C
[SavestateStruct_Exit]: 0x1D
[SavestateStruct_Character]: 0x1E
[SavestateStruct_SavedData]: 0x1F
[SavestateStruct_TempFlagBlock]: 0x20
[SavestateStruct_KongBase]: 0x30
[SavestateStruct_PermFlagBlock]: 0x210

// COLLECTABLES
[CollectableBase]: 0x807FCC40

// INTERNAL
[MenuOpen]: 0x807FFFFF // u8
[SpecialFlagIndex]: 0x807FFFFE // u8
[Slot3Position]: 0x807FFFFD // u8
[MenuPosition]: 0x807FFFFB // u8
[MenuActionCooldown]: 0x807FFFFA // u8 - Prevents crashes
[PauseMenuNextScreen]: 0x807FFFF9 // u8
[HasASavestate]: 0x807FFFF8 // u8 - Bool
[InBadMap]: 0x807FFFF7 // u8 - Bool
[MenuSavestateAction]: 0x807FFFF6 // u8 - 0 = Save, 1 = Load
[StickWasNonNeutral]: 0x807FFFF5 // u8 - Bool
[PauseMenuScreen]: 0x807FFFF4 // u8
[StoredMainMenuTextPointer]: 0x807FFFF0 // u32 pointer
[VariableDisplayOn]: 0x807FFFEF // u8
[ExtraSlotPosition]: 0x807FFFEE // u8
[SniperOn]: 0x807FFFED // u8
[SlamLevel]: 0x807FFFEC // u8
[CumulativeLag]: 0x807FFFE8 // u32
[ISGTimer]: 0x807FFFE0 // u64
[StoredLag]: 0x807FFFDC // u32
[StoredTime]: 0x807FFFD8 // u32
[StoredStart]: 0x807FFFD4 // u32
[StoredTimerMode]: 0x807FFFD3 // u8 - 0: Reset/Zeroed, 1: Started, 2: Stopped
[StoredRound]: 0x807FFFD2 // u8
[DisablePositionButtons]: 0x807FFFD1 // u8
[DisableTagAnywhere]: 0x807FFFD0 // u8
[SelectedMasterLevelIndex]: 0x807FFFCF // u8
[SelectedMapIndex]: 0x807FFFCE // u8
[SelectedMapCap]: 0x807FFFCD // u8
[MenuSlide]: 0x807FFFCC // u8
[FrameAdvanceStart]: 0x807FFFC8 // u32
[DisableStartupSkip]: 0x807FFFC7 // u8
[DisableForcedStorySkip]: 0x807FFFC6 // u8
[SandstormAddress]: 0x807FFDFC // u32
[SandstormActive]: 0x807FFDFB // u8
[SandstormChange]: 0x807FFDFA // u8
[SandstormChangeCountdown]: 0x807FFDF9 // u8
[AutoPhaseStateOn]: 0x807FFDF8 // u8
[GiantKoshaTimerAddress]: 0x807FFDF4 // u32
[GiantKoshaTimerValue]: 0x807FFDF2 // u16
[DisplayText]: 0x807FFDE0 // 0x10
[FrameAdvancing]: 0x807FFDDA // u8
[ArtificialPauseOn]: 0x807FFDD9 // u8
[InfiniteHealthCheatOn]: 0x807FFDD8 // u8
[LToLevitateOn]: 0x807FFDD7 // u8
[SelectedFileStatus]: 0x807FFDD6 // u8
[SelectedLMode]: 0x807FFDD5 // u8
[SelectedIndependentCheat]: 0x807FFDD4 // u8
[TimerStartMode]: 0x807FFDD3 // u8
[TimerPauseMode]: 0x807FFDD2 // u8
[TimerFinishMode]: 0x807FFDD1 // u8
[SelectedMasterWarpLevel]: 0x807FFDD0 // u8
[TimerReduction]: 0x807FFDCC // u32 - Pause Menu
[TimerAfterReduction]: 0x807FFDC8 // u32
[SelectedSubWarpLevel]: 0x807FFDC7 // u8
[NewMenuOpen]: 0x807FFDC6 // u8
[NewMenu_Position]: 0x807FFDC5 // u8
[NewMenu_Screen]: 0x807FFDC4 // u8
[NewMenu_ErrorStart]: 0x807FFDC0 // u32
[FocusedSavestate]: 0x807FFDBF // u8
[AutoMoonkickOn]: 0x807FFDBE // u8
[EnemySpawnOff]: 0x807FFDBD // u8
[WatchActor]: 0x807FFDB8 // u32
[PhaseChecker_PreviousMagnitude]: 0x807FFDB7 // u8
[WatchTextSpace]: 0x807FFD80 // 0x30 (47 characters)

// OSD Arrays
[LevelsArray]: 0x807FFF80 // 0x38
[SniperArray]: 0x807FF900 // 0x8
[SlamArray]: 0x807FF908 // 0x4
[Slot3Array]: 0x807FF90C // 0x20
[SandstormText]: 0x807FF990 // 0x4
[MovementStateText]: 0x807FF994 // 0x4
[LoadingZoneTypes]: 0x807FF998 // 0x14
[LoadingZoneMass]: 0x807FF9AC // 0x8

[ActiveTools_Error]: 0x807FFF1C // 0x4
[ActiveToolsMenu]: 0x807FFF20 // 0x60

[MapsArray_Japes]: 0x807FF600 // 0x30
[MapsArray_Aztec]: 0x807FF630 // 0x38
[MapsArray_Factory]: 0x807FF668 // 0x3C
[MapsArray_Galleon]: 0x807FF6A4 // 0x50
[MapsArray_Fungi]: 0x807FF6F4 // 0x5C
[MapsArray_Caves]: 0x807FF750 // 0x58
[MapsArray_Castle]: 0x807FF7A8 // 0x5C
[MapsArray_HelmRool]: 0x807FF804 // 0x20
[MapsArray_Isles]: 0x807FF824 // 0x48
[MapsArray_Master]: 0x807FF86C // 0x30

[SpecialFlagsArray]: 0x807FF500

// SAVEPOSITION STORAGE
[SavedCameraPosition]: 0x807FFEA4 // 3x f32
[SavedVerticalSpeedComponents]: 0x807FFEB0 // 2x f32 (Velocity then Accel)
[SavedHVelocity]: 0x807FFEB4 // f32
[SavedFloor]: 0x807FFEBC // f32
[SavedStoredPosition1]: 0x807FFEC0 // 3x s16
[SavedStoredPosition2]: 0x807FFEC6 // 3x s16
[SavedRotations]: 0x807FFECC // u16 Rot Y (Facing), u16 Rot Z
[SavedPositions]: 0x807FFED0 // 3x f32
[SavedMovement]: 0x807FFEDC // u8
[SavedMovementProgress]: 0x807FFEDD // u8
[SavedPositionMap]: 0x807FFEDE // u8
[SavedBoneArrayCounter]: 0x807FFEDF // u8 (Temp for loading)

// Looper
[LZLooper_On]: 0x807FFA00 // u8
[LZLooper_DestinationMap]: 0x807FFA01 // u8
[LZLooper_DestinationExit]: 0x807FFA02 // u8
[LZLooper_CurrentMap]: 0x807FFA03 // u8
[LZLooper_Mode]: 0x807FFA04 // u8 - 0 = From Position, 1 = From Exit
[LZLooper_HasSavedData]: 0x807FFA05 // u8
[LZLooper_IsRecording]: 0x807FFA06 // u8
[LZLooper_TransitionIndicator]: 0x807FFA07 // u8 - 0 = Not expecting change, 1 = Expecting change

// BUGS LIST:
	// Loading a state from position with savestate 4 causes a crash

.org 0x805FC164 // retroben's hook but up a few functions
J Start

.org 0x80600674 // Lag Hook - Safe
J 	UpdateLag
NOP

.org 0x8000072C // Boot
J 	LoadInAdditionalFile
NOP

.org 0x80646074 // GK Timer Hook - Safe
J 	GrabGKTimerAddress
NOP

.org 0x806F3750 // Kong hook - Safe
J 	KongCode
NOP

//Graphical Overlay Space Expansion
.org 0x8068C374
LA 		t8, GraphicalOverlaySpace

.org 0x8068C310
LA 		a2, GraphicalOverlaySpace

.org 0x8068C240
LA 		s2, GraphicalOverlaySpace

.org 0x8068C364 // Max Overlay limit
SLTI	at, v0, 32

// Start in Isles
.org 0x80714544
ADDIU 		a0, r0, 0x22 // Set destination map to be Isles

.org 0x80714558
ADDIU 		a1, r0, 0x0 // Set destination exit to Exit 0

.org 0x8000DE88 // 0x00DE88 > 0x00EDDA. EDD1 seems the safe limit before overwriting data.

Start:
	// Run the code we replaced
	JAL     0x805FC2B0
	NOP

	SetOtherVariables:
		// // Lag Hook - NOTE: UPDATE ON EVERY REVISION
		// LI 		a1, 0x080002DD
		// SW 		a1, 0x80600674
		// SW 		r0, 0x80600678
		// // GK Timer Hook - NOTE: UPDATE ON EVERY REVISION
		// LI 		a1, 0x08176D2A
		// SW 		a1, 0x80646074
		// SW 		r0, 0x80646078
		// // Kong Hook - NOTE: UPDATE ON EVERY REVISION
		// LI 		a1, 0x08176EBB
		// SW 		a1, 0x806F3750
		// SW 		r0, 0x806F3754
		// // Graphical Overlay Space Expansion - NOTE: UPDATE ON EVERY REVISION
		// LI 		a1, 0x3C18805E
		// SW 		a1, 0x8068C374
		// LI 		a1, 0x2718103C
		// SW 		a1, 0x8068C378
		// //
		// LI 		a1, 0x3C06805E
		// SW 		a1, 0x8068C310
		// LI 		a1, 0x24C6103C
		// SW 		a1, 0x8068C314
		// //
		// LI 		a1, 0x3C12805E
		// SW 		a1, 0x8068C240
		// LI 		a1, 0x2652103C
		// SW 		a1, 0x8068C244
		// //
		// LI 		a1, 0x28410020
		// SW 		a1, 0x8068C364

		// Unlock Mystery Menu
		LI      t6, 0x807ED558
		LI      t0, -1
		SD      t0, 0(t6)
		// Set K Rool to round 11 (Cause the sound effect is the best one)
		LBU 	t0, @InCutscene
		LI 		t6, 6
		BEQ 	t0, t6, TransitionFunctions
		LUI 	t6, 0x3F80 // f32 = 1
		LW 		t0, @TransitionSpeed
		BNE 	t0, t6, EveryFrameFunctions
		NOP

	TransitionFunctions:
		LW 		t6, @RNG
		LI 		a0, 11 // Max Round (RNG % a0). Range 0 - 10
		DIVU 	t6, a0
		MFHI 	t6
		ADDIU 	t6, t6, 1 // Add offset of 1
		SB 		t6, @StoredRound
		LA 		a0, Transition_Flags
		JAL 	SetAllFlags // Safe
		NOP

	EveryFrameFunctions:
		JAL 	ChangeColour // Safe
		NOP
		LBU 	a0, @StoredRound
		LBU 	a1, @DisableTagAnywhere
		BNEZ 	a1, EveryFrameFunctions2
		SB 		a0, @KRoolRound
		JAL 	TagAnywhere // Safe
		NOP
		
	EveryFrameFunctions2:
		JAL 	ToggleSpecialFlag // Safe
		NOP
		JAL 	GlobalSavestateHandler // Safe
		NOP
		JAL 	CheckMapType // Safe
		NOP
		JAL 	VariableDisplay // Safe
		NOP
		JAL 	ResetCLagCounter // Safe
		NOP
		JAL 	GrabSandstormAddress
		NOP
		JAL 	ToggleAztecSandstorm
		NOP
		JAL 	GetGKTimer
		NOP
		JAL 	UpdateMovementStateText
		NOP
		JAL 	InfiniteHealth
		NOP
		JAL 	LToLevitate
		NOP
		JAL  	ActiveMenu_Open
		NOP
		JAL 	ActiveMenu_MoveSlot
		NOP
		JAL 	ActiveMenu_CloseOnTransition
		NOP
		JAL 	ActiveMenu_EmergencyClose
		NOP
		JAL 	ActiveMenu_PressA
		NOP
		JAL 	ActiveMenu_PressB
		NOP
		JAL 	ActiveMenu_UpdateSavestateText
		NOP
		JAL 	Watch_CloseOnTransition
		NOP
		JAL 	Watch_OpenOnTransition
		NOP
		JAL 	LoadingZone_Recording
		NOP
		JAL 	LoadingZone_HandleLooper
		NOP
		JAL 	HandleEnemySpawnPrevent
		NOP
		JAL 	FrameControl_Toggle
		NOP
		JAL 	FrameControl_FrameAdvanceInit
		NOP
		JAL 	FrameControl_FrameAdvanceExit
		NOP
		JAL 	ColourSky
		NOP
		JAL 	StartupSkip
		NOP
		JAL 	ForceStorySkip
		NOP

		// JAL 	HandleTimer
		// NOP
		// JAL 	MenuHeader
		// NOP
		// LA 		s0, List_EveryFrameFunctions

		//FunctionLoop:
		//	LW 		a1, 0x0(s0)
		//	BEQZ 	a1, Finish
		//	NOP
		//	JALR 	a1
		//	NOP
		//	ADDIU 	s0, s0, 4
		//	B 		FunctionLoop
		//	NOP


	Finish:
		J       0x805FC15C // retroben's hook but up a few functions
		NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/PositionSavestates.asm"

CodedSetPermFlag:
	// a0 is parameter for encoded flag
	SW 		ra, @ReturnAddress3
	LI      a1, 1
	JAL     @SetFlag
	LI      a2, 0
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

CodedPlaySFX:
	// a0 is paramater for sound effect index
	SW 		ra, @ReturnAddress3
	LI 		a1, 0x7FFF
	LUI 	a2, 0x427C
	LUI		a3, 0x3F80
	SW 		r0, 0x10 (sp)
	JAL 	@PlaySFX
	SW 		r0, 0x14 (sp)
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/Savestate.asm"
.align

// Check if in Bad Map
CheckMapType:
	LW 		a0, @CurrentMap
	LA 		a1, BadSavestateMaps

	TypeCheckLoop:
		LBU 	a2, 0x0(a1)
		BEQ 	a0, a2, MapTypeInvalid
		NOP
		BNEZ 	a2, TypeCheckLoop
		ADDIU 	a1, a1, 1
		SLTI 	a2, a0, 0x73
		BNEZ 	a2, MapTypeValid
		SLTI 	a3, a0, 0x97
		BEQZ 	a3, MapTypeValid
		NOP

	MapTypeInvalid:
		LI 		a0, 1
		SB 		a0, @InBadMap
		B 		FinishMapCheck

	MapTypeValid:
		SB 		r0, @InBadMap

	FinishMapCheck:
		JR 		ra
		NOP

MultBy60:
	// Input = 60
	SLL 	a2, a1, 2 // a2 = 4 * a1 ; a1 = Original counter
	SUBU 	a2, a2, a1 // a2 = a2 - a1 ; a2 = 3 * Original
	SLL 	a1, a2, 2 // a1 = 4 * a2 ; a1 = 12 * Original
	ADD 	a1, a1, a2 // a1 = a1 + a2 ; a1 = 15 * Original
	JR 		ra
	SLL 	a1, a1, 2 // a1 = a1 * 4 ; a1 = 60 * Original

.org 0x80000A30 // 0x000A30 > 0x0010BC

LoadInAdditionalFile:
    JAL     @DMAFileTransfer
    ADDIU   a0, a0, 0x13F0
    LI      a1, 0x20070EA
    LI      a2, 0x805DAE00
    JAL     @DMAFileTransfer       
    LUI     a0, 0x200 // 0x2000000
    J       0x80000734
    NOP

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

ResetCLagCounter:
	LH 		a1, @NewlyPressedControllerInput
	ANDI 	a1, a1, @L_Button
	BEQZ  	a1, FinishResetCounter
	NOP
	SW 		r0, @CumulativeLag

	FinishResetCounter:
		JR 	ra
		NOP

UpdateSlamSnipe:
	LI 		a0, @MovesBase
	LBU 	a1, @SlamLevel
	SB 		a1, 0x1(a0) // DK Slam
	SB 		a1, 0x5F(a0) // Diddy Slam
	SB 		a1, 0xBD(a0) // Lanky Slam
	SB 		a1, 0x11B(a0) // Tiny Slam
	SB 		a1, 0x179(a0) // Chunky Slam
	LBU 	a1, @SniperOn // ANDI Statement: 0x7 on, 0x3 off
	SLL 	t9, a1, 2
	ADDIU 	a1, t9, 3
	// DK Gun Bitfield
	LBU 	a2, 0x2(a0)
	AND 	a3, a2, a1
	OR 		a2, a3, t9
	SB 		a2, 0x2(a0)
	// Diddy Gun Bitfield
	LBU 	a2, 0x60(a0)
	AND 	a3, a2, a1
	OR 		a2, a3, t9
	SB 		a2, 0x60(a0)
	// Lanky Gun Bitfield
	LBU 	a2, 0xBE(a0)
	AND 	a3, a2, a1
	OR 		a2, a3, t9
	SB 		a2, 0xBE(a0)
	// Tiny Gun Bitfield
	LBU 	a2, 0x11C(a0)
	AND 	a3, a2, a1
	OR 		a2, a3, t9
	SB 		a2, 0x11C(a0)
	// Chunky Gun Bitfield
	LBU 	a2, 0x17A(a0)
	AND 	a3, a2, a1
	OR 		a2, a3, t9
	JR 		ra
	SB 		a2, 0x17A(a0)

UpdateLag:
	// Our Code
	LW 		a0, @FrameReal
	LW 		a1, @FrameLag
	SUBU 	a1, a0, a1
	SW 		a1, @StoredLag
	// Run code we replaced
	LUI 	t6, 0x8077
	J 		0x8060067C
	LBU 	t6, 0xAF14(t6)

// Who says it's only Link's tunic which can change colour
ChangeColour:
	SW 		ra, @ReturnAddress
	LUI 	a0, 0x8069	
	SB 		r0, 0xA62F(a0) // 0x8068A62F // Enable colouring for 1-player gameplay
	SW 		r0, 0xA450(a0) // 0x8068A450 // Disable shading
	JAL 	0x8068A508
	// NOP
	SW 		r0, 0xA458(a0) // 0x8068A458 // Turn off low poly models
	LA 		a0, KongColours
	LBU 	a1, @Character
	ADD 	a0, a0, a1
	LBU 	a1, 0x0 (a0)
	SW 		a1, @PlayerOneColour

	FinishColourChange:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

.org 0x805DAE00
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Watches.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Input.asm"
.align

// Loops through a flag array and sets all of them
// Credit: Isotarge (Tag Anywhere V5)
SetAllFlags:
	// Params:
	// a0 = Array
	ADDIU	sp, sp, -0x18 // Push S0
	SW		s0, 0x10(sp)
	SW 		ra, 0x14(sp)
	NOP

	// Load flag array base into register to loop with
	ADDIU 	s0, a0, 0

	SetAllFlagsLoop:
	    LHU     a0, 0(s0) // Load the flag index from the array
	    BEQZ    a0, FinishSettingAllFlags // If the flag index is 0, exit the loop
	    NOP
	    JAL     CodedSetPermFlag
	    NOP
	    B       SetAllFlagsLoop
	    ADDIU   s0, s0, 2 // Move on to the next flag in the array

	FinishSettingAllFlags:
		LW		s0, 0x10(sp)  // Pop S0
		LW 		ra, 0x14(sp)
		JR
		ADDIU	sp, sp, 0x18

// Loops through a flag array and sets all of them
// Credit: Isotarge (Tag Anywhere V5)
ClearAllFlags:
	// Params:
	// a0 = Array
	ADDIU	sp, sp, -0x18 // Push S0
	SW		s0, 0x10(sp)
	SW 		ra, 0x14(sp)
	NOP

	// Load flag array base into register to loop with
	ADDIU 	s0, a0, 0

	ClearAllFlagsLoop:
	    LHU     a0, 0(s0) // Load the flag index from the array
	    BEQZ    a0, FinishClearingAllFlags // If the flag index is 0, exit the loop
	    LI 		a1, 0
	    JAL     @SetFlag
	    LI 		a2, 0
	    B       ClearAllFlagsLoop
	    ADDIU   s0, s0, 2 // Move on to the next flag in the array

	FinishClearingAllFlags:
		LW		s0, 0x10(sp)  // Pop S0
		LW 		ra, 0x14(sp)
		JR
		ADDIU	sp, sp, 0x18

.incasm "./../../Development/dk64-practice-rom/Source/Features/TagAnywhere.asm"
.align

GiveCoins:
	SW 		ra, @ReturnAddress4
	LI 		a0, @MovesBase
	LI 		a1, 50
	SH 		a1, 0x0006(a0) // DK
	SH 		a1, 0x0064(a0) // Diddy
	SH 		a1, 0x00C2(a0) // Lanky
	SH 		a1, 0x0120(a0) // Tiny
	SH 		a1, 0x017E(a0) // Chunky
	JAL 	CodedPlaySFX
	LI 		a0, @Coin
	LW 		ra, @ReturnAddress4
	JR 		ra
	NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/Sandstorm.asm"

.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/GiantKosha.asm"

AutoPhaseState:
	LBU 	a0, @AutoPhaseStateOn
	BEQZ 	a0, FinishAutoPhaseState
	NOP
	LW 		a0, @Player
	BEQZ 	a0, FinishAutoPhaseState
	NOP
	LHU	 	a1, 0xE6 (a0) // Facing Angle
	LHU 	a3, 0x18A (a0) // Moving Angle
	SLTIU 	a2, a1, 2048 // 4096 for hyper-extended phase state
	BEQZ 	a2, FinishAutoPhaseState
	NOP
	ADDIU 	a1, a1, 4096
	ADDIU 	a3, a3, 4096
	SH 		a1, 0xE6 (a0)
	SH 		a1, 0xEE (a0)
	SH 		a3, 0x18A (a0)

	FinishAutoPhaseState:
		JR 		ra
		NOP

AutoMoonkick:
	LBU 	a0, @AutoMoonkickOn
	BEQZ 	a0, AutoMoonkick_Finish
	NOP
	LBU 	a0, @Character
	BNEZ 	a0, AutoMoonkick_Finish
	NOP
	LW 		a0, @Player
	BEQZ 	a0, AutoMoonkick_Finish
	NOP
	LBU 	a1, 0x154 (a0) // Control State
	LI 		a2, 0x29
	BNE 	a1, a2, AutoMoonkick_Finish
	NOP
	LUI 	a2, 0xC020 // -2.5 
	SW	 	a2, 0xC4 (a0) // Y-Accel

	AutoMoonkick_Finish:
		JR 		ra
		NOP

UpdateMovementStateText:
	SW 		ra, @ReturnAddress
	LBU 	a0, @VariableDisplayOn
	LI 		a1, @MovementStateIndex
	BNE 	a0, a1, FinishUpdatingStateText
	NOP
	LW 		a0, @Player
	BEQZ 	a0, FinishUpdatingStateText
	NOP
	LBU 	a1, 0x154 (a0)
	LA 		a2, MovementStates
	LA 		a3, MovementStates_length

	LoopThroughText:
		BEQZ 	a1, WriteMovementStatePointer
		NOP
		ADDI 	a1, a1, -1
		LBU 	t6, 0x0 (a3)
		ADDIU 	t6, t6, 1
		ADD 	a2, a2, t6
		B 		LoopThroughText
		ADDIU 	a3, a3, 1

	WriteMovementStatePointer:
		JAL 	CopyTextToWatch
		ADDIU 	a0, a2, 0

	FinishUpdatingStateText:
		LW 		ra, @ReturnAddress
		JR 		ra
		NOP

CopyTextToWatch:
	// a0 = Text Pointer
	LI 		a1, @WatchTextSpace

	CopyTextToWatch_Loop:
		LBU 	a2, 0x0 (a0)
		SB 		a2, 0x0 (a1)
		BEQZ 	a2, CopyTextToWatch_Finish
		ADDIU 	a0, a0, 1
		B 		CopyTextToWatch_Loop
		ADDIU 	a1, a1, 1

	CopyTextToWatch_Finish:
		JR 		ra
		NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/FormatTextForWatch.asm"

ConvertCodePointerForWatchText:
	// a1 = New Address
	SRL 	a2, a1, 16
	ANDI 	a0, a1, 0xFFFF
	SLTIU 	a1, a0, 0x8000
	ADD 	a2, a2, a1
	SH 		a2, 0x8068E80A
	SH 		a0, 0x8068E812
	JR 		ra
	NOP

InfiniteHealth:
	LBU 	a0, @InfiniteHealthCheatOn
	BEQZ 	a0, InfiniteHealth_Finish
	NOP
	LI 		a0, @CollectableBase
	LBU 	a1, 0xC (a0) // Grab Melons
	SLL 	a1, a1, 2
	SB 		a1, 0xB (a0) // Grab Health
	
	InfiniteHealth_Finish:
		JR 		ra
		NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/FileStates.asm"
.align

LToLevitate:
	LBU 	a0, @LToLevitateOn
	BEQZ 	a0, LToLevitate_Finish
	NOP
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, LToLevitate_Finish // Pause Menu
	NOP
	LH 		a0, @ControllerInput
	ANDI 	a0, a0, @L_Button
	BEQZ 	a0, LToLevitate_Finish
	NOP
	LW 		a0, @Player
	BEQZ 	a0, LToLevitate_Finish
	NOP
	LH 		a1, @ControllerInput
	ANDI 	a1, a1, @R_Button
	BNEZ 	a1, FastLevitate
	NOP
	LH 		a1, @ControllerInput
	ANDI 	a1, a1, @Z_Button
	BNEZ 	a1, SlowLevitate
	NOP
	B 		NormalLevitate
	NOP

	FastLevitate:
		B 		IncrementHeight
		LUI 	a1, 0x41A0 // 20 as float

	SlowLevitate:
		B 		IncrementHeight
		LUI 	a1, 0x40A0 // 10 as float

	NormalLevitate:
		LUI 	a1, 0x4120 // 10 as float

	IncrementHeight:
		MTC1 	a1, f2
		SW 		r0, 0xC0 (a0) // Set Y Veloc
		LW 		a1, 0x80 (a0)
		MTC1 	a1, f0
		ADD.S 	f0, f0, f2
		MFC1 	a1, f0
		SW 		a1, 0x80 (a0)

	LToLevitate_Finish:
		JR 		ra
		NOP

CancelCutscene:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @TBVoidByte
	ANDI 	a0, a0, 2
	BNEZ 	a0, CancelCutscene_Finish // Pause Menu
	NOP
	LBU 	a0, @CutsceneActive
	BEQZ 	a0, CancelCutscene_Finish
	NOP
	LH 		a0, @CutsceneIndex
	LW 		a1, @CutsceneTypePointer
	BEQZ 	a1, CancelCutscene_Finish
	NOP
	LW  	a1, 0xD0 (a1) // Cutscene Databank
	BEQZ 	a1, CancelCutscene_Finish
	NOP
	LI 		a2, 0xC
	MULTU 	a0, a2
	MFLO 	a2
	ADD 	a1, a1, a2
	LH 		a1, 0x0 (a1) // Required Cam State
	SH 		a1, @CurrentCameraState
	SH 		a1, @PreviousCameraState
	ADDI 	a1, a1, -1
	SH 		r0, @CameraStateChangeTimer
	LW 		a0, @Player
	BEQZ 	a0, CancelCutscene_Finish
	NOP
	LI 		a1, 0xC
	SB 		a1, 0x154 (a0)

	CancelCutscene_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

KongCode:
	SW 		ra, @ReturnAddress2
	JAL 	AutoPhaseState
	NOP
	JAL 	AutoMoonkick
	NOP
	LBU		t6, @DisablePositionButtons
	BNEZ 	t6, KongCode_Finish
	NOP
	JAL 	PositionSavestates
	NOP

	KongCode_Finish:
		LW 		ra, @ReturnAddress2
		LW 		s0, 0x28 (sp)
		ADDIU 	sp, sp, 0x78
		J 		0x806F3758
		NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Timer.asm"

GiveMoves:
	LI 		a0, 4
	LI 		a1, @MovesBase
	GiveMoves_WriteMoves:
		LI 		t3, 0x0303
		SH 		t3, 0x0 (a1) // Special | Slam Level | Guns | Ammo Belt
		LI 		t3, 0x0702
		SH 		t3, 0x2 (a1) // Gun Bitfield, Ammo belt
		LI 		t3, 15
		SB 		t3, 0x4 (a1) // Instrument
		BEQZ 	a0, GiveMoves_WriteMoveFlags
		ADDI 	a0, a0, -1 // Decrement Value for next kong
		B 		GiveMoves_WriteMoves
		ADDIU 	a1, a1, 0x5E // Next kong base
	
	GiveMoves_WriteMoveFlags:
		SW 		ra, @ReturnAddress4
		LI 		a0, @CollectableBase
		// Melons
		LI 		a1, 3
		SB 		a1, 0xC(a0)
		// Health
		LI 		a1, 12
		SB 		a1, 0xB(a0)
		// How were your trading barrels this run?
		LA 		a0, MoveFlags
		JAL 	SetAllFlags
		NOP
		LA 		a0, Menu_MovesMaster_CameraOn
		LA 		a1, Menu_MovesMaster_Array
		SW 		a0, 0x14 (a1)
		LBU 	a1, @NewMenuOpen
		BEQZ 	a1, GiveMoves_PlaySFX
		LI 		a0, 31
		LBU 	a1, @NewMenu_Screen
		BNE 	a0, a1, GiveMoves_PlaySFX
		NOP
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 31
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP

	GiveMoves_PlaySFX:
		// Sound Effect
		JAL 	CodedPlaySFX
		LI 		a0, @Potion
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

ClearMoves:
	LI 		a0, 4
	LI 		a1, @MovesBase
	ClearMoves_WriteMoves:
		SH 		r0, 0x0 (a1) // Special | Slam Level | Guns | Ammo Belt
		SH 		r0, 0x2 (a1) // Gun Bitfield, Ammo belt
		SB 		r0, 0x4 (a1) // Instrument
		BEQZ 	a0, ClearMoves_WriteMoveFlags
		ADDI 	a0, a0, -1 // Decrement Value for next kong
		B 		ClearMoves_WriteMoves
		ADDIU 	a1, a1, 0x5E // Next kong base
	
	ClearMoves_WriteMoveFlags:
		SW 		ra, @ReturnAddress4
		LI 		a0, @CollectableBase
		// Melons
		LI 		a1, 1
		SB 		a1, 0xC(a0)
		// Health
		LI 		a1, 4
		SB 		a1, 0xB(a0)
		// How were your trading barrels this run?
		LA 		a0, MoveFlags
		JAL 	ClearAllFlags
		NOP
		LA 		a0, Menu_MovesMaster_CameraOff
		LA 		a1, Menu_MovesMaster_Array
		SW 		a0, 0x14 (a1)
		LBU 	a1, @NewMenuOpen
		BEQZ 	a1, ClearMoves_PlaySFX
		LI 		a0, 31
		LBU 	a1, @NewMenu_Screen
		BNE 	a0, a1, ClearMoves_PlaySFX
		NOP
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 31
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP

	ClearMoves_PlaySFX:
		// Sound Effect
		JAL 	CodedPlaySFX
		LI 		a0, @MatchingSound
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

RestockInventory:
	SW 		ra, @ReturnAddress4
	// Standard Ammo
	LI 		a0, @CollectableBase
	LI 		a1, 200
	SH 		a1, 0x0(a0)
	// Crystals
	LI 		a1, 3000 // Each crystal is 150, so this is 20 Crystals
	SH 		a1, 0x6(a0)
	// Film & Oranges
	LI 		a1, 20
	SH 		a1, 0x4(a0) // Oranges
	SH 		a1, 0x8(a0) // Film
	// Health
	LBU 	a1, 0xC (a0) // Grab Melons
	SLL 	a1, a1, 2
	SB 		a1, 0xB (a0) // Grab Health
	// Instrument Ammo
	LI 		a0, @MovesBase
	LI 		a1, 10
	SH 		a1, 0x0008(a0) // DK
	SH 		a1, 0x0066(a0) // Diddy
	SH 		a1, 0x00C4(a0) // Lanky
	SH 		a1, 0x0122(a0) // Tiny
	SH 		a1, 0x0180(a0) // Chunky
	// Sound Effect
	JAL 	CodedPlaySFX
	LI 		a0, @AmmoPickup
	LW 		ra, @ReturnAddress4
	JR 		ra
	NOP

SkewCheat:
	LW 		a0, @Player
	BEQZ 	a0, SkewCheat_Finish
	NOP
	LI 		a1, 0xC00
	SH 		a1, 0xE8 (a0)

	SkewCheat_Finish:
		JR 		ra
		NOP

HandleEnemySpawnPrevent:
	LW 		a0, @ObjectModel2Timer
	LI 		a1, 1
	BNE 	a0, a1, HandleEnemySpawnPrevent_Finish
	NOP
	LBU 	a0, @EnemySpawnOff
	BEQZ 	a0, HandleEnemySpawnPrevent_Finish
	NOP
	LW 		a0, @SpawnerArray
	LHU 	a1, @SpawnerCount

	HandleEnemySpawnPrevent_Loop:
		LBU 	t9, 0x0 (a0)
		LA 		t3, SpawnEnemyTypeAvoid

	HandleEnemySpawnPrevent_TypeLoop:
		LBU 	t6, 0x0 (t3)
		BEQZ 	t6, HandleEnemySpawnPrevent_Toggle
		ADDIU 	t3, t3, 1
		BEQ 	t6, t9, HandleEnemySpawnPrevent_Increment
		NOP
		B 		HandleEnemySpawnPrevent_TypeLoop
		NOP

	HandleEnemySpawnPrevent_Toggle:
		LBU 	t9, 0x42 (a0)
		ADDIU 	t9, t9, 8
		SB 		t9, 0x42 (a0)

	HandleEnemySpawnPrevent_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, HandleEnemySpawnPrevent_Finish
		ADDIU 	a0, a0, 0x48
		B 		HandleEnemySpawnPrevent_Loop
		NOP

	HandleEnemySpawnPrevent_Finish:
		JR 		ra
		NOP

.incasm "./../../Development/dk64-practice-rom/Source/Features/LZLooper.asm"

.incasm "./../../Development/dk64-practice-rom/Source/Features/FrameControl.asm"

.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/WatchControl.asm"

.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/base.asm"

ActiveMenu_OpenMapWarper:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 1
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Japes:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 2
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_JapesMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 11
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Aztec:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 3
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_AztecMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 12
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Aztec5DT:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 13
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Factory:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 4
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_FactoryMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 14
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Galleon:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 5
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_GalleonMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 15
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_GalleonShipwrecks:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 16
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Fungi:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 6
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_FungiMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 17
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_FungiGMush:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 18
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Caves:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 7
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_CavesMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 19
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Caves5DC:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 20
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Caves5DI:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 21
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Castle:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 8
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_CastleMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 22
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_CastleCrypt:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 23
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_CastleTunnel:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 24
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_HelmKRool:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 9
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_Isles:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 10
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_IslesMain:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 25
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_IslesLobbies:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 26
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenSavestateMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 27
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenChangeSavestateMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 28
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMovesMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 31
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_ChangeSavestate:
	SW 		ra, @ReturnAddress3
	LBU 	a1, @NewMenu_Position
	SB 		a1, @FocusedSavestate
	LA 		a0, Menu_Savestate_SelectedSavestate
	ADDIU 	a1, a1, 0x31
	SB 		a1, 0x10 (a0)
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 27
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	SB 		r0, @LZLooper_On
	SB 		r0, @LZLooper_HasSavedData
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenCheatsMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 30
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenGamemodeMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 32
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenWatchMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 33
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenSettingsMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 34
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenDPadLRMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 35
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_UpdateSavestateText:
	LA 		a1, Menu_Savestate_SelectedSavestate
	LBU 	a0, @FocusedSavestate
	ADDIU 	a0, a0, 0x31
	SB 		a0, 0x10 (a1)
	JR 		ra
	NOP

ActiveMenu_PerformSavestateAction_Save:
	LI 		a1, 1
	SB 		a1, @MenuSavestateAction
	JR 		ra
	NOP

ActiveMenu_PerformSavestateAction_LoadFromPosition:
	LI 		a1, 2
	SB 		a1, @MenuSavestateAction
	JR 		ra
	NOP

ActiveMenu_PerformSavestateAction_LoadFromExit:
	LI 		a1, 3
	SB 		a1, @MenuSavestateAction
	JR 		ra
	NOP

ActiveMenu_OpenLooperMenu:
	SW 		ra, @ReturnAddress4
	LA 		a0, Savestate_Array
	LBU 	a1, @FocusedSavestate
	SLL 	a1, a1, 2
	ADD 	a0, a0, a1
	LW 		a0, 0x0 (a0) // Savestate Struct
	LBU 	a0, @SavestateStruct_SavedData (a0)
	BNEZ 	a0, ActiveMenu_OpenLooperMenu_SavedData
	NOP
	JAL 	CodedPlaySFX
	LI 		a0, @Wrong
	B 		ActiveMenu_OpenLooperMenu_Finish
	NOP

	ActiveMenu_OpenLooperMenu_SavedData:
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 29
		SB 		a0, @NewMenu_Screen
		SB 		r0, @NewMenu_Position
		JAL 	ActiveMenu_SpawnMenu
		NOP

	ActiveMenu_OpenLooperMenu_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

ActiveMenu_WarpToMap:
	SW 		ra, @ReturnAddress4
	LBU		a1, @InBadMap
	BNEZ 	a1, ActiveMenu_WarpToMap_Error
	NOP
	LA 		a0, Maps_WarpingStruct
	LI 		a1, @MasterLevelCount

	ActiveMenu_WarpToMap_Loop:
		LBU 	t6, @NewMenu_Screen
		LW 		a3, 0x0 (a0) // Level Struct
		LBU 	a2, 0x8 (a3) // Screen
		BEQ 	a2, t6, ActiveMenu_WarpToMap_FoundMap
		ADDI 	a1, a1, -1
		BEQZ 	a1, ActiveMenu_WarpToMap_Finish
		ADDIU 	a0, a0, 4
		B 		ActiveMenu_WarpToMap_Loop
		NOP

	ActiveMenu_WarpToMap_FoundMap:
		// Timer Mode
		SW 		r0, @StoredTime
		SB 		r0, @StoredTimerMode
		// Clear some K Rool stuff to prevent Bugs
		LI 		a0, @TempFlagBlock
		LH 		a1, 0xA(a0)
		ORI 	a1, a1, 0x0021
		ANDI 	a1, a1, 0xE17F
		SH 		a1, 0xA(a0)
		// B. Locker FTT
		SW 		a3, @VarStorage0
		JAL 	CodedSetPermFlag
		LI 		a0, 0x17E
		LW 		a3, @VarStorage0
		// a3 = Level Struct
		LBU 	t6, @NewMenu_Position
		LW 		t9, 0x0 (a3) // Map Array
		ADD 	t9, t9, t6
		LBU 	a0, 0x0 (t9)
		LW 		t9, 0x4 (a3) // Exit Array
		ADD 	t9, t9, t6
		JAL 	@InitiateTransition
		LBU 	a1, 0x0 (t9)
		// Handle K. Rool
		SLTI 	a3, a0, 0xCB
		BNEZ	a3, ActiveMenu_WarpToMap_Finish // Not warping to K Rool
		SLTI 	a3, a0, 0xD0
		BEQZ 	a3, ActiveMenu_WarpToMap_Finish // Not warping to K Rool
		ADDI 	a3, a0, -0xCB // Get Character Index
		SB 		a3, @Character
		LI 		a3, 0xCD
		BEQ 	a0, a3 ActiveMenu_WarpToMap_Finish // If Lanky Phase, don't do some things
		// Lanky Phase Bugs
		// Reset everything
		LI      a0, 92
		LI      a1, 1
		JAL     @SetFlag
		LI      a2, 2
		B 		ActiveMenu_WarpToMap_Finish
		NOP

	ActiveMenu_WarpToMap_Error:
		JAL 	CodedPlaySFX
		LI 		a0, @Wrong
		B 		ActiveMenu_WarpToMap_Finish
		NOP

	ActiveMenu_WarpToMap_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

ActiveMenu_SetGamemode:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @NewMenu_Position
	LI 		a1, @Gamemode
	SB 		a0, 0x0 (a1)
	SB 		a0, 0x4 (a1)
	JAL 	CodedPlaySFX
	LI 		a0, @CameraPull
	LW 		ra, @ReturnAddress4
	JR 		ra
	NOP

ActiveMenu_SetDPadLR:
	SW 		ra, @ReturnAddress3
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1
	SB 		a0, @DisablePositionButtons
	// Array
	LA 		a1, Menu_HorizontalDPad_Mode_Array
	SLL 	a2, a0, 2
	ADD 	a1, a1, a2
	LW 		a1, 0x0 (a1)
	// Setting into
	LA 		a2, Menu_HorizontalDPad_Array
	SW 		a1, 0x0 (a2)
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 35
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_LZLooper_ToggleOn:
	SW 		ra, @ReturnAddress4
	LBU 	a1, @LZLooper_HasSavedData
	BEQZ 	a1, ActiveMenu_LZLooper_ToggleOn_Finish
	NOP
	LBU 	a1, @LZLooper_On
	LI 		a0, 1
	SUBU 	a1, a0, a1
	SB 		a1, @LZLooper_On
	BEQZ 	a1, ActiveMenu_LZLooper_ToggleOn_TurningOff
	NOP

	ActiveMenu_LZLooper_ToggleOn_TurningOn:
		LA 		a1, Menu_LZLooperSettings_TurnOffLooper
		LA 		a0, Menu_LZLooperSettings_Array
		B 		ActiveMenu_LZLooper_ToggleOn_UpdateMenu
		SW 		a1, 0x0 (a0)

	ActiveMenu_LZLooper_ToggleOn_TurningOff:
		LA 		a1, Menu_LZLooperSettings_TurnOnLooper
		LA 		a0, Menu_LZLooperSettings_Array
		SW 		a1, 0x0 (a0)

	ActiveMenu_LZLooper_ToggleOn_UpdateMenu:
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 29
		JAL 	ActiveMenu_SpawnMenu
		NOP

	ActiveMenu_LZLooper_ToggleOn_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

ActiveMenu_LZLooper_ToggleMode:
	SW 		ra, @ReturnAddress4
	LBU 	a1, @LZLooper_Mode
	LI 		a0, 1
	SUBU 	a1, a0, a1
	SB 		a1, @LZLooper_Mode
	BEQZ 	a1, ActiveMenu_LZLooper_ToggleMode_ChangeToPosition
	NOP

	ActiveMenu_LZLooper_ToggleMode_ChangeToExit:
		LA 		a1, Menu_LZLooperSettings_ModeExit
		LA 		a0, Menu_LZLooperSettings_Array
		B 		ActiveMenu_LZLooper_ToggleMode_UpdateMenu
		SW 		a1, 0x8 (a0)

	ActiveMenu_LZLooper_ToggleMode_ChangeToPosition:
		LA 		a1, Menu_LZLooperSettings_ModePosition
		LA 		a0, Menu_LZLooperSettings_Array
		SW 		a1, 0x8 (a0)

	ActiveMenu_LZLooper_ToggleMode_UpdateMenu:
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 29
		JAL 	ActiveMenu_SpawnMenu
		NOP

	ActiveMenu_LZLooper_ToggleMode_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

ActiveMenu_LZLooper_StartRecording:
	SW 		ra, @ReturnAddress4
	LI 		a0, 1
	SB 		a1, @LZLooper_IsRecording
	LA 		a1, Menu_LZLooperSettings_RecordIsRecording
	LA 		a0, Menu_LZLooperSettings_Array
	SW 		a1, 0x4 (a0)
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 29
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress4
	JR 		ra
	NOP

ActiveMenu_ToggleLToLevitate:
	LI 		a1, 1
	LBU 	a0, @LToLevitateOn
	SUBU 	a0, a1, a0
	SB 		a0, @LToLevitateOn
	LA 		a2, Menu_Cheats_Array 
	BEQZ 	a0, ActiveMenu_ToggleLToLevitate_IsOff
	NOP
	LA 		a1, Menu_Cheats_LToLevitateOn
	B 		ActiveMenu_ToggleLToLevitate_Finish
	NOP

	ActiveMenu_ToggleLToLevitate_IsOff:
		LA 		a1, Menu_Cheats_LToLevitateOff

	ActiveMenu_ToggleLToLevitate_Finish:
		SW 		a1, 0x18 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 30
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ToggleAutoPhaseState:
	LI 		a1, 1
	LBU 	a0, @AutoPhaseStateOn
	SUBU 	a0, a1, a0
	SB 		a0, @AutoPhaseStateOn
	LA 		a2, Menu_Cheats_Array 
	BEQZ 	a0, ActiveMenu_ToggleAutoPhaseState_IsOff
	NOP
	LA 		a1, Menu_Cheats_AutoPhaseOn
	B 		ActiveMenu_ToggleAutoPhaseState_Finish
	NOP

	ActiveMenu_ToggleAutoPhaseState_IsOff:
		LA 		a1, Menu_Cheats_AutoPhaseOff

	ActiveMenu_ToggleAutoPhaseState_Finish:
		SW 		a1, 0x20 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 30
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ToggleAutoMoonkick:
	LI 		a1, 1
	LBU 	a0, @AutoMoonkickOn
	SUBU 	a0, a1, a0
	SB 		a0, @AutoMoonkickOn
	LA 		a2, Menu_Cheats_Array 
	BEQZ 	a0, ActiveMenu_ToggleAutoMoonkick_IsOff
	NOP
	LA 		a1, Menu_Cheats_AutoMoonkickOn
	B 		ActiveMenu_ToggleAutoMoonkick_Finish
	NOP

	ActiveMenu_ToggleAutoMoonkick_IsOff:
		LA 		a1, Menu_Cheats_AutoMoonkickOff

	ActiveMenu_ToggleAutoMoonkick_Finish:
		SW 		a1, 0x24 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 30
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ToggleInfHealth:
	LI 		a1, 1
	LBU 	a0, @InfiniteHealthCheatOn
	SUBU 	a0, a1, a0
	SB 		a0, @InfiniteHealthCheatOn
	LA 		a2, Menu_Cheats_Array 
	BEQZ 	a0, ActiveMenu_ToggleInfHealth_IsOff
	NOP
	LA 		a1, Menu_Cheats_InfHealthOn
	B 		ActiveMenu_ToggleInfHealth_Finish
	NOP

	ActiveMenu_ToggleInfHealth_IsOff:
		LA 		a1, Menu_Cheats_InfHealthOff

	ActiveMenu_ToggleInfHealth_Finish:
		SW 		a1, 0x28 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 30
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ToggleEnemySpawn:
	LI 		a1, 1
	LBU 	a0, @EnemySpawnOff
	SUBU 	a0, a1, a0
	SB 		a0, @EnemySpawnOff
	LA 		a2, Menu_Cheats_Array 
	BEQZ 	a0, ActiveMenu_ToggleEnemySpawn_IsOn
	NOP
	LA 		a1, Menu_Cheats_EnemySpawnOff
	B 		ActiveMenu_ToggleEnemySpawn_DefineLoop
	NOP

	ActiveMenu_ToggleEnemySpawn_IsOn:
		LA 		a1, Menu_Cheats_EnemySpawnOn

	ActiveMenu_ToggleEnemySpawn_DefineLoop:
		SW 		a1, 0x2C (a2)
		LW 		a0, @SpawnerArray
		LHU 	a1, @SpawnerCount
		LBU 	a2, @EnemySpawnOff
		BEQZ 	a1, ActiveMenu_ToggleEnemySpawn_Finish
		SLL 	a2, a2, 4
		ADDI 	a2, a2, -8

	ActiveMenu_ToggleEnemySpawn_Loop:
		LBU 	t9, 0x0 (a0)
		LA 		t3, SpawnEnemyTypeAvoid

	ActiveMenu_ToggleEnemySpawn_TypeLoop:
		LBU 	t6, 0x0 (t3)
		BEQZ 	t6, ActiveMenu_ToggleEnemySpawn_Toggle
		ADDIU 	t3, t3, 1
		BEQ 	t6, t9, ActiveMenu_ToggleEnemySpawn_Increment
		NOP
		B 		ActiveMenu_ToggleEnemySpawn_TypeLoop
		NOP

	ActiveMenu_ToggleEnemySpawn_Toggle:
		LBU 	t9, 0x42 (a0)
		ADD 	t9, t9, a2
		SB 		t9, 0x42 (a0)

	ActiveMenu_ToggleEnemySpawn_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, ActiveMenu_ToggleEnemySpawn_Finish
		ADDIU 	a0, a0, 0x48
		B 		ActiveMenu_ToggleEnemySpawn_Loop
		NOP

	ActiveMenu_ToggleEnemySpawn_Finish:
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 30
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ChangeWatch:
	SW 		ra, @ReturnAddress3
	SB 		r0, 0x807FFDBC
	LBU 	a3, @VariableDisplayOn // Old Variable Display Value
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1 // Change display options start at position 1, so offset back
	SB 		a0, @VariableDisplayOn
	SLL 	a0, a0, 2
	LA 		a1, Menu_Watch_Viewed_Array
	ADD 	a1, a1, a0
	LA 		a2, Menu_Watch_Array
	LW 		a1, 0x0 (a1)
	SW 		a1, 0x0 (a2)
	BEQZ 	a3, ActiveMenu_ChangeWatch_WasOff
	NOP

	ActiveMenu_ChangeWatch_WasOn:
		LBU 	a3, @VariableDisplayOn
		BEQZ 	a3, ActiveMenu_ChangeWatch_Destroy
		NOP
		B 		ActiveMenu_ChangeWatch_Reload
		NOP

	ActiveMenu_ChangeWatch_WasOff:
		LBU 	a3, @VariableDisplayOn
		BEQZ 	a3, ActiveMenu_ChangeWatch_Reload
		NOP

	ActiveMenu_ChangeWatch_Spawn:
		JAL 	Watch_SpawnWatch
		NOP
		LI 		a0, 1
		SB 		a0, 0x807FFDBC
		B 		ActiveMenu_ChangeWatch_Reload
		NOP

	ActiveMenu_ChangeWatch_Destroy:
		JAL 	Watch_DestroyWatch
		NOP
		LI 		a0, 2
		SB 		a0, 0x807FFDBC

	ActiveMenu_ChangeWatch_Reload:
		LI 		a0, 0xFFFFFF
		JAL 	Watch_ColourWatch
		NOP
		JAL 	ActiveMenu_ClearMenu
		NOP
		JAL 	ActiveMenu_SpawnMenu
		LI 		a0, 33
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
ROM_Name:
	.asciiz "PRACTICE THROUGH VERTICAL WALLS"
Maps_Title:
	.asciiz "WARP TO MAP"
Display_Calibrating:
	.asciiz "CALIBRATING..."
OutOfCavesText:
	.asciiz "THIS AIN'T CAVES, BUD"

.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Japes.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Aztec.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Factory.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Galleon.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Fungi.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Caves.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Castle.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/HelmAndKRool.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Isles.asm"

.align
Maps_WarpingStruct:
	.word Maps_JungleJapes_Struct
	.word Maps_AngryAztec_Struct
	.word Maps_FranticFactory_Struct
	.word Maps_GloomyGalleon_Struct
	.word Maps_FungiForest_Struct
	.word Maps_CrystalCaves_Struct
	.word Maps_CreepyCastle_Struct
	.word Maps_HideoutHelmKRool_Struct
	.word Maps_Isles_Struct
	.word Maps_JungleJapesMain_Struct
	.word Maps_AngryAztecMain_Struct
	.word Maps_AngryAztec5DT_Struct
	.word Maps_FranticFactoryMain_Struct
	.word Maps_GloomyGalleonMain_Struct
	.word Maps_GloomyGalleonShipwrecks_Struct
	.word Maps_FungiForestMain_Struct
	.word Maps_FungiForestGiantMushroom_Struct
	.word Maps_CrystalCavesMain_Struct
	.word Maps_CrystalCaves5DC_Struct
	.word Maps_CrystalCaves5DI_Struct
	.word Maps_CreepyCastleMain_Struct
	.word Maps_CreepyCastleCrypt_Struct
	.word Maps_CreepyCastleTunnel_Struct
	.word Maps_IslesMain_Struct
	.word Maps_IslesLobbies_Struct

.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Container.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Kongs.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/KeysIn.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/KeysHave.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/LevelIntros.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/LevelTnS.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Bosses.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Cutscenes.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Modifiers.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Misc.asm"

.align
BadSavestateMaps:
	.byte 0x01 // Funky's
	.byte 0x03 // Lanky's Maze
	.byte 0x05 // Cranky's Lab
	.byte 0x08 // Japes: Dillo
	.byte 0x0A // KKosh (V Easy)
	.byte 0x0F // Snide's
	.byte 0x12 // TTTrouble (V Easy)
	.byte 0x19 // Candy's
	.byte 0x20 // BBBandit (Easy)
	.byte 0x23 // DK Target Minigame
	.byte 0x2A // Troff n Scoff
	.byte 0x32 // Tiny Mush Bounce Minigame
	.byte 0x35 // Crown - Beaver Bother
	.byte 0x41 // SSnoop (Normal)
	.byte 0x42 // MMMaul (Hard)
	.byte 0x43 // SSnatch (Hard)
	.byte 0x44 // MMMaul (Easy)
	.byte 0x45 // MMMaul (Normal)
	.byte 0x49 // Crown - Kritter Karnage
	.byte 0x4A // SSnatch (Easy)
	.byte 0x4B // SSnatch (Hard)
	.byte 0x4D // MMayhem (Easy)
	.byte 0x4E // BBBarrage (Easy)
	.byte 0x4F // BBBarrage (Normal)
	.byte 0x53 // Fungi: Dogadon
	.byte 0x60 // SSSalvage (Normal)
	.byte 0x63 // SSSortie (Easy)
	.byte 0x65 // Krazy KK (Easy)
	.byte 0x66 // BBBash (V Easy)
	.byte 0x67 // SSeek (V Easy)
	.byte 0x68 // BBother (Easy)
	.byte 0x6F // Galleon: Pufftoss
	// All values between 0x73 and 0x96 (Inclusive). Various bonus minigames
	.byte 0x9A // Factory: Jack
	.byte 0x9B // Crown - Arena Ambush
	.byte 0x9C // Crown - More Kritter Karnage
	.byte 0x9D // Crown - Forest Fracas
	.byte 0x9E // Crown - Bish Bash Brawl
	.byte 0x9F // Crown - Kamikaze Kremlings
	.byte 0xA0 // Crown - Plinth Panic
	.byte 0xA1 // Crown - Pinnacle Palaver
	.byte 0xA2 // Crown - Shockwave Showdown
	.byte 0xA5 // Diddy Kremling Game
	.byte 0xC4 // Caves: Dillo
	.byte 0xC5 // Aztec: Dogadon
	.byte 0xC7 // Castle: Kut Out
	.byte 0xC9 // Diddy Rocketbarrel Game
	.byte 0xCA // Lanky Shooting Game
	.byte 0xD1 // Chunky ? Box Game
	.byte 0xD2 // Tiny "Floor is Lava" Game
	.byte 0xD3 // Chunky Shooting Game
	.byte 0xD4 // DK Rambi Game
	.byte 0x0 // Terminator

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

.align
MoveFlags:
	.half 386 // Dive Barrel
	.half 387 // Vine Barrel
	.half 388 // Orange Barrel
	.half 389 // Barrel Barrel
	.half 377 // BFI Camera/Shockwave
	.half 6 // Diddy
	.half 66 // Tiny
	.half 70 // Lanky
	.half 117 // Chunky
	.half 385 // DK
	.half 0 // Terminator

PauseMenu_Slam:
	.asciiz "SLAM LEVEL - 0" // Replace last char with 0/1/2/3

.align
PauseMenu_Sniper_Off:
	.asciiz "SNIPER SCOPE - OFF"

.align
PauseMenu_Sniper_On:
	.asciiz "SNIPER SCOPE - ON"

.align
PauseMenu_Takeoff:
	.asciiz "SETUP TAKEOFF SKIP"

// DISABLE POSITION BUTTONS
.align
PauseMenu_DisablePositionLoad_Off:
	.asciiz "POSITION LOAD - ENABLED"
PauseMenu_DisablePositionLoad_On:
	.asciiz "POSITION LOAD - DISABLED"

.align
PauseMenu_DisablePositionLoad_Array:
	.word PauseMenu_DisablePositionLoad_Off
	.word PauseMenu_DisablePositionLoad_On

// DISABLE TAG ANYWHERE BUTTONS
.align
PauseMenu_DisableTagAnywhere_Off:
	.asciiz "TAG ANYWHERE - ENABLED"
PauseMenu_DisableTagAnywhere_On:
	.asciiz "TAG ANYWHERE - DISABLED"

.align
PauseMenu_DisableTagAnywhere_Array:
	.word PauseMenu_DisableTagAnywhere_Off
	.word PauseMenu_DisableTagAnywhere_On

// DISABLE SOUND EFFECTS
.align
PauseMenu_Sound_On:
	.asciiz "SOUND EFFECTS - ON"
PauseMenu_Sound_Off:
	.asciiz "SOUND EFFECTS - OFF"

.align
PauseMenu_Sound_Array:
	.word PauseMenu_Sound_Off
	.word PauseMenu_Sound_On

// DISABLE MUSIC
.align
PauseMenu_Music_On:
	.asciiz "MUSIC - ON"
PauseMenu_Music_Off:
	.asciiz "MUSIC - OFF"

.align
PauseMenu_Music_Array:
	.word PauseMenu_Music_Off
	.word PauseMenu_Music_On

// TOGGLE CAMERA
.align
PauseMenu_CameraMode_Free:
	.asciiz "CAMERA MODE - FREE"
PauseMenu_CameraMode_Follow:
	.asciiz "CAMERA MODE - FOLLOW"

.align
PauseMenu_CameraMode_Array:
	.word PauseMenu_CameraMode_Free
	.word PauseMenu_CameraMode_Follow

// TOGGLE SCREEN
.align
PauseMenu_ScreenMode_Normal:
	.asciiz "SCREEN RATIO - 4:3"
PauseMenu_ScreenMode_Wide:
	.asciiz "SCREEN RATIO - 16:9"

.align
PauseMenu_ScreenMode_Array:
	.word PauseMenu_ScreenMode_Normal
	.word PauseMenu_ScreenMode_Wide

.align
KongColours:
	.byte 0x02 // DK - Green Body
	.byte 0x02 // Diddy - Yellow Cap
	.byte 0x01 // Lanky - Green Straps
	.byte 0x02 // Tiny - Purple Suit
	.byte 0x01 // Chunky - Red Suit

.align
PauseMenu_Warp_Length:
	.byte 9  //11
	.byte 9  //11
	.byte 9  //11
	.byte 11 //13
	.byte 11 //13
	.byte 9  //11
	.byte 9  //11
	.byte 10 //12
	.byte 8  //10
	.byte 12 //14
	.byte 15 //17
	.byte 15 //17
	.byte 14 //16
	//.byte 17 //18 - Chunky phase, not needed

.align
MovementStates:
	// 0x0
	.asciiz "UNKNOWN 0x0"
	.asciiz "IDLE - ENEMY"
	.asciiz "1ST PERSON"
	.asciiz "WATER 1ST PERSON"
	.asciiz "CAMERA"
	.asciiz "WATER CAMERA"
	.asciiz "LOCKED 0x6"
	.asciiz "MINECART - IDLE"
	.asciiz "MINECART - DUCK"
	.asciiz "MINECART - JUMP"
	.asciiz "MINECART - L"
	.asciiz "MINECART - R"
	.asciiz "IDLE"
	.asciiz "WALKING"
	.asciiz "SKIDDING"
	.asciiz "SLIDING"
	// 0x10
	.asciiz "SLIDING - LEFT"
	.asciiz "SLIDING - RIGHT"
	.asciiz "SLIDING - UP"
	.asciiz "SLIDING - BACK"
	.asciiz "SLIDING - JUMP"
	.asciiz "SLIPPING 0x15"
	.asciiz "SLIPPING 0x16"
	.asciiz "JUMPING"
	.asciiz "BBLAST PAD"
	.asciiz "BOUNCING - MUSH"
	.asciiz "DOUBLE JUMP"
	.asciiz "SIMIAN SPRING"
	.asciiz "SIMIAN SLAM"
	.asciiz "LONG JUMPING"
	.asciiz "FALLING"
	.asciiz "GUN - FALLING"
	// 0x20
	.asciiz "FALLING TOO FAR"
	.asciiz "SLIDING - FALL"
	.asciiz "PONY TAIL TWIRL"
	.asciiz "ATTACKING 0x23"
	.asciiz "PRIMATE PUNCH"
	.asciiz "ATTACKING 0x25"
	.asciiz "GROUND ATTACK"
	.asciiz "ATTACKING 0x27"
	.asciiz "GROUND ATTACK 2"
	.asciiz "MOVING ATTACK"
	.asciiz "AERIAL ATTACK"
	.asciiz "ROLLING"
	.asciiz "THROWING ORANGE"
	.asciiz "SHOCKWAVE"
	.asciiz "CHIMPY CHARGE"
	.asciiz "CHARGING"
	// 0x30
	.asciiz "ENEMY BOUNCING"
	.asciiz "DAMAGED"
	.asciiz "STUNLOCKED"
	.asciiz "DAMAGED - MJ"
	.asciiz "UNKNOWN 0x34"
	.asciiz "DAMAGED - KLUMP"
	.asciiz "DEATH"
	.asciiz "DAMAGED - WATER"
	.asciiz "DAMAGED - BOAT"
	.asciiz "SHRINKING"
	.asciiz "UNKNOWN 0X3A"
	.asciiz "DEATH - DOGADON"
	.asciiz "CROUCHING"
	.asciiz "UNCROUCHING"
	.asciiz "BACKFLIP"
	.asciiz "ENTERING OSTAND"
	// 0x40
	.asciiz "ORANGSTAND"
	.asciiz "ORANGSTAND JUMP"
	.asciiz "BARREL"
	.asciiz "BARREL - WATER"
	.asciiz "BBLAST SHOT"
	.asciiz "CANNON SHOT"
	.asciiz "PUSHING OBJECT"
	.asciiz "PICK UP OBJECT"
	.asciiz "OBJECT - IDLE"
	.asciiz "OBJECT - WALK"
	.asciiz "DROPPING OBJECT"
	.asciiz "THROWING OBJECT"
	.asciiz "OBJECT - JUMP"
	.asciiz "AIRTHROW OBJECT"
	.asciiz "SURFACE SWIM"
	.asciiz "UNDERWATER"
	// 0x50
	.asciiz "LEAVING WATER"
	.asciiz "JUMPING - WATER"
	.asciiz "BANANAPORTING"
	.asciiz "MONKEYPORTING"
	.asciiz "BANANAPORT - MP"
	.asciiz "UNKNOWN 0x55"
	.asciiz "LOCKED - SHOPS"
	.asciiz "VINE - SWINGING"
	.asciiz "VINE - LEAVING"
	.asciiz "TREE - CLIMBING"
	.asciiz "TREE - LEAVING"
	.asciiz "GRABBING LEDGE"
	.asciiz "LEDGE PULL UP"
	.asciiz "GUN - IDLE"
	.asciiz "GUN - WALKING"
	.asciiz "PUT AWAY GUN"
	// 0x60
	.asciiz "PULLING OUT GUN"
	.asciiz "GUN - JUMPING"
	.asciiz "GUN - AIMING"
	.asciiz "ROCKETBARREL"
	.asciiz "PHOTO"
	.asciiz "PHOTO - WATER"
	.asciiz "DAMAGED - TNT"
	.asciiz "INSTRUMENT"
	.asciiz "UNKNOWN 0x68"
	.asciiz "FACTORY CAR"
	.asciiz "LEARNING GUN"
	.asciiz "LOCKED - 0X6B"
	.asciiz "FEEDING SCOFF"
	.asciiz "BOAT"
	.asciiz "BABOON BALLOON"
	.asciiz "UPDRAFT"
	// 0x70
	.asciiz "GB DANCE"
	.asciiz "KEY DANCE"
	.asciiz "CROWN DANCE"
	.asciiz "LOSS DANCE"
	.asciiz "VICTORY DANCE"
	.asciiz "CASTLE CAR"
	.asciiz "ENTERING CROWN"
	.asciiz "CUTSCENE LOCK"
	.asciiz "GORILLA GRAB"
	.asciiz "LEARNING MOVE"
	.asciiz "LOCKED - CAR"
	.asciiz "LOCKED - BEETLE"
	.asciiz "TRAPPED"
	.asciiz "KLAPTRAP KONG"
	.asciiz "ENG SWIM"
	.asciiz "ENG UNDERWATER"
	// 0x80
	.asciiz "ENG S.ATTACKING"
	.asciiz "ENG ATTACKING"
	.asciiz "ENG LEAPING"
	.asciiz "FAIRY REFILL"
	.asciiz "UNKNOWN 0x84"
	.asciiz "MAIN MENU"
	.asciiz "ENTER MAIN MENU"
	.asciiz "ENTERING PORTAL"
	.asciiz "EXITING PORTAL"

.align
MovementStates_length:
	// 0x0
	.byte 11 // "UNKNOWN 0X0"
	.byte 12 // "IDLE - ENEMY"
	.byte 10 // "1ST PERSON"
	.byte 16 // "WATER 1ST PERSON"
	.byte 6 // "CAMERA"
	.byte 12 // "WATER CAMERA"
	.byte 10 // "LOCKED 0X6"
	.byte 15 // "MINECART - IDLE"
	.byte 15 // "MINECART - DUCK"
	.byte 15 // "MINECART - JUMP"
	.byte 12 // "MINECART - L"
	.byte 12 // "MINECART - R"
	.byte 4 // "IDLE"
	.byte 7 // "WALKING"
	.byte 8 // "SKIDDING"
	.byte 7 // "SLIDING"
	// 0x10
	.byte 14 // "SLIDING - LEFT"
	.byte 15 // "SLIDING - RIGHT"
	.byte 12 // "SLIDING - UP"
	.byte 14 // "SLIDING - BACK"
	.byte 14 // "SLIDING - JUMP"
	.byte 13 // "SLIPPING 0X15"
	.byte 13 // "SLIPPING 0X16"
	.byte 7 // "JUMPING"
	.byte 10 // "BBLAST PAD"
	.byte 15 // "BOUNCING - MUSH"
	.byte 11 // "DOUBLE JUMP"
	.byte 13 // "SIMIAN SPRING"
	.byte 11 // "SIMIAN SLAM"
	.byte 12 // "LONG JUMPING"
	.byte 7 // "FALLING"
	.byte 13 // "GUN - FALLING"
	// 0x20
	.byte 15 // "FALLING TOO FAR"
	.byte 14 // "SLIDING - FALL"
	.byte 15 // "PONY TAIL TWIRL"
	.byte 14 // "ATTACKING 0X23"
	.byte 13 // "PRIMATE PUNCH"
	.byte 14 // "ATTACKING 0X25"
	.byte 13 // "GROUND ATTACK"
	.byte 14 // "ATTACKING 0X27"
	.byte 15 // "GROUND ATTACK 2"
	.byte 13 // "MOVING ATTACK"
	.byte 13 // "AERIAL ATTACK"
	.byte 7 // "ROLLING"
	.byte 15 // "THROWING ORANGE"
	.byte 9 // "SHOCKWAVE"
	.byte 13 // "CHIMPY CHARGE"
	.byte 8 // "CHARGING"
	// 0x30
	.byte 14 // "ENEMY BOUNCING"
	.byte 7 // "DAMAGED"
	.byte 10 // "STUNLOCKED"
	.byte 12 // "DAMAGED - MJ"
	.byte 12 // "UNKNOWN 0X34"
	.byte 15 // "DAMAGED - KLUMP"
	.byte 5 // "DEATH"
	.byte 15 // "DAMAGED - WATER"
	.byte 14 // "DAMAGED - BOAT"
	.byte 9 // "SHRINKING"
	.byte 12 // "UNKNOWN 0X3A"
	.byte 15 // "DEATH - DOGADON"
	.byte 9 // "CROUCHING"
	.byte 11 // "UNCROUCHING"
	.byte 8 // "BACKFLIP"
	.byte 15 // "ENTERING OSTAND"
	// 0x40
	.byte 10 // "ORANGSTAND"
	.byte 15 // "ORANGSTAND JUMP"
	.byte 6 // "BARREL"
	.byte 14 // "BARREL - WATER"
	.byte 11 // "BBLAST SHOT"
	.byte 11 // "CANNON SHOT"
	.byte 14 // "PUSHING OBJECT"
	.byte 14 // "PICK UP OBJECT"
	.byte 13 // "OBJECT - IDLE"
	.byte 13 // "OBJECT - WALK"
	.byte 15 // "DROPPING OBJECT"
	.byte 15 // "THROWING OBJECT"
	.byte 13 // "OBJECT - JUMP"
	.byte 15 // "AIRTHROW OBJECT"
	.byte 12 // "SURFACE SWIM"
	.byte 10 // "UNDERWATER"
	// 0x50
	.byte 13 // "LEAVING WATER"
	.byte 15 // "JUMPING - WATER"
	.byte 13 // "BANANAPORTING"
	.byte 13 // "MONKEYPORTING"
	.byte 15 // "BANANAPORT - MP"
	.byte 12 // "UNKNOWN 0X55"
	.byte 14 // "LOCKED - SHOPS"
	.byte 15 // "VINE - SWINGING"
	.byte 14 // "VINE - LEAVING"
	.byte 15 // "TREE - CLIMBING"
	.byte 14 // "TREE - LEAVING"
	.byte 14 // "GRABBING LEDGE"
	.byte 13 // "LEDGE PULL UP"
	.byte 10 // "GUN - IDLE"
	.byte 13 // "GUN - WALKING"
	.byte 12 // "PUT AWAY GUN"
	// 0x60
	.byte 15 // "PULLING OUT GUN"
	.byte 13 // "GUN - JUMPING"
	.byte 12 // "GUN - AIMING"
	.byte 12 // "ROCKETBARREL"
	.byte 5 // "PHOTO"
	.byte 13 // "PHOTO - WATER"
	.byte 13 // "DAMAGED - TNT"
	.byte 10 // "INSTRUMENT"
	.byte 12 // "UNKNOWN 0X68"
	.byte 11 // "FACTORY CAR"
	.byte 12 // "LEARNING GUN"
	.byte 13 // "LOCKED - 0X6B"
	.byte 13 // "FEEDING SCOFF"
	.byte 4 // "BOAT"
	.byte 14 // "BABOON BALLOON"
	.byte 7 // "UPDRAFT"
	// 0x70
	.byte 8 // "GB DANCE"
	.byte 9 // "KEY DANCE"
	.byte 11 // "CROWN DANCE"
	.byte 10 // "LOSS DANCE"
	.byte 13 // "VICTORY DANCE"
	.byte 10 // "CASTLE CAR"
	.byte 14 // "ENTERING CROWN"
	.byte 13 // "CUTSCENE LOCK"
	.byte 12 // "GORILLA GRAB"
	.byte 13 // "LEARNING MOVE"
	.byte 12 // "LOCKED - CAR"
	.byte 15 // "LOCKED - BEETLE"
	.byte 7 // "TRAPPED"
	.byte 13 // "KLAPTRAP KONG"
	.byte 8 // "ENG SWIM"
	.byte 14 // "ENG UNDERWATER"
	// 0x80
	.byte 15 // "ENG S.ATTACKING"
	.byte 13 // "ENG ATTACKING"
	.byte 11 // "ENG LEAPING"
	.byte 12 // "FAIRY REFILL"
	.byte 12 // "UNKNOWN 0X84"
	.byte 9 // "MAIN MENU"
	.byte 15 // "ENTER MAIN MENU"
	.byte 15 // "ENTERING PORTAL"
	.byte 14 // "EXITING PORTAL"

.align
FileStatus_Custom_text:
	.asciiz "FILE STATUS - CUSTOM"

.align
FileStatus_101_text:
	.asciiz "FILE STATUS - 101%"
	
.align
FileStatus_Max_text:
	.asciiz "FILE STATUS - MAX%"

.align
FileStatus_array_text:
	.word FileStatus_Custom_text
	.word FileStatus_101_text
	.word FileStatus_Max_text

.align
Timer_Start_OnL:
	.asciiz "START - ON L"

.align
Timer_Start_OnMapLoad:
	.asciiz "START - ON MAP LOAD"

.align
Timer_Start_OnInput:
	.asciiz "START - ON INPUT"

.align
Timer_Start_Array:
	.word Timer_Start_OnL
	.word Timer_Start_OnMapLoad
	.word Timer_Start_OnInput

.align
Timer_Pause_On:
	.asciiz "PAUSE ON PAUSE - ON"

.align
Timer_Pause_Off:
	.asciiz "PAUSE ON PAUSE - OFF"

.align
Timer_Pause_Array:
	.word Timer_Pause_Off
	.word Timer_Pause_On

.align
Timer_Finish_OnL:
	.asciiz "FINISH - ON L"

.align
Timer_Finish_OnTransition:
	.asciiz "FINISH - ON TRANSITION"

.align
Timer_Finish_OnCutscene:
	.asciiz "FINISH - ON CUTSCENE"

.align
Timer_Finish_OnGBGrab:
	.asciiz "FINISH - ON GB DANCE"

.align
Timer_Finish_Array:
	.word Timer_Finish_OnL
	.word Timer_Finish_OnTransition
	.word Timer_Finish_OnCutscene
	.word Timer_Finish_OnGBGrab

.align
FTT_Flags:
	.half 355
	.half 358
	.half 359
	.half 360
	.half 361
	.half 362
	.half 363
	.half 364
	.half 365
	.half 366
	.half 367
	.half 368
	.half 369
	.half 370
	.half 372
	.half 373
	.half 374
	.half 376
	.half 382
	.half 392
	.half 775
	.half 776
	.half 777
	.half 778
	.half 779
	.half 780
	.half 781
	.half 782
	.half 783
	.half 784
	.half 785
	.half 786
	.half 787
	.half 282
	.half 194
	.half 256
	.half 257
	.half 303
	.half 349
	.half 27
	.half 95
	.half 93
	.half 94
	.half 140
	.half 195
	.half 196
	.half 255
	.half 277
	.half 299
	.half 378


// WARPS
// Japes
.align
Warps_Japes_W1Portal:
	.asciiz "WARP 1 - PORTAL"

.align
Warps_Japes_W1Tunnel:
	.asciiz "WARP 1 - TUNNEL"

.align
Warps_Japes_W2Lower:
	.asciiz "WARP 2 - LOWER"

.align
Warps_Japes_W2Mountain:
	.asciiz "WARP 2 - MOUNTAIN"

.align
Warps_Japes_W3BBlast:
	.asciiz "WARP 3 - BBLAST"

.align
Warps_Japes_W3DiddyBP:
	.asciiz "WARP 3 - DIDDY BP"

.align
Warps_Japes_W4Tunnel:
	.asciiz "WARP 4 - TUNNEL"

.align
Warps_Japes_W4Cranky:
	.asciiz "WARP 4 - CRANKY"

.align
Warps_Japes_W5Shell:
	.asciiz "WARP 5 - SHELLHIVE"

.align
Warps_Japes_W5Mountain:
	.asciiz "WARP 5 - MOUNTAIN"

// Aztec
.align
Warps_Aztec_W1Portal:
	.asciiz "WARP 1 - PORTAL"

.align
Warps_Aztec_W1Oasis:
	.asciiz "WARP 1 - OASIS"

.align
Warps_Aztec_W2Oasis:
	.asciiz "WARP 2 - OASIS"

.align
Warps_Aztec_W2Tunnel:
	.asciiz "WARP 2 - TUNNEL"

.align
Warps_Aztec_W3Cranky:
	.asciiz "WARP 3 - CRANKY"

.align
Warps_Aztec_W3Tunnel:
	.asciiz "WARP 3 - TUNNEL"

.align
Warps_Aztec_W4Funky:
	.asciiz "WARP 4 - FUNKY"

.align
Warps_Aztec_W4Tunnel:
	.asciiz "WARP 4 - TUNNEL"

.align
Warps_Aztec_W5Totem:
	.asciiz "WARP 5 - TOTEM"

.align
Warps_Aztec_W5BonusRoom:
	.asciiz "WARP 5 - BONUS ROOM"

// Llama Temple
.align
Warps_Llama_W1Entrance:
	.asciiz "WARP 1 - ENTRANCE"

.align
Warps_Llama_W1Matching:
	.asciiz "WARP 1 - MATCHING GAME"

.align
Warps_Llama_W2Entrance:
	.asciiz "WARP 2 - ENTRANCE"

.align
Warps_Llama_W2LavaRoom:
	.asciiz "WARP 2 - LAVA ROOM"

// Factory
.align
Warps_Factory_W1Lobby:
	.asciiz "WARP 1 - LOBBY"

.align
Warps_Factory_W1Storage:
	.asciiz "WARP 1 - STORAGE ROOM"

.align
Warps_Factory_W2Lobby:
	.asciiz "WARP 2 - LOBBY"

.align
Warps_Factory_W2RND:
	.asciiz "WARP 2 - RND"

.align
Warps_Factory_W3Lobby:
	.asciiz "WARP 3 - LOBBY"

.align
Warps_Factory_W3Snide:
	.asciiz "WARP 3 - SNIDES"

.align
Warps_Factory_W4Low:
	.asciiz "WARP 4 - LOW"

.align
Warps_Factory_W4High:
	.asciiz "WARP 4 - HIGH"

.align
Warps_Factory_W5Arcade:
	.asciiz "WARP 5 - ARCADE"

.align
Warps_Factory_W5Funky:
	.asciiz "WARP 5 - FUNKY"

// Galleon
.align
Warps_Galleon_W1Portal:
	.asciiz "WARP 1 - PORTAL"

.align
Warps_Galleon_W1Lighthouse:
	.asciiz "WARP 1 - LIGHTHOUSE"

.align
Warps_Galleon_W2Tunnel:
	.asciiz "WARP 2 - TUNNEL"

.align
Warps_Galleon_W25DS:
	.asciiz "WARP 2 - SHIPWRECK"

.align
Warps_Galleon_W3Cranky:
	.asciiz "WARP 3 - CRANKY"

.align
Warps_Galleon_W3Snide:
	.asciiz "WARP 3 - SNIDES"

.align
Warps_Galleon_W45DS:
	.asciiz "WARP 4 - SHIPWRECK"

.align
Warps_Galleon_W4GoldTower:
	.asciiz "WARP 4 - GOLD TOWER"

.align
Warps_Galleon_W5Lighthouse:
	.asciiz "WARP 5 - LIGHTHOUSE"

.align
Warps_Galleon_W55DS:
	.asciiz "WARP 5 - SHIPWRECK"

// Fungi
.align
Warps_Fungi_W1Clock:
	.asciiz "WARP 1 - CLOCK"

.align
Warps_Fungi_W1Mill:
	.asciiz "WARP 1 - MILL"

.align
Warps_Fungi_W2Clock:
	.asciiz "WARP 2 - CLOCK"

.align
Warps_Fungi_W2Funky:
	.asciiz "WARP 2 - FUNKY"

.align
Warps_Fungi_W3Clock:
	.asciiz "WARP 3 - CLOCK"

.align
Warps_Fungi_W3Mushroom:
	.asciiz "WARP 3 - MUSHROOM"

.align
Warps_Fungi_W4Clock:
	.asciiz "WARP 4 - CLOCK"

.align
Warps_Fungi_W4Tree:
	.asciiz "WARP 4 - TREE"

.align
Warps_Fungi_W5Low:
	.asciiz "WARP 5 - LOW"

.align
Warps_Fungi_W5High:
	.asciiz "WARP 5 - HIGH"

// Caves
.align
Warps_Caves_W1Near:
	.asciiz "WARP 1 - NEAR"

.align
Warps_Caves_W15DI:
	.asciiz "WARP 1 - IGLOOS"

.align
Warps_Caves_W2Near:
	.asciiz "WARP 2 - NEAR"

.align
Warps_Caves_W2Cabins:
	.asciiz "WARP 2 - CABINS"

.align
Warps_Caves_W35DI:
	.asciiz "WARP 3 - IGLOOS"

.align
Warps_Caves_W3Cave:
	.asciiz "WARP 3 - CAVERN"

.align
Warps_Caves_W4Pillar:
	.asciiz "WARP 4 - PILLAR"

.align
Warps_Caves_W4Cave:
	.asciiz "WARP 4 - CAVERN"

.align
Warps_Caves_W5Cabins:
	.asciiz "WARP 5 - CABINS"

.align
Warps_Caves_W5LankyBP:
	.asciiz "WARP 5 - LANKY BP"

// Castle
.align
Warps_Castle_W1Near:
	.asciiz "WARP 1 - NEAR"

.align
Warps_Castle_W1Far:
	.asciiz "WARP 1 - FAR"

.align
Warps_Castle_W2Near:
	.asciiz "WARP 2 - NEAR"

.align
Warps_Castle_W2Upper:
	.asciiz "WARP 2 - UPPER"

.align
Warps_Castle_W3Near:
	.asciiz "WARP 3 - NEAR"

.align
Warps_Castle_W3Cranky:
	.asciiz "WARP 3 - CRANKY"

.align
Warps_Castle_W4Near:
	.asciiz "WARP 4 - NEAR"

.align
Warps_Castle_W4Trash:
	.asciiz "WARP 4 - TRASH CAN"

.align
Warps_Castle_W5Near:
	.asciiz "WARP 5 - NEAR"

.align
Warps_Castle_W5WindTower:
	.asciiz "WARP 5 - WIND TOWER"

// Crypt
.align
Warps_Crypt_W1Near:
	.asciiz "WARP 1 - NEAR"

.align
Warps_Crypt_W1DiddyCoffin:
	.asciiz "WARP 1 - DIDDY COFFIN"

.align
Warps_Crypt_W2Near:
	.asciiz "WARP 2 - NEAR"

.align
Warps_Crypt_W2Minecart:
	.asciiz "WARP 2 - MINECART"

.align
Warps_Crypt_W3Near:
	.asciiz "WARP 3 - NEAR"

.align
Warps_Crypt_W3ChunkyCoffin:
	.asciiz "WARP 3 - CHUNKY COFFINS"

// Isles
.align
Warps_Isles_W1Ring:
	.asciiz "WARP 1 - RING"

.align
Warps_Isles_W1KLumsy:
	.asciiz "WARP 1 - K. LUMSY"

.align
Warps_Isles_W2Ring:
	.asciiz "WARP 2 - RING"

.align
Warps_Isles_W2Aztec:
	.asciiz "WARP 2 - AZTEC LOBBY"

.align
Warps_Isles_W3Ring:
	.asciiz "WARP 3 - RING"

.align
Warps_Isles_W3KRool:
	.asciiz "WARP 3 - K. ROOL"

.align
Warps_Isles_W4Ring:
	.asciiz "WARP 4 - RING"

.align
Warps_Isles_W4Factory:
	.asciiz "WARP 4 - FACTORY LOBBY"

.align
Warps_Isles_W5Ring:
	.asciiz "WARP 5 - RING"

.align
Warps_Isles_W5BFI:
	.asciiz "WARP 5 - BFI"

// Helm
.align
Warps_Helm_W1Entrance:
	.asciiz "WARP 1 - ENTRANCE"

.align
Warps_Helm_W1Navigation:
	.asciiz "WARP 1 - NAVIGATION ROOM"

// Helm
.align
Warps_HelmLobby_W1Near:
	.asciiz "WARP 1 - NEAR"

.align
Warps_HelmLobby_W1Far:
	.asciiz "WARP 1 - FAR"

// Text Arrays & Flag Arrays
.align
Warps_Japes_Array:
	.word Warps_Japes_W1Portal
	.word Warps_Japes_W1Tunnel
	.word Warps_Japes_W2Lower
	.word Warps_Japes_W2Mountain
	.word Warps_Japes_W3BBlast
	.word Warps_Japes_W3DiddyBP
	.word Warps_Japes_W4Tunnel
	.word Warps_Japes_W4Cranky
	.word Warps_Japes_W5Shell
	.word Warps_Japes_W5Mountain

.align
Warps_Japes_Flags:
	.half 0x20
	.half 0x21
	.half 0x23
	.half 0x22
	.half 0x25
	.half 0x24
	.half 0x28
	.half 0x29
	.half 0x26
	.half 0x27

.align
Warps_Aztec_Array:
	.word Warps_Aztec_W1Portal
	.word Warps_Aztec_W1Oasis
	.word Warps_Aztec_W2Oasis
	.word Warps_Aztec_W2Tunnel
	.word Warps_Aztec_W3Cranky
	.word Warps_Aztec_W3Tunnel
	.word Warps_Aztec_W4Tunnel
	.word Warps_Aztec_W4Funky
	.word Warps_Aztec_W5Totem
	.word Warps_Aztec_W5BonusRoom

.align
Warps_Aztec_Flags:
	.half 0x4F
	.half 0x50
	.half 0x51
	.half 0x52
	.half 0x53
	.half 0x54
	.half 0x55
	.half 0x56
	.half 0x57
	.half 0x3E

.align
Warps_Llama_Array:
	.word Warps_Llama_W1Entrance
	.word Warps_Llama_W1Matching
	.word Warps_Llama_W2Entrance
	.word Warps_Llama_W2LavaRoom

.align
Warps_Llama_Flags:
	.half 0x59
	.half 0x58
	.half 0x5B
	.half 0x5A

.align
Warps_Factory_Array:
	.word Warps_Factory_W1Lobby
	.word Warps_Factory_W1Storage
	.word Warps_Factory_W2Lobby
	.word Warps_Factory_W2RND
	.word Warps_Factory_W3Lobby
	.word Warps_Factory_W3Snide
	.word Warps_Factory_W4Low
	.word Warps_Factory_W4High
	.word Warps_Factory_W5Arcade
	.word Warps_Factory_W5Funky

.align
Warps_Factory_Flags:
	.half 0x8D
	.half 0x8E
	.half 0x8F
	.half 0x90
	.half 0x91
	.half 0x92
	.half 0x94
	.half 0x93
	.half 0x96
	.half 0x95

.align
Warps_Galleon_Array:
	.word Warps_Galleon_W1Portal
	.word Warps_Galleon_W1Lighthouse
	.word Warps_Galleon_W2Tunnel
	.word Warps_Galleon_W25DS
	.word Warps_Galleon_W3Cranky
	.word Warps_Galleon_W3Snide
	.word Warps_Galleon_W45DS
	.word Warps_Galleon_W4GoldTower
	.word Warps_Galleon_W55DS
	.word Warps_Galleon_W5Lighthouse

.align
Warps_Galleon_Flags:
	.half 0xB2
	.half 0xB1
	.half 0xAC
	.half 0xAB
	.half 0xAE
	.half 0xAD
 	.half 0xAF
 	.half 0xA3
	.half 0xA9
	.half 0xAA

.align
Warps_Fungi_Array:
	.word Warps_Fungi_W1Clock
	.word Warps_Fungi_W1Mill
	.word Warps_Fungi_W2Clock
	.word Warps_Fungi_W2Funky
	.word Warps_Fungi_W3Clock
	.word Warps_Fungi_W3Mushroom
	.word Warps_Fungi_W4Clock
	.word Warps_Fungi_W4Tree
	.word Warps_Fungi_W5Low
	.word Warps_Fungi_W5High

.align
Warps_Fungi_Flags:
	.half 0xEE
	.half 0xED
	.half 0xEF
	.half 0xF0
	.half 0xF1
	.half 0xF2
	.half 0xF3
	.half 0xF4
	.half 0xF5
	.half 0xF6

.align
Warps_Caves_Array:
	.word Warps_Caves_W1Near
	.word Warps_Caves_W15DI
	.word Warps_Caves_W2Near
	.word Warps_Caves_W2Cabins
	.word Warps_Caves_W35DI
	.word Warps_Caves_W3Cave
	.word Warps_Caves_W4Pillar
	.word Warps_Caves_W4Cave
	.word Warps_Caves_W5Cabins
	.word Warps_Caves_W5LankyBP

.align
Warps_Caves_Flags:
	.half 0x11C
	.half 0x11B
	.half 0x11D
	.half 0x11E
	.half 0x123
	.half 0x127
	.half 0x120
	.half 0x11F
	.half 0x121
	.half 0x122

.align
Warps_Castle_Array:
	.word Warps_Castle_W1Near
	.word Warps_Castle_W1Far
	.word Warps_Castle_W2Near
	.word Warps_Castle_W2Upper
	.word Warps_Castle_W3Near
	.word Warps_Castle_W3Cranky
	.word Warps_Castle_W4Near
	.word Warps_Castle_W4Trash
	.word Warps_Castle_W5Near
	.word Warps_Castle_W5WindTower

.align
Warps_Castle_Flags:
	.half 0x147
	.half 0x148
	.half 0x149
	.half 0x14A
	.half 0x14B
	.half 0x14C
	.half 0x14D
	.half 0x14E
	.half 0x14F
	.half 0x150

.align
Warps_Crypt_Array:
	.word Warps_Crypt_W1Near
	.word Warps_Crypt_W1DiddyCoffin
	.word Warps_Crypt_W2Near
	.word Warps_Crypt_W2Minecart
	.word Warps_Crypt_W3Near
	.word Warps_Crypt_W3ChunkyCoffin

.align
Warps_Crypt_Flags:
	.half 0x151
	.half 0x152
	.half 0x153
	.half 0x154
	.half 0x155
	.half 0x156

.align
Warps_Helm_Array:
	.word Warps_Helm_W1Entrance
	.word Warps_Helm_W1Navigation

.align
Warps_Helm_Flags:
	.half 0x305
	.half 0x306

.align
Warps_Isles_Array:
	.word Warps_Isles_W1Ring
	.word Warps_Isles_W1KLumsy
	.word Warps_Isles_W2Ring
	.word Warps_Isles_W2Aztec
	.word Warps_Isles_W3Ring
	.word Warps_Isles_W3KRool
	.word Warps_Isles_W4Ring
	.word Warps_Isles_W4Factory
	.word Warps_Isles_W5Ring
	.word Warps_Isles_W5BFI

.align
Warps_Isles_Flags:
	.half 0x1B1
	.half 0x1B2
	.half 0x1B3
	.half 0x1B4
	.half 0x1B5
	.half 0x1B6
	.half 0x1B7
	.half 0x1B8
	.half 0x1BA
	.half 0x1B9

.align
Warps_HelmLobby_Array:
	.word Warps_HelmLobby_W1Near
	.word Warps_HelmLobby_W1Far

.align
Warps_HelmLobby_Flags:
	.half 0x1A1
	.half 0x1A2

// Master
.align
Warps_Master_Japes:
	.asciiz "JUNGLE JAPES"

.align
Warps_Master_Aztec:
	.asciiz "ANGRY AZTEC"

.align
Warps_Master_Llama:
	.asciiz "LLAMA TEMPLE"

.align
Warps_Master_Factory:
	.asciiz "FRANTIC FACTORY"

.align
Warps_Master_Galleon:
	.asciiz "GLOOMY GALLEON"

.align
Warps_Master_Fungi:
	.asciiz "FUNGI FOREST"

.align
Warps_Master_Caves:
	.asciiz "CRYSTAL CAVES"

.align
Warps_Master_Castle:
	.asciiz "CREEPY CASTLE"

.align
Warps_Master_Crypt:
	.asciiz "CASTLE CRYPT"

.align
Warps_Master_Helm:
	.asciiz "HIDEOUT HELM"

.align
Warps_Master_Isles:
	.asciiz "DK ISLES"

.align
Warps_Master_HelmLobby:
	.asciiz "HELM LOBBY"

.align
Warps_Master_Array:
	.word Warps_Master_Japes
	.word Warps_Master_Aztec
	.word Warps_Master_Llama
	.word Warps_Master_Factory
	.word Warps_Master_Galleon
	.word Warps_Master_Fungi
	.word Warps_Master_Caves
	.word Warps_Master_Castle
	.word Warps_Master_Crypt
	.word Warps_Master_Helm
	.word Warps_Master_Isles
	.word Warps_Master_HelmLobby

.align
Warps_Text_Array:
	.word Warps_Japes_Array
	.word Warps_Aztec_Array
	.word Warps_Llama_Array
	.word Warps_Factory_Array
	.word Warps_Galleon_Array
	.word Warps_Fungi_Array
	.word Warps_Caves_Array
	.word Warps_Castle_Array
	.word Warps_Crypt_Array
	.word Warps_Helm_Array
	.word Warps_Isles_Array
	.word Warps_HelmLobby_Array

.align
Warps_Flag_Array:
	.word Warps_Japes_Flags
	.word Warps_Aztec_Flags
	.word Warps_Llama_Flags
	.word Warps_Factory_Flags
	.word Warps_Galleon_Flags
	.word Warps_Fungi_Flags
	.word Warps_Caves_Flags
	.word Warps_Castle_Flags
	.word Warps_Crypt_Flags
	.word Warps_Helm_Flags
	.word Warps_Isles_Flags
	.word Warps_HelmLobby_Flags

.align
Warps_Master_Length:
	.byte 10 // Japes
	.byte 10 // Aztec
	.byte 4 // Llama Temple
	.byte 10 // Factory
	.byte 10 // Galleon
	.byte 10 // Fungi
	.byte 10 // Caves
	.byte 10 // Castle
	.byte 6 // Crypt
	.byte 2 // Helm
	.byte 10 // Isles
	.byte 2 // Helm Lobby

.align
Warps_FlagControl_Set:
	.asciiz "SET"

.align
Warps_FlagControl_Unset:
	.asciiz "CLEAR"

.align
Warps_FlagControl_Array:
	.word Warps_FlagControl_Set
	.word Warps_FlagControl_Unset

.align
Transition_Flags:
	.half 378 // Waterfall CS
	.half 390 // Escape CS
	.half 367 // Diddy FTT
	.half 368 // Lanky FTT
	.half 369 // Tiny FTT
	.half 370 // Chunky FTT
	.half 0 // Null Terminator

.align
Menu_ForceClose:
	.asciiz "EMERGENCY - ERROR 01"
Menu_WarpMenu:
	.asciiz "WARP TO MAP"
Menu_SpecialFlags:
	.asciiz "SPECIAL FLAGS"
Menu_Savestates:
	.asciiz "SAVE STATES"
Menu_Display:
	.asciiz "WATCHES"
Menu_FileStates:
	.asciiz "FILE STATES"
Menu_Cheats:
	.asciiz "CHEATS"
Menu_Bananaports:
	.asciiz "BANANAPORTS"
Menu_Settings:
	.asciiz "SETTINGS"

.align
Menu_Main_Array:
	.word Menu_WarpMenu
	.word Menu_SpecialFlags
	.word Menu_Savestates
	.word Menu_Display
	.word Menu_FileStates
	.word Menu_Cheats
	.word Menu_Bananaports
	.word Menu_Settings

.align
Menu_Main_Functions:
	.word ActiveMenu_OpenMapWarper
	.word ActiveMenu_OpenFlagMenu
	.word ActiveMenu_OpenSavestateMenu
	.word ActiveMenu_OpenWatchMenu
	.word 0
	.word ActiveMenu_OpenCheatsMenu
	.word 0
	.word ActiveMenu_OpenSettingsMenu

.align
Menu_Main_Struct:
	.word Menu_Main_Array // Text Array
	.word Menu_Main_Functions // Function Array
	.byte 8 // Array Items
	.byte 0 // Parent Screen

.align
Menu_Screens:
	.word Menu_Main_Struct // 0
	.word Menu_MapWarp_Struct
	.word Menu_MapJapes_Struct // 2
	.word Menu_MapAztec_Struct
	.word Menu_MapFactory_Struct // 4
	.word Menu_MapGalleon_Struct
	.word Menu_MapFungi_Struct // 6
	.word Menu_MapCaves_Struct
	.word Menu_MapCastle_Struct // 8
	.word Menu_MapHelmKRool_Struct
	.word Menu_MapIsles_Struct // 10
	.word Menu_MapJapesMain_Struct
	.word Menu_MapAztecMain_Struct // 12
	.word Menu_MapAztec5DTs_Struct
	.word Menu_MapFactoryMain_Struct // 14
	.word Menu_MapGalleonMain_Struct
	.word Menu_MapGalleonShipwrecks_Struct // 16
	.word Menu_MapFungiMain_Struct
	.word Menu_MapFungiGMush_Struct // 18
	.word Menu_MapCavesMain_Struct
	.word Menu_MapCaves5DC_Struct // 20
	.word Menu_MapCaves5DI_Struct
	.word Menu_MapCastleMain_Struct // 22
	.word Menu_MapCastleCrypt_Struct
	.word Menu_MapCastleTunnel_Struct // 24
	.word Menu_MapIslesMain_Struct
	.word Menu_MapIslesLobbies_Struct // 26
	.word Menu_Savestate_Struct
	.word Menu_ChangeSavestate_Struct // 28
	.word Menu_LZLooperSettings_Struct
	.word Menu_Cheats_Struct // 30
	.word Menu_MovesMaster_Struct
	.word Menu_Gamemodes_Struct // 32
	.word Menu_Watch_Struct
	.word Menu_Settings_Struct // 34
	.word Menu_HorizontalDPad_Struct
	.word Menu_Flags_Struct // 36
	.word Menu_Flags_Kong_Struct
	.word Menu_Flags_KeyIn_Struct // 38
	.word Menu_Flags_KeyHave_Struct
	.word Menu_Flags_LevelIntro_Struct // 40
	.word Menu_Flags_LevelTnS_Struct
	.word Menu_Flags_BossIntro_Struct // 42
	.word Menu_Flags_Cutscenes_Struct
	.word Menu_Flags_Modifiers_Struct // 44
	.word Menu_Flags_Misc_Struct
	.word Menu_QOL_Control_Struct // 46

.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Container.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Aesthetic/MenuSky.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Quality of Life/StartupSkip.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Quality of Life/ForcedStorySkip.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Quality of Life/QOLControl.asm"

.align
Menu_Savestate_SelectedSavestate:
	.asciiz "SELECTED STATE: 1"
Menu_Savestate_ChangeSelected:
	.asciiz "CHANGE SAVESTATE"
Menu_Savestate_Save:
	.asciiz "SAVE STATE"
Menu_Savestate_LoadPosition:
	.asciiz "LOAD STATE FROM POSITION"
Menu_Savestate_LoadExit:
	.asciiz "LOAD STATE FROM EXIT"
Menu_Savestate_LZLooper:
	.asciiz "LOADING ZONE LOOPER SETTINGS"

.align
Menu_Savestate_Array:
	.word Menu_Savestate_SelectedSavestate
	.word Menu_Savestate_ChangeSelected
	.word Menu_Savestate_Save
	.word Menu_Savestate_LoadPosition
	.word Menu_Savestate_LoadExit
	.word Menu_Savestate_LZLooper

.align
Menu_Savestate_Functions:
	.word 0
	.word ActiveMenu_OpenChangeSavestateMenu
	.word ActiveMenu_PerformSavestateAction_Save
	.word ActiveMenu_PerformSavestateAction_LoadFromPosition
	.word ActiveMenu_PerformSavestateAction_LoadFromExit
	.word ActiveMenu_OpenLooperMenu

.align
Menu_Savestate_Struct:
	.word Menu_Savestate_Array // Text Array
	.word Menu_Savestate_Functions // Function Array
	.byte 6 // Array Items
	.byte 0 // Parent Screen

.align
Menu_Savestate_SetTo1:
	.asciiz "SAVESTATE 1"
Menu_Savestate_SetTo2:
	.asciiz "SAVESTATE 2"
Menu_Savestate_SetTo3:
	.asciiz "SAVESTATE 3"
Menu_Savestate_SetTo4:
	.asciiz "SAVESTATE 4"

.align
Menu_ChangeSavestate_Array:
	.word Menu_Savestate_SetTo1
	.word Menu_Savestate_SetTo2
	.word Menu_Savestate_SetTo3
	.word Menu_Savestate_SetTo4

.align
Menu_ChangeSavestate_Functions:
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_ChangeSavestate

.align
Menu_ChangeSavestate_Struct:
	.word Menu_ChangeSavestate_Array // Text Array
	.word Menu_ChangeSavestate_Functions // Function Array
	.byte 4 // Array Items
	.byte 27 // Parent Screen

.align
Menu_LZLooperSettings_TurnOnLooper:
	.asciiz "LZ LOOPER: OFF"
Menu_LZLooperSettings_TurnOffLooper:
	.asciiz "LZ LOOPER: ON"
Menu_LZLooperSettings_Record:
	.asciiz "SET NEXT LOADING ZONE AS END"
Menu_LZLooperSettings_RecordIsRecording:
	.asciiz "SET NEXT LOADING ZONE AS END: RECORDING"
Menu_LZLooperSettings_ModePosition:
	.asciiz "MODE: LOAD FROM POSITION"
Menu_LZLooperSettings_ModeExit:
	.asciiz "MODE: LOAD FROM EXIT"

.align
Menu_LZLooperSettings_Array:
	.word Menu_LZLooperSettings_TurnOnLooper
	.word Menu_LZLooperSettings_Record
	.word Menu_LZLooperSettings_ModePosition

.align
Menu_LZLooperSettings_Functions:
	.word ActiveMenu_LZLooper_ToggleOn
	.word ActiveMenu_LZLooper_StartRecording
	.word ActiveMenu_LZLooper_ToggleMode

.align
Menu_LZLooperSettings_Struct:
	.word Menu_LZLooperSettings_Array // Text Array
	.word Menu_LZLooperSettings_Functions // Function Array
	.byte 3 // Array Items
	.byte 27 // Parent Screen

.align
Menu_Cheats_ChangeMoves:
	.asciiz "ALTER MOVESET"
Menu_Cheats_GiveCoins:
	.asciiz "GIVE COINS"
Menu_Cheats_RestockInventory:
	.asciiz "RESTOCK INVENTORY"
Menu_Cheats_Gamemode:
	.asciiz "CHANGE GAMEMODE"
Menu_Cheats_CancelCutscene:
	.asciiz "CANCEL CUTSCENE"
Menu_Cheats_Skew:
	.asciiz "INSTANT SKEW"
Menu_Cheats_LToLevitateOff:
	.asciiz "L TO LEVITATE: OFF"
Menu_Cheats_LToLevitateOn:
	.asciiz "L TO LEVITATE: ON"
Menu_Cheats_SandstormOff:
	.asciiz "AZTEC SANDSTORM: OFF"
Menu_Cheats_SandstormOn:
	.asciiz "AZTEC SANDSTORM: ON"
Menu_Cheats_SandstormUnknown:
	.asciiz "AZTEC SANDSTORM: UNKNOWN"
Menu_Cheats_AutoPhaseOff:
	.asciiz "AUTO PHASE STATE: OFF"
Menu_Cheats_AutoPhaseOn:
	.asciiz "AUTO PHASE STATE: ON"
Menu_Cheats_AutoMoonkickOff:
	.asciiz "AUTO MOONKICK: OFF"
Menu_Cheats_AutoMoonkickOn:
	.asciiz "AUTO MOONKICK: ON"
Menu_Cheats_InfHealthOff:
	.asciiz "INFINITE HEALTH: OFF"
Menu_Cheats_InfHealthOn:
	.asciiz "INFINITE HEALTH: ON"
Menu_Cheats_EnemySpawnOff:
	.asciiz "ENEMY SPAWNING: OFF"
Menu_Cheats_EnemySpawnOn:
	.asciiz "ENEMY SPAWNING: ON"

.align
Menu_Cheats_Array:
	.word Menu_Cheats_ChangeMoves
	.word Menu_Cheats_GiveCoins
	.word Menu_Cheats_RestockInventory
	.word Menu_Cheats_Gamemode
	.word Menu_Cheats_CancelCutscene
	.word Menu_Cheats_Skew
	.word Menu_Cheats_LToLevitateOff
	.word Menu_Cheats_SandstormUnknown
	.word Menu_Cheats_AutoPhaseOff
	.word Menu_Cheats_AutoMoonkickOff
	.word Menu_Cheats_InfHealthOff
	.word Menu_Cheats_EnemySpawnOn

.align
Menu_Cheats_Functions:
	.word ActiveMenu_OpenMovesMenu
	.word GiveCoins
	.word RestockInventory
	.word ActiveMenu_OpenGamemodeMenu
	.word CancelCutscene
	.word SkewCheat
	.word ActiveMenu_ToggleLToLevitate
	.word 0
	.word ActiveMenu_ToggleAutoPhaseState
	.word ActiveMenu_ToggleAutoMoonkick
	.word ActiveMenu_ToggleInfHealth
	.word ActiveMenu_ToggleEnemySpawn

.align
Menu_Cheats_Struct:
	.word Menu_Cheats_Array // Text Array
	.word Menu_Cheats_Functions // Function Array
	.byte 12 // Array Items
	.byte 0 // Parent Screen

.align
Menu_MovesMaster_GiveAll:
	.asciiz "GIVE ALL MOVES"
Menu_MovesMaster_ClearAll:
	.asciiz "REVOKE ALL MOVES"
Menu_MovesMaster_Cranky:
	.asciiz "CRANKY"
Menu_MovesMaster_Funky:
	.asciiz "FUNKY"
Menu_MovesMaster_Candy:
	.asciiz "CANDY"
Menu_MovesMaster_CameraOn:
	.asciiz "CAMERA AND SHOCKWAVE: ON"
Menu_MovesMaster_CameraOff:
	.asciiz "CAMERA AND SHOCKWAVE: OFF"

.align
Menu_MovesMaster_Array:
	.word Menu_MovesMaster_GiveAll
	.word Menu_MovesMaster_ClearAll
	.word Menu_MovesMaster_Cranky
	.word Menu_MovesMaster_Funky
	.word Menu_MovesMaster_Candy
	.word Menu_MovesMaster_CameraOff

.align
Menu_MovesMaster_Functions:
	.word GiveMoves
	.word ClearMoves
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_MovesMaster_Struct:
	.word Menu_MovesMaster_Array // Text Array
	.word Menu_MovesMaster_Functions // Function Array
	.byte 6 // Array Items
	.byte 30 // Parent Screen

.align
Menu_Gamemodes_NintendoLogo:
	.asciiz "NINTENDO LOGO"
Menu_Gamemodes_OpeningCutscene:
	.asciiz "OPENING CUTSCENE"
Menu_Gamemodes_Rap:
	.asciiz "DK RAP"
Menu_Gamemodes_DKTV:
	.asciiz "DK TV"
Menu_Gamemodes_4:
	.asciiz "GAMEMODE 4"
Menu_Gamemodes_MainMenu:
	.asciiz "MAIN MENU"
Menu_Gamemodes_Adventure:
	.asciiz "ADVENTURE MODE"
Menu_Gamemodes_LoadingGameOver:
	.asciiz "LOADING GAME OVER"
Menu_Gamemodes_8:
	.asciiz "GAMEMODE 8"
Menu_Gamemodes_GameOver:
	.asciiz "GAME OVER"
Menu_Gamemodes_EndSeqAdv:
	.asciiz "END SEQUENCE: ADVENTURE"
Menu_Gamemodes_DKTheatre:
	.asciiz "DK THEATRE"
Menu_Gamemodes_Bosses:
	.asciiz "DK BONUS AND BOSSES"
Menu_Gamemodes_Snides:
	.asciiz "SNIDES BONUS GAMES"
Menu_Gamemodes_EndSeqDKT:
	.asciiz "END SEQUENCE: DK THEATRE"

.align
Menu_Gamemodes_Array:
	.word Menu_Gamemodes_NintendoLogo
	.word Menu_Gamemodes_OpeningCutscene
	.word Menu_Gamemodes_Rap
	.word Menu_Gamemodes_DKTV
	.word Menu_Gamemodes_4
	.word Menu_Gamemodes_MainMenu
	.word Menu_Gamemodes_Adventure
	.word Menu_Gamemodes_LoadingGameOver
	.word Menu_Gamemodes_8
	.word Menu_Gamemodes_GameOver
	.word Menu_Gamemodes_EndSeqAdv
	.word Menu_Gamemodes_DKTheatre
	.word Menu_Gamemodes_Bosses
	.word Menu_Gamemodes_Snides
	.word Menu_Gamemodes_EndSeqDKT

.align
Menu_Gamemodes_Functions:
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode
	.word ActiveMenu_SetGamemode

.align
Menu_Gamemodes_Struct:
	.word Menu_Gamemodes_Array // Text Array
	.word Menu_Gamemodes_Functions // Function Array
	.byte 15 // Array Items
	.byte 30 // Parent Screen

.align
Menu_Watch_Viewed_None:
	.asciiz "WATCHED: NONE"
Menu_Watch_Viewed_Lag:
	.asciiz "WATCHED: LAG"
Menu_Watch_Viewed_CumulativeLag:
	.asciiz "WATCHED: CUMULATIVE LAG"
Menu_Watch_Viewed_Speed:
	.asciiz "WATCHED: SPEED"
Menu_Watch_Viewed_Timer:
	.asciiz "WATCHED: TIMER"
Menu_Watch_Viewed_GKTimer:
	.asciiz "WATCHED: GIANT KOSHA TIMER"
Menu_Watch_Viewed_Movement:
	.asciiz "WATCHED: MOVEMENT STATE"
Menu_Watch_Viewed_Angle:
	.asciiz "WATCHED: ANGLE"
Menu_Watch_Viewed_Input:
	.asciiz "WATCHED: INPUT"

.align
Menu_Watch_Viewed_Array:
	.word Menu_Watch_Viewed_None
	.word Menu_Watch_Viewed_Lag
	.word Menu_Watch_Viewed_CumulativeLag
	.word Menu_Watch_Viewed_Speed
	.word Menu_Watch_Viewed_Timer
	.word Menu_Watch_Viewed_GKTimer
	.word Menu_Watch_Viewed_Movement
	.word Menu_Watch_Viewed_Angle
	.word Menu_Watch_Viewed_Input

.align
Menu_Watch_ToggleOff:
	.asciiz "TURN OFF DISPLAY"
Menu_Watch_Lag:
	.asciiz "LAG"
Menu_Watch_CumulativeLag:
	.asciiz "CUMULATIVE LAG"
Menu_Watch_Speed:
	.asciiz "SPEED"
Menu_Watch_Timer:
	.asciiz "TIMER"
Menu_Watch_GKTimer:
	.asciiz "GIANT KOSHA TIMER"
Menu_Watch_Movement:
	.asciiz "MOVEMENT STATE"
Menu_Watch_Angle:
	.asciiz "ANGLE"
Menu_Watch_Input:
	.asciiz "INPUT"

.align
Menu_Watch_Array:
	.word Menu_Watch_Viewed_None
	.word Menu_Watch_ToggleOff
	.word Menu_Watch_Lag
	.word Menu_Watch_CumulativeLag
	.word Menu_Watch_Speed
	.word Menu_Watch_Timer
	.word Menu_Watch_GKTimer
	.word Menu_Watch_Movement
	.word Menu_Watch_Angle
	.word Menu_Watch_Input

.align
Menu_Watch_Functions:
	.word 0
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch

.align
Menu_Watch_Struct:
	.word Menu_Watch_Array // Text Array
	.word Menu_Watch_Functions // Function Array
	.byte 10 // Array Items
	.byte 0 // Parent Screen

// TO ADD:
// Special Flags
	// Special Flags Toggle
// Cheats
	// Moves
		// Sniper Scope
		// Slam Level
	// Toggle Sandstorm
// File Status
	// 101%
	// Max%
	// Takeoff Skip
// Warps
	// Set/Clear Individual
	// Set/Clear Level
	// Set/Clear All
// Watches
	// Lag
	// Cumulative Lag
	// Speed
	// Timer
	// Giant Kosha Timer
	// Movement State
	// Angle
	// Input
// Settings
	// Disable Position Buttons
	// Disable Tag Anywhere
	// Sound
	// Music
	// Screen Ratio
	// Camera Mode

.align
Menu_Settings_HorizontalDPad:
	.asciiz "D-PAD LEFT AND RIGHT FUNCTION"
Menu_Settings_DDown:
	.asciiz "D-DOWN FUNCTION"
Menu_Settings_Sound:
	.asciiz "SOUND"
Menu_Settings_Music:
	.asciiz "MUSIC"
Menu_Settings_ScreenRatio:
	.asciiz "SCREEN RATIO"
Menu_Settings_Camera:
	.asciiz "CAMERA MODE"
Menu_Settings_QOLChanges:
	.asciiz "QUALITY OF LIFE CHANGES"

.align
Menu_Settings_Array:
	.word Menu_Settings_HorizontalDPad
	.word Menu_Settings_DDown
	.word Menu_Settings_Sound
	.word Menu_Settings_Music
	.word Menu_Settings_ScreenRatio
	.word Menu_Settings_Camera
	.word Menu_Settings_QOLChanges

.align
Menu_Settings_Functions:
	.word ActiveMenu_OpenDPadLRMenu
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word ActiveMenu_OpenQOLMenu

.align
Menu_Settings_Struct:
	.word Menu_Settings_Array // Text Array
	.word Menu_Settings_Functions // Function Array
	.byte 7 // Array Items
	.byte 0 // Parent Screen

.align
Menu_HorizontalDPad_Mode_PositionWarp:
	.asciiz "ACTION: POSITION WARP"
Menu_HorizontalDPad_Mode_FrameAdvance:
	.asciiz "ACTION: FRAME ADVANCE"
Menu_HorizontalDPad_Mode_Nothing:
	.asciiz "ACTION: NOTHING"
Menu_HorizontalDPad_PositionWarp:
	.asciiz "POSITION WARP"
Menu_HorizontalDPad_FrameAdvance:
	.asciiz "FRAME ADVANCE"
Menu_HorizontalDPad_Nothing:
	.asciiz "NOTHING"

.align
Menu_HorizontalDPad_Array:
	.word Menu_HorizontalDPad_Mode_PositionWarp
	.word Menu_HorizontalDPad_PositionWarp
	.word Menu_HorizontalDPad_FrameAdvance
	.word Menu_HorizontalDPad_Nothing

.align
Menu_HorizontalDPad_Mode_Array:
	.word Menu_HorizontalDPad_Mode_PositionWarp
	.word Menu_HorizontalDPad_Mode_FrameAdvance
	.word Menu_HorizontalDPad_Mode_Nothing

.align
Menu_HorizontalDPad_Functions:
	.word 0
	.word ActiveMenu_SetDPadLR
	.word ActiveMenu_SetDPadLR
	.word ActiveMenu_SetDPadLR

.align
Menu_HorizontalDPad_Struct:
	.word Menu_HorizontalDPad_Array // Text Array
	.word Menu_HorizontalDPad_Functions // Function Array
	.byte 4 // Array Items
	.byte 34 // Parent Screen

.align
SpawnEnemyTypeAvoid:
	.byte 0x01 // Giant Clam
	.byte 0x08 // Army Dillo
	.byte 0x0B // Cranky
	.byte 0x0C // Funky
	.byte 0x0D // Candy
	.byte 0x0E // Beetle
	.byte 0x0F // Mermaid
	.byte 0x13 // Cutscene DK
	.byte 0x14 // Cutscene Diddy
	.byte 0x15 // Cutscene Lanky
	.byte 0x16 // Cutscene Tiny
	.byte 0x17 // Cutscene Chunky
	.byte 0x18 // T&S Padlock
	.byte 0x19 // Llama
	.byte 0x1A // MJ
	.byte 0x1D // Race Vulture
	.byte 0x26 // Pufftoss
	.byte 0x28 // K Rool's Foot
	.byte 0x2E // Troff
	.byte 0x30 // BHDM
	.byte 0x34 // Toy Box (BHDM)
	.byte 0x37 // Scoff
	.byte 0x39 // Dogadon
	.byte 0x42 // Mech Fish
	.byte 0x44 // Fairy
	.byte 0x48 // Rabbit
	.byte 0x49 // Owl
	.byte 0x5A // Rabbit
	.byte 0x5D // K. Lumsy
	.byte 0x5E // Spider Boss
	.byte 0x61 // K. Rool (DK Phase)
	.byte 0x69 // Enemy Car
	.byte 0x6A // K. Rool (Diddy Phase)
	.byte 0x6B // K. Rool (Lanky Phase)
	.byte 0x6C // K. Rool (Tiny Phase)
	.byte 0x6D // K. Rool (Chunky Phase)
	.byte 0x6E // Bug
	.byte 0x6F // BFI Fairy
	.byte 0x70 // Ice Tomato
	.byte 0 // Null Terminator

.align
Savestate_Array:
	.word Savestate_0
	.word Savestate_1
	.word Savestate_2
	.word Savestate_3

.align
GraphicalOverlaySpace:
	// GO1-1
	.word 0
	.word 0
	.word 0
	// GO1-2
	.word 0
	.word 0
	.word 0
	// GO1-3
	.word 0
	.word 0
	.word 0
	// GO1-4
	.word 0
	.word 0
	.word 0
	// GO1-5
	.word 0
	.word 0
	.word 0
	// GO1-6
	.word 0
	.word 0
	.word 0
	// GO1-7
	.word 0
	.word 0
	.word 0
	// GO1-8
	.word 0
	.word 0
	.word 0
	// GO2-1
	.word 0
	.word 0
	.word 0
	// GO2-2
	.word 0
	.word 0
	.word 0
	// GO2-3
	.word 0
	.word 0
	.word 0
	// GO2-4
	.word 0
	.word 0
	.word 0
	// GO2-5
	.word 0
	.word 0
	.word 0
	// GO2-6
	.word 0
	.word 0
	.word 0
	// GO2-7
	.word 0
	.word 0
	.word 0
	// GO2-8
	.word 0
	.word 0
	.word 0
	// GO3-1
	.word 0
	.word 0
	.word 0
	// GO3-2
	.word 0
	.word 0
	.word 0
	// GO3-3
	.word 0
	.word 0
	.word 0
	// GO3-4
	.word 0
	.word 0
	.word 0
	// GO3-5
	.word 0
	.word 0
	.word 0
	// GO3-6
	.word 0
	.word 0
	.word 0
	// GO3-7
	.word 0
	.word 0
	.word 0
	// GO3-8
	.word 0
	.word 0
	.word 0
	// GO4-1
	.word 0
	.word 0
	.word 0
	// GO4-2
	.word 0
	.word 0
	.word 0
	// GO4-3
	.word 0
	.word 0
	.word 0
	// GO4-4
	.word 0
	.word 0
	.word 0
	// GO4-5
	.word 0
	.word 0
	.word 0
	// GO4-6
	.word 0
	.word 0
	.word 0
	// GO4-7
	.word 0
	.word 0
	.word 0
	// GO4-8
	.word 0
	.word 0
	.word 0