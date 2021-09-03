import os
import subprocess

# traverse whole directory
for root, dirs, files in os.walk(r'src'):
    # select file name
    for file in files:
        # check the extension of files
        if file.endswith('.c'):
            # print whole path of files
            print(os.path.join(root, file))
            cmd = ["mips64-elf-gcc", "-Wall", "-O1", "-mtune=vr4300", "-march=vr4300", "-mabi=32", "-fomit-frame-pointer", "-G0", "-c", os.path.join(root, file)];  
            p = subprocess.Popen(cmd);
            p.wait();