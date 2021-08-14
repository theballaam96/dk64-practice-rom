file_size = 0x13C + 0x1E0 + 0xC
ROM_start = 0x2000000
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
	}
]

file_dir_start = "./../Source/File States/"
for x in state_files:
	file_dir = file_dir_start + x["folder"] + "/State Files/"
	for y in x["files"]:
		#print(file_dir + y)
		with open(file_dir + y, "rb") as fh:
			with open(ROM_name, "r+b") as fg:
				_byteread = fh.read()
				fg.seek(ROM_start + (file_size * state_index))
				fg.write(_byteread)
				state_index += 1