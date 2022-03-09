import subprocess
import os
import shutil
import gzip
import zlib

from getVersion import getVersion
rom_version = getVersion();

# Patcher functions for the extracted files
import patch_text
from actor_bin_builder import *
from snag_bins_builder import *
from font_image_builder import build_font
from filestatewriter import writeFileStatesToDict, wipeStateFiles
import check_unused

ROMName = "rom/temp_rom.z64"
newROMName = "rom/dk64-practice-rom.z64"

if os.path.exists(newROMName):
    os.remove(newROMName)
shutil.copyfile(ROMName, newROMName)

base_file_dict = [
	{
		"name": "Menu Text",
		"pointer_table_index": 12,
		"file_index": 37,
		"source_file": "menu_text.bin",
		"do_not_delete_source": True,
		"versions":[0],
	},
	{
		"name": "Dolby Text",
		"pointer_table_index": 12,
		"file_index": 13,
		"source_file": "dolby_text.bin",
		"do_not_delete_source": True,
		"versions":[0,2],
	},
	{
		"name": "K. Lumsy Text",
		"pointer_table_index": 12,
		"file_index": 27,
		"source_file": "klumsy_text.bin",
		"do_not_delete_source": True,
		"versions":[0],
	},
	{
		"name": "Wrinkly Hint Text",
		"pointer_table_index": 12,
		"file_index": 41,
		"source_file": "wrinkly_text.bin",
		"do_not_delete_source": True,
		"versions":[0],
	},
	{
		"name": "Thumb Image (US)",
		"pointer_table_index": 14,
		"file_index": 94,
		"source_file": "assets/Non-Code/Nintendo Logo/Nintendo.png",
		"texture_format": "rgba5551",
		"versions":[0],
	},
	{
		"name": "Thumb Image (JP)",
		"pointer_table_index": 14,
		"file_index": 240,
		"source_file": "assets/Non-Code/Nintendo Logo/NintendoJP.png",
		"texture_format": "rgba5551",
		"versions":[2],
	},
	{
		"name": "Dolby Logo",
		"pointer_table_index": 14,
		"file_index": [176,176,322][rom_version],
		"source_file": "assets/Non-Code/Dolby/DolbyThin.png",
		"texture_format": "i4",
		"versions":[0,2],
	},
	{
		"name": "Employee Head Image",
		"pointer_table_index": 25,
		"file_index": [5003,5003,4927][rom_version],
		"source_file": "assets/Non-Code/Employee Head/employee_head.png",
		"texture_format": "i8",
		"versions":[0,2],
	},
	{
		"name": "Fairy Viewer Square",
		"pointer_table_index": 14,
		"file_index": [107,107,194][rom_version],
		"source_file": "assets/Non-Code/Fairy Viewer/fairy_square.png",
		"texture_format": "rgba5551",
		"do_not_extract": True,
		"versions":[0,2],
	},
	{
		"name": "Fairy Viewer Dot",
		"pointer_table_index": 14,
		"file_index": [108,108,195][rom_version],
		"source_file": "assets/Non-Code/Fairy Viewer/fairy_dot.png",
		"texture_format": "rgba5551",
		"do_not_extract": True,
		"versions":[0,2],
	},
	{
		"name": "GitHub Logo",
		"pointer_table_index": 14,
		"file_index": 109,
		"source_file": "assets/Non-Code/Info/GitHub.png",
		"texture_format": "rgba5551",
		"do_not_extract": True,
		"versions": [0],
	},
	{
		"name": "Avatar (Ballaam)",
		"pointer_table_index": 14,
		"file_index": 110,
		"source_file": "assets/Non-Code/Info/Icon_Ballaam.png",
		"texture_format": "rgba5551",
		"do_not_extract": True,
		"versions": [0],
	},
	{
		"name": "Avatar (Rain)",
		"pointer_table_index": 14,
		"file_index": 111,
		"source_file": "assets/Non-Code/Info/Icon_Rain.png",
		"texture_format": "rgba5551",
		"do_not_extract": True,
		"versions": [0],
	},
	{
		"name": "Avatar (Iso)",
		"pointer_table_index": 14,
		"file_index": 112,
		"source_file": "assets/Non-Code/Info/Icon_Iso.png",
		"texture_format": "rgba5551",
		"do_not_extract": True,
		"versions": [0],
	},
	{
		"name": "Arcade Font (US)",
		"pointer_table_index": 14,
		"file_index": 19,
		"source_file": "assets/Non-Code/Font/arcade_font_modified_us.png",
		"texture_format": "i4",
		"font_key": "arcade_font_us",
		"versions":[0],
	},
	{
		"name": "Arcade Font (JP)",
		"pointer_table_index": 14,
		"file_index": 165,
		"source_file": "assets/Non-Code/Font/arcade_font_modified_jp.png",
		"texture_format": "i4",
		"font_key": "arcade_font_jp",
		"versions":[2],
	},
	{
		"name": "Jetpac Font",
		"pointer_table_index": 14,
		"file_index": [31,31,177][rom_version],
		"source_file": "assets/Non-Code/Font/jetpac_font_modified.png",
		"texture_format": "i4",
		"font_key": "jetpac_font",
		"versions":[0,2],
	},
	{
		"name": "Actor Names",
		"start": 0x2040000,
		"source_file": "assets/Non-Code/actor_names.bin",
		"do_not_extract": True,
		"do_not_compress": True,
		"versions":[0,1,2],
	},
	{
		"name": "Snag Names",
		"start": 0x2041800,
		"source_file": "assets/Non-Code/snag_names.bin",
		"do_not_extract": True,
		"do_not_compress": True,
		"versions":[0,1,2],
	},
	{
		"name": "Snag Names (Capitals)",
		"start": 0x2041C00,
		"source_file": "assets/Non-Code/snag_names_capitals.bin",
		"do_not_extract": True,
		"do_not_compress": True,
		"versions":[0,1,2],
	},
]

