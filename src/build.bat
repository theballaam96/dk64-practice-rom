@echo off
mkdir obj
set src_file=%1
set bps_arg=%2
echo Started: %date% %time%

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

python compile.py

armips %jl_file%
cd ".\..\Build\"
python build.py
python generate_watch_file.py
echo Generated Watch File
cd ".\..\src\"
armips %ml_file% -sym symbols_map.txt
python cleanup.py
n64crc "rom/dk64-practice-rom-dev.z64"
if "%bps_arg%" == "--bps" (
	cd ".\..\Build\flips"
	echo Building BPS Patch
	flips --create ".\..\..\src\rom\dk64.z64" ".\..\..\src\rom\dk64-practice-rom-dev.z64" ".\..\..\src\rom\dk64-practice-rom-dev.bps"
)

:finish
echo Completed: %date% %time%