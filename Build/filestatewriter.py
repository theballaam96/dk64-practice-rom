import os

file_size = 0x140 + 0x1E0 + 0x10 + 0x10 + 0x10 + 0x10 # 0x1 at end, rounded up
ROM_start = 0x2022000
ROM_name = "dk64-practice-rom.z64";
state_index = 0;
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
	}
]

def arrToInt(arr):
	total = 0;
	for x in arr:
		total = (total * 256) + x
	return total

def bytereadToInt(byteread):
	return arrToInt(list(byteread))

def grabFileState(input_file,output_file):
	with open(input_file, "rb") as fh:
		if os.path.exists(output_file):
			os.remove(output_file)
		with open(output_file, "wb") as fg:
			# Grab File Index
			fh.seek(0x7467C8)
			file_index = bytereadToInt(fh.read(1));
			# Grab Eeprom Slot
			found_slot = False;
			for x in range(4):
				fh.seek(0x7EDEA8 + x);
				EEPROMMap = bytereadToInt(fh.read(1))
				if not found_slot:
					if EEPROMMap == file_index:
						eeprom_slot = x;
						found_slot = True;
			if not found_slot:
				eeprom_slot = 0;
			# Get Flag Block Address
			flag_block_address = 0x7ECEA8 + eeprom_slot * 0x1AC
			fh.seek(flag_block_address)
			_perm_flag_block = fh.read(0x140)
			fg.write(_perm_flag_block)
			#print(hex(flag_block_address))
			fh.seek(0x7FC950)
			fg.write(fh.read(0x1E0))
			fh.seek(0x7FCC40)
			fg.write(fh.read(0x10))
			fh.seek(0x7FDD90)
			fg.write(fh.read(0x10))
			# Map
			fh.seek(0x76A0A8)
			fg.write(fh.read(0x4))
			# X Y Z
			fh.seek(0x7FBB4C)
			player = bytereadToInt(fh.read(0x4)) - 0x80000000;
			fh.seek(player + 0x7C)
			fg.write(fh.read(0x4))
			fh.seek(player + 0x80)
			fg.write(fh.read(0x4))
			fh.seek(player + 0x84)
			fg.write(fh.read(0x4))
			# Character
			fh.seek(0x74E77C)
			fg.write(fh.read(0x1))

file_dir_start = "./../assets/File States/"
for x in state_files:
	state_dir = file_dir_start + x["folder"] + "/State Files/"
	dump_dir = file_dir_start + x["folder"] + "/RAM Dump/"
	for y in x["files"]:
		#print(file_dir + y)
		if os.path.exists(state_dir + y):
			os.remove(state_dir + y);
		grabFileState(dump_dir + y, state_dir + y);
		with open(state_dir + y, "rb") as fh:
			with open(ROM_name, "r+b") as fg:
				_byteread = fh.read()
				fg.seek(ROM_start + (file_size * state_index))
				fg.write(_byteread)
				state_index += 1
		if os.path.exists(state_dir + y):
			os.remove(state_dir + y);
print("Generated File States")