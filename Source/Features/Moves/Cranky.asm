.align
Menu_Cranky_Slam_None:
	.asciiz "SLAM - NONE"
Menu_Cranky_Slam_Regular:
	.asciiz "SLAM - REGULAR"
Menu_Cranky_Slam_Super:
	.asciiz "SLAM - SUPER"
Menu_Cranky_Slam_Duper:
	.asciiz "SLAM - SUPER DUPER"
Menu_Cranky_DK_None:
	.asciiz "DK - NONE"
Menu_Cranky_DK_BBlast:
	.asciiz "DK - BBLAST"
Menu_Cranky_DK_Strong:
	.asciiz "DK - BBLAST AND STRONG KONG"
Menu_Cranky_DK_All:
	.asciiz "DK - ALL"
Menu_Cranky_Diddy_None:
	.asciiz "DIDDY - NONE"
Menu_Cranky_Diddy_BBlast:
	.asciiz "DIDDY - CCHARGE"
Menu_Cranky_Diddy_Strong:
	.asciiz "DIDDY - CCHARGE AND ROCKETBARREL"
Menu_Cranky_Diddy_All:
	.asciiz "DIDDY - ALL"
Menu_Cranky_Lanky_None:
	.asciiz "LANKY - NONE"
Menu_Cranky_Lanky_BBlast:
	.asciiz "LANKY - OSTAND"
Menu_Cranky_Lanky_Strong:
	.asciiz "LANKY - OSTAND AND BBALLOON"
Menu_Cranky_Lanky_All:
	.asciiz "LANKY - ALL"
Menu_Cranky_Tiny_None:
	.asciiz "TINY - NONE"
Menu_Cranky_Tiny_BBlast:
	.asciiz "TINY - MMONKEY"
Menu_Cranky_Tiny_Strong:
	.asciiz "TINY - MMONKEY AND PTT"
Menu_Cranky_Tiny_All:
	.asciiz "TINY - ALL"
Menu_Cranky_Chunky_None:
	.asciiz "CHUNKY - NONE"
Menu_Cranky_Chunky_BBlast:
	.asciiz "CHUNKY - HUNKY CHUNKY"
Menu_Cranky_Chunky_Strong:
	.asciiz "CHUNKY - HUNKY CHUNKY AND PPUNCH"
Menu_Cranky_Chunky_All:
	.asciiz "CHUNKY - ALL"

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

.align
Menu_Cranky_Functions:
	.word 0
	.word 0
	.word 0
	.word 0

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
	.byte 4 // Array Items
	.byte 31 // Parent Screen

.align
UpdateCrankyKongMove:
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1
	LI 		a1, @CollectableBase
	LI 		a2, 0x5E
	MULTU 	a0, a2
	MFLO	a2
	ADDU 	a1, a1, a2
	LBU 	a3, 0x0 (a1)
	LI 		t0, 3
	BEQ 	a3, t0, UpdateCrankyKongMove_Write
	LI 		t3, 0
	ADDIU 	t3, a3, 1

	UpdateCrankyKongMove_Write:
		SB 		t3, 0x0 (a1)
		JR 		ra
		NOP