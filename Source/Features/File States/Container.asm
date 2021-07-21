ActiveMenu_OpenFileStatesMenu:
	SW 		ra, @ReturnAddress3
	JAL 	ActiveMenu_ClearMenu
	NOP
	LI 		a0, 61
	SB 		a0, @NewMenu_Screen
	SB 		r0, @NewMenu_Position
	JAL 	ActiveMenu_SpawnMenu
	NOP
	LW 		ra, @ReturnAddress3
	JR 		ra
	NOP

.align
FileState_CleanCart:
	.asciiz "SET TO: CLEAN FILE"
FileState_TakeoffSkip:
	.asciiz "SET TO: TAKEOFF SKIP"
FileState_101:
	.asciiz "SET TO: 101%"
FileState_Max:
	.asciiz "SET TO: MAX%"

.align
Menu_FileStates_Array:
	.word FileState_CleanCart
	.word FileState_TakeoffSkip
	.word FileState_101
	.word FileState_Max
	.word Menu_Return

.align
Menu_FileStates_Functions:
	.word SetClean
	.word TakeoffSkip
	.word CompleteFile
	.word MaxFile
	.word ActiveMenu_PreviousScreen

.align
Menu_FileStates_Struct:
	.word Menu_FileStates_Array // Text Array
	.word Menu_FileStates_Functions // Function Array
	.byte 5 // Array Items
	.byte 0 // Parent Screen