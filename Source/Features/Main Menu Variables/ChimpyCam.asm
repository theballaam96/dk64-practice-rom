SetChimpyCam:
	SW 		ra, @ReturnAddress4
	LBU 	a0, @NewMenu_Position
	ADDI 	a0, a0, -1
	SB 		a0, @ChimpyCam
	JAL 	ActiveMenu_OpenChimpyCamMenu
	NOP
	LW 		ra, @ReturnAddress4
	JR 		ra
	NOP

ActiveMenu_OpenChimpyCamMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LBU		a0, @ChimpyCam
	SLL 	a0, a0, 2
	LA 		t0, Menu_ChimpyCam_CurrentCameras
	ADD 	t0, t0, a0
	LW 		t0, 0x0 (t0)
	LA 		a0, Menu_ChimpyCam_Array
	SW 		t0, 0x0 (a0)
	LI 		a0, 54
	LBU 	a1, @NewMenu_Screen
	BEQ 	a0, a1, ActiveMenu_OpenChimpyCamMenu_Spawn
	NOP
	SB 		r0, @NewMenu_Position

	ActiveMenu_OpenChimpyCamMenu_Spawn:
		SB 		a0, @NewMenu_Screen
		JAL 	ActiveMenu_SpawnMenu
		NOP
		LW 		ra, @ReturnAddress3
		JR 		ra
		NOP

.align
Menu_ChimpyCam_Current_Free:
	.asciiz "CURRENT: FREE CAM"
Menu_ChimpyCam_Current_Follow:
	.asciiz "CURRENT: FOLLOW CAM"
Menu_ChimpyCam_Set_Free:
	.asciiz "SET TO FREE CAM"
Menu_ChimpyCam_Set_Follow:
	.asciiz "SET TO FOLLOW CAM"

.align
Menu_ChimpyCam_CurrentCameras:
	.word Menu_ChimpyCam_Current_Free
	.word Menu_ChimpyCam_Current_Follow

.align
Menu_ChimpyCam_Array:
	.word 0
	.word Menu_ChimpyCam_Set_Free
	.word Menu_ChimpyCam_Set_Follow
	.word Menu_Return

.align
Menu_ChimpyCam_Functions:
	.word 0
	.word SetChimpyCam
	.word SetChimpyCam
	.word ActiveMenu_PreviousScreen

Menu_ChimpyCam_Struct:
	.word Menu_ChimpyCam_Array // Text Array
	.word Menu_ChimpyCam_Functions // Function Array
	.byte 4 // Array Items
	.byte 34 // Parent Screen
	.byte 3 // Parent Position
