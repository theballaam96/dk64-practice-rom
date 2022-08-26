import os

cwd = os.getcwd()
pre = "./"
srch = "\scripts"
if cwd[-len(srch):] == srch or cwd[-len(srch):] == srch.replace("\\","/"):
    pre = "../"
for f in os.listdir(f"{pre}src"):
    if f[-2:] == ".c":
        l_list = []
        with open(f"{pre}src/{f}","r") as fh:
            ln = fh.readlines()
            for l in ln:
                if "include/common.h" in l and "#include" in l:
                    l_list.append("#include \"include/common.h\"\n")
                else:
                    l_list.append(l)
        with open(f"{pre}/src/{f}","w") as fh:
            for l in l_list:
                fh.write(l)
