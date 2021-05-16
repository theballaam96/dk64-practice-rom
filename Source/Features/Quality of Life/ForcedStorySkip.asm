ForceStorySkip:
	LBU 	a0, @DisableForcedStorySkip
	BNEZ 	a0, ForceStorySkip_Finish
	NOP

	ForceStorySkip_Enable:
		LI 		a1, 1
		SB 		a1, @StorySkip

	ForceStorySkip_Finish:
		JR 		ra
		NOP