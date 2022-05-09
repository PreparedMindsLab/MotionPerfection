rem prepareOneModelPose.cmd D:\modelposes d:\workingimgefolder\findframelist.txt
SETLOCAL ENABLEEXTENSIONS
SET me=%~n0
SET parent=%~dp0
@echo off
set argsOK=1
if "%1" EQU "" set argsOK=0
if "%2" EQU "" set argsOK=0
if "%3" EQU "" set argsOK=0
if "%argsOK%" NEQ "1" (
    echo missing arguments, needed
    echo %me% prepareOneModelPose.cmd modelposeInputFolder findFrameList.txt
) ELSE (
    for /f "Tokens=* Delims=" %%x in (%3) do (
        call %parent%%1 %2 %%x
    )
)
