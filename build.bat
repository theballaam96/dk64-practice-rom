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
IF "%vfile%" == "0" GOTO compile
rem IF "%vfile%" == "1" GOTO compile
rem IF "%vfile%" == "2" GOTO compile
echo invalid version
GOTO finish

:compile
echo valid version

python build/symbols_generator.py
python build/screen_generator.py
python build\compile.py
build\armips.exe %jl_file%
python build\build.py
build\armips.exe %ml_file% -sym rom\dk64-practice-rom-dev.sym
rmdir /s /q .\obj > NUL
python build\correct_file_size.py
build\n64crc.exe rom\dk64-practice-rom-dev.z64
python build\dump_pointer_tables_vanilla.py
python build\dump_pointer_tables_modified.py
del rom\dk64-practice-rom-temp.z64
del rom\dk64-practice-rom.z64
if "%bps_arg%" == "--bps" (
	echo Building BPS Patch
	build\flips.exe --create "rom\temp_rom.z64" "rom\dk64-practice-rom-dev.z64" "rom\dk64-practice-rom-dev.bps"
)
del rom\temp_rom.z64

:finish
echo Completed: %date% %time%