rem .\extractAndPrepareFocalPoses.cmd D:\pdftesting\frames D:\pdftesting\modelposes D:\NotBackedup\EliVideo\image_times.txt D:\NotBackedup\EliVideo\GMT20210331-114231_Recording_gvo_1280x720.mp4 5309.36 D:\pdftesting\pdfs

rem %1 == tempFramesFolder
rem %2 == modelposesOutputFolder
rem %3 times.txt
rem %4 video
rem %5 timeOffset
rem %6 destination folder
IF not exist %1 (mkdir %1)
IF not exist %2 (mkdir %2)
IF not exist %6 (mkdir %6)
.\findFrame.exe -d%1 -l%3 -f%4 -i%5 -r%4
rem prepareOnePDF.cmd D:\output D:\modelposes d:\workingimgefolder\findframelist.txt
call .\preparePDFs.cmd .\prepareOnePDF.cmd %6 %2 %1\%~n4%~x4_List.txt
del %1\%~n4%~x4*.*
