rem D:\modelposes D:\imageworkingfolder\GMT20210331-114231_Recording_gvo_1280x720.mp4 10 09 10 1 1 2 3 4 5
rem                                                                                    9 08 09 1 1 2 3 4 5
rem       %1                     %1                                                  %1 %2 %3 %4 %5%67 8 9
SETLOCAL ENABLEEXTENSIONS
SET me=%~n0
SET parent=%~dp0
@echo off
set posedir=%1
shift
set filepathname=%1
shift
if "%5" NEQ "" (
    copy /y /b %filepathname%_1_%2_%5.png %posedir%\Position%3_%5.png
    del %filepathname%_1_%2_%5.png
)
if "%6" NEQ "" (
    copy /y /b %filepathname%_1_%2_%6.png %posedir%\Position%3_%6.png
    del %filepathname%_1_%2_%6.png
)
if "%7" NEQ "" (
    copy /y /b %filepathname%_1_%2_%7.png %posedir%\Position%3_%7.png
    del %filepathname%_1_%2_%7.png
)
if "%8" NEQ "" (
    copy /y /b %filepathname%_1_%2_%8.png %posedir%\Position%3_%8.png
    del %filepathname%_1_%2_%8.png
)
if "%9" NEQ "" (
    copy /y /b %filepathname%_1_%2_%9.png %posedir%\Position%3_%9.png
    del %filepathname%_1_%2_%9.png
)
