def arrToInt(arr):
	total = 0
	for x in arr:
		total = (total * 256) + x
	return total

def bytereadToInt(byteread):
	return arrToInt(list(byteread))

def getFlagBlockAddress(_f):
	with open(_f, "rb") as fh:
		# Grab File Index
		fh.seek(0x7467C8)
		file_index = bytereadToInt(fh.read(1))
		# Grab Eeprom Slot
		found_slot = False
		for x in range(4):
			fh.seek(0x7EDEA8 + x)
			EEPROMMap = bytereadToInt(fh.read(1))
			if not found_slot:
				if EEPROMMap == file_index:
					eeprom_slot = x
					found_slot = True
		if not found_slot:
			eeprom_slot = 0
		# Get Flag Block Address
		return 0x7ECEA8 + eeprom_slot * 0x1AC

def checkFlag(file,byte,bit):
	with open(file,"rb") as fh:
		fba = getFlagBlockAddress(file)
		print(hex(fba))
		fh.seek(fba + byte)
		val = bytereadToInt(fh.read(1))
		andi = 1 << bit
		return (val & andi) != 0

def setFlag(file,byte,bit):
	with open(file,"r+b") as fh:
		fba = getFlagBlockAddress(file)
		print(hex(fba))
		fh.seek(fba + byte)
		val = bytereadToInt(fh.read(1))
		andi = 1 << bit
		fh.seek(fba + byte)
		fh.write(bytearray([(val | andi)]))
		print("Written " + hex(byte) + ">" + str(bit))

def clearFlag(file,byte,bit):
	with open(file,"r+b") as fh:
		fba = getFlagBlockAddress(file)
		print(hex(fba))
		fh.seek(fba + byte)
		val = bytereadToInt(fh.read(1))
		andi = 1 << bit
		fh.seek(fba + byte)
		fh.write(bytearray([(val & (0xFF - andi))]))
		print("Wiped " + hex(byte) + ">" + str(bit))


print(hex(checkFlag("./Glitchless/RAM Dump/helm.bin",0x4D,1)))
clearFlag("./Glitchless/RAM Dump/helm.bin",0x4D,1)