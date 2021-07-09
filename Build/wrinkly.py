import subprocess
import os
import shutil

WrinklyText = "Wrinkly_Copy.bin"

if os.path.exists(WrinklyText):
  os.remove(WrinklyText)

shutil.copyfile("Wrinkly.bin", WrinklyText);

os.chdir("../Source/Non-Code/Wrinkly")

with open("FTT.bin", "rb") as fh:
  patch_wrinkly_ftt = fh.read(0x17A)

os.chdir("Japes")
with open("DKJapes.bin", "rb") as fh:
  patch_wrinkly_japes_dk = fh.read(0x52)
with open("DiddyJapes.bin", "rb") as fh:
  patch_wrinkly_japes_diddy = fh.read(0x5A)
with open("LankyJapes.bin", "rb") as fh:
  patch_wrinkly_japes_lanky = fh.read(0x5F)
with open("TinyJapes.bin", "rb") as fh:
  patch_wrinkly_japes_tiny = fh.read(0x4F)
with open("ChunkyJapes.bin", "rb") as fh:
  patch_wrinkly_japes_chunky = fh.read(0x45)
os.chdir("..")

os.chdir("Aztec")
with open("DKAztec.bin", "rb") as fh:
  patch_wrinkly_aztec_dk = fh.read(0x3A)
with open("DiddyAztec.bin", "rb") as fh:
  patch_wrinkly_aztec_diddy = fh.read(0x45)
with open("LankyAztec.bin", "rb") as fh:
  patch_wrinkly_aztec_lanky = fh.read(0x3E)
with open("TinyAztec.bin", "rb") as fh:
  patch_wrinkly_aztec_tiny = fh.read(0x43)
with open("ChunkyAztec.bin", "rb") as fh:
  patch_wrinkly_aztec_chunky = fh.read(0x4D)
os.chdir("..")

os.chdir("Factory")
with open("DKFactory.bin", "rb") as fh:
  patch_wrinkly_factory_dk = fh.read(0x4F)
with open("DiddyFactory.bin", "rb") as fh:
  patch_wrinkly_factory_diddy = fh.read(0x4D)
with open("LankyFactory.bin", "rb") as fh:
  patch_wrinkly_factory_lanky = fh.read(0x41)
with open("TinyFactory.bin", "rb") as fh:
  patch_wrinkly_factory_tiny = fh.read(0x30)
with open("ChunkyFactory.bin", "rb") as fh:
  patch_wrinkly_factory_chunky = fh.read(0x3E)
os.chdir("..")

os.chdir("Galleon")
with open("DKGalleon.bin", "rb") as fh:
  patch_wrinkly_galleon_dk = fh.read(0x47)
with open("DiddyGalleon.bin", "rb") as fh:
  patch_wrinkly_galleon_diddy = fh.read(0x44)
with open("LankyGalleon.bin", "rb") as fh:
  patch_wrinkly_galleon_lanky = fh.read(0x41)
with open("TinyGalleon.bin", "rb") as fh:
  patch_wrinkly_galleon_tiny = fh.read(0x4C)
with open("ChunkyGalleon.bin", "rb") as fh:
  patch_wrinkly_galleon_chunky = fh.read(0x40)
os.chdir("..")

os.chdir("Fungi")
with open("DKFungi.bin", "rb") as fh:
  patch_wrinkly_fungi_dk = fh.read(0x2C)
with open("DiddyFungi.bin", "rb") as fh:
  patch_wrinkly_fungi_diddy = fh.read(0x40)
with open("LankyFungi.bin", "rb") as fh:
  patch_wrinkly_fungi_lanky = fh.read(0x5E)
with open("TinyFungi.bin", "rb") as fh:
  patch_wrinkly_fungi_tiny = fh.read(0x3A)
with open("ChunkyFungi.bin", "rb") as fh:
  patch_wrinkly_fungi_chunky = fh.read(0x39)
os.chdir("..")

os.chdir("Caves")
with open("DKCaves.bin", "rb") as fh:
  patch_wrinkly_caves_dk = fh.read(0x33)
with open("DiddyCaves.bin", "rb") as fh:
  patch_wrinkly_caves_diddy = fh.read(0x40)
with open("LankyCaves.bin", "rb") as fh:
  patch_wrinkly_caves_lanky = fh.read(0x49)
