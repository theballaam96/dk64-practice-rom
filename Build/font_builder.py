import os

previous_char = 0x20

def int_to_word(val):
	low = val % 256
	hi = (val - low) / 256
	return [int(hi),int(low)]

file_list = [
	"assets/Non-Code/Font/symbols_new_gz.png.ia4",
	"assets/Non-Code/Font/capitals_new_gz.png.ia4",
	"assets/Non-Code/Font/lower_new_gz.png.ia4",
]

temp_bins = ["./test_sym.bin","./test_upp.bin","./test_low.bin"]
data = []
char_index = 0
for x in range(len(file_list)):
	with open(file_list[x],"rb") as fg:
		with open(temp_bins[x],"wb") as fh:
			entire = len(fg.read())
			fg.seek(0)
			for _x in range(entire):
				val = int.from_bytes(fg.read(1),"big")
				upper = ((((val & 0xF0) >> 4) & 1) != 0) * 0x40
				lower = (((val & 0xF) & 1) != 0) * 0x40
				fh.write(bytearray([upper,lower]))
		with open(temp_bins[x],"rb") as fh:
			prev_empty_state = True
			for y in range(512):
				is_empty = True
				for z in range(16):
					fh.seek((z * 512) + y)
					if (int.from_bytes(fh.read(1),"big") != 0):
						is_empty = False
				if is_empty and not prev_empty_state:
					# Empty
					data[char_index]["end"] = y
					char_index += 1
				elif prev_empty_state and not is_empty:
					s = 0
					if (y - 1) >= 0:
						s = y - 1
					data.append({
						"character": 0x21 + char_index,
						"start": s,
					})
				prev_empty_state = is_empty

with open("assets/Non-Code/Font/font_boundaries.bin","wb") as fh:
	arr = []
	for x in range(0x180):
		arr.append(0)
	fh.write(bytearray(arr))
	for x in data:
		char_val = -1
		if isinstance(x["character"], str):
			char_val = int.from_bytes(x["character"].encode("ascii"), "big")
		elif isinstance(x["character"], int):
			char_val = x["character"]
		if (char_val - previous_char) != 1:
			print("Gap detected between "+hex(previous_char)+" and "+hex(char_val))
		previous_char = char_val
		if (char_val > -1):
			fh.seek(4 * (char_val - 0x21))
			diff = int(x["end"])-int(x["start"])
			lst = int_to_word(int(x["start"]))
			fh.write(bytearray(lst))
			fh.write(bytearray([diff,0]))

#print(data)

for x in temp_bins:
	if os.path.exists(x):
 		os.remove(x)
print("Made Font Boundaries")