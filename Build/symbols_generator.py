import json
import os

raw_json = "include/symbols.json"
dyn_json = "include/dyn_symbols.json"

cwd = os.getcwd()
pre_app = ""; # "../" if running just this file. Otherwise "" since it'll be run from build.bat
if "\\Build" in cwd:
	pre_app = "../"

raw_json = pre_app + raw_json;
dyn_json = pre_app + dyn_json;

def getSymFile(version):
	return pre_app + "asm/" + version + "/symbols.asm";

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
				sym_func.append(".definelabel " + func["name"] + ", " + func["versions"][version])
				func_count += 1;
			else:
				sym_func.append("//.definelabel " + func["name"])
		vanilla_list = data["vanilla_vars"]
		vanilla_count = 0;
		vanilla_length = len(vanilla_list)
		for var in vanilla_list:
			if version in var["versions"]:
				sym_vanilla.append(".definelabel " + var["name"] + ", " + var["versions"][version])
				vanilla_count += 1;
			else:
				sym_vanilla.append("//.definelabel " + var["name"])
		hack_list = data["hack_vars"]
		hack_count = 0;
		hack_length = len(hack_list)
		for var in hack_list:
			sym_hack.append(".definelabel " + var["name"] + ", " + var["address"] + " // " + var["size_comment"])
			hack_count += 1;
		code_list = data["code"]
		code_count = 0;
		code_length = len(code_list)
		for code in code_list:
			if version in code["versions"]:
				sym_code.append(".definelabel " + code["name"] + ", " + code["versions"][version])
				code_count += 1;
			else:
				sym_code.append("//.definelabel " + code["name"])
		with open(getSymFile(version),"w") as fg:
			fg.write("/*\n")
			for x in warnings:
				fg.write("\t" + x + "\n")
			fg.write("\tStats:\n")
			fg.write("\t\tFunctions: " + str(func_count) + "/" + str(func_length) + "(" + str(round(100 * (func_count / max(func_length,1)),2)) + "%)\n")
			fg.write("\t\tVanilla Vars: " + str(vanilla_count) + "/" + str(vanilla_length) + "(" + str(round(100 * (vanilla_count /  max(vanilla_length,1)),2)) + "%)\n")
			fg.write("\t\tHack Vars: " + str(hack_count) + "/" + str(hack_length) + "(" + str(round(100 * (hack_count /  max(hack_length,1)),2)) + "%)\n")
			fg.write("\t\tCode: " + str(code_count) + "/" + str(code_length) + "(" + str(round(100 * (code_count /  max(code_length,1)),2)) + "%)\n")
			fg.write("*/\n\n")
			fg.write("//functions\n")
			for x in sym_func:
				fg.write(x + "\n")
			fg.write("\n//vanilla data\n")
			for x in sym_vanilla:
				fg.write(x + "\n")
			fg.write("\n//hack data\n")
			for x in sym_hack:
				fg.write(x + "\n")
			fg.write("\n// Code\n")
			for x in sym_code:
				fg.write(x + "\n")
	with open(dyn_json,"r") as fh:
		data = json.load(fh)
		dyn_vars = data["dynamic_vars"]
		dyn_list = [];
		for dyn in dyn_vars:
			if version in dyn["versions"]:
				dyn_list.append(".definelabel " + dyn["name"] + ", " + dyn["versions"][version])
		with open(getSymFile(version),"a") as fg:
			fg.write("\n")
			for x in dyn_list:
				fg.write(x + "\n")
versions = ["us","pal","jp"]
for x in versions:
	writeSymbols(x);
	print("Generated symbols for version: " + x)