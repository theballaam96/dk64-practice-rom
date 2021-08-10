// Donkey Kong 64 - Practice ROM
// By theballaam96
// http://www.twitter.com/tjballaam

.incasm "./../../Development/dk64-practice-rom/Source/Memory/GameVars.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/Buttons.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/AddressStorage.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/Functions.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/SFX.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/Colors.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/Hack.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/SavestateStruct.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/PositionSavestate.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/LZLooper.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Memory/ActiveMenu.asm"

// OSD
[WriteTextZone]: 0x807FCAA0
[WarpY]: 69
[WipeY]: 117
[PauseMenuTextPointer]: 0x807FC7E0
[PauseMenuPointer]: 0x807FC640
[MaxCooldown]: 6
[MinCooldown]: 2
[SpecialFlagCategories]: 11

// Variables
[MasterLevelCount]: 28
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
[MaxMenuItems]: 23 // 32 (practice rom cap) - 8 (normal cap) - 1 (watch)
[EmergencyCloseLoadedAmount]: 60
[ErrorLength]: 180

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

.org 0x8073129C // Set Flag Hook
J 	WriteLastUpdatedFlags
NOP

.org 0x805FC890 // Pause Menu Volume Hook
J 	SetPauseMenuVolume
NOP

.org 0x80665354 // Movement speed hook
J 	ControlSuperspeed
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
	SB 		r0, @ClosingMenu

	SetOtherVariables:
		.incasm "./../../Development/dk64-practice-rom/Source/Features/OtherVars.asm"

		// Unlock Mystery Menu
		LI      t6, 0x807ED558
		LI      t0, -1
		SD      t0, 0(t6)
		// Set K Rool to round 11 (Cause the sound effect is the best one)
		LBU 	t0, @CutsceneActive
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
		LI 		a0, 378 // Waterfall CS
		JAL 	@CheckFlag
		LI 		a1, 0
		ADDIU 	a0, v0, 0
		BNEZ 	a0, EveryFrameFunctions 	
		NOP
		LA 		a0, Transition_Flags
		JAL 	SetAllFlags // Safe
		NOP

	EveryFrameFunctions:
		JAL 	IsPaused
		NOP
		JAL 	ChangeColour // Safe
		NOP
		LBU 	a0, @StoredRound
		LBU 	a1, @DisableTagAnywhere
		BNEZ 	a1, EveryFrameFunctions2
		SB 		a0, @KRoolRound
		JAL 	TagAnywhere // Safe
		NOP
		
	EveryFrameFunctions2:
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
		JAL 	GetGKTimer
		NOP
		JAL 	UpdateMovementStateText
		NOP
		JAL 	InfiniteHealth
		NOP
		JAL 	LToLevitate
		NOP
		JAL 	ActiveMenu_MoveSlot
		NOP
		JAL 	ActiveMenu_CloseOnTransition
		NOP
		JAL 	ActiveMenu_EmergencyClose
		NOP
		JAL 	ActiveMenu_ConfirmOption
		NOP
		JAL 	ActiveMenu_UpdateSavestateText
		NOP
		JAL  	ActiveMenu_Open
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
		JAL 	ChangeEncodedFlag
		NOP
		JAL 	Savestate_ShorthandCombo
		NOP
		JAL 	HandleTimer
		NOP
		JAL 	LTo_CancelCS
		NOP
		JAL 	LTo_ToggleTB
		NOP
		JAL 	LToEndMinigame
		NOP
		JAL 	ActiveMenu_ShortcutButtons
		NOP

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
.incasm "./../../Development/dk64-practice-rom/Source/Features/isPaused.asm"

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

.org 0x80000A30 // 0x000A30 > 0x0010BC

LoadInAdditionalFile:
    JAL     @DMAFileTransfer
    ADDIU   a0, a0, 0x13F0
    .incasm "./../../Development/dk64-practice-rom/Source/Features/EndLoadingSpot.asm"
    LI      a2, 0x805DAE00
    JAL     @DMAFileTransfer       
    LUI     a0, 0x200 // 0x2000000
    J       0x80000734
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

.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Lag.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/HeldObject.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/ISG.asm"
.align
//.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Position.asm"
//.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/ColorKong.asm"


