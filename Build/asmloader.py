import subprocess
import os
import shutil
from OtherVarsWriter import updateOtherVars
from pathlib import Path

newASMName = "master-copy.asm"
oldASMName = "Master.asm"
ROMName = "dk64-practice-rom.z64"
pathExt = "../Source/"
os.chdir("../Source/")
if os.path.exists(newASMName):
    os.remove(newASMName)
shutil.copyfile(oldASMName, newASMName);
os.chdir("../Build/")

new_dir = "./../Source/"
edited_lines = [];

with open("./../Source/master-copy.asm", "r") as fh:
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

if os.path.exists("../Source/master-copy.asm"):
    os.remove("../Source/master-copy.asm")
with open("../Source/master-copy.asm", "a") as fh:
    for e in edited_lines:
        fh.write(e)

result = subprocess.check_output(["lua", "-l", "loadASM", "-e", "loadASMPatch('../Source/master-copy.asm')"])

def processBytePatch(addr, val):
    val = bytes([val])
    if addr >= 0x72C and addr < (0x72C + 8):
        diff = addr - 0x72C
        with open(ROMName, "r+b") as fh:
            fh.seek(0x132C + diff)
            fh.write(val)
        # print("Boot hook code")
    elif addr >= 0xA30 and addr < (0xA30 + 1696):
        diff = addr - 0xA30
        with open(ROMName, "r+b") as fh:
            fh.seek(0x1630 + diff)
            fh.write(val)
        # print("Expansion Pak Draw Code")
    elif addr >= 0xDE88 and addr < (0xDE88 + 3920):
        diff = addr - 0xDE88
        with open(ROMName, "r+b") as fh:
            fh.seek(0xEA88 + diff)
            fh.write(val)
        # print("Expansion Pak Picture")
    elif addr >= 0x5DAE00 and addr < (0x5DAE00 + 0x20000):
        diff = addr - 0x5DAE00
        with open(ROMName, "r+b") as fh:
            fh.seek(0x2000000 + diff)
            fh.write(val)
        # print("Heap Shrink Space")
    #else:
        #print("Attempt to write to address " + str(addr) + " with value " + str(val) + " failed")

foundHookBytes = [0];
def processHookInfo(addr,val):
    val = bytes([val])
    if addr >= 0x600674 and addr < 0x600678:
        diff = addr - 0x600674
        laghook[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x646074 and addr < 0x646078:
        diff = addr - 0x646074
        gkhook[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x6F3750 and addr < 0x6F3754:
        diff = addr - 0x6F3750
        konghook[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C374 and addr < 0x68C378:
        diff = addr - 0x68C374
        graphhook_374[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C378 and addr < 0x68C37C:
        diff = addr - 0x68C378
        graphhook_378[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C310 and addr < 0x68C314:
        diff = addr - 0x68C310
        graphhook_310[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C314 and addr < 0x68C318:
        diff = addr - 0x68C314
        graphhook_314[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C240 and addr < 0x68C244:
        diff = addr - 0x68C240
        graphhook_240[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C244 and addr < 0x68C248:
        diff = addr - 0x68C244
        graphhook_244[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x68C364 and addr < 0x68C368:
        diff = addr - 0x68C364
        graphhook_364[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x73129C and addr < 0x7312A0:
        diff = addr - 0x73129C
        flaghook[diff] = val;
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x5FC890 and addr < 0x5FC894:
        diff = addr - 0x5FC890
        pausemenuhook[diff] = val;
        foundHookBytes[0] = foundHookBytes[0] + 1;
    elif addr >= 0x665354 and addr < 0x665358:
        diff = addr - 0x665354
        speedhook[diff] = val
        foundHookBytes[0] = foundHookBytes[0] + 1;

def arrToInt(arr):
    total = 0;
    for x in arr:
        total = total * 256
        total = total + int.from_bytes(x,"big")
    return total

f = open("codeOutput.txt", "r")
laghook = [0,0,0,0];
gkhook = [0,0,0,0];
konghook = [0,0,0,0];
flaghook = [0,0,0,0];
pausemenuhook = [0,0,0,0];
speedhook = [0,0,0,0];
graphhook_374 = [0,0,0,0];
graphhook_378 = [0,0,0,0];
graphhook_310 = [0,0,0,0];
graphhook_314 = [0,0,0,0];
graphhook_240 = [0,0,0,0];
graphhook_244 = [0,0,0,0];
graphhook_364 = [0,0,0,0];

highest_heapspace = 0;

for x in f:
    line = x
    segs = line.split(":")
    if int(segs[0]) < 0x5FAE00 and int(segs[0]) > highest_heapspace:
        highest_heapspace = int(segs[0])
    processHookInfo(int(segs[0]),int(segs[1]))

new_end = (highest_heapspace - 0x5DAE00) + 0x2000000 + 1;
if os.path.exists("../Source/Features/EndLoadingSpot.asm"):
  os.remove("../Source/Features/EndLoadingSpot.asm")
with open("../Source/Features/EndLoadingSpot.asm", "a") as fh:
    fh.write("LI    a1, " + str(hex(new_end)))

graphhooks = [
    arrToInt(graphhook_374),
    arrToInt(graphhook_378),
    arrToInt(graphhook_310),
    arrToInt(graphhook_314),
    arrToInt(graphhook_240),
    arrToInt(graphhook_244),
    arrToInt(graphhook_364)
]

if foundHookBytes[0] >= 40:
    updateOtherVars(arrToInt(laghook),arrToInt(gkhook),arrToInt(konghook),arrToInt(flaghook),arrToInt(pausemenuhook),arrToInt(speedhook),graphhooks,False)

    result = subprocess.check_output(["lua", "-l", "loadASM", "-e", "loadASMPatch('../Source/master-copy.asm')"])
    with open("codeOutput.txt","r") as f:
        for x in f:
            line = x
            segs = line.split(":")
            processBytePatch(int(segs[0]), int(segs[1]))
    updateOtherVars(arrToInt(laghook),arrToInt(gkhook),arrToInt(konghook),arrToInt(flaghook),arrToInt(pausemenuhook),arrToInt(speedhook),graphhooks,True)
    if os.path.exists("codeOutput.txt"):
        os.remove("codeOutput.txt")
    if os.path.exists("../Source/master-copy.asm"):
        os.remove("../Source/master-copy.asm")
else:
    print("Not all hooks found: " + str(foundHookBytes[0]))
