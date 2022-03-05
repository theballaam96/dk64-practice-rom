from getVersion import getVersion
import os
import shutil
rom_version = getVersion();
names = ["us","pal","jp"]
rom = "rom/dk64-practice-rom-dev-" + names[rom_version] + ".z64"
base = "rom/dk64-practice-rom-dev.z64"
temp = "rom/temp_rom.z64"

if os.path.exists(temp):
	os.remove(temp)
if os.path.exists(rom):
	os.remove(rom)
shutil.copyfile(base, rom)
if os.path.exists(base):
	os.remove(base)