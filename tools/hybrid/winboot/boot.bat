@echo off
rem boot.bat EXE: start a hybrid exe from SporeBin (run through an interactive scheduled task)
cd /d "C:\Program Files (x86)\Steam\steamapps\common\Spore\SporeBin"
start "" "%~1"
