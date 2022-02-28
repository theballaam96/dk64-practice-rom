def getVersion():
	rom_version = 3
	with open(".version","r") as fh:
		rom_version = int(fh.readlines()[0][0])
	return rom_version