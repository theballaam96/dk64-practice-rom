import json
import os

raw_json = "src/include/symbols.json"
dyn_json = "src/include/dyn_symbols.json"

cwd = os.getcwd()
pre_app = ""; # "../" if running just this file. Otherwise "" since it'll be run from build.bat
pre_lib = ""
if "\\Build" in cwd:
	pre_app = "../"
	pre_lib = "../../"


raw_json = pre_lib + raw_json;
dyn_json = pre_lib + dyn_json;

def getSymFile(version):
	return pre_lib + "lib/libdk-" + version + ".a";

def writeSymbols(version):
	sym_func = []
	sym_vanilla = []
	sym_hack = []
	sym_code = []
	warnings = [
		"This is an automatically generated file.",
		"Please don't make edits to this file directly as they will be overwritten at next build.",
		"To make amendments, see include/symbols.json and build/symbols_generator.py.",
		"Thanks.",
	]
	with open(raw_json,"r") as fh:
		data = json.load(fh)
		func_list = data["functions"]
		func_count = 0;
		func_length = len(func_list)
		for func in func_list:
			if version in func["versions"]:
				sym_func.append(f"{func['name']} = {func['versions'][version]};")
				func_count += 1;
			else:
				print(f"Ignoring {func['name']}")
				# sym_func.append("//.definelabel " + func["name"])
		vanilla_list = data["vanilla_vars"]
		vanilla_count = 0;
		vanilla_length = len(vanilla_list)
		for var in vanilla_list:
			if version in var["versions"]:
				sym_vanilla.append(f"{var['name']} = {var['versions'][version]};")
				vanilla_count += 1
			else:
				print(f"Ignoring {var['name']}")
				# sym_vanilla.append("//.definelabel " + var["name"])
		hack_list = data["hack_vars"]
		hack_count = 0;
		hack_length = len(hack_list)
		for var in hack_list:
			sym_hack.append(f"{var['name']} = {var['address']};")
			# sym_hack.append(var["name"] + ", " + var["address"] + " // " + var["size_comment"])
			hack_count += 1;
		code_list = data["code"]
		code_count = 0;
		code_length = len(code_list)
		for code in code_list:
			if version in code["versions"]:
				sym_code.append(f"{code['name']} = {code['versions'][version]};")
				code_count += 1;
			else:
				print(f"Ignoring {code['name']}")
				# sym_code.append("//.definelabel " + code["name"])
		total_count = func_count + vanilla_count + hack_count + code_count;
		total_length = func_length + vanilla_length + hack_length + code_length
		with open(getSymFile(version),"w") as fg:
			# fg.write("/*\n")
			# for x in warnings:
			# 	fg.write("\t" + x + "\n")
			# fg.write("\tStats:\n")
			# fg.write("\t\tFunctions: " + str(func_count) + "/" + str(func_length) + "(" + str(round(100 * (func_count / max(func_length,1)),2)) + "%)\n")
			# fg.write("\t\tVanilla Vars: " + str(vanilla_count) + "/" + str(vanilla_length) + "(" + str(round(100 * (vanilla_count /  max(vanilla_length,1)),2)) + "%)\n")
			# fg.write("\t\tHack Vars: " + str(hack_count) + "/" + str(hack_length) + "(" + str(round(100 * (hack_count /  max(hack_length,1)),2)) + "%)\n")
			# fg.write("\t\tCode: " + str(code_count) + "/" + str(code_length) + "(" + str(round(100 * (code_count /  max(code_length,1)),2)) + "%)\n")
			# fg.write("\t\tOverall: " + str(total_count) + "/" + str(total_length) + "(" + str(round(100 * (total_count /  max(total_length,1)),2)) + "%)\n")
			# fg.write("*/\n\n")
			# fg.write("//functions\n")
			for x in sym_func:
				fg.write(x + "\n")
			# fg.write("\n//vanilla data\n")
			for x in sym_vanilla:
				fg.write(x + "\n")
			# fg.write("\n//hack data\n")
			for x in sym_hack:
				fg.write(x + "\n")
			# fg.write("\n// Code\n")
			for x in sym_code:
				fg.write(x + "\n")
	with open(dyn_json,"r") as fh:
		data = json.load(fh)
		dyn_vars = data["dynamic_vars"]
		dyn_list = [];
		for dyn in dyn_vars:
			if version in dyn["versions"]:
				dyn_list.append(f"{dyn['name']} = {dyn['versions'][version]};")
		with open(getSymFile(version),"a") as fg:
			fg.write("\n")
			for x in dyn_list:
				fg.write(x + "\n")
versions = ["us","pal","jp"]
for x in versions:
	writeSymbols(x);
	print("Generated symbols for version: " + x)