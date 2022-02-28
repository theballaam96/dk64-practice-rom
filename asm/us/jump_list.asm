.n64 // Let armips know we're coding for the N64 architecture
.open "rom/temp_rom.z64", "rom/dk64-practice-rom-temp.z64", 0 // Open the ROM file
.include "asm/us/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.headersize 0x7FFFF400
.org 0x80000A30
.include "asm/us/hookcode.asm" // Hook code
.headersize 0x7E5DAE00
.org 0x805DAE00
.include "asm/us/boot.asm" //include modified boot code
.include "asm/objects.asm"
.headersize 0x7E5FBE00 // Jump instructions located at 0x1FFF000 in ROM. Header size calculated by org_dest - rom_dest
.org 0x805FAE00
.include "asm/us/jump_instructions.asm" // jump instructions
.close // Close the ROM file