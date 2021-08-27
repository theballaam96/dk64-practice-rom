import os

def arrToInt(arr):
	total = 0;
	for x in arr:
		total = (total * 256) + x
	return total

def bytereadToInt(byteread):
	return arrToInt(list(byteread))

def grabFileState(input_file,output_file):
	with open(input_file, "rb") as fh:
		if os.path.exists(output_file):
			os.remove(output_file)
		with open(output_file, "wb") as fg:
			# Grab File Index
			fh.seek(0x7467C8)
			file_index = bytereadToInt(fh.read(1));
			# Grab Eeprom Slot
			found_slot = False;
			for x in range(4):
				fh.seek(0x7EDEA8 + x);
				EEPROMMap = bytereadToInt(fh.read(1))
				if not found_slot:
					if EEPROMMap == file_index:
						eeprom_slot = x;
						found_slot = True;
			if not found_slot:
				eeprom_slot = 0;
			# Get Flag Block Address
			flag_block_address = 0x7ECEA8 + eeprom_slot * 0x1AC
			fh.seek(flag_block_address)
			_perm_flag_block = fh.read(0x140)
			fg.write(_perm_flag_block)
			#print(hex(flag_block_address))
			fh.seek(0x7FC950)
			fg.write(fh.read(0x1E0))
			fh.seek(0x7FCC40)
			fg.write(fh.read(0x10))


grabFileState("./No Levels Early/RAM Dump/japes1.bin","./No Levels Early/State Files/japes1.bin")
grabFileState("./No Levels Early/RAM Dump/aztec.bin","./No Levels Early/State Files/aztec.bin")
grabFileState("./No Levels Early/RAM Dump/factory.bin","./No Levels Early/State Files/factory.bin")
grabFileState("./No Levels Early/RAM Dump/japes2.bin","./No Levels Early/State Files/japes2.bin")
grabFileState("./No Levels Early/RAM Dump/galleon.bin","./No Levels Early/State Files/galleon.bin")
grabFileState("./No Levels Early/RAM Dump/fungi.bin","./No Levels Early/State Files/fungi.bin")
grabFileState("./No Levels Early/RAM Dump/caves.bin","./No Levels Early/State Files/caves.bin")
grabFileState("./No Levels Early/RAM Dump/castle.bin","./No Levels Early/State Files/castle.bin")
grabFileState("./No Levels Early/RAM Dump/helm.bin","./No Levels Early/State Files/helm.bin")
grabFileState("./No Levels Early/RAM Dump/takeoffskip.bin","./No Levels Early/State Files/takeoffskip.bin")
grabFileState("./General/RAM Dump/cleanfile.bin","./General/State Files/cleanfile.bin");