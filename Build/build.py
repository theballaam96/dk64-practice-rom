import subprocess
import os
import shutil
import binascii
import gzip
import sys

file_dict = {
	"files": [
		{
			"start": 0x1118420,
			"compressed_size": 0x37A,
			"source_file": "Menu.bin",
			"output_file": "Menu_Copy.bin",
			"name": "Menu Text"
		},
		{
			"start": 0x1115766,
			"compressed_size": 0x6D,
			"source_file": "Dolby.bin",
			"output_file": "Dolby_Copy.bin",
			"name": "Dolby Tet"
		},
		{
			"start": 0x11172E8,
			"compressed_size": 0x1FF,
			"source_file": "KLumsy.bin",
			"output_file": "KLumsy_Copy.bin",
			"name": "K. Lumsy Text"
		},
		{
			"start": 0x1118BA4,
			"compressed_size": 0x60D,
			"source_file": "Wrinkly.bin",
			"output_file": "Wrinkly_Copy.bin",
			"name": "Wrinkly Hint Text"
		},
		{
			"start": 0x113F0,
			"compressed_size": 0xF064C, # GEDECOMPRESS - B15DC, PYTHON - B17A8, FINALISE ROM - B15E0
			"source_file": "StaticCode.bin",
			"output_file": "StaticCode_Copy.bin",
			"name": "Static ASM Code"
		}
	]
}

# with open("../0113F0_ZLib - Original Copy.bin","rb") as fh:
# 	test = fh.read(0x149160)
# 	test_comp = gzip.compress(test,compresslevel=9)
# 	print(hex(len(test_comp)))

ROMName = "./../dk64.z64"
with open(ROMName, "r+b") as fh:
	for x in file_dict["files"]:
		fh.seek(x["start"])
		byte_read = fh.read(x["compressed_size"])
		#print(gzip.decompress(byte_read))
		binName = x["source_file"]

		if os.path.exists(binName):
		    os.remove(binName)

		with open(binName, "wb") as fg:
			dec = gzip.decompress(byte_read)
			fg.write(dec)
			print("Unzipped " + x["name"])

	# fh.seek(0x1118420)
	# menu_bytes = fh.read(0x37A)
	# print(gzip.decompress(menu_bytes))
	#print(menu_bytes)
	#print(zlib.decompress(menu_bytes))

import modules
newROMName = "dk64-practice-rom.z64"
if os.path.exists(newROMName):
    os.remove(newROMName)
shutil.copyfile(ROMName, newROMName);

with open(newROMName, "r+b") as fh:
	for x in file_dict["files"]:
		binName = x["output_file"]
		if os.path.exists(binName):
			with open(binName, "rb") as fg:
				print("Reading " + x["output_file"])
				byte_read = fg.read()
				compress = gzip.compress(byte_read, compresslevel=9)
				fh.seek(x["start"])
				fh.write(compress)
		else:
			print(x["output_file"] + " does not exist")

for x in file_dict["files"]:
	if os.path.exists(x["output_file"]):
		os.remove(x["output_file"])
	if os.path.exists(x["source_file"]):
		os.remove(x["source_file"])

# crc patch
with open(newROMName, "r+b") as fh:
    fh.seek(0x3154)
    fh.write(bytearray([0, 0, 0, 0]))
crcresult = subprocess.check_output(["n64crc", newROMName])
print(crcresult)
exit()