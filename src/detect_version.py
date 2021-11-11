import os

with open(".rom","r") as fh:
	rom_file = "./rom/" + fh.readlines()[0].replace("\n","")
	version = 3;
	if os.path.exists(rom_file):
		with open(rom_file,"rb") as rom:
			rom.seek(0x3E)
			rom_letter = rom.read(1)
			version_names = ["US Retail","PAL Retail","JP Retail","Unknown"];
			if rom_letter == b'E':
				version = 0; # US
			elif rom_letter == b'P':
				version = 1; # PAL
			elif rom_letter == b'J':
				version = 2; # JP
			
			print(version_names[version] + " detected!")
	else:
		print("ERROR: ROM File doesn't exist")
	with open(".version","w") as vfile:
		vfile.write(str(version))
	with open("./include/rom_version.h","w") as vhfile:
		vhfile.write("#define ROM_VERSION " + str(version))