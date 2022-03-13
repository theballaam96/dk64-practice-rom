.orga crcPatchROM ; ROM
.org crcPatchMemory ; RDRAM
NOP ; CRC Patch
.include "asm/bootPatch.asm" //patch boot routine to DMA our code from ROM
.headersize 0x7FFFF400 ; Same for both JP/US
.org customBootCodeStart
.include "asm/hookcode.asm" // Hook code
.headersize customCodeStart - 0x2000000
.org customCodeStart
.include "asm/boot.asm" //include modified boot code
.include "asm/objects.asm"
.close // Close the ROM file