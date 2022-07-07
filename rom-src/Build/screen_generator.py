import json
import os

data_file = "include/screens_list.json";
list_file = "include/screens_list.h";
def_file = "include/screen_struct_def.h";
c_file = "src/activeMenu_screens.c";

cwd = os.getcwd()
pre_app = ""; # "../" if running just this file. Otherwise "" since it'll be run from build.bat
if "\\Build" in cwd:
	pre_app = "../"
data_file = pre_app + data_file;
list_file = pre_app + list_file;
def_file = pre_app + def_file;
c_file = pre_app + c_file;

indexvar_list = []
struct_list = []
screenlist_list = []

with open(data_file,"r") as fh:
	data = json.load(fh)
	screen_list = data["screens"]
	index = 0;
	for x in screen_list:
		indexvar_list.append("#define " + x["index_var"] + " " + str(index))
		const_str = ""
		if x["const"]:
			const_str = "const "
		struct_list.append("extern " + const_str + "Screen " + x["struct"] + ";")
		screenlist_list.append("&" + x["struct"] + ",")
		index += 1;

warning = [
	"/*",
	"\tThis is an automatically generated file.",
	"\tPlease don't make edits to this file directly as they will be overwritten at next build.",
	"\tTo make amendments, see include/screens_list.json and build/screen_generator.py.",
	"\tThanks.",
	"*/",
]

with open(list_file,"w") as fh:
	for x in warning:
		fh.write(x+"\n")
	for x in indexvar_list:
		fh.write("\n" + x)

with open(def_file,"w") as fh:
	for x in warning:
		fh.write(x+"\n")
	fh.write("\n#include \"vars.h\"\n")
	for x in struct_list:
		fh.write("\n" + x)

with open(c_file,"w") as fh:
	for x in warning:
		fh.write(x+"\n")
	fh.write("\n#include \"../include/common.h\"\n\n")
	fh.write("const Screen* menu_screens[] = {")
	for x in screenlist_list:
		fh.write("\n\t" + x)
	fh.write("\n};")

print("Successfully built screens")