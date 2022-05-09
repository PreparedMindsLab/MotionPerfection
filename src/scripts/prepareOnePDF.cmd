rem D:\output D:\modelposes D:\imageworkingfolder\GMT20210331-114231_Recording_gvo_1280x720.mp4 10 09 10 1 1 2 3 4 5
rem                                                                                              9 08 09 1 1 2 3 4 5
rem        %1      %1                     %1                                                    %1 %2 %3 %4 %5%67 8 9
SETLOCAL ENABLEEXTENSIONS
SET me=%~n0
SET parent=%~dp0
@echo off
set destdir=%1
shift
set posedir=%1
shift
set filepathname=%1
set filename=%~n1
shift
if "%5" NEQ "" (copy /y /b %filepathname%_1_%2_%5.png student_1.png)
if "%6" NEQ "" (copy /y /b %filepathname%_1_%2_%6.png student_2.png)
if "%7" NEQ "" (copy /y /b %filepathname%_1_%2_%7.png student_3.png)
if "%8" NEQ "" (copy /y /b %filepathname%_1_%2_%8.png student_4.png)
if "%9" NEQ "" (copy /y /b %filepathname%_1_%2_%9.png student_5.png)
copy /y /b %posedir%\Position%3_1.png modelpose.png
copy /y /b %posedir%\Position%3_2.png modelpose2.png
copy /y /b %posedir%\Position%3_3.png modelpose3.png
copy /y /b %posedir%\Position%3_4.png modelpose4.png
copy /y /b %posedir%\Position%3_5.png modelpose5.png
echo %1 > partnum.txt
copy /b /y annotation_part1.txt + partnum.txt + annotation_part2.txt template.tex
.\miktex-portable\texmfs\install\miktex\bin\x64\pdflatex template.tex --quiet
copy /y /b template.pdf %destdir%\%filename%_1_%3.pdf
del modelpose.png
del modelpose?.png
del student_?.png
del partnum.txt
del template.tex
del template.aux
del template.log
del template.out
del template.pdf
