@echo off
set src_file=%1
set bps_arg=%2
echo Started: %date% %time%
mkdir obj

IF "%src_file%" == "temp_rom.z64" GOTO invalid_name
GOTO valid_name

:invalid_name
echo ROM Name can't be "temp_rom.z64"
GOTO finish

:valid_name
echo %src_file% > .rom
python detect_version.py
set /p vfile=< .version
set jl_file="asm/us/jump_list.asm"
set ml_file="asm/us/main.asm"
set final_rom="rom\dk64-practice-rom-dev-us.z64"
set final_bps="rom\dk64-practice-rom-dev-us.bps"
IF "%vfile%" == "0" GOTO compile
rem IF "%vfile%" == "1" GOTO compile
set jl_file="asm/jp/jump_list.asm"
set ml_file="asm/jp/main.asm"
set final_rom="rom\dk64-practice-rom-dev-jp.z64"
set final_bps="rom\dk64-practice-rom-dev-jp.bps"
IF "%vfile%" == "2" GOTO compile
echo invalid version
GOTO finish

:compile
echo valid version

python build/heap_handle.py
set /p heap_size=< heap.shrink
echo Honey, I shrunk the heap by %heap_size% bytes
python build/symbols_generator.py
python build/screen_generator.py
python build\compile.py
build\armips.exe %jl_file%
python build\build.py
build\armips.exe %ml_file% -sym rom\dk64-practice-rom-dev.sym
rmdir /s /q .\obj > NUL
python build\correct_file_size.py
build\n64crc.exe rom\dk64-practice-rom-dev.z64

if "%vfile" == "0" GOTO dump
GOTO cleanup

:dump
python build\dump_pointer_tables_vanilla.py
python build\dump_pointer_tables_modified.py

:cleanup
del heap.shrink
del rom\dk64-practice-rom-temp.z64
del rom\dk64-practice-rom.z64
if "%bps_arg%" == "--bps" (
	echo Building BPS Patch
	build\flips.exe --create "rom\temp_rom.z64" "rom\dk64-practice-rom-dev.z64" %final_bps%
)
python build/segmentFile.py

:finish
echo Completed: %date% %time%