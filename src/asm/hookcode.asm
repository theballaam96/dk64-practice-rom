START_HOOK:
	updateLag:
		LW 		a0, FrameReal
		LW 		a1, FrameLag
		SUBU 	a1, a0, a1
		SH 		a1, StoredLag
		LUI 	t6, 0x8077
		J 		0x8060067C
		LBU 	t6, 0xAF14 (t6)

	isSaving:
		ADDIU 	t6, r0, 1
		SB 	 	t6, SavePromptIsSaving
		LUI 	t6, 0x8080
		J 		0x8060DED4
		LBU 	t6, 0xC928 (t6)

	logSpriteAddress:
		LUI 	t6, hi(SpriteAddress)
		SW 		v0, lo(SpriteAddress) (t6)
		LUI 	v1, 0x8080
		J 		0x806AB7D8
		ADDIU 	v1, v1, 0xC80F

	setPauseVolume:
		LUI 	a0, hi(PauseMenuMusicSetting)
		LBU 	a1, lo(PauseMenuMusicSetting) (a0)
		BEQZ 	a1, setPauseVolume_Regular
		NOP
		ADDIU 	a0, r0, 1
		BEQ 	a0, a1, setPauseVolume_Quiet
		NOP
		ADDIU 	a0, r0, 2
		BEQ 	a0, a1, setPauseVolume_Silent
		NOP

		setPauseVolume_Regular:
			B 		setPauseVolume_Finish
			LUI 	a1, 0x3F80

		setPauseVolume_Quiet:
			B 		setPauseVolume_Finish
			LUI 	a1, 0x3F00

		setPauseVolume_Silent:
			B 		setPauseVolume_Finish
			LUI 	a1, 0x0

		setPauseVolume_Finish:
			JAL 	playSong
			ADDIU 	a0, r0, 0x22
			J 		0x805FC898
			NOP

.align 0x10
END_HOOK: