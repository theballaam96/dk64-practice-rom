START:
	displacedBootCode:
		LUI v0, 0x8001
		ADDIU v0, v0, 0xDCC4
		//set story skip to always be on
		ORI t3, r0, 0x0001
		LUI t4, 0x8074
		SB t3, 0x452C (t4) //set story skip to 1
		//write per frame hook
		//
		LUI t3, hi(mainASMFunctionJump)
		LW t3, lo(mainASMFunctionJump) (t3)
		LUI t4, 0x8060
		SW t3, 0xC164 (t4) //store per frame hook
		J 0x80000784
		LUI t6, 0x000D
		//end of boot code
		/////////////////////////////////////////////////////

mainASMFunction:
	JAL	0x805FC2B0
	NOP
	JAL endClose
	NOP
	JAL toggleMenu
	NOP
	JAL moveSlot
	NOP
	JAL colorMenuSky
	NOP
	JAL colorKong
	NOP
	JAL levitate
	NOP
	JAL closeMenuOnTransition
	NOP
	JAL emergencyClose
	NOP
	JAL confirmOption
	NOP
	JAL menuShortcutButtons
	NOP
	J 0x805FC16C
	NOP

mainASMFunctionJump:
	J mainASMFunction //instruction copied and used as a hook
	NOP

mainASMFunctionVanilla:
	JAL	0x805FC2B0
	NOP

callFunc:
	// a0 = function addr
	ADDI 	sp, sp, -4
	SW 		ra, 0x0 (sp)
	JALR 	a0
	NOP
	LW 		ra, 0x0 (sp)
	JR 		ra
	ADDIU 	sp, sp, 4

.align 0x10
END: