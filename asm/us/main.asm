.n64 // Let armips know we're coding for the N64 architecture
.open "rom/dk64-practice-rom.z64", "rom/dk64-practice-rom-dev.z64", 0 // Open the ROM file
.include "asm/us/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.include "asm/main_0.asm"