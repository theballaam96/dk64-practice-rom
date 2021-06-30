HandleEnemySpawnPrevent:
	LW 		a0, @ObjectModel2Timer
	LI 		a1, 1
	BNE 	a0, a1, HandleEnemySpawnPrevent_Finish
	NOP
	LBU 	a0, @EnemySpawnOff
	BEQZ 	a0, HandleEnemySpawnPrevent_Finish
	NOP
	LW 		a0, @SpawnerArray
	LHU 	a1, @SpawnerCount

	HandleEnemySpawnPrevent_Loop:
		LBU 	t9, 0x0 (a0)
		LA 		t3, SpawnEnemyTypeAvoid

	HandleEnemySpawnPrevent_TypeLoop:
		LBU 	t6, 0x0 (t3)
		BEQZ 	t6, HandleEnemySpawnPrevent_Toggle
		ADDIU 	t3, t3, 1
		BEQ 	t6, t9, HandleEnemySpawnPrevent_Increment
		NOP
		B 		HandleEnemySpawnPrevent_TypeLoop
		NOP

	HandleEnemySpawnPrevent_Toggle:
		LBU 	t9, 0x42 (a0)
		ADDIU 	t9, t9, 8
		SB 		t9, 0x42 (a0)

	HandleEnemySpawnPrevent_Increment:
		ADDI 	a1, a1, -1
		BEQZ 	a1, HandleEnemySpawnPrevent_Finish
		ADDIU 	a0, a0, 0x48
		B 		HandleEnemySpawnPrevent_Loop
		NOP

	HandleEnemySpawnPrevent_Finish:
		JR 		ra
		NOP