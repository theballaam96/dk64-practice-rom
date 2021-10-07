import subprocess
import os
import shutil

DolbyText = "Dolby_Copy.bin"

if os.path.exists(DolbyText):
  os.remove(DolbyText)

shutil.copyfile("Dolby.bin", DolbyText);

with open(DolbyText, "r+b") as fh:
  fh.seek(0x30);
  fh.write("PRESENTED BY".encode("ascii"))
  fh.seek(0x3C);
  fh.write("RED IS STINKY\0".encode("ascii"))
  fh.seek(0x5D);
  fh.write("\0\0\0\0\0\0\0\0\0\0\0\0".encode("ascii"))