moves_base_start = 0x7FC950
inventory_base_start = 0x7FCC40
eeprom_copy_base = 0x7ECEA8
eeprom_file_mapping = 0x7EDEA8
file_index = 0x7467C8

function getFileIndex()
	return mainmemory.readbyte(file_index);
end

function getCurrentEEPROMSlot()
	local fileIndex = getFileIndex();
	for i = 0, 3 do
		local EEPROMMap = mainmemory.readbyte(eeprom_file_mapping + i);
		if EEPROMMap == fileIndex then
			return i;
		end
	end
	return 0; -- Default
end

function getFlagBlockAddress()
	return eeprom_copy_base + getCurrentEEPROMSlot() * 0x1AC;
end

function createFile(time)
	file = io.open("dk64dump_"..time..".bin", "w+");
	file:close(file);
end

function dump()
	file_time = os.time()
	createFile(file_time)
	flags = getFlagBlockAddress();
	file = io.open("dk64dump_"..file_time..".bin", "wb")
	for i = 0, 0x13B do
		file:write(string.char(mainmemory.readbyte(flags + i)))
	end
	for i = 0, 0x1DF do
		file:write(string.char(mainmemory.readbyte(moves_base_start + i)))
	end
	for i = 0, 0xC do
		file:write(string.char(mainmemory.readbyte(inventory_base_start + i)))
	end
	file:close()
	print("Written to dk64dump_"..file_time..".bin")
end

dump();