with open("TinyCaves.bin", "rb") as fh:
  patch_wrinkly_caves_tiny = fh.read(0x4C)
with open("ChunkyCaves.bin", "rb") as fh:
  patch_wrinkly_caves_chunky = fh.read(0x34)
os.chdir("..")

os.chdir("Castle")
with open("DKCastle.bin", "rb") as fh:
  patch_wrinkly_castle_dk = fh.read(0x5D)
with open("DiddyCastle.bin", "rb") as fh:
  patch_wrinkly_castle_diddy = fh.read(0x39)
with open("LankyCastle.bin", "rb") as fh:
  patch_wrinkly_castle_lanky = fh.read(0x44)
with open("TinyCastle.bin", "rb") as fh:
  patch_wrinkly_castle_tiny = fh.read(0x3E)
with open("ChunkyCastle.bin", "rb") as fh:
  patch_wrinkly_castle_chunky = fh.read(0x2A)
os.chdir("..")

os.chdir("../../../Build")
with open(WrinklyText, "r+b") as fh:
  fh.seek(0x23F)
  fh.write(patch_wrinkly_ftt)
  fh.seek(0x3B9)
  fh.write(patch_wrinkly_japes_dk)
  fh.seek(0x40C)
  fh.write(patch_wrinkly_japes_diddy)
  fh.seek(0x464)
  fh.write(patch_wrinkly_japes_lanky)
  fh.seek(0x4C3)
  fh.write(patch_wrinkly_japes_tiny)
  fh.seek(0x512)
  fh.write(patch_wrinkly_japes_chunky)
  fh.seek(0x557)
  fh.write(patch_wrinkly_aztec_dk)
  fh.seek(0x591)
  fh.write(patch_wrinkly_aztec_diddy)
  fh.seek(0x5D6)
  fh.write(patch_wrinkly_aztec_lanky)
  fh.seek(0x614)
  fh.write(patch_wrinkly_aztec_tiny)
  fh.seek(0x657)
  fh.write(patch_wrinkly_aztec_chunky)
  fh.seek(0x6A4)
  fh.write(patch_wrinkly_factory_dk)
  fh.seek(0x6F3)
  fh.write(patch_wrinkly_factory_diddy)
  fh.seek(0x740)
  fh.write(patch_wrinkly_factory_lanky)
  fh.seek(0x781)
  fh.write(patch_wrinkly_factory_tiny)
  fh.seek(0x7B1)
  fh.write(patch_wrinkly_factory_chunky)
  fh.seek(0x7EF)
  fh.write(patch_wrinkly_galleon_dk)
  fh.seek(0x836)
  fh.write(patch_wrinkly_galleon_diddy)
  fh.seek(0x87A)
  fh.write(patch_wrinkly_galleon_lanky)
  fh.seek(0x8BB)
  fh.write(patch_wrinkly_galleon_tiny)
  fh.seek(0x907)
  fh.write(patch_wrinkly_galleon_chunky)
  fh.seek(0x947)
  fh.write(patch_wrinkly_fungi_dk)
  fh.seek(0x973)
  fh.write(patch_wrinkly_fungi_diddy)
  fh.seek(0x9B3)
  fh.write(patch_wrinkly_fungi_lanky)
  fh.seek(0xA11)
  fh.write(patch_wrinkly_fungi_tiny)
  fh.seek(0xA4B)
  fh.write(patch_wrinkly_fungi_chunky)
  fh.seek(0xA84)
  fh.write(patch_wrinkly_caves_dk)
  fh.seek(0xAB7)
  fh.write(patch_wrinkly_caves_diddy)
  fh.seek(0xAF7)
  fh.write(patch_wrinkly_caves_lanky)
  fh.seek(0xB40)
  fh.write(patch_wrinkly_caves_tiny)
  fh.seek(0xB8C)
  fh.write(patch_wrinkly_caves_chunky)
  fh.seek(0xBC0)
  fh.write(patch_wrinkly_castle_dk)
  fh.seek(0xC1D)
  fh.write(patch_wrinkly_castle_diddy)
  fh.seek(0xC56)
  fh.write(patch_wrinkly_castle_lanky)
  fh.seek(0xC9A)
  fh.write(patch_wrinkly_castle_tiny)
  fh.seek(0xCD8)
  fh.write(patch_wrinkly_castle_chunky)