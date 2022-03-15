.headersize customCodeStart - 0x2000000
.org customCodeStart
.include "asm/boot.asm" //include modified boot code
.include "asm/objects.asm"
.close // Close the ROM file