.org 0x805DAE00
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Watches.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Savestate.asm"
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
.incasm "./../../Development/dk64-practice-rom/Source/Features/Main Menu Variables/ScreenRatio.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Main Menu Variables/ChimpyCam.asm"
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
.align
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

.incasm "./../../Development/dk64-practice-rom/Source/Features/File States/Container.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/File States/General/101.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/File States/General/Max.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/File States/General/clean.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/File States/NLE/TakeoffSkip.asm"
.align

.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/Levitate.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/TBVoid.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/SpawnSnagCheats.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/CutsceneCancel.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/EndMinigame.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/TagAllWarps.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/UndoFlagWrite.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/GainControl.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/Superspeed.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/Corruption.asm"

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

.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Watch/Timer.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Moves/GiveAll.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Moves/ClearAll.asm"
.align

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

.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/Skew.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Cheats/NoSpawn.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/PauseMenu.asm"
.align

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

ActiveMenu_OpenMapWarper_FungiMills:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 55
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

ActiveMenu_OpenMapWarper_CastleOutside:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 56
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenMapWarper_CastleRooms:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 57
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
	LI 		a0, 0x179
	JAL 	@CheckFlag
	LI 		a1, 0
	ADDIU 	t0, v0, 0
	LA 		a0, Menu_MovesMaster_CameraOff
	BEQZ 	t0, ActiveMenu_OpenMovesMenu_WriteText
	NOP
	LA 		a0, Menu_MovesMaster_CameraOn

	ActiveMenu_OpenMovesMenu_WriteText:
		LA 		a1, Menu_MovesMaster_Array
		SW 		a0, 0x18 (a1)
		LBU 	a1, @NewMenu_Screen
		LI 		a0, 31
		BEQ 	a0, a1, ActiveMenu_OpenMovesMenu_Spawn
		NOP
		SB 		r0, @NewMenu_Position

	ActiveMenu_OpenMovesMenu_Spawn:
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ChangeSavestate:
	SW 		ra, @ReturnAddress5
	LBU 	a1, @NewMenu_Position
	SB 		a1, @FocusedSavestate
	LA 		a0, Menu_Savestate_SelectedSavestate
	ADDIU 	a1, a1, 0x31
	SB 		a1, 0x10 (a0)
	JAL 	ActiveMenu_PreviousScreen
	NOP
	LW 		ra, @ReturnAddress5
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

ActiveMenu_OpenCheatsSnagMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 59
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

ActiveMenu_OpenCheatsTogglesMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP

	ActiveMenu_OpenCheatsTogglesMenu_Sandstorm:
		LW 		a0, @CurrentMap
		LI 		a1, 0x26 // Aztec
		BNE 	a0, a1, ActiveMenu_OpenCheatsTogglesMenu_WriteSandstormText
		LI 		t0, 0
		LW 		a0, @SandstormAddress
		BEQZ 	a0, ActiveMenu_OpenCheatsTogglesMenu_WriteSandstormText
		LI 		t0, 0
		LBU 	a1, 0x0 (a0)
		ADDIU 	t0, a1, 1

	ActiveMenu_OpenCheatsTogglesMenu_WriteSandstormText:
		LA 		a0, Sandstorm_TextPointers
		SLL 	t0, t0, 2
		ADD 	a0, a0, t0
		LW 		a0, 0x0 (a0)
		LA 		a1, Menu_CheatsToggles_Array
		SW 		a0, 0x4 (a1)
		LI 		a0, 58
		LBU 	a1, @NewMenu_Screen
		BEQ 	a0, a1, ActiveMenu_OpenCheatsTogglesMenu_Spawn 
		NOP
		SB 		r0, @NewMenu_Position

	ActiveMenu_OpenCheatsTogglesMenu_Spawn:
		SB 		a0, @NewMenu_Screen
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

ActiveMenu_OpenDPadDMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 62
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
	SB 		a1, @LastLoadStateAction
	JR 		ra
	NOP

ActiveMenu_PerformSavestateAction_LoadFromExit:
	LI 		a1, 3
	SB 		a1, @MenuSavestateAction
	SB 		a1, @LastLoadStateAction
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
	JAL 	@ResetMap
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

