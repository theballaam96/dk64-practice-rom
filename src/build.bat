@echo off
mkdir obj
set arg1=%1
echo Started: %date% %time%

python compile.py

armips asm/jump_list.asm
cd ".\..\Build\"
python build.py
python generate_watch_file.py
echo Generated Watch File
cd ".\..\src\"
armips asm/main.asm -sym symbols_map.txt
python cleanup.py
n64crc "rom/dk64-practice-rom-dev.z64"
if "%arg1%" == "--bps" (
	cd ".\..\Build\flips"
	echo Building BPS Patch
	flips --create ".\..\..\src\rom\dk64.z64" ".\..\..\src\rom\dk64-practice-rom-dev.z64" ".\..\..\src\rom\dk64-practice-rom-dev.bps"
)
echo Completed: %date% %time%