progress_index = 0;
def printProgress(sub):
	global progress_index
	progress_index += 1;
	print(f"[{progress_index} / 8] - {sub}")

print("DK64 Extractor")
printProgress("Importing File States")

base_file_dict = writeFileStatesToDict(base_file_dict)

# Infrastructure for recomputing DK64 global pointer tables
from map_names import maps
from recompute_pointer_table import pointer_tables, dumpPointerTableDetails, replaceROMFile, writeModifiedPointerTablesToROM, parsePointerTables, getFileInfo, make_safe_filename
from recompute_overlays import isROMAddressOverlay, readOverlayOriginalData, replaceOverlayData, writeModifiedOverlaysToROM

file_dict = []
for x in base_file_dict:
	allowed = True;
	if "versions" in x:
		allowed = False;
		if rom_version in x["versions"]:
			allowed = True;
	if allowed:
		file_dict.append(x)

map_replacements = [
	# {
	# 	"name": "Test Map",
	# 	"map_index": 0,
	# 	"map_folder": "maps/path_test/"
	# },
]



with open(ROMName, "rb") as fh:
	printProgress("Parsing pointer tables")
	parsePointerTables(fh)
	readOverlayOriginalData(fh)

	for x in map_replacements:
		print(" - Processing map replacement " + x["name"])
		if os.path.exists(x["map_folder"]):
			found_geometry = False
			found_floors = False
			found_walls = False
			should_compress_walls = True
			should_compress_floors = True
			for y in pointer_tables:
				if not "encoded_filename" in y:
					continue

				# Convert decoded_filename to encoded_filename using the encoder function
				# Eg. exits.json to exits.bin
				if "encoder" in y and callable(y["encoder"]):
					if "decoded_filename" in y and os.path.exists(x["map_folder"] + y["decoded_filename"]):
						y["encoder"](x["map_folder"] + y["decoded_filename"], x["map_folder"] + y["encoded_filename"])
				
				if os.path.exists(x["map_folder"] + y["encoded_filename"]):
					if y["index"] == 1:
						with open(x["map_folder"] + y["encoded_filename"], "rb") as fg:
							byte_read = fg.read(10)
							should_compress_walls = (byte_read[9] & 0x1) != 0
							should_compress_floors = (byte_read[9] & 0x2) != 0
						found_geometry = True
					elif y["index"] == 2:
						found_walls = True
					elif y["index"] == 3:
						found_floors = True

			# Check that all walls|floors|geometry files exist on disk, or that none of them do
			walls_floors_geometry_valid = (found_geometry == found_walls) and (found_geometry == found_floors)

			if not walls_floors_geometry_valid:
				print("  - WARNING: In map replacement: " + x["name"])
				print("    - Need all 3 files present to replace walls, floors, and geometry.")
				print("    - Only found 1 or 2 of them out of 3. Make sure all 3 exist on disk.")
				print("    - Will skip replacing walls, floors, and geometry to prevent crashes.")

			for y in pointer_tables:
				if not "encoded_filename" in y:
					continue

				if os.path.exists(x["map_folder"] + y["encoded_filename"]):
					# Special case to prevent crashes with custom level geometry, walls, and floors
					# Some of the files are compressed in ROM, some are not
					if y["index"] in [1, 2, 3] and not walls_floors_geometry_valid:
						continue

					do_not_compress = "do_not_compress" in y and y["do_not_compress"]
					if y["index"] == 2:
						do_not_compress = not should_compress_walls
					elif y["index"] == 3:
						do_not_compress = not should_compress_floors

					print("  - Found " + x["map_folder"] + y["encoded_filename"])
					file_dict.append({
						"name": x["name"] + y["name"],
						"pointer_table_index": y["index"],
						"file_index": x["map_index"],
						"source_file": x["map_folder"] + y["encoded_filename"],
						"do_not_extract": True,
						"do_not_compress": do_not_compress,
						"use_external_gzip": "use_external_gzip" in y and y["use_external_gzip"],
					})

	printProgress("Extracting files from ROM")
	for x in file_dict:
		# N64Tex conversions do not need to be extracted to disk from ROM
		if "texture_format" in x:
			x["do_not_extract"] = True
			if "font_key" in x:
				x["output_file"] = x["source_file"].replace(".png", ".bin")
			else:
				x["output_file"] = x["source_file"].replace(".png", "." + x["texture_format"])

		if not "output_file" in x:
			x["output_file"] = x["source_file"]

		# gzip.exe appends .gz to the filename, we'll do the same
		if "use_external_gzip" in x and x["use_external_gzip"]:
			x["output_file"] = x["output_file"] + ".gz"

		# If we're not extracting the file to disk, we're using a custom .bin that shoudn't be deleted
		if "do_not_extract" in x and x["do_not_extract"]:
			x["do_not_delete_source"] = True

		if "font_key" in x:
			byte_read = bytes()
			if "pointer_table_index" in x and "file_index" in x:
				file_info = getFileInfo(x["pointer_table_index"], x["file_index"])
				if file_info:
					x["start"] = file_info["new_absolute_address"]
					x["compressed_size"] = len(file_info["data"])

			fh.seek(x["start"])
			byte_read = fh.read(x["compressed_size"])
			dec = zlib.decompress(byte_read, 15 + 32)
			bin_file = x["source_file"].split(".")[0]+".bin";
			with open(bin_file,"wb") as fg:
				fg.write(dec)
			build_font(bin_file,x["texture_format"],x["font_key"])

		# Extract the compressed file from ROM
		if not ("do_not_extract" in x and x["do_not_extract"]):
			byte_read = bytes()
			if "pointer_table_index" in x and "file_index" in x:
				file_info = getFileInfo(x["pointer_table_index"], x["file_index"])
				if file_info:
					x["start"] = file_info["new_absolute_address"]
					x["compressed_size"] = len(file_info["data"])

			fh.seek(x["start"])
			byte_read = fh.read(x["compressed_size"])

			if not ("do_not_delete_source" in x and x["do_not_delete_source"]):
				if os.path.exists(x["source_file"]):
					os.remove(x["source_file"])

				with open(x["source_file"], "wb") as fg:
					dec = zlib.decompress(byte_read, 15 + 32)
					fg.write(dec)

