# Donkey Kong 64 Practice ROM
Practice ROM for Donkey Kong 64 that assists with practising the game for speedrunning.

## Building Pre-requisites
1. Python (version 3 or higher) or a text editor that can run a python terminal
2. [ARMIPS](https://hack64.net/Thread-Importing-C-Code-Into-SM64-Using-n64chain-and-armips)
3. mips64-elf-gcc

## Build Setup
1. Place a vanilla US DK64 ROM named `dk64.z64` in the `src>rom` directory. You must source this yourself
2. Through a command window, run ./build.bat in the `src` directory
3. In the `src>rom` directory, the developer version of the practice rom `dk64-practice-rom-dev.z64`.

## Development Tools
Below is a list of tools that you may find useful
- [HXD](https://mh-nexus.de/en/hxd/)
- [BizHawk](http://tasvideos.org/BizHawk.html)
- [MIPS Converter](https://www.eg.bucknell.edu/~csci320/mips_web/)
- [MIPS Manual](http://math-atlas.sourceforge.net/devel/assembly/mips-iv.pdf)
