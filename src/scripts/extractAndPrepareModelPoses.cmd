rem .\extractAndPrepareModelPoses.cmd D:\pdftesting\frames D:\pdftesting\modelposes D:\NotBackedup\EliVideo\image_times.txt D:\NotBackedup\EliVideo\GMT20210331-114231_Recording_avo_640x360.mp4 5309.36

rem %1 == tempFramesFolder
rem %2 == modelposesOutputFolder
rem %3 times.txt
rem %4 video
rem %5 timeOffset
IF not exist %1 (mkdir %1)
IF not exist %2 (mkdir %2)
.\findFrame.exe -d%1 -l%3 -f%4 -t%5
rem prepareOneModelPose.cmd D:\modelposes d:\workingimgefolder\findframelist.txt
call .\prepareModelPoses.cmd .\prepareOneModelPose.cmd %2 %1\%~n4%~x4_List.txt
del %1\%~n4%~x4*.*
