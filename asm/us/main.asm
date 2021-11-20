.n64 // Let armips know we're coding for the N64 architecture
.open "rom/dk64-practice-rom.z64", "rom/dk64-practice-rom-dev.z64", 0 // Open the ROM file
.include "asm/us/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.orga 0x3154 ; ROM
.org 0x80002554 ; RDRAM
NOP ; CRC Patch
.include "asm/us/bootPatch.asm" //patch boot routine to DMA our code from ROM
.headersize 0x7FFFF400
.org 0x80000A30
.include "asm/us/hookcode.asm" // Hook code
.headersize 0x7E5DAE00
.org 0x805DAE00
.include "asm/us/boot.asm" //include modified boot code
.include "asm/objects.asm"
.close // Close the ROM file