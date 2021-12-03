import os

def int_to_word(val):
	low = val % 256
	hi = (val - low) / 256
	return [int(hi),int(low)]

data = []

for x in range(126-0x20):
	data.append({
		"character": 0x21 + x,
		"start": (x % 0x20) * 0x10,
		"end": ((x % 0x20) * 0x10) + 16,
	})

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
		if (char_val > -1):
			fh.seek(4 * (char_val - 0x21))
			diff = int(x["end"])-int(x["start"])
			lst = int_to_word(int(x["start"]))
			fh.write(bytearray(lst))
			fh.write(bytearray([diff,0]))

#print(data)

print("Made Font Boundaries")