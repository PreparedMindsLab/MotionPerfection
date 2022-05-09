rem .\extractAndPrepareFocalPoses.cmd D:\pdftesting\frames D:\pdftesting\modelposes D:\NotBackedup\EliVideo\image_times.txt D:\NotBackedup\EliVideo\GMT20210331-114231_Recording_gvo_1280x720.mp4 5309.36 D:\pdftesting\pdfs
rem %1 == tempFramesFolder
rem %2 == modelposesOutputFolder
rem %3 times.txt
rem %4 video
rem %5 timeOffset
rem %6 destination folder
rem %7 optional name for output file
IF not exist %1 (mkdir %1)
IF not exist %2 (mkdir %2)
IF not exist %6 (mkdir %6)
.\findFrame.exe -d%1 -l%3 -f%4 -t%5
rem prepareOnePDF.cmd D:\output D:\modelposes d:\workingimgefolder\findframelist.txt
call .\preparePDFs.cmd .\prepareOnePDF.cmd %6 %2 %1\%~n4%~x4_List.txt
copy %6\FORM*.pdf %~dp6\
del %6\FORM*.pdf
if "%7" NEQ "" ren %~dp6\FORM*.pdf %7.pdf
del %1\%~n4%~x4*.*
