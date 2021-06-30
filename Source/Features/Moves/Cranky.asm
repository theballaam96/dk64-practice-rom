UpdateCrankyKongMove:
	SW 		ra, @ReturnAddress5
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1
	LI 		a1, @MovesBase
	LI 		a2, 0x5E
	MULTU 	a0, a2
	MFLO	a2
	ADDU 	a1, a1, a2
	LBU 	a3, 0x0 (a1) // Move Value
	LI 		t0, 3
	BEQ 	a3, t0, UpdateCrankyKongMove_Write
	LI 		t3, 0
	ADDIU 	t3, a3, 1

	UpdateCrankyKongMove_Write:
		SB 		t3, 0x0 (a1)
		JAL 	ActiveMenu_OpenCrankyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateCrankySlamMove:
	SW 		ra, @ReturnAddress5
	LI 		a1, @MovesBase
	LBU 	a3, 0x1 (a1) // Slam Value
	LI 		t0, 3
	BEQ 	a3, t0, UpdateCrankySlamMove_Write
	LI 		t3, 0
	ADDIU 	t3, a3, 1

	UpdateCrankySlamMove_Write:
		SB 		t3, 0x1 (a1) // DK
		SB 		t3, 0x5F (a1) // Diddy
		SB 		t3, 0xBD (a1) // Lanky
		SB 		t3, 0x11B (a1) // Tiny
		SB 		t3, 0x179 (a1) // Chunky
		JAL 	ActiveMenu_OpenCrankyMenu
		NOP
		LW 		ra, @ReturnAddress5
		JR 		ra
		NOP

UpdateCrankyMenu:
	LI 		a0, @MovesBase
	LBU 	a1, 0x1 (a0) // Slam Level
	LA 		a2, Menu_Cranky_Slam_List
	SLL 	a1, a1, 2
	ADD 	a2, a2, a1
	LW 		t0, 0x0 (a2) // Slam Text Pointer
	LA 		a3, Menu_Cranky_Array
	SW 		t0, 0x0 (a3)

	UpdateCrankyMenu_DefineLoop:
		LI 		a1, 5
		LA 		a2, Menu_Cranky_Kong_Lists
		ADDIU 	a3, a3, 4

	UpdateCrankyMenu_Loop:
		LBU 	t0, 0x0 (a0)
		LW 		t3, 0x0 (a2) // Kong Text Array
		SLL 	t0, t0, 2
		ADD 	t3, t3, t0
		LW 		t3, 0x0 (t3) // Move Text Pointer
		SW 		t3, 0x0 (a3)

	UpdateCrankyMenu_Increment:
		ADDIU 	a0, a0, 0x5E
		ADDI 	a1, a1, -1
		BEQZ 	a1, UpdateCrankyMenu_Finish	
		ADDIU 	a2, a2, 4
		B 		UpdateCrankyMenu_Loop
		ADDIU 	a3, a3, 4

	UpdateCrankyMenu_Finish:
		JR 		ra
		NOP

ActiveMenu_OpenCrankyMenu:
	SW 		ra, @ReturnAddress3
	LBU 	a0, @NewMenu_Screen
	LI 		a1, 47
	BEQ 	a0, a1, ActiveMenu_OpenCrankyMenu_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenCrankyMenu_Spawn:
		JAL 	ActiveMenu_ClearMenu
		NOP
		JAL 	UpdateCrankyMenu
		NOP
		LI 		a0, 47
		SB 		a0, @NewMenu_Screen	
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
Menu_Cranky_Slam_None:
	.asciiz "SLAM: NONE"
Menu_Cranky_Slam_Regular:
	.asciiz "SLAM: REGULAR"
Menu_Cranky_Slam_Super:
	.asciiz "SLAM: SUPER"
Menu_Cranky_Slam_Duper:
	.asciiz "SLAM: SUPER DUPER"
Menu_Cranky_DK_None:
	.asciiz "DK: NONE"
Menu_Cranky_DK_BBlast:
	.asciiz "DK: BBLAST"
