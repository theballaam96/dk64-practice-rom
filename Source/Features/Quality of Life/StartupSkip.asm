StartupSkip:
	LBU 	a0, @DisableStartupSkip
	BNEZ 	a0, DontSkipStartup
	NOP

	SkipStartup:
		LBU 	t3, @Gamemode
		LI 		a1, 1 		// Nin/RW Skip
		LI 		a2, 0x50 	// Dest Map
		BEQ 	a1, t3, SetSkip
		LI 		a3, 5 		// Dest GM
		B 		SetSkip
		LI 		a1, 0 		// Nin/RW Skip

	DontSkipStartup:
		LI 		a1, 0
		LI 		a2, 0x4C
		LI 		a3, 2

	SetSkip:
		SB 		a1, @BetaNinRWSkip
		SB 		a2, 0x807132BF // Set Destination Map after N/R Logos to Main Menu
		SB 		a3, 0x807132CB // Set Gamemode after N/R Logos to Main Menu Mode
		JR 		ra
		NOP