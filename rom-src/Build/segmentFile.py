from getVersion import getVersion
from heap_handle import getHeapLocation, getHeapSize
import os
import shutil
rom_version = getVersion();
names = ["us","pal","jp"]
rom = "rom/dk64-practice-rom-dev-" + names[rom_version] + ".z64"
base = "rom/dk64-practice-rom-dev.z64"
temp = "rom/temp_rom.z64"
codebin = "temp-code.bin"

if os.path.exists(temp):
	os.remove(temp)
if os.path.exists(rom):
	os.remove(rom)
with open(base,"r+b") as fh:
	fh.seek(getHeapLocation(0x2000000 - 0x10))
	read = int.from_bytes(fh.read(0x10),"big")
	if read != 0:
		print("WARNING: Heap needs to be shrunk further")
	else:
		with open(codebin,"wb") as fg:
			fh.seek(0x2000000)
			fg.write(fh.read(getHeapSize()))
		with open(codebin,"rb") as fg:
			data = fg.read()
			while data.endswith(bytearray([0])):
				data = data[:-1]
			print("Approx Code Size: " + hex(len(data)))
if os.path.exists(codebin):
	os.remove(codebin)
shutil.copyfile(base, rom)
if os.path.exists(base):
	os.remove(base)