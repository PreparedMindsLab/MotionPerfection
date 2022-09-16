# MotionPerfection

This software tool enables users to easily visualise, analyse, annotate and record a practice routine (dance, workout, martial arts, etc.). The focal participant imitates and follows the movement of a model video whilst being video recorded. The software can then extract certain key frames from both videos and create multi-page PDF assessment forms for experts to easily assess the performance of the focal participant. 

A tutorial video is available showing how to use the software, and the results that can be acheived.
https://www.youtube.com/watch?v=qAehvhGQZGs

## Important
- **MikTex** Copyright notice...this project includes a copy of MikTex, bundled here for convenience. It was originally downloaded then configured according to the instructions for creating a portable image. It was then run, and therefore it automatically installed any support libraries needed for MikText to convert to PDFs. The image including those additional components was then added to this repository. Note...this version is static and will not include any subsequent updates which may be added to the main MikTex project.
- **PySimpleGUI** Acknowledgement...The GUI and installer icluded in this project are built using PySimpleGUI, which is distributed under the GNU Lesser General Public License (LGPL 3) +. 
- **PyInstaller** Acknowledgement... The GUI, installer and PDFMerger in this project are compiled into executables (.exe) using PyInstaller, which is covered under both GPL 2.0 License (with exception that allows it to build commercial products) as well as the Apache License, version 2.0.

## Instructions

### Step 0: Installation
- Download the code image and install Motion Perfection by running setup.exe. 

Alternatively, you can use the command line to install the software:
- Open a command line window (cmd or powershell) and cd to the downloaded folder. 
- Unpack the tools into a functional directory (say D:\motionPerfection) by running the command
createWorkingFolder.cmd D:\motionPerfection


### Step 1: Preparation
- Create a folder to be used as the Working Folder. The software will use this folder to store temporary files and will also output the final PDFs in this folder. Additional sub-folders .\modelposes, .\frames, and .\pdfs will be automatically created in the Working Folder later on.
- Gather the videos of the performance sessions into a convenient folder.
- To sync focal and model video, it is essential for the software to know the exact moment each performance starts. You can either 1. insert a trigger image (for example the included fixation_resized.png) into each video, **such that the trigger image ends one frame before the performance starts**, or 2. note down the delay between start of video and beginning of performance as the **time offset**.
- Now that model and focal videos can be synchronised, it is time to decide on the key frames that you want to analyse. Say these are at 30.1, 45.3 and 67.5 seconds into the performance. Up to 99 such poses can be accumulated. Each pose will result into a page in the final PDF form.
- Consider the times before and after those perfect key times which may be considered to be early, very early, late and very late. Say a tenth of a second and a quarter of a second before and after. The offsets will then be -250, -100, 0, +100 and +250 ms relative to the pose times.
- Compose the frame extraction list of times in a .txt file, one time per line. These will be expressed in milliseconds from the start of the performance…hence the text file for the above mentioned example will be:

29850 \
30000 \
30100 \
30200 \
30350 \
45050 \
45200 \
45300 \
45400 \
45550 \
67250 \
67400 \
67500 \
67600 \
67750 


### Step 2: Prepare model poses
- The key frames (poses) of the model video are extracted first, as a separate step from extracting focal poses and generating PDFs. This is because multiple focal participant might follow the same model video, so it is redundant to extract the same model poses for each of these focal participants. 
- Open MotionPerfection.exe, and select the Working Folder and the Frame Extraction List prepared in **Step 1: Preparation**.
- In "Prepare Model Poses" tab, select the model video and either type in time offset or choose trigger image if your video has a trigger image embedded.
- Press the "Prepare Model Poses" button, upon which the software will create a subfolder \modelposes in your chosen working directory and output the final model poses in this subfolder.
- **Note:** If you extract from a new model video, the extracted framed in \modelposes will be overwritten. It might be wise to create a new Working Folder for each model video.

Alternatively, if you want to use command line:
- Assuming your software is intalled in D:\danceTools, your Working Folder is D:\performancePDFs, your time offset is 1234.56 seconds, and the video to be modelVideo.mp4 found in the folder E:\recordings.
- Open a command line window (cmd or powershell) and make D:\danceTools the current directory
- Enter into the command line: \
  .\extractAndPrepareModelPoses.cmd D:\performancePDFs\frames D:\performancePDFs\modelposes E:\recordings\image_times.txt E:\recordings\modelVideo.mp4 1234.56
- This will create a series of PositionXX_N.png images in the folder D:\performancePDFs\modelposes


### Step 3: Prepare focal poses and PDF
- This will extract frames at specific times from each video recording the focal performance, and prepare a multi-page assessment form PDF.
- In "Prepare Focal Poses and PDF" tab, select the focal video and either type in time offset or choose trigger image if your video has a trigger image embedded.
- Press the "Prepare PDFs" button, upon which the software will create a subfolder \PDFs in your chosen working directory and output the final PDF in this subfolder.

Alternatively, if you want to use command line:
- Assuming your software is intalled in D:\danceTools, your Working Folder is D:\performancePDFs, your time offset is 2345.67 seconds, and the video to be focalVideo.mp4 found in the folder E:\recordings.
- Open a command line window (cmd or powershell) and make D:\danceTools the current directory
- Enter into the command line: \
  .\extractAndPrepareFocalPoses.cmd D:\performancePDFs\frames D:\performancePDFs\modelposes E:\recordings\image_times.txt E:\recordings\focalVideo.mp4 2345.67 D:\performancePDFs\pdfs 
- This will create an editable assessment PDF showing each of the participant poses compared with the equivalent model poses in the folder D:\performancePDFs\PDFs
- Repeat for each participant’s video

### Testing: To check system can rodcue the correct output
- Two test videos have been provided that contain simple black frames with a white number showing th ecurrent frame number. These have been produced at different frame rates.
- The two command lines below will extract from test.avi as if it were a model video and from test2.avi as a focal video to create a PDF file.
-  .\extractAndPrepareModelPoses.cmd D:\performancePDFs\frames D:\performancePDFs\modelposes D:\danceTools\testing\image_times_test.txt D:\danceTools\testing\test.avi 10
-  .\extractAndPrepareFocalPoses.cmd D:\performancePDFs\frames D:\performancePDFs\modelposes D:\danceTools\testing\image_times_test.txt D:\danceTools\testing\test2.avi 10 D:\performancePDFs\pdfs 
- The resulting PDF should be the same as "Test_result.pdf" supplied in the testing folder.
