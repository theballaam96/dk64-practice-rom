.n64 // Let armips know we're coding for the N64 architecture
.open "rom/temp_rom.z64", "rom/dk64-practice-rom-temp.z64", 0 // Open the ROM file
.include "asm/jp/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.include "asm/jump_list_0.asm"