ActiveMenu_SetDPadD:
	SW 		ra, @ReturnAddress3
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1
	SB 		a0, @DisableTagAnywhere
	// Array
	LA 		a1, Menu_DPadDown_Mode_Array
	SLL 	a2, a0, 2
	ADD 	a1, a1, a2
	LW 		a1, 0x0 (a1)
	// Setting into
	LA 		a2, Menu_DPadDown_Array
	SW 		a1, 0x0 (a2)
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 62
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
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ActiveMenu_ToggleLToLevitate_IsOff
	NOP
	LA 		a1, Menu_Cheats_LToLevitateOn
	B 		ActiveMenu_ToggleLToLevitate_Finish
	NOP

	ActiveMenu_ToggleLToLevitate_IsOff:
		LA 		a1, Menu_Cheats_LToLevitateOff

	ActiveMenu_ToggleLToLevitate_Finish:
		SW 		a1, 0x0 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 58
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
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ActiveMenu_ToggleAutoPhaseState_IsOff
	NOP
	LA 		a1, Menu_Cheats_AutoPhaseOn
	B 		ActiveMenu_ToggleAutoPhaseState_Finish
	NOP

	ActiveMenu_ToggleAutoPhaseState_IsOff:
		LA 		a1, Menu_Cheats_AutoPhaseOff

	ActiveMenu_ToggleAutoPhaseState_Finish:
		SW 		a1, 0x8 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 58
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
	LA 		a2, Menu_CheatsToggles_Array 
	BEQZ 	a0, ActiveMenu_ToggleAutoMoonkick_IsOff
	NOP
	LA 		a1, Menu_Cheats_AutoMoonkickOn
	B 		ActiveMenu_ToggleAutoMoonkick_Finish
	NOP

	ActiveMenu_ToggleAutoMoonkick_IsOff:
		LA 		a1, Menu_Cheats_AutoMoonkickOff

	ActiveMenu_ToggleAutoMoonkick_Finish:
		SW 		a1, 0x0C (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 58
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
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ActiveMenu_ToggleInfHealth_IsOff
	NOP
	LA 		a1, Menu_Cheats_InfHealthOn
	B 		ActiveMenu_ToggleInfHealth_Finish
	NOP

	ActiveMenu_ToggleInfHealth_IsOff:
		LA 		a1, Menu_Cheats_InfHealthOff

	ActiveMenu_ToggleInfHealth_Finish:
		SW 		a1, 0x10 (a2)
		SW 		ra, @ReturnAddress3
		JAL 	ActiveMenu_ClearMenu
		NOP
		LI 		a0, 58
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
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ActiveMenu_ToggleEnemySpawn_IsOn
	NOP
	LA 		a1, Menu_Cheats_EnemySpawnOff
	B 		ActiveMenu_ToggleEnemySpawn_DefineLoop
	NOP

	ActiveMenu_ToggleEnemySpawn_IsOn:
		LA 		a1, Menu_Cheats_EnemySpawnOn

	ActiveMenu_ToggleEnemySpawn_DefineLoop:
		SW 		a1, 0x14 (a2)
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
		LI 		a0, 58
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

ActiveMenu_ChangeWatch:
	SW 		ra, @ReturnAddress3
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
		B 		ActiveMenu_ChangeWatch_Reload
		NOP

	ActiveMenu_ChangeWatch_Destroy:
		JAL 	Watch_DestroyWatch
		NOP
		LI 		a0, 2

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

ActiveMenu_ToggleCamera:
	SW 		ra, @ReturnAddress5
	LI 		a0, 0x179
	JAL 	@CheckFlag
	LI 		a1, 0
	ADDIU 	a1, v0, 0
	LI 		a0, 1
	SUBU 	a1, a0, a1
	LI 		a2, 0
	JAL 	@SetFlag
	LI 		a0, 0x179
	JAL 	ActiveMenu_OpenMovesMenu
	NOP
	LW 		ra, @ReturnAddress5
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
	.word Maps_FungiForestMills_Struct
	.word Maps_CreepyCastleOutsideBuildings_Struct
	.word Maps_CreepyCastleRooms_Struct

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
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/FTT.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Special Flags/Custom.asm"
.align

.align
BadSavestateMaps:
	.byte 0x01 // Funky's
	.byte 0x03 // Lanky's Maze
	.byte 0x05 // Cranky's Lab
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
	.byte 0x60 // SSSalvage (Normal)
	.byte 0x63 // SSSortie (Easy)
	.byte 0x65 // Krazy KK (Easy)
	.byte 0x66 // BBBash (V Easy)
	.byte 0x67 // SSeek (V Easy)
	.byte 0x68 // BBother (Easy)
	// All values between 0x73 and 0x96 (Inclusive). Various bonus minigames
	.byte 0x9B // Crown - Arena Ambush
	.byte 0x9C // Crown - More Kritter Karnage
	.byte 0x9D // Crown - Forest Fracas
	.byte 0x9E // Crown - Bish Bash Brawl
	.byte 0x9F // Crown - Kamikaze Kremlings
	.byte 0xA0 // Crown - Plinth Panic
	.byte 0xA1 // Crown - Pinnacle Palaver
	.byte 0xA2 // Crown - Shockwave Showdown
	.byte 0xA5 // Diddy Kremling Game
	.byte 0xC9 // Diddy Rocketbarrel Game
	.byte 0xCA // Lanky Shooting Game
	.byte 0xD1 // Chunky ? Box Game
	.byte 0xD2 // Tiny "Floor is Lava" Game
	.byte 0xD3 // Chunky Shooting Game
	.byte 0xD4 // DK Rambi Game
	.byte 0x0 // Terminator

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

.align
ROM_Title:
	.asciiz "DK64 PRACTICE ROM"
ROM_Version:
	.asciiz "VERSION 1.4"

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
Menu_Return:
	.asciiz "RETURN"
Menu_WarpMenu:
	.asciiz "WARP TO MAP"
Menu_SpecialFlags:
	.asciiz "SPECIAL FLAGS"
Menu_Savestates:
	.asciiz "SAVE STATES"
Menu_Display:
	.asciiz "WATCHES"
Menu_TimerSettings:
	.asciiz "TIMER SETTINGS"
Menu_FileStates:
	.asciiz "FILE STATES"
Menu_Cheats:
	.asciiz "CHEATS"
Menu_Settings:
	.asciiz "SETTINGS"

.align
Menu_Main_Array:
	.word Menu_WarpMenu
	.word Menu_SpecialFlags
	.word Menu_Savestates
	.word Menu_Display
	.word Menu_TimerSettings
	.word Menu_FileStates
	.word Menu_Cheats
	.word Menu_Settings
	.word Menu_Return

.align
Menu_Main_Functions:
	.word ActiveMenu_OpenMapWarper
	.word ActiveMenu_OpenFlagMenu
	.word ActiveMenu_OpenSavestateMenu
	.word ActiveMenu_OpenWatchMenu
	.word ActiveMenu_OpenTimerSettingsMenu
	.word ActiveMenu_OpenFileStatesMenu
	.word ActiveMenu_OpenCheatsMenu
	.word ActiveMenu_OpenSettingsMenu
	.word ActiveMenu_PreviousScreen

.align
Menu_Main_Struct:
	.word Menu_Main_Array // Text Array
	.word Menu_Main_Functions // Function Array
	.byte 9 // Array Items
	.byte 0 // Parent Screen
	.byte 0 // Parent Position

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
	.word Menu_Cranky_Struct
	.word Menu_Funky_Struct // 48
	.word Menu_Candy_Struct
	.word Menu_Flags_Training_Struct // 50
	.word Menu_Flags_Custom_Struct
	.word Menu_Flags_FTT_Struct // 52
	.word Menu_ScreenRatio_Struct
	.word Menu_ChimpyCam_Struct // 54
	.word Menu_MapFungiMills_Struct
	.word Menu_MapCastleOutsideBuildings_Struct // 56
	.word Menu_MapCastleRooms_Struct
	.word Menu_CheatsToggles_Struct // 58
	.word Menu_CheatsSnag_Struct
	.word Menu_TimerSettings_Struct // 60
	.word Menu_FileStates_Struct
	.word Menu_DPadDown_Struct // 62

.incasm "./../../Development/dk64-practice-rom/Source/Features/Active Menu/Warps/Container.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Aesthetic/MenuSky.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Quality of Life/StartupSkip.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Quality of Life/ForcedStorySkip.asm"
.incasm "./../../Development/dk64-practice-rom/Source/Features/Quality of Life/QOLControl.asm"

.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Moves/Cranky.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Moves/Funky.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Moves/Candy.asm"
.align
.incasm "./../../Development/dk64-practice-rom/Source/Features/Moves/Training.asm"
.align

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
	.word Menu_Return

.align
Menu_Savestate_Functions:
	.word 0
	.word ActiveMenu_OpenChangeSavestateMenu
	.word ActiveMenu_PerformSavestateAction_Save
	.word ActiveMenu_PerformSavestateAction_LoadFromPosition
	.word ActiveMenu_PerformSavestateAction_LoadFromExit
	.word ActiveMenu_PreviousScreen

.align
Menu_Savestate_Struct:
	.word Menu_Savestate_Array // Text Array
	.word Menu_Savestate_Functions // Function Array
	.byte 6 // Array Items
	.byte 0 // Parent Screen
	.byte 2 // Parent Position

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
	.word Menu_Return

.align
Menu_ChangeSavestate_Functions:
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_ChangeSavestate
	.word ActiveMenu_PreviousScreen

.align
Menu_ChangeSavestate_Struct:
	.word Menu_ChangeSavestate_Array // Text Array
	.word Menu_ChangeSavestate_Functions // Function Array
	.byte 5 // Array Items
	.byte 27 // Parent Screen
	.byte 1 // Parent Position

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
	.word Menu_Return

.align
Menu_LZLooperSettings_Functions:
	.word ActiveMenu_LZLooper_ToggleOn
	.word ActiveMenu_LZLooper_StartRecording
	.word ActiveMenu_LZLooper_ToggleMode
	.word ActiveMenu_PreviousScreen

.align
Menu_LZLooperSettings_Struct:
	.word Menu_LZLooperSettings_Array // Text Array
	.word Menu_LZLooperSettings_Functions // Function Array
	.byte 4 // Array Items
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
Menu_Cheats_TBVoid:
	.asciiz "TOGGLE TAG BARREL VOID"
Menu_Cheats_VisifySnag:
	.asciiz "VISIFY SPAWN SNAG COLLECTABLES"
Menu_Cheats_ResetSnag:
	.asciiz "RESET SPAWN SNAG COLLECTABLES"
Menu_Cheats_UndoFlag:
	.asciiz "UNDO LAST FLAG WRITE"
Menu_Cheats_GainControl:
	.asciiz "GAIN CONTROL"
Menu_Cheats_Toggles:
	.asciiz "TOGGLES"
Menu_Cheats_SnagCheats:
	.asciiz "SPAWN SNAG CHEATS"
Menu_Cheats_ForceEndMinigame:
	.asciiz "FORCE END MINIGAME"
Menu_Cheats_Superspeed_Off:
	.asciiz "SUPERSPEED: OFF"
Menu_Cheats_Superspeed_On:
	.asciiz "SUPERSPEED: ON"
Menu_Cheats_LToCancelCS_Off:
	.asciiz "L TO CANCEL CUTSCENE: OFF"
Menu_Cheats_LToCancelCS_On:
	.asciiz "L TO CANCEL CUTSCENE: ON"
Menu_Cheats_LToToggleTB_Off:
	.asciiz "L TO TOGGLE TB VOID: OFF"
Menu_Cheats_LToToggleTB_On:
	.asciiz "L TO TOGGLE TB VOID: ON"
Menu_Cheats_LToEndMinigame_Off:
	.asciiz "L TO END MINIGAME: OFF"
Menu_Cheats_LToEndMinigame_On:
	.asciiz "L TO END MINIGAME: ON"
Menu_Cheats_TagWarps:
	.asciiz "TAG ALL WARPS"
Menu_Cheats_Corruption:
	.asciiz "CORRUPT"

.align
Menu_Cheats_Array:
	.word Menu_Cheats_ChangeMoves
	.word Menu_Cheats_GiveCoins
	.word Menu_Cheats_RestockInventory
	.word Menu_Cheats_Gamemode
	.word Menu_Cheats_CancelCutscene
	.word Menu_Cheats_Skew
	.word Menu_Cheats_SnagCheats
	.word Menu_Cheats_Toggles
	.word Menu_Cheats_UndoFlag
	.word Menu_Cheats_GainControl
	.word Menu_Cheats_ForceEndMinigame
	.word Menu_Cheats_TagWarps
	.word Menu_Cheats_Corruption
	.word Menu_Return

.align
Menu_Cheats_Functions:
	.word ActiveMenu_OpenMovesMenu
	.word GiveCoins
	.word RestockInventory
	.word ActiveMenu_OpenGamemodeMenu
	.word CancelCutscene
	.word SkewCheat
	.word ActiveMenu_OpenCheatsSnagMenu
	.word ActiveMenu_OpenCheatsTogglesMenu
	.word UndoLastFlagWrite
	.word GainControl
	.word EndMinigame
	.word TagAllWarpsCheat
	.word CorruptMe
	.word ActiveMenu_PreviousScreen

.align
Menu_Cheats_Struct:
	.word Menu_Cheats_Array // Text Array
	.word Menu_Cheats_Functions // Function Array
	.byte 14 // Array Items
	.byte 0 // Parent Screen
	.byte 6 // Parent Position

.align
Menu_CheatsToggles_Array:
	.word Menu_Cheats_LToLevitateOff
	.word Menu_Cheats_SandstormUnknown
	.word Menu_Cheats_AutoPhaseOff
	.word Menu_Cheats_AutoMoonkickOff
	.word Menu_Cheats_InfHealthOff
	.word Menu_Cheats_EnemySpawnOn
	.word Menu_Cheats_TBVoid
	.word Menu_Cheats_Superspeed_Off
	.word Menu_Cheats_LToCancelCS_Off
	.word Menu_Cheats_LToToggleTB_Off
	.word Menu_Cheats_LToEndMinigame_Off
	.word Menu_Return

.align
Menu_CheatsToggles_Functions:
	.word ActiveMenu_ToggleLToLevitate
	.word ToggleAztecSandstorm
	.word ActiveMenu_ToggleAutoPhaseState
	.word ActiveMenu_ToggleAutoMoonkick
	.word ActiveMenu_ToggleInfHealth
	.word ActiveMenu_ToggleEnemySpawn
	.word ActiveMenu_ToggleTBVoid
	.word ToggleSuperspeed
	.word ToggleCSCancelLMode
	.word ToggleTBVoidLMode
	.word ToggleEndMinigameWithL
	.word ActiveMenu_PreviousScreen

.align
Menu_CheatsToggles_Struct:
	.word Menu_CheatsToggles_Array // Text Array
	.word Menu_CheatsToggles_Functions // Function Array
	.byte 12 // Array Items
	.byte 30 // Parent Screen
	.byte 7 // Parent Position

.align
Menu_CheatsSnag_Array:
	.word Menu_Cheats_VisifySnag
	.word Menu_Cheats_ResetSnag
	.word Menu_Return

.align
Menu_CheatsSnag_Functions:
	.word VisifySnagGBs
	.word ResetSnagGBs
	.word ActiveMenu_PreviousScreen

.align
Menu_CheatsSnag_Struct:
	.word Menu_CheatsSnag_Array // Text Array
	.word Menu_CheatsSnag_Functions // Function Array
	.byte 3 // Array Items
	.byte 30 // Parent Screen
	.byte 6 // Parent Position

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
Menu_MovesMaster_Training:
	.asciiz "TRAINING BARRELS"
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
	.word Menu_MovesMaster_Training
	.word Menu_MovesMaster_CameraOff
	.word Menu_Return

.align
Menu_MovesMaster_Functions:
	.word GiveMoves
	.word ClearMoves
	.word ActiveMenu_OpenCrankyMenu
	.word ActiveMenu_OpenFunkyMenu
	.word ActiveMenu_OpenCandyMenu
	.word ActiveMenu_OpenFlagMenu_Training
	.word ActiveMenu_ToggleCamera
	.word ActiveMenu_PreviousScreen

.align
Menu_MovesMaster_Struct:
	.word Menu_MovesMaster_Array // Text Array
	.word Menu_MovesMaster_Functions // Function Array
	.byte 8 // Array Items
	.byte 30 // Parent Screen
	.byte 0 // Parent Position

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
	.word Menu_Return

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
	.word ActiveMenu_PreviousScreen

.align
Menu_Gamemodes_Struct:
	.word Menu_Gamemodes_Array // Text Array
	.word Menu_Gamemodes_Functions // Function Array
	.byte 16 // Array Items
	.byte 30 // Parent Screen
	.byte 3 // Parent Position

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
Menu_Watch_Viewed_HeldObject:
	.asciiz "WATCHED: HELD ACTOR"
Menu_Watch_Viewed_ISG:
	.asciiz "WATCHED: INTRO STORY TIMER"

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
	.word Menu_Watch_Viewed_HeldObject
	.word Menu_Watch_Viewed_ISG

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
Menu_Watch_HeldObject:
	.asciiz "HELD ACTOR"
Menu_Watch_ISG:
	.asciiz "INTRO STORY TIMER"

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
	.word Menu_Watch_HeldObject
	.word Menu_Watch_ISG
	.word Menu_Return

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
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_ChangeWatch
	.word ActiveMenu_PreviousScreen

.align
Menu_Watch_Struct:
	.word Menu_Watch_Array // Text Array
	.word Menu_Watch_Functions // Function Array
	.byte 13 // Array Items
	.byte 0 // Parent Screen
	.byte 3 // Parent Position

.align
Menu_Settings_HorizontalDPad:
	.asciiz "D-PAD LEFT AND RIGHT FUNCTION"
Menu_Settings_DDown:
	.asciiz "D-DOWN FUNCTION"
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
	.word Menu_Settings_ScreenRatio
	.word Menu_Settings_Camera
	.word Menu_Settings_QOLChanges
	.word Menu_Return

.align
Menu_Settings_Functions:
	.word ActiveMenu_OpenDPadLRMenu
	.word ActiveMenu_OpenDPadDMenu
	.word ActiveMenu_OpenScreenRatioMenu
	.word ActiveMenu_OpenChimpyCamMenu
	.word ActiveMenu_OpenQOLMenu
	.word ActiveMenu_PreviousScreen

.align
Menu_Settings_Struct:
	.word Menu_Settings_Array // Text Array
	.word Menu_Settings_Functions // Function Array
	.byte 6 // Array Items
	.byte 0 // Parent Screen
	.byte 7 // Parent Position

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
	.word Menu_Return

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
	.word ActiveMenu_PreviousScreen

.align
Menu_HorizontalDPad_Struct:
	.word Menu_HorizontalDPad_Array // Text Array
	.word Menu_HorizontalDPad_Functions // Function Array
	.byte 5 // Array Items
	.byte 34 // Parent Screen
	.byte 0 // Parent Position

.align
Menu_DPadDown_Mode_TagAnywhere:
	.asciiz "ACTION: TAG ANYWHERE"
Menu_DPadDown_Mode_Nothing:
	.asciiz "ACTION: NOTHING"
Menu_DPadDown_TagAnywhere:
	.asciiz "TAG ANYWHERE"
Menu_DPadDown_Nothing:
	.asciiz "NOTHING"

.align
Menu_DPadDown_Array:
	.word Menu_DPadDown_Mode_TagAnywhere
	.word Menu_DPadDown_TagAnywhere
	.word Menu_DPadDown_Nothing
	.word Menu_Return
Menu_DPadDown_Mode_Array:
	.word Menu_DPadDown_Mode_TagAnywhere
	.word Menu_DPadDown_Mode_Nothing
Menu_DPadDown_Functions:
	.word 0
	.word ActiveMenu_SetDPadD
	.word ActiveMenu_SetDPadD
	.word ActiveMenu_PreviousScreen
.align
Menu_DPadDown_Struct:
	.word Menu_DPadDown_Array
	.word Menu_DPadDown_Functions
	.byte 4 // Array Items
	.byte 34 // Parent Screen
	.byte 1 // Parent Position

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
GraphicalOverlaySpace:
	.space 0x180