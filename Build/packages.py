import os

def install_pckg(pckg_name):
	pckg_installed = False;
	with open(".pckg","r") as fh:
		pckg_l = fh.readlines()
		for x in pckg_l:
			if x == (pckg_name + "\n"):
				pckg_installed = True;
	if not pckg_installed:
		with open(".pckg","a") as fh:
			fh.write(pckg_name+"\n")
		os.system("python -m pip install --upgrade " + pckg_name)

pckg_list = ["pip","Pillow"]

if not os.path.exists(".pckg"):
	with open(".pckg","w") as fh:
		fh.write("")
for pckg in pckg_list:
	install_pckg(pckg);