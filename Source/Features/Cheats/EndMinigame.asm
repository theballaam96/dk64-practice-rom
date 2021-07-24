EndMinigame:
	SW 		ra, @ReturnAddress4
	LA 		a0, EndMinigame_Maps_Spawner
	LW 		a1, @CurrentMap

	EndMinigame_MapLoop_Spawner:
		LBU 	t0, 0x0 (a0)
		BEQZ 	t0, EndMinigame_Define_PPPanic
		NOP
		BEQ 	t0, a1, EndMinigame_Spawner_Define
		NOP
		B 		EndMinigame_MapLoop_Spawner
		ADDIU 	a0, a0, 1

	EndMinigame_Define_PPPanic:
		LA 		a0, EndMinigame_Maps_PPPanic
		LI 		t0, 124
		LI 		t6, 1

	EndMinigame_MapLoop_PPPanic:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_KrazyKK
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_PPPanic
		ADDIU 	a0, a0, 1

	EndMinigame_Define_KrazyKK:
		LA 		a0, EndMinigame_Maps_KrazyKK
		LI 		t0, 125
		LI 		t6, 2

	EndMinigame_MapLoop_KrazyKK:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_BBBandit
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_KrazyKK
		ADDIU 	a0, a0, 1

	EndMinigame_Define_BBBandit:
		LA 		a0, EndMinigame_Maps_BBBandit
		LI 		t0, 218
		LI 		t6, 3

	EndMinigame_MapLoop_BBBandit:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_BBBash
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_BBBandit
		ADDIU 	a0, a0, 1

	EndMinigame_Define_BBBash:
		LA 		a0, EndMinigame_Maps_BBBash
		LI 		t0, 126
		LI 		t6, 4

	EndMinigame_MapLoop_BBBash:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_KKosh
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_BBBash
		ADDIU 	a0, a0, 1

	EndMinigame_Define_KKosh:
		LA 		a0, EndMinigame_Maps_KKosh
		LI 		t0, 34
		LI 		t6, 5

	EndMinigame_MapLoop_KKosh:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_SSeek
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_KKosh
		ADDIU 	a0, a0, 1

	EndMinigame_Define_SSeek:
		LA 		a0, EndMinigame_Maps_SSeek
		LI 		t0, 127
		LI 		t6, 6

	EndMinigame_MapLoop_SSeek:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_TBarrels
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_SSeek
		ADDIU 	a0, a0, 1

	EndMinigame_Define_TBarrels:
		LA 		a0, EndMinigame_Maps_TBarrels
		LI 		t0, 336
		LI 		t6, 7

	EndMinigame_MapLoop_TBarrels:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Define_Timer
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_TBarrels
		ADDIU 	a0, a0, 1

	EndMinigame_Define_Timer:
		LA 		a0, EndMinigame_Maps_Timer
		LI 		t0, 176
		LI 		t6, 8

	EndMinigame_MapLoop_Timer:
		LBU 	t3, 0x0 (a0)
		BEQZ 	t3, EndMinigame_Error
		NOP
		BEQ 	t3, a1, EndMinigame_ActorSearch_Define
		NOP
		B 		EndMinigame_MapLoop_Timer
		ADDIU 	a0, a0, 1

	EndMinigame_Spawner_Define:
		LW 		a0, @SpawnerArray
		LHU 	a1, @SpawnerCount

	EndMinigame_Spawner_Loop:
		LBU 	t0, 0x0 (a0)
		LI 		t3, 0x4C
		BNE 	t0, t3, EndMinigame_Spawner_Increment
		NOP
		LW 		t6, 0x18 (a0)
		BEQZ 	t6, EndMinigame_Spawner_Increment
		NOP
		LI 		t9, 4
		SB 		t9, 0x14 (a0)
		B 		EndMinigame_Finish
		SB 		r0, 0x1C5 (t6)

	EndMinigame_Spawner_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, EndMinigame_Error
		ADDIU 	a0, a0, 0x48
		B 		EndMinigame_Spawner_Loop
		NOP

	EndMinigame_ActorSearch_Define:
		// t0 = searched actor type
		// t6 = end response type
		LI 		a0, @ActorArray
		LHU 	a1, @ActorCount

	EndMinigame_ActorSearch_Loop:
		LW 		a2, 0x0 (a0)
		BEQZ 	a2, EndMinigame_ActorSearch_Increment
		NOP
		LW 		t3, 0x58 (a2)
		BEQ 	t0, t3, EndMinigame_ActorSearch_FoundItem
		NOP

	EndMinigame_ActorSearch_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, EndMinigame_Error
		ADDIU 	a0, a0, 4
		B 		EndMinigame_ActorSearch_Loop
		NOP

	EndMinigame_ActorSearch_FoundItem:
		LI 		t9, 1
		BEQ 	t6, t9, EndMinigame_Write_PPPanic
		LI 		t9, 2
		BEQ 	t6, t9, EndMinigame_Write_KrazyKK
		LI 		t9, 3
		BEQ 	t6, t9, EndMinigame_Write_BBBandit
		LI 		t9, 4
		BEQ 	t6, t9, EndMinigame_Write_BBBash
		LI 		t9, 5
		BEQ 	t6, t9, EndMinigame_Write_KKosh
		LI 		t9, 6
		BEQ 	t6, t9, EndMinigame_Write_SSeek
		LI 		t9, 7
		BEQ 	t6, t9, EndMinigame_Write_TBarrels
		LI 		t9, 8
		BEQ 	t6, t9, EndMinigame_Write_Timer
		NOP
		B 		EndMinigame_Error
		NOP

	EndMinigame_Write_PPPanic:
		SB 		r0, 0x1B1 (a2)
		B 		EndMinigame_Finish
		SB 		r0, 0x1B3 (a2)

	EndMinigame_Write_KrazyKK:
		SB 		r0, 0x1BD (a2)
		B 		EndMinigame_Finish
		SB 		r0, 0x1BF (a2)

	EndMinigame_Write_BBBandit:
		LW 		t0, 0x11C (a2)
		BEQZ 	t0, EndMinigame_Error
		NOP
		// Set Handle + 0x154 to 7
		LI 		t3, 7
		SB 		t3, 0x154 (a2)
		// Set completion state for all reels
		LI 		t6, 0
		LI 		t8, 4
		LW 		t7, 0x174 (a2) // Handle Info

		EndMinigame_Write_BBBandit_Loop:
			SLL 	t9, t6, 2 // 4 * index
			ADD 	a1, t7, t9
			LW 		a0, 0x0 (a1)
			LUI 	t2, 0x8003
			ADDU 	t2, t2, t9
			LW 		t2, 0xD8B0 (t2)
			LBU 	a0, 0x15F (a0)
			ADDU 	t2, a0, t2
			SB 		r0, 0x0 (t2)
			ADDI 	t8, t8, -1
			BEQZ 	t8, EndMinigame_Write_BBBandit_TheRest
			ADDIU 	t6, t6, 1
			B 		EndMinigame_Write_BBBandit_Loop
			NOP

		EndMinigame_Write_BBBandit_TheRest:
			// Set hits_actual to 0
			LI 		t2, 1
			SH 		t2, 0x16 (t7)
			// Set Handle + 0x11C > 0x154 to not equal 5
			B 		EndMinigame_Finish
			SB 		r0, 0x154 (t0)
	
	EndMinigame_Write_BBBash:
		B 		EndMinigame_Finish
		SB 		r0, 0x1A1 (a2)

	EndMinigame_Write_KKosh:
		B 		EndMinigame_Finish
		SB 		r0, 0x1CB (a2)

	EndMinigame_Write_SSeek:
		B 		EndMinigame_Finish
		SB 		r0, 0x19F (a2)

	EndMinigame_Write_TBarrels:
		LBU 	a0, @CutsceneActive
		BNEZ 	a0, EndMinigame_Error
		LI 		t0, 3
		B 		EndMinigame_Finish
		SB 		t0, 0x154 (a2)

	EndMinigame_Write_Timer:
		LI 		t0, 5
		B 		EndMinigame_Finish
		SB 		t0, 0x154 (a2)

	EndMinigame_Error:
		JAL 	CodedPlaySFX
		LI 		a0, @Quack

	EndMinigame_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP

