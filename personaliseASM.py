import subprocess
import os
import shutil
import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()

scripthawk_directory = filedialog.askdirectory(parent=root,initialdir="/",title='Please select your ScriptHawk directory')
practicerom_directory = filedialog.askdirectory(parent=root,initialdir="/",title='Please select your Practice ROM directory')
if scripthawk_directory == "":
	print("[ERROR] No ScriptHawk directory selected")
	exit()
if practicerom_directory == "":
	print("[ERROR] No Practice ROM directory selected")
	exit()
sh_split = scripthawk_directory.split("/")
pr_split = practicerom_directory.split("/")
in_right_dir = True
dir_end = -1;
new_dir = "./"
for x in range(len(sh_split)):
	if in_right_dir:
		if sh_split[x] != pr_split[x]:
			new_dir += "../"
			in_right_dir = False;
			dir_end = x;
	else:
		new_dir += "../"
for y in range(len(pr_split)):
	if y >= dir_end:
		new_dir += pr_split[y] + "/"
new_dir += "Source/"

edited_lines = [];

with open("./Source/Master.asm", "r") as fh:
	asmlines = fh.readlines()
	for l in asmlines:
		if ".incasm" in l:
			split_line = l.split("/")
			source_found = False;
			new_line = ".incasm \"" + new_dir
			for s in split_line:
				if source_found:
					new_line += s.replace("\n","").replace("\"","") + "/"
				if s == "Source":
					source_found = True;
			new_line = new_line[:-1] + "\"\n"
			edited_lines.append(new_line)
		else:
			edited_lines.append(l)
os.remove("./Source/Master.asm")
with open("./Source/Master.asm", "a") as fh:
	for e in edited_lines:
		fh.write(e)

print("ASM Altered for your PC")