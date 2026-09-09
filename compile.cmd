@echo off
set WATCOM=C:\WATCOM
set INCLUDE=%WATCOM%\h;%WATCOM%\h\os2;.
set WIPFC=%WATCOM%\wipfc
set PATH=%WATCOM%\bin;%PATH%
wmake -f makefile.wat clean
wmake -f makefile.wat > make_wat.out
type make_wat.out