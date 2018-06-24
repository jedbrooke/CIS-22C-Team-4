@echo off
 
set gtk_ver=gtk+-3.0
pkg-config %gtk_ver% --cflags --libs >tmp.txt
set /p pkg-info= <tmp.txt
del tmp.txt
 
rem echo %pkg-info%
g++ *.cpp -o program.exe -static -static-libgcc -static-libstdc++ -Wall %pkg-info%
program.exe
pause