LToEndMinigame:
	SW 	 	ra, @ReturnAddress2
	LBU 	a0, @LToEndGameOn
	BEQZ 	a0, LToEndMinigame_Finish
	NOP
	LBU 	a0, @NewMenuOpen
	BNEZ 	a0, LToEndMinigame_Finish
	NOP
	LBU 	a0, @ClosingMenu
	BNEZ 	a0, LToEndMinigame_Finish
	NOP
	LHU 	a0, @NewlyPressedControllerInput
	ANDI 	a0, a0, @L_Button
	BEQZ 	a0, LToEndMinigame_Finish
	NOP
	JAL		EndMinigame
	NOP

	LToEndMinigame_Finish:
		LW 		ra, @ReturnAddress2
		JR 		ra
		NOP

ToggleEndMinigameWithL:
	LI 		a1, 1
	LBU 	a0, @LToEndGameOn
	SUBU 	a0, a1, a0
	SB 		a0, @LToEndGameOn
	LA 		a2, Menu_CheatsToggles_Array
	BEQZ 	a0, ToggleEndMinigameWithL_IsOff
	NOP
	LA 		a1, Menu_Cheats_LToEndMinigame_On
	B 		ToggleEndMinigameWithL_Finish
	NOP

	ToggleEndMinigameWithL_IsOff:
		LA 		a1, Menu_Cheats_LToEndMinigame_Off

	ToggleEndMinigameWithL_Finish:
		SW 		a1, 0x28 (a2)
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

