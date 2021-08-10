.n64 // Let armips know we're coding for the N64 architecture
.open "rom/dk64-practice-rom.z64", "rom/dk64-practice-rom-test.z64", 0 // Open the ROM file
.include "asm/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.include "asm/bootPatch.asm" //patch boot routine to DMA our code from ROM
.headersize 0x7E5EDDE0
.org 0x805DAE00
.include "asm/boot.asm" //include modified boot code
.importobj "obj/lib.o"
.importobj "obj/mapContainer.o"
.importobj "obj/japes.o"
.importobj "obj/mapwarp_list.o"
.importobj "obj/activeMenu.o"
.importobj "obj/aesthetic.o"
.importobj "obj/levitate.o"
.close // Close the ROM file