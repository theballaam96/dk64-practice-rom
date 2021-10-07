import subprocess
import os
import shutil
import binascii
import gzip
import sys
from compressFile import compressGZipFile

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
			"name": "Dolby Text"
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
			"output_file": "StaticCode_Copy.bin.gz",
			"name": "Static ASM Code"
		},
	]
}

print("Practice ROM Extractor")
print("[0 / 2] - Analyzing ROM")
ROMName = "./../src/rom/dk64.z64"
with open(ROMName, "r+b") as fh:
	print("[1 / 2] - Unzipping files from ROM")
	for x in file_dict["files"]:
		fh.seek(x["start"])
		byte_read = fh.read(x["compressed_size"])
		binName = x["source_file"]

		if os.path.exists(binName):
		    os.remove(binName)

		with open(binName, "wb") as fg:
			dec = gzip.decompress(byte_read)
			if x["source_file"] == "StaticCode.bin":
				fg.write(dec[:0x149160])
			else:
				fg.write(dec)

import modules
newROMName = "dk64-practice-rom.z64"
if os.path.exists(newROMName):
    os.remove(newROMName)
shutil.copyfile(ROMName, newROMName);

with open(newROMName, "r+b") as fh:
	print("[2 / 2] - Writing modified compressed files to ROM")
	for x in file_dict["files"]:
		binName = x["output_file"]
		if os.path.exists(binName):
			with open(binName, "rb") as fg:
				byte_read = fg.read()
				if x["source_file"] != "StaticCode.bin":
					compress = gzip.compress(byte_read, compresslevel=9)
					if (len(compress) > x["compressed_size"]):
						print("ERROR: " + x["name"].upper() + " IS TOO BIG (" + hex(len(compress)) + ")")
				else:
					compress = byte_read
					print(hex(len(compress)))
					if (len(compress) > 0xB15E2):
						print("ERROR: STATIC CODE BIN IS TOO BIG (" + hex(len(compress)) + ")")
				fh.seek(x["start"])
				fh.write(compress)
		else:
			print(x["output_file"] + " does not exist")
	# Thumb
	compressGZipFile("../Source/Non-Code/Nintendo Logo/Thumb.bin", "ThumbCompressed.bin.gz", False)
	with open("ThumbCompressed.bin.gz","rb") as fg:
		thumb_image = fg.read()
		fh.seek(0x1156AC4)
		fh.write(thumb_image)
	if os.path.exists("ThumbCompressed.bin.gz"):
		os.remove("ThumbCompressed.bin.gz")
	# Dolby Logo
	compressGZipFile("../Source/Non-Code/Dolby/DolbyLogo.bin", "DolbyCompressed.bin.gz", False)
	with open("DolbyCompressed.bin.gz","rb") as fg:
		dolby_image = fg.read()
		fh.seek(0x116818C)
		fh.write(dolby_image)
	if os.path.exists("DolbyCompressed.bin.gz"):
		os.remove("DolbyCompressed.bin.gz")
	# Employee Head
	#compressGZipFile("../Source/Non-Code/Employee Head/175D4A8_ZLib.bin", "EmployeeHead.bin.gz", False)
	compressGZipFile("../Source/Non-Code/Employee Head/employee_head.bin", "EmployeeHead.bin.gz", False)
	with open("EmployeeHead.bin.gz","rb") as fg:
		head_image = fg.read()
		fh.seek(0x175D4A8)
		if (len(head_image) <= 4000):
			fh.write(head_image)
	if os.path.exists("EmployeeHead.bin.gz"):
		os.remove("EmployeeHead.bin.gz")

for x in file_dict["files"]:
	if os.path.exists(x["output_file"]):
		os.remove(x["output_file"])
	if os.path.exists(x["source_file"]):
		os.remove(x["source_file"])
	if os.path.exists("StaticCode_Copy.bin"):
		os.remove("StaticCode_Copy.bin")
#import asmloader
# crc patch
with open(newROMName, "r+b") as fh:
    fh.seek(0x3154)
    fh.write(bytearray([0, 0, 0, 0]))
    with open("./../Source/Non-Code/actor_names.bin","rb") as fg:
    	_actor_names = fg.read()
    	fh.seek(0x2020000)
    	fh.write(_actor_names)
    with open ("./../Source/Non-Code/snag_names.bin","rb") as fg:
    	_snag_names = fg.read()
    	fh.seek(0x2021800)
    	fh.write(_snag_names)
    with open ("./../Source/Non-Code/snag_names_capitals.bin","rb") as fg:
    	_snag_names2 = fg.read()
    	fh.seek(0x2021C00)
    	fh.write(_snag_names2)


import filestatewriter

if os.path.exists("dk64-practice-rom.z64"):
	shutil.copyfile("dk64-practice-rom.z64", "./../src/rom/dk64-practice-rom-python.z64");
	os.remove("dk64-practice-rom.z64")
# crcresult = subprocess.check_output(["n64crc", newROMName])
# print("[5 / 5] - CRC Updated")
exit()