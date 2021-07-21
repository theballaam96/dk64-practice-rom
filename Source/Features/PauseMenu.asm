SetPauseMenuVolume:
	// Available Registers = a0, a1
	LBU  	a1, @PauseMenuMusicSetting
	BEQZ 	a1, SetPauseMenuVolume_Regular
	NOP
	LI 		a0, 1
	BEQ 	a0, a1, SetPauseMenuVolume_Quiet
	NOP
	LI 		a0, 2
	BEQ 	a0, a1, SetPauseMenuVolume_Silent
	NOP

	SetPauseMenuVolume_Regular:
		B 		SetPauseMenuVolume_Finish
		LUI 	a1, 0x3F80

	SetPauseMenuVolume_Quiet:
		B 		SetPauseMenuVolume_Finish
		LUI 	a1, 0x3F00

	SetPauseMenuVolume_Silent:
		LUI 	a1, 0x0

	SetPauseMenuVolume_Finish:
		JAL 	@PlaySong
		LI 		a0, 0x22
		J 		0x805FC898
		NOP