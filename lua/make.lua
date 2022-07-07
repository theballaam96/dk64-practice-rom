require("lua/rom_info")

local arg = { ... }

local rom = gru.n64rom_load(arg[1])
local rom_info = roms[rom:crc32()]

-- We don't have an identiable rom here, stop patching
if rom_info == nil then
    error("invalid rom", 0)
    return 1
end

local dk_version = "dk-" .. rom_info.rom_id
print("Building " .. dk_version)

print("make " .. 
dk_version ..
" build/patch/" .. dk_version .. "/hooks.gsc")
local _,_,res = os.execute("make " .. 
                           dk_version ..
                           " build/patch/" .. dk_version .. "/hooks.gsc")
if res ~= 0 then
    error("could not build dk", 0)
end

local hooks = gru.gsc_load("build/patch/" .. dk_version .. "/hooks.gsc")

print("Applying hooks")
hooks:shift(-rom_info.rom_to_ram)
hooks:apply_be(rom)

local old_ldr = rom:copy(rom_info.ldr_rom, 0x54)
local dk = gru.blob_load("build/bin/" .. dk_version .. "/dk.bin")
local payload_rom = 0x2800000
local dk_rom = payload_rom + 0x60

print("Building Loader")

local make_ldr = string.format("make -B CPPFLAGS=' -DDMA_COPY=0x%08x -DEND=0x%08x' LDFLAGS=' -Wl,--defsym,start=0x%08x'" ..
                                " ldr-" .. dk_version, rom_info.dma_func, dk:size() + dk_rom, rom_info.ldr_addr)

print(make_ldr)
local _,_,res = os.execute(make_ldr)
if(res ~= 0) then
    error("Could not build loader", 0)
end

local ldr = gru.blob_load("build/bin/ldr-" .. dk_version .. "/ldr.bin")

print("Inserting payload")
rom:write(rom_info.ldr_rom, ldr)
rom:write(payload_rom, old_ldr)
local payload = gru.blob_load("build/bin/" .. dk_version .. "/dk.bin")
rom:write(dk_rom, dk)
rom:crc_update()

return rom, rom_info.rom_id