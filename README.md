# Donkey Kong 64 Practice ROM
Practice ROM for Donkey Kong 64 that assists with practising the game for speedrunning.

## Building Pre-requisites
1. Python (version 3 or higher) or a text editor that can run a python terminal
2. [n64chain](https://hack64.net/Thread-Importing-C-Code-Into-SM64-Using-n64chain-and-armips)

## Build Setup
1. Create a folder called `/rom` in the root of the repo
2. Place a vanilla DK64 ROM in the `/rom` directory. You must source this yourself (this file must not be marked as read only)
3. Through a command window, run `./build.bat {file_name}` in the root directory (eg. `./build.bat dk64.z64`)
4. In the `/rom` directory, the developer version of the practice rom `dk64-practice-rom-dev.z64`.

## Development Tools
Below is a list of tools that you may find useful
- [HXD](https://mh-nexus.de/en/hxd/)
- [BizHawk](http://tasvideos.org/BizHawk.html)
- [MIPS Converter](https://www.eg.bucknell.edu/~csci320/mips_web/)
- [MIPS Manual](http://math-atlas.sourceforge.net/devel/assembly/mips-iv.pdf)
