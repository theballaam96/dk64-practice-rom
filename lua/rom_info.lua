roms = {
    [0xD44B4FC6] = {
        rom_to_ram = 0x805FAE00-0x23000-0x2000000,
        ldr_rom = 0x1364,
        ldr_addr = 0x80000764,
        dma_func = 0x80000450,
        rom_id = "US",
    },
    [0xA28C71C6] = {
        rom_to_ram = 0x805F3E00-0x23000-0x2000000,
        ldr_rom = 0x1420,
        ldr_addr = 0x80000820,
        dma_func = 0x800004CC,
        rom_id = "PAL",
    },
    [0x919F7E74] = {
        rom_to_ram = 0x805F8600-0x23000-0x2000000,
        ldr_rom = 0x141C,
        ldr_addr = 0x8000081C,
        dma_func = 0x800004CC,
        rom_id = "JP",
    },
}