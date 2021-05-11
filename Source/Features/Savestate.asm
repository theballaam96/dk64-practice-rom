// Savestate Handler
GlobalSavestateHandler:
	SW 		ra, @ReturnAddress4
	LBU 	a1, @MenuSavestateAction
	BEQZ 	a1, FinishStateHandler
	NOP
	LBU 	a1, @InBadMap
	BNEZ 	a1, Nope
	NOP
	JAL 	@GetFlagBlockAddress
	ADDIU 	a0, r0, 0 // Flag Type 0 (Permanent)
	LI 		a0, 0x13C
	LBU 	t9, @FocusedSavestate
	SLL 	t9, t9, 2
	LA 		a1, Savestate_Array
	ADD 	t9, a1, t9
	LW 		t9, 0x0 (t9) // Focused Savestate Struct
	LBU 	a1, 0x1F (t9) // Save Bool
	ADDIU 	a3, v0, 0 // Copy v0
	SRA 	a2, a3, 16
	SLTIU 	a2, a2, 0x8000
	BNEZ 	a2, FinishStateHandler
	NOP
	SRA 	a2, a3, 16
	SLTIU 	a2, a2, 0x8080
	BEQZ 	a2, FinishStateHandler
	NOP
	LBU 	t6, @MenuSavestateAction
	LI 		t3, 1 // Save Action
	BEQ 	t3, t6, Handler_Save
	NOP
	BEQZ 	a1, Nope
	NOP
	B 		Handler_Load
	NOP

	Nope:
		JAL 	CodedPlaySFX
		LI 		a0, @Wrong
		B 		FinishStateHandler
		NOP

	Handler_Save:
		// t9 = Focused Savestate Struct
		LI 		a1, 1
		SB 		a1, 0x1F (t9)
		ADDIU	a1, t9, @SavestateStruct_PermFlagBlock // Permanent Flag Struct

		ReadFlags:
			LW 		a2, 0x0(a3)
			SW 		a2, 0x0(a1)
			BEQZ 	a0, SaveMap
			ADDI 	a0, a0, -4
			ADDIU 	a3, a3, 4
			B 		ReadFlags
			ADDIU 	a1, a1, 4

		SaveMap:
			SW 		t9, @VarStorage0
			// Play "Okay" SFX
			JAL 	CodedPlaySFX
			LI 		a0, @Okay
			LW 		t9, @VarStorage0
			LI 		a0, @MovesBase
			LI 		a1, @MovesBaseSize
			ADDIU 	a2, t9, @SavestateStruct_KongBase
		
			SaveKongBase:
				// Store Kong Base
				LW 		a3, 0x0(a0)
				SW 		a3, 0x0(a2)
				BEQZ 	a1, SaveKongPosition
				ADDIU 	a0, a0, 4
				ADDIU  	a2, a2, 4
				B 		SaveKongBase
				ADDI 	a1, a1, -4

		SaveKongPosition:
			LW 		a0, @Player
			BEQZ 	a0, SaveMapVars
			NOP
			SRA 	a1, a0, 16
			SLTIU 	a2, a1, 0x8000
			BNEZ 	a2, FinishStateHandler
			NOP
			SLTIU 	a2, a1, 0x8080
			BEQZ 	a2, FinishStateHandler
			NOP
			ADDIU 	a2, t9, @SavestateStruct_PositionTuple
			LW 		a1, 0x7C (a0)
			SW 		a1, 0x0 (a2)
			LW 		a1, 0x80 (a0)
			SW 		a1, 0x4 (a2)
			LW 		a1, 0x84 (a0)
			SW 		a1, 0x8 (a2)

		SaveMapVars:
			// Store Map & Kong variables
			LW 		a1, @CurrentMap
			SB 		a1, @SavestateStruct_Map (t9)
			LW 		a1, @DestExit
			SB 		a1, @SavestateStruct_Exit (t9)
			LBU		a1, @Character
			SB 		a1, @SavestateStruct_Character (t9)
			// Collectable Base
			LI 		a0, @CollectableBase
			ADDIU	a2, t9, @SavestateStruct_CollectableBase
			LD 		a1, 0x0 (a0)
			SD 		a1, 0x0 (a2)
			LD 		a1, 0x8 (a0)
			SD 		a1, 0x8 (a2)
			// Temp Flag Block
			LI 		a0, @TempFlagBlock
			ADDIU 	a1, t9, @SavestateStruct_TempFlagBlock
			LD 		a2, 0x0(a0)
			LD 		a3, 0x8(a0)
			SD 		a2, 0x0(a1)
			B 		FinishStateHandler
			SD 		a3, 0x8(a1)

	Handler_Load:
		// t9 = Focused Savestate Struct
		SW 		r0, @StoredTime
		SB 		r0, @StoredTimerMode
		// Reset LZ Recording
		SB 		r0, @LZLooper_IsRecording
		LA 		a2, Menu_LZLooperSettings_Array
		LA 		a1, Menu_LZLooperSettings_Record
		SW 		a1, 0x4 (a2)
		ADDIU	a1, t9, @SavestateStruct_PermFlagBlock

		WriteFlags:
			LW 		a2, 0x0(a1)
			SW 		a2, 0x0(a3)
			BEQZ 	a0, LoadWarp
			ADDIU 	a1, a1, 4
			ADDI 	a0, a0, -4
			B 		WriteFlags
			ADDIU 	a3, a3, 4

		LoadWarp:
			LI 		a0, @MovesBase
			LI 		a1, @MovesBaseSize
			ADDIU	a2, t9, @SavestateStruct_KongBase
		
			LoadKongBase:
				// Load Kong Base
				LW 		a3, 0x0(a2)
				SW 		a3, 0x0(a0)
				BEQZ 	a1, LoadMapVars
				ADDIU 	a0, a0, 4
				ADDIU  	a2, a2, 4
				B 		LoadKongBase
				ADDI 	a1, a1, -4

		LoadMapVars:
			// Load Map & Kong Variables
			ADDIU	a0, t9, @SavestateStruct_TempFlagBlock
			LI 		a1, @TempFlagBlock
			LD 		a2, 0x0(a0)
			LD 		a3, 0x8(a0)
			SD 		a2, 0x0(a1)
			SD 		a3, 0x8(a1)
			// LBU		a0, @SavedInSubmap
			// SB 		a0, @InSubmap
			// LBU 	a0, @SavedParentMap
			// SH		a0, @ParentMap
			// LBU 	a0, @SavedParentExit
			// SB		a0, @ParentExit
			JAL 	0x805FFFC8
			NOP
			LBU 	a0, @SavestateStruct_Character (t9)
			SB 		a0, @Character
			LBU 	a0, @SavestateStruct_Map (t9) // Destination Map
			LBU 	a1, @SavestateStruct_Exit (t9) // Destination Exit
			SW 		t9, @VarStorage0
			JAL 	@InitiateTransition
			NOP
			LW 		t9, @VarStorage0
			// Collectable Base
			LI 		a0, @CollectableBase
			ADDIU	a2, t9, @SavestateStruct_CollectableBase
			LD 		a1, 0x0 (a2)
			SD 		a1, 0x0 (a0)
			LD 		a1, 0x8 (a2)
			SD 		a1, 0x8 (a0)

		LoadKongPosition:
			ADDIU	a0, t9, @SavestateStruct_PositionTuple
			LI 		a2, @PositionWarpInfo
			LI 		a3, @PositionFloatWarps
			// X
			LW 		a1, 0x0 (a0)
			SW 		a1, 0x0 (a3)
			MTC1 	a1, f0
			CVT.W.S f0, f0
			MFC1 	a1, f0
			SH 		a1, 0x0 (a2)
			// Y & Floor
			LW 		a1, 0x4 (a0)
			SW 		a1, 0x4 (a3)
			MTC1 	a1, f0
			CVT.W.S f0, f0
			MFC1 	a1, f0
			SH 		a1, 0x2 (a2)
			// Z
			LW 		a1, 0x8 (a0)
			SW 		a1, 0x8 (a3)
			MTC1 	a1, f0
			CVT.W.S f0, f0
			MFC1 	a1, f0
			SH 		a1, 0x4 (a2)
			// Check Load State mode
			LBU 	a1, @MenuSavestateAction
			LI 		a3, 2 // Warp from position
			BNE 	a1, a3, FinishStateHandler
			NOP
			// Load in position rather than exit
			LHU 	a1, @PositionWarpBitfield
			ORI 	a1, a1, 1
			SH 		a1, @PositionWarpBitfield

	FinishStateHandler:
		SB 	r0, @MenuSavestateAction
		LW 	ra, @ReturnAddress4
		JR 	ra
		NOP

.align
Savestate_0:
	.space 0x34C

.align
Savestate_1:
	.space 0x34C

.align
Savestate_2:
	.space 0x34C

.align
Savestate_3:
	.space 0x34C