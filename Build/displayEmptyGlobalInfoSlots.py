# DISPLAY EMPTY GLOBAL INFO SLOTS
# Displays which parts of the end of memory (0x807FF310 -> 0x807FFFFF) are unused by your code
# This is great if you have a lot of variables and need to find free space
# Or search for conflicts where two variables share the same space in memory

# To customize for your hack, change 'symbols_file', 'start_text' and 'end_text' to match your repo

# There is a tiny bit of maintainance that you will need to do for this to be accurate
# After every definition of a variable's location in memory, you will need to comment it's size with the size being the first thing after the "// "
# Sizes can either be specified as the ultra64/c type name (eg. u8/s8/float. Full list is in 'default_sizes') or as a hex/dec number (eg. 0x8, 1)
# To define that a variable is an array, append " x {count}", where "{count}" is the amount of items in your array.
# For example, "// u32 x 8" would indicate that each item has a size of 4-bytes where there are 8 items
# If your variable isn't an array, the " x {count}" isn't necessary
# This won't be able to read your structs file, so you will need to update your symbols file with the struct sizes should you alter the size of your struct

symbols_file = "../asm/us/symbols.asm" # Relative path to your symbols.asm file
start_text = "//hack data" # Text which precedes the data you want to analyze
end_text = "// Code" # Text which is immediately after the data you want to analyze

min_vanilla_unused = 0x807FF310 # Last unused item is a copy of size 0x210 for data at 0x101A50->0x101C50 to 0x7FF100 (0x805FBE38)
min_end = 0x80800000 # First address out of range

bytes_used = []
for x in range(min_end - min_vanilla_unused):
	bytes_used.append({
		"used_by": "none",
		"used": False,
	})

default_sizes = [
	{"text":"u8","size":1},
	{"text":"s8","size":1},
	{"text":"char","size":1},
	{"text":"u16","size":2},
	{"text":"s16","size":2},
	{"text":"short","size":2},
	{"text":"u32","size":4},
	{"text":"s32","size":4},
	{"text":"f32","size":4},
	{"text":"ptr","size":4},
	{"text":"pointer","size":4},
	{"text":"int","size":4},
	{"text":"float","size":4},
]

hack_data = []

with open(symbols_file,"r") as fh:
	lines = fh.readlines()
	in_range = False;
	for x in lines:
		if "//hack data" in x and not in_range:
			in_range = True;
		if "// Code" in x and in_range:
			in_range = False;
		if in_range and ".definelabel" == x[:12]:
			x = x.replace("\n","")
			addr = int(x[x.find(", ")+2:x.find("//")],16)
			if addr >= min_vanilla_unused:
				offset = addr - min_vanilla_unused
				size_data = x[x.find("// ") + 3:]
				size = 0;
				for y in default_sizes:
					if y["text"] in size_data:
						if y["size"] > size:
							size = y["size"]
				if size == 0:
					space_index = size_data.find(" ")
					more_size_info = size_data
					if space_index > -1:
						more_size_info = size_data[:space_index]
					if "0x" in more_size_info:
						size = int(more_size_info,16)
					else:
						size = int(more_size_info)
				count = 1
				if " x " in size_data:
					count_info = size_data.split(" x ")[1]
					space_index = count_info.find(" ")
					more_count_info = count_info
					if space_index > -1:
						more_count_info = count_info[:space_index]
					if "0x" in more_count_info:
						count = int(more_count_info,16)
					else:
						count = int(more_count_info)
				size = size * count
				hack_data.append({
					"text": x,
					"name": x[13:x.find(", ")],
					"offset": offset,
					"size": size,
				})

usage_data = []
has_error = False;
for x in hack_data:
	for y in range(x["size"]):
		byte_info = bytes_used[x["offset"] + y]
		if byte_info["used"] == True:
			print("Duplicate use of byte " + hex(min_vanilla_unused + offset) + " by " + byte_info["used_by"] + " and " + x["name"])
			has_error = True;
		else:
			byte_info["used"] = True;
			byte_info["used_by"] = x["name"]

if not has_error:
	in_byte_range = False;
	byte_range_start = min_vanilla_unused;
	byte_range_end = -1;
	free_range_start = min_vanilla_unused;
	free_range_end = -1;
	for x in range(len(bytes_used)):
		byte_info = bytes_used[x]
		if byte_info["used"] == True and in_byte_range == False:
			in_byte_range = True;
			byte_range_start = min_vanilla_unused + x
			free_range_end = min_vanilla_unused + x - 1
			free_size = free_range_end - free_range_start
			if free_size > 0:
				usage_data.append({
					"start": hex(free_range_start),
					"end": hex(free_range_end),
					"size": hex(free_size),
					"used": False
				})
		elif byte_info["used"] == False and in_byte_range == True:
			in_byte_range = False;
			free_range_start = min_vanilla_unused + x
			byte_range_end = min_vanilla_unused + x - 1
			byte_size = byte_range_end - byte_range_start
			if byte_size > 0:
				usage_data.append({
					"start": hex(byte_range_start),
					"end": hex(byte_range_end),
					"size": hex(byte_size),
					"used": True
				})

	byte_range_end = min_end - 1
	free_range_end = min_end - 1
	if in_byte_range == True:
		byte_size = byte_range_end - byte_range_start
		if byte_size > 0:
			usage_data.append({
				"start": hex(byte_range_start),
				"end": hex(byte_range_end),
				"size": hex(byte_size),
				"used": True
			})
	else:
		free_size = free_range_end - free_range_start
		if free_size > 0:
			usage_data.append({
				"start": hex(free_range_start),
				"end": hex(free_range_end),
				"size": hex(free_size),
				"used": False
			})
	for x in usage_data:
		print(x)