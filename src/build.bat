mkdir obj
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/lib.c
mv lib.o obj/
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/warps/mapContainer.c
mv mapContainer.o obj/
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/warps/japes.c
mv japes.o obj/
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/warps/mapwarp_list.c
mv mapwarp_list.o obj/
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/aesthetic.c
mv aesthetic.o obj/
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/levitate.c
mv levitate.o obj/
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/activeMenu.c
mv activeMenu.o obj/
armips asm/main.asm
n64crc "rom/dk64-practice-rom-test.z64"