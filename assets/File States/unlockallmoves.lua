moves_base_start = 0x7FC950

for i = 1, 5 do
	mainmemory.writebyte(moves_base_start + 0,3);
	mainmemory.writebyte(moves_base_start + 1,3);
	mainmemory.writebyte(moves_base_start + 2,7);
	mainmemory.writebyte(moves_base_start + 3,2);
	mainmemory.writebyte(moves_base_start + 4,15);
	moves_base_start = moves_base_start + 0x5E;
end