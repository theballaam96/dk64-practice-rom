import subprocess
import os
import shutil

MainMenuText = "Menu_Copy.bin"

if os.path.exists(MainMenuText):
  os.remove(MainMenuText)

shutil.copyfile("Menu.bin", MainMenuText);

with open(MainMenuText, "r+b") as fh:
  fh.seek(0x5FD);
  fh.write("PRACTICE\0".encode("ascii"));
  fh.seek(0x606);
  fh.write("TUNES".encode("ascii"));
  fh.seek(0x60B);
  fh.write("FORTNITE\0\0\0".encode("ascii"));
  fh.seek(0x616);
  fh.write("CHEATIN".encode("ascii"));
  fh.seek(0x61D);
  fh.write("MEMES\0\0".encode("ascii"));
  fh.seek(0x674);
  fh.write("S\0\0\0\0\0\0\0".encode("ascii"));
  fh.seek(0x67C);
  fh.write("C\0\0\0\0\0\0\0\0\0".encode("ascii"));
  fh.seek(0x68E);
  fh.write("C\0\0\0\0\0\0".encode("ascii"));
  fh.seek(0x695);
  fh.write("C\0\0\0\0\0\0\0\0\0\0".encode("ascii"));