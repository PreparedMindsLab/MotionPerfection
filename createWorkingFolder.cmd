rem createWorkingFolder.cmd D:\motionPerfection
echo off
SETLOCAL ENABLEEXTENSIONS
SET me=%~n0
SET parent=%~dp0
set argsOK=1
if "%1" EQU "" set argsOK=0
if "%argsOK%" NEQ "1" (
    echo missing arguments, needed
    echo %me% pathToOutputfolder
) ELSE (
    mkdir %1
    copy %parent%\src\templates\* %1
    copy %parent%\src\scripts\* %1
    copy %parent%\src\bin\* %1
    copy %parent%\src\findFrame\x64\Release\* %1
    copy %parent%\src\GUI\dist\* %1
    echo copying miktex....this takes a while
    mkdir %1\miktex-portable\
    xcopy %parent%\miktex-portable\* %1\miktex-portable\ /s /y /q
    echo miktex done...
)
echo
echo copy completed, now you can change directory to %1 to use this tool, eg.
echo cd %1
echo and...assuming a destination folder of D:\performancePDFs
echo .\extractAndPrepareModelPoses.cmd D:\performancePDFs\frames D:\performancePDFs\modelposes E:\recordings\image_times.txt E:\recordings\focalVideo.mp4 134.56
echo - to create the model poses for a performance into the folder D:\motionPerfection\modelposes
echo ... then ...
echo .\extractAndPrepareFocalPoses.cmd D:\performancePDFs\frames D:\performancePDFs\modelposes E:\recordings\image_times.txt E:\recordings\focalVideo.mp4 2345.67 D:\performancePDFs\pdfs 
echo for each participant video to create an editable assessment PDF
