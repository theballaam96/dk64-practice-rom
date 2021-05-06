LoadingZone_Recording:
	LBU 	a0, @LZLooper_IsRecording
	BEQZ 	a0, LoadingZone_Recording_Finish
	NOP
	LBU 	a0, @TransitionSpeed
	ANDI 	a0, a0, 0x80
	BNEZ 	a0, LoadingZone_Recording_Finish // Non-negative
	NOP
	LW 		a0, @TransitionSpeed
	BEQZ 	a0, LoadingZone_Recording_Finish
	NOP
	LW 		a0, @CurrentMap
	SB 		a0, @LZLooper_CurrentMap
	LW 		a0, @DestMap
	SB 		a0, @LZLooper_DestinationMap
	LW 		a0, @DestExit
	SB 		a0, @LZLooper_DestinationExit
	LI 		a0, 1
	SB 		a0, @LZLooper_HasSavedData
	SB 		a0, @LZLooper_On
	LBU  	a0, @LZLooper_Mode
	ADDIU 	a0, a0, 2
	SB 		a0, @MenuSavestateAction
	LA 		a0, Menu_LZLooperSettings_Array
	LA 		a1, Menu_LZLooperSettings_TurnOffLooper
	SW 		a1, 0x0 (a0)

	LoadingZone_Recording_Finish:
		JR 		ra
		NOP

LoadingZone_HandleLooper:
	LBU 	a1, @LZLooper_On
	BEQZ 	a1, LoadingZone_HandleLooper_TransitionIndicator
	NOP
	LBU 	a1, @LZLooper_TransitionIndicator
	BEQZ 	a1, LoadingZone_HandleLooper_TransitionIndicator
	NOP
	LW 		a0, @CurrentMap
	LBU 	a1, @LZLooper_CurrentMap
	BNE 	a0, a1, LoadingZone_HandleLooper_TransitionIndicator
	NOP
	LW 		a0, @DestMap
	LBU 	a1, @LZLooper_DestinationMap
	BNE 	a0, a1, LoadingZone_HandleLooper_TransitionIndicator
	NOP
	LW 		a0, @DestExit
	LBU 	a1, @LZLooper_DestinationExit
	BNE 	a0, a1, LoadingZone_HandleLooper_TransitionIndicator
	NOP
	LBU  	a0, @LZLooper_Mode
	ADDIU 	a0, a0, 2
	SB 		a0, @MenuSavestateAction

	LoadingZone_HandleLooper_TransitionIndicator:
		LW 		a0, @TransitionSpeed
		BEQZ 	a0, LoadingZone_HandleLooper_IsZero
		NOP
		LBU 	a0, @TransitionSpeed
		ANDI 	a0, a0, 0x80
		BNEZ 	a0, LoadingZone_HandleLooper_IsZero // Non-negative
		NOP
		B 		LoadingZone_HandleLooper_Entering
		NOP

	LoadingZone_HandleLooper_IsZero:
		SB 		r0, @LZLooper_TransitionIndicator
		B 		LoadingZone_HandleLooper_Finish
		NOP

	LoadingZone_HandleLooper_Entering:
		LI 		a1, 1
		SB 		a1, @LZLooper_TransitionIndicator

	LoadingZone_HandleLooper_Finish:
		JR 		ra
		NOP