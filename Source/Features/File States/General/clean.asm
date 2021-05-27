.align
FileState_Clean_KongBase:
	.space 0x1D6

.align
FileState_Clean_FlagBlock:
	.space 0x13C

.align
FileState_Clean_Data:
	.word FileState_Clean_KongBase
	.word FileState_Clean_FlagBlock