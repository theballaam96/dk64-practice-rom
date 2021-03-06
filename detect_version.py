import os
import shutil
from datetime import date, datetime, timedelta

with open(".rom","r") as fh:
	rom_file = "./rom/" + fh.readlines()[0].replace("\n","")
	if os.path.exists(rom_file):
		if os.path.exists("./rom/temp_rom.z64"):
		    os.remove("./rom/temp_rom.z64")
		shutil.copyfile(rom_file, "./rom/temp_rom.z64")
		version = 3
		with open(rom_file,"rb") as rom:
			rom.seek(0x3E)
			rom_letter = rom.read(1)
			version_names = ["US Retail","PAL Retail","JP Retail","Unknown"]
			if rom_letter == b'E':
				version = 0 # US
			elif rom_letter == b'P':
				version = 1 # PAL
			elif rom_letter == b'J':
				version = 2 # JP
			
			print(version_names[version] + " detected!")
	else:
		print("ERROR: ROM File doesn't exist")
		exit()
	with open(".version","w") as vfile:
		vfile.write(str(version))
	with open("./include/build_date.h","w") as bdfile:
		now = datetime.now();
		today = date.today();
		bdfile.write("#define BUILD_DATE \"BUILD DATE: " + today.strftime("%d-%m-%Y") + " " + now.astimezone(tz=None).strftime("%H:%M" + "\""))
	with open("./include/rom_version.h","w") as vhfile:
		vhfile.write("#define ROM_VERSION " + str(version))