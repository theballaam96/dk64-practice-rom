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
			"file_type": "text",
			"source_file": "Menu.bin",
			"output_file": "Menu_Copy.bin",
			"name": "Menu Text"
		},
		{
			"start": 0x1115766,
			"compressed_size": 0x6D,
			"file_type": "text",
			"source_file": "Dolby.bin",
			"output_file": "Dolby_Copy.bin",
			"name": "Dolby Text"
		},
		{
			"start": 0x11172E8,
			"compressed_size": 0x1FF,
			"file_type": "text",
			"source_file": "KLumsy.bin",
			"output_file": "KLumsy_Copy.bin",
			"name": "K. Lumsy Text"
		},
		{
			"start": 0x1118BA4,
			"compressed_size": 0x60D,
			"file_type": "text",
			"source_file": "Wrinkly.bin",
			"output_file": "Wrinkly_Copy.bin",
			"name": "Wrinkly Hint Text"
		},
		{
			"start": 0x113F0,
			"compressed_size": 0xB15E4, # GEDECOMPRESS - B15DC, PYTHON - B17A8, FINALISE ROM - B15E0 | 0xF064C
			"forced_compressed_size": 0xB15E2,
			"file_type": "code",
			"source_file": "StaticCode.bin",
			"output_file": "StaticCode_Copy.bin",
			"name": "Static ASM Code",
			"use_external_gzip": True,
		},
		{
			"start": 0x1156AC4,
			"compressed_size": 0xA0C,
			"file_type": "image",
			#"source_file": "../assets/Non-Code/Nintendo Logo/Thumb.bin",
			"source_file": "../assets/Non-Code/Nintendo Logo/Nintendo.png",
			"output_file": "ThumbCompressed.bin.gz",
			"name": "Thumb Image",
			"convert": True,
			"texture_format": "rgba5551",
		},
		{
			"start": 0x116818C,
			"compressed_size": 0x880,
			"file_type": "image",
			#"source_file": "../assets/Non-Code/Dolby/DolbyLogo.bin",
			"source_file": "../assets/Non-Code/Dolby/DolbyThin.png",
			"output_file": "DolbyCompressed.bin.gz",
			"name": "Dolby Image",
			"convert": True,
			"texture_format": "i4",
		},
		{
			"start": 0x175D4A8,
			"compressed_size": 0xFA0,
			"file_type": "image",
			"source_file": "../assets/Non-Code/Employee Head/employee_head.bin",
			"output_file": "EmployeeHead.bin",
			"name": "Employee Head Image",
			"convert": False,
			"texture_format": "i8",
			"use_external_gzip": True,
		}
	]
}

print("Practice ROM Extractor")
print("[0 / 2] - Analyzing ROM")
ROMName = "./../src/rom/dk64.z64"
with open(ROMName, "r+b") as fh:
	print("[1 / 2] - Unzipping files from ROM")
	for x in file_dict["files"]:
		if "use_external_gzip" in x and x["use_external_gzip"]:
			if x["output_file"][-3:] != ".gz":
				x["output_file"] += ".gz"
		if x["file_type"] != "image":
			fh.seek(x["start"])
			byte_read = fh.read(x["compressed_size"])
			binName = x["source_file"]

			if os.path.exists(binName):
			    os.remove(binName)

			with open(binName, "wb") as fg:
				dec = gzip.decompress(byte_read)
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
		if x["file_type"] != "image":
			if "use_external_gzip" in x and x["use_external_gzip"]:
				compressGZipFile(x["source_file"],x["output_file"],False)
			if os.path.exists(binName):
				with open(binName, "rb") as fg:
					byte_read = fg.read()
					if "use_external_gzip" in x and x["use_external_gzip"]:
						compress = byte_read
					else:
						compress = gzip.compress(byte_read, compresslevel=9)
					sizeProp = "compressed_size"
					if "forced_compressed_size" in x:
						sizeProp = "forced_compressed_size"
					if len(compress) > x[sizeProp]:
						print("ERROR: " + x["name"].upper() + " IS TOO BIG (" + hex(len(compress)) + ")")
					fh.seek(x["start"])
					fh.write(compress)
			else:
				print(x["output_file"] + " does not exist")
		else:
			will_convert = False;
			if "convert" in x:
				if x["convert"]:
					will_convert = True;
			if will_convert:
				converted = False;
				if "texture_format" in x:
					if x["texture_format"] == "rgba5551":
						result = subprocess.check_output(["./n64tex.exe", x["texture_format"], x["source_file"]])
						converted = True;
					elif x["texture_format"] == "i4":
						result = subprocess.check_output(["./n64tex.exe", x["texture_format"], x["source_file"]])
						converted = True;
					else:
						print(" - ERROR: Unsupported texture format " + x["texture_format"])
				if converted:
					print(x["name"])
					file_name = ".".join(x["source_file"].split(".")[0:-1]) + "." + x["texture_format"]
					if os.path.exists(file_name):
						compressGZipFile(file_name,x["output_file"],False);
						with open(x["output_file"],"rb") as fg:
							img = fg.read()
							fh.seek(x["start"])
							print(x["name"] + ": " + str(len(img)) + " bytes. Lim: " + str(x["compressed_size"]) + " bytes")
							if len(img) > x["compressed_size"]:
								print("ERROR: " + x["name"].upper() + " IS TOO BIG (" + hex(len(img)) + ")")
							else:
								fh.write(img)
					if os.path.exists(file_name):
						os.remove(file_name)
					if os.path.exists(x["output_file"]):
						os.remove(x["output_file"])
			else:
				if os.path.exists(x["source_file"]):
					compressGZipFile(x["source_file"],x["output_file"],False)
					with open(x["output_file"],"rb") as fg:
						img = fg.read()
						fh.seek(x["start"])
						print(x["name"] + ": " + str(len(img)) + " bytes. Lim: " + str(x["compressed_size"]) + " bytes")
						if len(img) > x["compressed_size"]:
							print("ERROR: " + x["name"].upper() + " IS TOO BIG (" + hex(len(img)) + ")")
						else:
							fh.write(img)
					if os.path.exists(x["output_file"]):
						os.remove(x["output_file"])
				else:
					print(x["source_file"] + " does not exist")

for x in file_dict["files"]:
	if x["file_type"] != "image":
		if os.path.exists(x["output_file"]):
			os.remove(x["output_file"])
		if os.path.exists(x["source_file"]):
			os.remove(x["source_file"])
if os.path.exists("StaticCode_Copy.bin"):
	os.remove("StaticCode_Copy.bin")
if os.path.exists("StaticCode.bin.gz"):
	os.remove("StaticCode.bin.gz")
		
# crc patch
with open(newROMName, "r+b") as fh:
    fh.seek(0x3154)
    fh.write(bytearray([0, 0, 0, 0]))
    with open("./../assets/Non-Code/actor_names.bin","rb") as fg:
    	_actor_names = fg.read()
    	fh.seek(0x2020000)
    	fh.write(_actor_names)
    with open ("./../assets/Non-Code/snag_names.bin","rb") as fg:
    	_snag_names = fg.read()
    	fh.seek(0x2021800)
    	fh.write(_snag_names)
    with open ("./../assets/Non-Code/snag_names_capitals.bin","rb") as fg:
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