import subprocess
import os
import shutil

KLumsyText = "KLumsy_Copy.bin"

if os.path.exists(KLumsyText):
  os.remove(KLumsyText)

shutil.copyfile("KLumsy.bin", KLumsyText);

os.chdir("../Source/Non-Code/K Lumsy")

with open("first_textbox.bin", "rb") as fh:
  patch_klumsyfirst = fh.read(339)

with open("final_textbox.bin", "rb") as fh:
  patch_klumsyfinal = fh.read(281)

os.chdir("../../../Build")
with open(KLumsyText, "r+b") as fh:
  fh.seek(0x67)
  fh.write(patch_klumsyfirst)
  fh.seek(0x245)
  fh.write(patch_klumsyfinal)