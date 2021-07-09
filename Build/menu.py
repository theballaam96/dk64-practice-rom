import subprocess
import os
import shutil

MainMenuText = "Menu_Copy.bin"

if os.path.exists(MainMenuText):
  os.remove(MainMenuText)

shutil.copyfile("Menu.bin", MainMenuText);

os.chdir("../Source/Non-Code/Main Menu")

with open("adventure.bin", "rb") as fh:
  patch_adventure = fh.read(9);
  
with open("sound.bin", "rb") as fh:
  patch_sound = fh.read(5);

with open("kong_battle.bin", "rb") as fh:
  patch_kongbattle = fh.read(11);

with open("mystery.bin", "rb") as fh:
  patch_mystery = fh.read(7);

with open("options.bin", "rb") as fh:
  patch_options = fh.read(7);

with open ("survival.bin", "rb") as fh:
  patch_survival = fh.read(8);

with open("coin_hoard.bin", "rb") as fh:
  patch_coinhoard = fh.read(10);

with open("capture.bin", "rb") as fh:
  patch_capture = fh.read(7);

with open("capture_pad.bin", "rb") as fh:
  patch_capturepad = fh.read(11);

os.chdir("../../../Build")
with open(MainMenuText, "r+b") as fh:
  fh.seek(0x5FD);
  fh.write(patch_adventure);
  fh.seek(0x606);
  fh.write(patch_sound);
  fh.seek(0x60B);
  fh.write(patch_kongbattle);
  fh.seek(0x616);
  fh.write(patch_mystery);
  fh.seek(0x61D);
  fh.write(patch_options);
  fh.seek(0x674);
  fh.write(patch_survival);
  fh.seek(0x67C);
  fh.write(patch_coinhoard);
  fh.seek(0x68E);
  fh.write(patch_capture);
  fh.seek(0x695);
  fh.write(patch_capturepad);