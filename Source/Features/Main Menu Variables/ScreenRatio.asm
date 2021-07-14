SetScreenRatio:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1
	SB 		a0, @ScreenRatio
	JAL 	ActiveMenu_OpenScreenRatioMenu
	NOP
	LW 		ra, @ReturnAddress4
	JR 		ra
	NOP

ActiveMenu_OpenScreenRatioMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LBU		a0, @ScreenRatio
	SLL 	a0, a0, 2
	LA 		t0, Menu_ScreenRatio_CurrentRatios
	ADD 	t0, t0, a0
	LW 		t0, 0x0 (t0)
	LA 		a0, Menu_ScreenRatio_Array
	SW 		t0, 0x0 (a0)
	LI 		a0, 53
	LBU 	a1, @NewMenu_Screen
	BEQ 	a0, a1, ActiveMenu_OpenScreenRatioMenu_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenScreenRatioMenu_Spawn:
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
Menu_ScreenRatio_Current_Normal:
	.asciiz "CURRENT: 4:3"
Menu_ScreenRatio_Current_Wide:
	.asciiz "CURRENT: 16:9"
Menu_ScreenRatio_Set_Normal:
	.asciiz "SET TO 4:3"
Menu_ScreenRatio_Set_Wide:
	.asciiz "SET TO 16:9"

.align
Menu_ScreenRatio_CurrentRatios:
	.word Menu_ScreenRatio_Current_Normal
	.word Menu_ScreenRatio_Current_Wide

.align
Menu_ScreenRatio_Array:
	.word 0
	.word Menu_ScreenRatio_Set_Normal
	.word Menu_ScreenRatio_Set_Wide
	.word Menu_Return

.align
Menu_ScreenRatio_Functions:
	.word 0
	.word SetScreenRatio
	.word SetScreenRatio
	.word ActiveMenu_PreviousScreen

Menu_ScreenRatio_Struct:
	.word Menu_ScreenRatio_Array // Text Array
	.word Menu_ScreenRatio_Functions // Function Array
	.byte 4 // Array Items
	.byte 34 // Parent Screen
