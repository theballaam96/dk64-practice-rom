import subprocess
import os
import shutil

DolbyText = "Dolby_Copy.bin"

if os.path.exists(DolbyText):
  os.remove(DolbyText)

shutil.copyfile("Dolby.bin", DolbyText);

os.chdir("../Source/Non-Code/Dolby")

with open("presented_line.bin","rb") as fh:
  patch_dolbypresented = fh.read(0x0C);

with open("top_line.bin", "rb") as fh:
  patch_dolbytop = fh.read(33);

with open("bottom_line.bin", "rb") as fh:
  patch_dolbybottom = fh.read(33);

os.chdir("../../../Build")
with open(DolbyText, "r+b") as fh:
  fh.seek(0x30);
  fh.write(patch_dolbypresented)
  fh.seek(0x3C);
  fh.write(patch_dolbytop)
  fh.seek(0x5D);
  fh.write(patch_dolbybottom)