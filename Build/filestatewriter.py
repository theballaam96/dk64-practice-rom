import os
import struct
import math
from heap_handle import getHeapLocation, getHeapSize

file_size = 0x340 # 0x1 at end, rounded up
ROM_start = getHeapLocation(0x2002000)
ROM_name = "rom/dk64-practice-rom.z64"
file_dir_start = "assets/File States/"
state_files = [
	{
		"folder": "No Levels Early",
		"files": [
			"japes1.bin",
			"aztec.bin",
			"factory.bin",
			"japes2.bin",
			"galleon.bin",
			"fungi.bin",
			"caves.bin",
			"castle.bin",
			"helm.bin",
			"takeoffskip.bin",
			"aztec40bp.bin",
			"factory40bp.bin",
			"japes240bp.bin",
			"galleon40bp.bin",
			"fungi40bp.bin",
			"caves40bp.bin",
			"castle40bp.bin",
			"aztec240bp.bin",
			"helm40bp.bin",
		]
	},
	{
		"folder": "General",
		"files": [
			"cleanfile.bin",
		],
	},
	{
		"folder": "101",
		"files": [
			"caves1_organic.bin",
			"japes1_organic.bin",
			"aztec1_organic.bin",
			"factory_organic.bin",
			"galleon_organic.bin",
			"helm_organic.bin",
			"castle_organic.bin",
			"aztec2_organic.bin",
			"aztec2_organic_alt.bin",
			"caves2_organic.bin",
			"japes2_organic.bin",
			"fungi.bin",
			"aztec1_jfm.bin",
			"castle1_jfm.bin",
			"japes_jfm.bin",
			"factory_jfm.bin",
			"galleon_jfm.bin",
			"helm_jfm.bin",
			"castle2_jfm.bin",
			"aztec2_jfm.bin",
			"caves_jfm.bin",
		]
	},
	{
		"folder": "Glitchless",
		"files": [
			"japes1.bin",
			"aztec.bin",
			"factory.bin",
			"japes2.bin",
			"galleon.bin",
			"fungi.bin",
			"caves.bin",
			"castle.bin",
			"helm.bin",
		]
	}
]

def arrToInt(arr):
	total = 0
	for x in arr:
		total = (total * 256) + x
	return total

def bytereadToInt(byteread):
	return arrToInt(list(byteread))

def floatbytereadToSignedShort(read):
	if bytereadToInt(read) == 0:
		flt = 0
	else:
		flt = struct.unpack('!f', bytes.fromhex(hex(bytereadToInt(read))[2:]))[0]
	_flt = math.floor(flt)
	if _flt < 0:
		hx = (("0000" + hex(0x10000 + _flt))[2:])[-4:]
	else:
		hx = ("0000" + hex(_flt)[2:])[-4:]
	arr = [int("0x" + hx[:2],16),int("0x" + hx[2:],16)]
	return arr

def grabFileState(input_file,output_file):
	with open(input_file, "rb") as fh:
		if os.path.exists(output_file):
			os.remove(output_file)
		with open(output_file, "wb") as fg:
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
			flag_block_address = 0x7ECEA8 + eeprom_slot * 0x1AC
			fh.seek(flag_block_address)
			_perm_flag_block = fh.read(0x140)
			fg.write(_perm_flag_block)
			#print(hex(flag_block_address))
			fh.seek(0x7FC950)
			fg.write(fh.read(0x1D6))
			fh.seek(0x7FBB4C)
			player = bytereadToInt(fh.read(4)) - 0x80000000
			fh.seek(player + 0x7C)
			fg.write(bytearray(floatbytereadToSignedShort(fh.read(4))))
			fh.seek(player + 0x80)
			fg.write(bytearray(floatbytereadToSignedShort(fh.read(4))))
			fh.seek(player + 0x84)
			fg.write(bytearray(floatbytereadToSignedShort(fh.read(4))))
			fg.write(bytearray([0,0,0,0]))
			fh.seek(0x7FCC40)
			fg.write(fh.read(0xD))
			fh.seek(0x76A0AB)
			fg.write(fh.read(0x1))
			fh.seek(0x74E77C)
			fg.write(fh.read(0x1))
			fg.write(bytearray([0]))
			fh.seek(0x7FDD90)
			fg.write(fh.read(0x10))
			
def wipeStateFiles():
	for x in state_files:
		state_dir = file_dir_start + x["folder"] + "/State Files/"
		for y in x["files"]:
			if os.path.exists(state_dir + y):
				os.remove(state_dir + y)

file_state_count = 0;
			
def writeFileStatesToDict(original_dict):
	global file_state_count
	state_index = 0
	for x in state_files:
		state_dir = file_dir_start + x["folder"] + "/State Files/"
		dump_dir = file_dir_start + x["folder"] + "/RAM Dump/"
		for y in x["files"]:
			#print(file_dir + y)
			if not os.path.exists(state_dir):
				os.mkdir(state_dir)
			if os.path.exists(state_dir + y):
				os.remove(state_dir + y)
			grabFileState(dump_dir + y, state_dir + y)
			with open(state_dir + y, "rb") as fh:
				with open(ROM_name, "r+b") as fg:
					_byteread = fh.read()
					if (len(_byteread) > file_size):
						print("File State is too big: " + hex(len(_byteread)) + " > " + hex(file_size))
					state_name = y.replace(".bin","")
					folder_name = x["folder"]
					original_dict.append({
						"name": f"File State: {state_name} + ({folder_name})",
						"start": ROM_start + (file_size * state_index),
						"source_file": state_dir + y,
						"do_not_extract": True,
						"do_not_compress": True,
						"versions":[0],
					})
					file_state_count += 1;
					print(f"- {state_name} ({folder_name}): {hex(ROM_start + (file_size * state_index))} -> {hex(ROM_start + (file_size * (state_index + 1)))}")
					state_index += 1
	return original_dict;

def getFileStateEnd():
	return ROM_start + (file_size * file_state_count)