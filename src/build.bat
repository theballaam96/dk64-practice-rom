@echo off
mkdir obj
set arg1=%1
echo Started: %date% %time%

python compile.py

move *.o obj/

armips asm/jump_list.asm
cd ".\..\Build\"
python build.py
if "%arg1%" == "--generate-watch" (
	python generate_watch_file.py
	echo Generated Watch File
)
cd ".\..\src\"
armips asm/main.asm
python cleanup.py
n64crc "rom/dk64-practice-rom-dev.z64"
echo Completed: %date% %time%