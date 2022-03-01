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
.close // Close the ROM file