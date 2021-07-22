CorruptMe:
	SW 		ra, @ReturnAddress4
	LBU 	t0, @LoadedActorCount
	LI 		t3, 64
	SUBU 	t3, t3, t0 // Amount of actors to spawn
	SB 		t3, @AddedCorruptionActorCount

	CorruptMe_Loop:
		SW 		t3, @VarStorage0
		JAL 	@SpawnActor
		LI 		a0, 265
		LW 		t3, @VarStorage0
		LW 		a0, @CurrentActorPointer
		ADDI 	t3, t3, -1
		BEQZ 	t3, CorruptMe_Finish
		NOP
		B 		CorruptMe_Loop
		NOP

	CorruptMe_Finish:
		LW 		ra, @ReturnAddress4
		JR 		ra
		NOP