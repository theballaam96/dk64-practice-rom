import os
import subprocess

pckg = ".pckg"
pre_app = "./Build/"
pckg = pre_app + pckg;

if not os.path.exists(pckg):
	with open(pckg,"w") as fh:
		fh.write("")

packages = []
installed = []

with open(pckg,"r") as fh:
	lines = fh.readlines()
	lines_ = []
	for x in lines:
		if x != "" or x != "\n":
			lines_.append(x.replace("\n",""))
	for package in packages:
		if package not in lines_:
			print(f"Installing package: {package}")
			cmd = ["pip","install",package]
			subprocess.Popen(cmd).wait()
			installed.append(package)
with open(pckg,"a") as fh:
	for x in installed:
		fh.write(x + "\n")