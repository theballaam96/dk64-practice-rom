.orga crcPatchROM ; ROM
.org crcPatchMemory ; RDRAM
NOP ; CRC Patch
.include "asm/bootPatch.asm" //patch boot routine to DMA our code from ROM
.headersize customCodeStart - 0x2000000
.org customCodeStart