Menu_Cranky_DK_Strong:
	.asciiz "DK: BBLAST AND STRONG KONG"
Menu_Cranky_DK_All:
	.asciiz "DK: ALL"
Menu_Cranky_Diddy_None:
	.asciiz "DIDDY: NONE"
Menu_Cranky_Diddy_BBlast:
	.asciiz "DIDDY: CCHARGE"
Menu_Cranky_Diddy_Strong:
	.asciiz "DIDDY: CCHARGE AND ROCKETBARREL"
Menu_Cranky_Diddy_All:
	.asciiz "DIDDY: ALL"
Menu_Cranky_Lanky_None:
	.asciiz "LANKY: NONE"
Menu_Cranky_Lanky_BBlast:
	.asciiz "LANKY: OSTAND"
Menu_Cranky_Lanky_Strong:
	.asciiz "LANKY: OSTAND AND BBALLOON"
Menu_Cranky_Lanky_All:
	.asciiz "LANKY: ALL"
Menu_Cranky_Tiny_None:
	.asciiz "TINY: NONE"
Menu_Cranky_Tiny_BBlast:
	.asciiz "TINY: MMONKEY"
Menu_Cranky_Tiny_Strong:
	.asciiz "TINY: MMONKEY AND PTT"
Menu_Cranky_Tiny_All:
	.asciiz "TINY: ALL"
Menu_Cranky_Chunky_None:
	.asciiz "CHUNKY: NONE"
Menu_Cranky_Chunky_BBlast:
	.asciiz "CHUNKY: HUNKY CHUNKY"
Menu_Cranky_Chunky_Strong:
	.asciiz "CHUNKY: HUNKY CHUNKY AND PPUNCH"
Menu_Cranky_Chunky_All:
	.asciiz "CHUNKY: ALL"

.align
Menu_Cranky_Slam_List:
	.word Menu_Cranky_Slam_None
	.word Menu_Cranky_Slam_Regular
	.word Menu_Cranky_Slam_Super
	.word Menu_Cranky_Slam_Duper
Menu_Cranky_DK_List:
	.word Menu_Cranky_DK_None
	.word Menu_Cranky_DK_BBlast
	.word Menu_Cranky_DK_Strong
	.word Menu_Cranky_DK_All
Menu_Cranky_Diddy_List:
	.word Menu_Cranky_Diddy_None
	.word Menu_Cranky_Diddy_BBlast
	.word Menu_Cranky_Diddy_Strong
	.word Menu_Cranky_Diddy_All
Menu_Cranky_Lanky_List:
	.word Menu_Cranky_Lanky_None
	.word Menu_Cranky_Lanky_BBlast
	.word Menu_Cranky_Lanky_Strong
	.word Menu_Cranky_Lanky_All
Menu_Cranky_Tiny_List:
	.word Menu_Cranky_Tiny_None
	.word Menu_Cranky_Tiny_BBlast
	.word Menu_Cranky_Tiny_Strong
	.word Menu_Cranky_Tiny_All
Menu_Cranky_Chunky_List:
	.word Menu_Cranky_Chunky_None
	.word Menu_Cranky_Chunky_BBlast
	.word Menu_Cranky_Chunky_Strong
	.word Menu_Cranky_Chunky_All

.align
Menu_Cranky_Array:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

.align
Menu_Cranky_Functions:
	.word UpdateCrankySlamMove
	.word UpdateCrankyKongMove
	.word UpdateCrankyKongMove
	.word UpdateCrankyKongMove
	.word UpdateCrankyKongMove
	.word UpdateCrankyKongMove

.align
Menu_Cranky_Kong_Lists:
	.word Menu_Cranky_DK_List
	.word Menu_Cranky_Diddy_List
	.word Menu_Cranky_Lanky_List
	.word Menu_Cranky_Tiny_List
	.word Menu_Cranky_Chunky_List

.align
Menu_Cranky_Struct:
	.word Menu_Cranky_Array // Text Array
	.word Menu_Cranky_Functions // Function Array
	.byte 6 // Array Items
	.byte 31 // Parent Screen