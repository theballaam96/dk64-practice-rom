# Donkey Kong 64 Practice ROM
Practice ROM for Donkey Kong 64 that assists with practising the game. Written in assembler but segmented into modular files.

## Building Pre-requisites
```
1. Python (version 3 or higher) or a text editor that can run a python terminal
2. [ARMIPS](https://hack64.net/Thread-Importing-C-Code-Into-SM64-Using-n64chain-and-armips)
3. mips64-elf-gcc
```

## Build Setup
1. Run build.py in the "Build" directory
2. In the "Build" directory should be a fully converted practice ROM (Note that this will be a development version of the practice ROM. As such, the build may be buggy depending on the state of the ASM at the time)

## Development Pre-requisites
```
1. Python (version 3 or higher) or a text editor that can run a python terminal
2. Some text editor
```
## Development Setup
1. Setup a version of [BizHawk](http://tasvideos.org/Bizhawk) (Some version between 1.11.8.1 and 1.13.2 works best for DK64)
2. Download [ScriptHawk](https://github.com/Isotarge/ScriptHawk)
3. Run [personaliseASM.py](https://github.com/theballaam96/dk64-practice-rom/blob/main/personaliseASM.py), this will open a few file directory prompts
	a. For the first prompt, select your **ScriptHawk** directory
	b. For the second prompt, select your **Practice ROM** directory
	This will modify the master assembler file to account for your system file structure. You will need to re-run this script every time you shift your ScriptHawk folder or your Practice ROM folder
4. Open BizHawk, then a Heap Shrink DK64 ROM. Open the LUA Console, and then ScriptHawk.lua from your ScriptHawk directory and run the following command
```
console.clear();loadASMPatch();
```
5.  Select the master.asm file in the ```Source``` directory
