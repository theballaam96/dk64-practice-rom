import os

src_folders = ["src","asm"]
symbols_file = "asm/us/symbols.asm"

c_files = [];
c_lines = [];
unused = [];

for x in src_folders:
	for root, dirs, files in os.walk(x):
	    # select file name
	    for file in files:
	        # check the extension of files
	        if file.endswith('.c'):
	        	c_files.append(os.path.join(root, file))

for x in c_files:
	with open(x, "r") as fh:
		ln = fh.readlines();
		for y in ln:
			c_lines.append(y.split("//")[0])

with open(symbols_file,"r") as fh:
	for x in fh.readlines():
		if x.split(".definelabel")[0] == "":
			name = x.split(".definelabel ")[1].split(",")[0];
			found_name = False;
			for y in c_lines:
				if name in y:
					found_name = True;
			if not found_name:
				unused.append(name)

if len(unused) > 0:
	print("\nUNUSED VARIABLES/FUNCTIONS: ")
	for x in unused:
		print("\t" + x)
	print("")
#print(c_lines)