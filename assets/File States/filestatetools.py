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
		fh.seek(fba + byte)
		val = bytereadToInt(fh.read(1))
		andi = 1 << bit
		return (val & andi) != 0

def setFlag(file,byte,bit):
	with open(file,"r+b") as fh:
		fba = getFlagBlockAddress(file)
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

def getGBCount(file, kong, level):
	with open(file,"r+b") as fh:
		fh.seek(0x7FC950 + (kong * 0x5E) + 0x42 + (2 * level))
		return int.from_bytes(fh.read(2), "big")

def addGB(file, kong, level):
	old = getGBCount(file, kong, level)
	with open(file, "r+b") as fh:
		fh.seek(0x7FC950 + (kong * 0x5E) + 0x42 + (2 * level))
		fh.write((old + 1).to_bytes(2, "big"))

# for x in ["helm2"]:
# 	print(x)
# 	print(hex(checkFlag(f"./101/RAM Dump/{x}_fh.bin",0x35,1)))
# 	print(hex(checkFlag(f"./101/RAM Dump/{x}_fh.bin",0x35,3)))
# 	print(getGBCount(f"./101/RAM Dump/{x}_fh.bin", 3, 7))
# 	setFlag(f"./101/RAM Dump/{x}_fh.bin",0x35,1)
# 	setFlag(f"./101/RAM Dump/{x}_fh.bin",0x35,3)
# 	addGB(f"./101/RAM Dump/{x}_fh.bin", 3, 7)
# 	print(hex(checkFlag(f"./101/RAM Dump/{x}_fh.bin",0x35,1)))
# 	print(hex(checkFlag(f"./101/RAM Dump/{x}_fh.bin",0x35,3)))
# 	print(getGBCount(f"./101/RAM Dump/{x}_fh.bin", 3, 7))
# 	print("")

# print(hex(checkFlag("./101/RAM Dump/castle2_fh.bin",0x3F,1)))
# # print(getGBCount("./101/RAM Dump/caves_fh.bin", 3, 7))
# setFlag("./101/RAM Dump/castle2_fh.bin",0x3F,1)
# print(hex(checkFlag("./101/RAM Dump/castle2_fh.bin",0x3F,1)))