.align
EndMinigame_Maps_Spawner:
	.byte 0x68 // BBother Easy
	.byte 0x88 // BBother Normal
	.byte 0x89 // BBother Hard
	.byte 0x0B // SSnoop Normal No Logo
	.byte 0x41 // SSnoop Normal
	.byte 0x7E // SSnoop V Easy
	.byte 0x7F // SSnoop Easy
	.byte 0x80 // SSnoop Hard
	.byte 0x63 // SSSortie Easy
	.byte 0x86 // SSSortie Normal
	.byte 0x87 // SSSortie Hard
	.byte 0x60 // SSSalvage Normal
	.byte 0x84 // SSSalvage Hard
	.byte 0x85 // SSSalvage Easy
	.byte 0x23 // DK BBlast
	.byte 0xD4 // DK Rambi
	.byte 0xA5 // Diddy Kremling
	.byte 0xC9 // Diddy Rocketbarrel
	.byte 0x03 // Lanky Maze
	.byte 0xCA // Lanky Zinger
	.byte 0x32 // Tiny Bounce
	.byte 0xD2 // Tiny Floor is lava
	.byte 0xD1 // Chunky ? Box
	.byte 0xD3 // Chunky Gun
	.byte 0x4E // BBBarrage Easy
	.byte 0x4F // BBBarrage Normal
	.byte 0x83 // BBBarrage Hard
	.byte 0x42 // MMMaul Hard
	.byte 0x44 // MMMaul Easy
	.byte 0x45 // MMMaul Normal
	.byte 0x7C // MMMaul Insane
	.byte 0x43 // SSnatch Normal
	.byte 0x4A // SSnatch Easy
	.byte 0x4B // SSnatch Hard
	.byte 0x7D // SSnatch Insane
	.byte 0 // Null terminator

EndMinigame_Maps_PPPanic:
	.byte 0x90 // PPPanic V Easy
	.byte 0x91 // PPPanic Easy
	.byte 0x92 // PPPanic Normal
	.byte 0x93 // PPPanic Hard
	.byte 0 // Null terminator

EndMinigame_Maps_KrazyKK:
	.byte 0x65 // KrazyKK Easy
	.byte 0x8D // KrazyKK Normal
	.byte 0x8E // KrazyKK Hard
	.byte 0x8F // KrazyKK Insane
	.byte 0

EndMinigame_Maps_BBBandit:
	.byte 0x20 // BBBandit V Easy
	.byte 0x79 // BBBandit Easy
	.byte 0x7A // BBBandit Normal
	.byte 0x7B // BBBandit Hard
	.byte 0

EndMinigame_Maps_BBBash:
	.byte 0x66 // BBBash V Easy
	.byte 0x94 // BBBash Easy
	.byte 0x95 // BBBash Normal
	.byte 0x96 // BBBash Hard
	.byte 0

EndMinigame_Maps_KKosh:
	.byte 0x0A // KKosh V Easy
	.byte 0x73 // KKosh Easy
	.byte 0x74 // KKosh Normal
	.byte 0x75 // KKosh Hard
	.byte 0

EndMinigame_Maps_SSeek:
	.byte 0x67 // SSeek V Easy
	.byte 0x8A // SSeek Easy
	.byte 0x8B // SSeek Normal
	.byte 0x8C // SSeek Hard
	.byte 0

EndMinigame_Maps_TBarrels:
	.byte 0xB1 // Dive Barrel
	.byte 0xB4 // Orange Barrel
	.byte 0xB5 // Barrel Barrel
	.byte 0xB6 // Vine Barrel
	.byte 0

EndMinigame_Maps_Timer:
	.byte 0x4D // MMayhem Easy
	.byte 0x81 // MMayhem Normal
	.byte 0x82 // MMayhem Hard
	.byte 0x12 // TTTrouble V Easy
	.byte 0x76 // TTTrouble Easy
	.byte 0x77 // TTTrouble Normal
	.byte 0x78 // TTTrouble Hard
	.byte 0