printProgress("Patching Extracted Files")
for x in file_dict:
	if "patcher" in x and callable(x["patcher"]):
		print(" - Running patcher for " + x["source_file"])
		x["patcher"](x["source_file"])

with open(newROMName, "r+b") as fh:
	printProgress("Writing patched files to ROM")
	for x in file_dict:
		if "texture_format" in x and not "font_key" in x:
			if x["texture_format"] in ["rgba5551", "i4", "ia4", "i8", "ia8"]:
				result = subprocess.check_output(["./build/n64tex.exe", x["texture_format"], x["source_file"]])
			else:
				print(" - ERROR: Unsupported texture format " + x["texture_format"])

		if "use_external_gzip" in x and x["use_external_gzip"]:
			if os.path.exists(x["source_file"]):
				result = subprocess.check_output(["./build/gzip.exe", "-f", "-n", "-k", "-q", "-9", x["output_file"].replace(".gz", "")])
				if os.path.exists(x["output_file"]):
					with open(x["output_file"], "r+b") as outputFile:
						# Chop off gzip footer
						outputFile.truncate(len(outputFile.read()) - 8)

		if os.path.exists(x["output_file"]):
			byte_read = bytes()
			uncompressed_size = 0
			with open(x["output_file"], "rb") as fg:
				byte_read = fg.read()
				uncompressed_size = len(byte_read)

			if "do_not_compress" in x and x["do_not_compress"]:
				compress = bytearray(byte_read)
			elif "use_external_gzip" in x and x["use_external_gzip"]:
				compress = bytearray(byte_read)
			elif "use_zlib" in x and x["use_zlib"]:
				compressor = zlib.compressobj(zlib.Z_BEST_COMPRESSION, zlib.DEFLATED, 25)
				compress = compressor.compress(byte_read)
				compress += compressor.flush()
				compress = bytearray(compress)
				# Zero out timestamp in gzip header to make builds deterministic
				compress[4] = 0
				compress[5] = 0
				compress[6] = 0
				compress[7] = 0
			else:
				compress = bytearray(gzip.compress(byte_read, compresslevel=9))
				# Zero out timestamp in gzip header to make builds deterministic
				compress[4] = 0
				compress[5] = 0
				compress[6] = 0
				compress[7] = 0

			print(" - Writing " + x["output_file"] + " (" + hex(len(compress)) + ") to ROM")
			if "pointer_table_index" in x and "file_index" in x:
				# More complicated write, update the pointer tables to point to the new data
				replaceROMFile(x["pointer_table_index"], x["file_index"], compress, uncompressed_size)
			elif "start" in x:
				if isROMAddressOverlay(x["start"]):
					replaceOverlayData(x["start"], compress)
				else:
					# Simply write the bytes at the absolute address in ROM specified by x["start"]
					fh.seek(x["start"])
					fh.write(compress)
			else:
				print("  - WARNING: Can't find address information in file_dict entry to write " + x["output_file"] + " (" + hex(len(compress)) + ") to ROM")
		else:
			print(x["output_file"] + " does not exist")

		# Cleanup temporary files
		if not ("do_not_delete" in x and x["do_not_delete"]):
			if not ("do_not_delete_output" in x and x["do_not_delete_output"]):
				if os.path.exists(x["output_file"]) and x["output_file"] != x["source_file"]:
					os.remove(x["output_file"])
			if not ("do_not_delete_source" in x and x["do_not_delete_source"]):
				if os.path.exists(x["source_file"]):
					os.remove(x["source_file"])

	printProgress("Writing recomputed pointer tables to ROM")
	writeModifiedPointerTablesToROM(fh)
	if rom_version == 0:
		writeModifiedOverlaysToROM(fh) # US Only for now

	printProgress("Dumping details of all pointer tables to rom/build.log")
	dumpPointerTableDetails("rom/build.log", fh)

# import font_builder
# with open(newROMName, "r+b") as fh:
#     with open("assets/Non-Code/Font/font_boundaries.bin","rb") as fg:
#     	_font_boundaries = fg.read()
#     	fh.seek(0x2021600)
#     	fh.write(_font_boundaries)
# if os.path.exists("assets/Non-Code/Font/font_boundaries.bin"):
# 	os.remove("assets/Non-Code/Font/font_boundaries.bin")

bins = [
	"assets/Non-Code/actor_names",
	"assets/Non-Code/snag_names",
	"assets/Non-Code/snag_names_capitals",
	"dolby_text",
	"wrinkly_text",
	"menu_text",
	"klumsy_text",
]
for x in bins:
	pth = x + ".bin"
	if os.path.exists(pth):
		os.remove(pth)
	else:
		print(x + "doesn't exist")
wipeStateFiles();

printProgress("Generating BizHawk RAM watch")
import generate_watch_file

exit()