heap_size = 0x21000;

def getHeapLocation(offset):
	return heap_size + offset;

def getHeapSize():
	return getHeapLocation(0);

#Write Include File
with open("include/heap.h","w") as fh:
	filestateromstart = hex(getHeapLocation(0x2002000))
	fh.write(f"#define FileStatesROMStart {filestateromstart}\n")
	actornamesstart = hex(getHeapLocation(0x2000000))
	fh.write(f"#define ActorNamesStart {actornamesstart}\n")
	snaglowerstart = hex(getHeapLocation(0x2001800))
	fh.write(f"#define SnagLowerStart {snaglowerstart}\n")
	snagcapsstart = hex(getHeapLocation(0x2001C00))
	fh.write(f"#define SnagCapitalsStart {snagcapsstart}\n")

us_heap_end = 0x805FAE00;
jp_heap_end = 0x805F8600;
pal_heap_end = 0x805F3E00;

dyn_vars = [
	{
		"name":"customCodeStart",
		"offset_dir":-1,
		"value":getHeapSize(),
		"versions":{
			"us":us_heap_end,
			"jp":jp_heap_end,
		}
	},
	{
		"name":"customCodeUpper",
		"offset_dir":-1,
		"value":0,
		"versions":{
			"us":((us_heap_end - getHeapSize()) >> 16) & 0xFFFF,
			"jp":((jp_heap_end - getHeapSize()) >> 16) & 0xFFFF,
		}
	},
	{
		"name":"customCodeLower",
		"offset_dir":-1,
		"value":0,
		"versions":{
			"us":(us_heap_end - getHeapSize()) & 0xFFFF,
			"jp":(jp_heap_end - getHeapSize()) & 0xFFFF,
		}
	},
	{
		"name":"customCodeSize",
		"offset_dir":1,
		"value":0,
		"versions":{
			"us":getHeapSize(),
			"jp":getHeapSize(),
		}
	}
]

with open("include/dyn_symbols.json","w") as fh:
	fh.write("{\n")
	fh.write("\t\"dynamic_vars\":[\n")
	for a in range(len(dyn_vars)):
		x = dyn_vars[a];
		fh.write("\t\t{\n")
		fh.write("\t\t\t\"name\":\"" + x["name"] + "\",\n")
		fh.write("\t\t\t\"versions\":{\n")
		for b in range(len(x["versions"].keys())):
			y = list(x["versions"].keys())[b]
			version = y;
			addr = hex(x["versions"][y] + (x["offset_dir"] * x["value"]))
			comma = ","
			if (b + 1) == len(x["versions"]):
				comma = ""
			fh.write(f"\t\t\t\t\"{y}\":\"{addr}\"{comma}\n")
		comma = ","
		if (a + 1) == len(dyn_vars):
			comma = ""
		fh.write("\t\t\t}\n")
		fh.write("\t\t}" + comma + "\n")
	fh.write("\t]\n")
	fh.write("}")

with open("heap.shrink","w") as fh:
	fh.write(hex(getHeapSize()))