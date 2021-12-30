from snag_names import snag_names

shortened_names = []

def shorten_mini(s,_in,_out):
	s = s.strip();
	if len(s) < 16:
		return s
	else:
		return s.replace(_in,_out)

def shorten(s):
	s = shorten_mini(s,"Production Room","Prod Room")
	s = shorten_mini(s,"Chunky Prod Room","Chunky Crusher")
	return s

error_count = 0;
for y in range(len(snag_names)):
	x = snag_names[y].strip()
	if len(x) < 16:
		shortened_names.append(x)
	else:
		x = shorten(x)
		if len(x) > 15:
			print("Too long: [" + hex(y) + "] " + x + " (" + str(len(x) - 15) + ")")
			shortened_names.append("LONG ERROR")
			error_count += 1
		else:
			shortened_names.append(x)

with open("assets/Non-Code/snag_names.bin","wb") as fh:
	with open("assets/Non-Code/snag_names_capitals.bin","wb") as fg:
		for x in shortened_names:
			arr = []
			arr_upper = []
			for y in range(16):
				arr.append(0)
				arr_upper.append(0)
			x = x.replace("'","")
			x = x.replace("(","<")
			x = x.replace(")",">")
			x = x.replace("-"," ")
			x = x.replace("&","#")
			x_upper = x.upper()
			for y in range(len(x)):
				arr[y] = ord(x[y])
				arr_upper[y] = ord(x_upper[y])
			fh.write(bytearray(arr))
			fg.write(bytearray(arr_upper))