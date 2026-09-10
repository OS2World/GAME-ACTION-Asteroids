@echo off
rem compile.cmd - Build ASTEROID for OS/2 using Open Watcom
rem Output goes to bin\, log to compile-wat.log

set LOGFILE=compile-wat.log
echo Build started: %DATE% %TIME% > %LOGFILE%

rem Auto-detect Open Watcom installation
if exist C:\WATCOM\bin\wcc386.exe set WATCOM=C:\WATCOM
if exist D:\WATCOM\bin\wcc386.exe set WATCOM=D:\WATCOM
if "%WATCOM%"=="" (
    echo ERROR: Open Watcom not found. Set WATCOM environment variable. >> %LOGFILE%
    echo ERROR: Open Watcom not found. Set WATCOM environment variable.
    exit /b 1
)

set INCLUDE=%WATCOM%\h;%WATCOM%\h\os2
set PATH=%WATCOM%\bin;%PATH%
set WIPFC=%WATCOM%\wipfc

echo Using WATCOM=%WATCOM% >> %LOGFILE%

wmake -f makefile.wat clean >> %LOGFILE% 2>&1
wmake -f makefile.wat all >> %LOGFILE% 2>&1
if errorlevel 1 (
    echo BUILD FAILED - see %LOGFILE%
    type %LOGFILE%
    exit /b 1
)

echo Build OK >> %LOGFILE%
echo Build OK
