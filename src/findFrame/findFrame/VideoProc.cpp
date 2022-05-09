
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <list>


//#define TRYSUBIMAGEPROC

using namespace cv;
using namespace std;
using namespace System;

namespace VideoProc {
	struct syncMark {
		int startFrame;
		int endFrame;
		float average;
		float varriance;
	};
	std::vector<float> accumulator;
	std::vector<syncMark *> syncMarks;
	bool amInMarker;
	bool seenDrop;
	double frameComparison = -1;
	double previousFrameComparison = -1;
	double markerTotal;
	int markStart;
	int markerCount;
	bool markersChanged = false;
	bool scanAccelerated = false;
	int acceleratedStep = 1;
	float acceleratedRewind = 4.0f;

	void halfSizeFrame(Mat *inputClr);
	void reizeFrame(Mat *inputClr, int nRows, int nCols);
	void setSubSampling(int NthFrame, bool halfSized);
	void decorateFrameDisplay(Mat dispFrame, int frameNumber, float framesPerSec, float matchFactor);
	bool showOneVideoFrame(bool showIt);
	bool processNVideoFrame(int num);
	bool  processOneVideoFrame();
	void setMarkerQty(int qty);
	float getFPS();
	int getEndFrameNum();
	bool inputOpened();

	std::vector<float> *readTimes(char *timesFilename);
	std::vector<float> *readSubImageCoords(char *timesFilename);

	int getEndFrame();
	float getEndMS();
	int getStartFrame();
	float getStartMS();

	Mat frame; //current frame
	Mat refFrame;
	Mat oneFrame;

	float mFramesPerSec;
	int mLastFrame = -1;
	char *videoFrameName = "Frame";
	char *refFrameName = "refFrame";
	Point subImageTL;
	Point subImageBR;
	VideoCapture capture;
	VideoCapture vidreader;
	int frameNum;
	bool isOpen = false;
	int mFrameRateDivision = 1;
	bool mHalfSize = false;
	int rawPixelsW;
	int rawPixelsH;
	int pixelsW;
	int pixelsH;

	int refPixelsW;
	int refPixelsH;


	void setSubSampling(int NthFrame, bool halfSized) {
		if (rawPixelsW < 1000) {
			halfSized = false;
		}
		bool redraw = (mHalfSize != halfSized);
		mFrameRateDivision = NthFrame;
		mHalfSize = halfSized;
		if (redraw) {
			halfSizeFrame(&frame);
			pixelsW = frame.cols;
			pixelsH = frame.rows;
			reizeFrame(&refFrame, pixelsH, pixelsW);
			imshow(refFrameName, refFrame);

		}
	}

	bool inputOpened() {
		return isOpen;
	}

	void setMarkerQty(int qty) {
		markerCount = qty;
	}

	bool haveAtLeastOneMarker() {
		return syncMarks.size() > 0;
	}
	int getMarkerCount() {
		return syncMarks.size();
	}
	bool getMarkersChanged() {
		bool retv = markersChanged;
		markersChanged = false;
		return retv;
	}
	void setMarkersChanged() {
		markersChanged = true;
	}
	int getFrameNum() {
		return frameNum;
	}

	int getEndFrameNum() 
	{
		return mLastFrame;
	}


	bool showOneVideoFrame(bool showIt) {
		bool retv = false;
		if (isOpen && capture.read(frame)) {
			halfSizeFrame(&frame);
			frameNum++;
			if (showIt)
				imshow(videoFrameName, frame);
			retv = true;
		}
		return retv;
	}
	float getFPS() {
		return mFramesPerSec;
	}
	int getHighestMark(float skipLevel) {
		float minAverage = 0; // silly level to ensure we will find the min
		int retv = -1;
		for (int idx = 0; idx < syncMarks.size(); idx++) {
			if (syncMarks[idx]->average > skipLevel) {
				if (syncMarks[idx]->average > minAverage) {
					minAverage = syncMarks[idx]->average;
					retv = idx;
				}
			}
		}
		return retv;
	}
	int getLowestMark(float skipLevel) {
		float minAverage = 1000; // silly level to ensure we will find the min
		int retv = -1;
		for (int idx = 0; idx < syncMarks.size(); idx++) {
			if (syncMarks[idx]->average > skipLevel) {
				if (syncMarks[idx]->average < minAverage) {
					minAverage = syncMarks[idx]->average;
					retv = idx;
				}
			}
		}
		return retv;
	}
	void addIfLowest(syncMark *pOneMark) {
		if (syncMarks.size() >= markerCount) {
			int foundGreater = getHighestMark(pOneMark->average);
			if (foundGreater >= 0) {
				syncMarks[foundGreater] = pOneMark;
				setMarkersChanged();
			}
		}
		else {
			syncMarks.push_back(pOneMark);
			setMarkersChanged();
		}
	}
	int getEndFrame() {
		int retv = 0;
		int idx = getLowestMark(0);
		if (idx >= 0) {
			retv = syncMarks[idx]->endFrame;
		}
		return retv;
	}
	int getEndFrame(int idx) {
		int retv = 0;
		retv = syncMarks[idx]->endFrame;
		return retv;
	}
	float getEndMS() {
		int retv = 0;
		int idx = getLowestMark(0);
		if (idx >= 0) {
			retv = syncMarks[idx]->endFrame;
		}
		return 1000 * retv / mFramesPerSec;

	}
	float getEndMS(int idx) {
		int retv = 0;
		retv = syncMarks[idx]->endFrame;
		return 1000 * retv / mFramesPerSec;

	}
	int getStartFrame() {
		int retv = 0;
		int idx = getLowestMark(0);
		if (idx >= 0) {
			retv = syncMarks[idx]->startFrame;
		}
		return retv;
	}
	int getStartFrame(int idx) {
		int retv = 0;
		retv = syncMarks[idx]->startFrame;
		return retv;
	}
	float getStartMS() {
		int retv = 0;
		int idx = getLowestMark(0);
		if (idx >= 0) {
			retv = syncMarks[idx]->startFrame;
		}
		return 1000 * retv / mFramesPerSec;

	}
	float getStartMS(int idx) {
		int retv = 0;
		retv = syncMarks[idx]->startFrame;
		return 1000 * retv / mFramesPerSec;

	}
	float getQual() {
		float retv = 0;
		int idx = getLowestMark(0);
		if (idx >= 0) {
			retv = syncMarks[idx]->average;
		}
		return retv;

	}
	float getQual(int idx) {
		return syncMarks[idx]->average;
	}

	int frameDropDetected = 0;
	bool  processOneVideoFrame() {
		bool retv = false;
		if (isOpen) {
			Mat comparison;
			absdiff(frame, refFrame, comparison);
//			imshow("comparison", comparison);
			int fractionH = 10;
			int fractionV = 10;
			int startElementH = 3; // 4th
			int endElementH = 7; // 7th
			int startElementVT = 1; // 4th
			int endElementVT = 2; // 5th
			int startElementVB = 8; // 4th
			int endElementVB = 9; // 5th

			Mat comparisonSub = comparison.rowRange((startElementVT * pixelsH) / fractionH, (endElementVT * pixelsH) / fractionH).colRange((startElementH * pixelsW) / fractionH, (endElementH * pixelsW) / fractionH);
			double deltaRGB_TL = sum(comparisonSub)[0];
//			imshow("top", comparisonSub);
			deltaRGB_TL /= ((comparisonSub.rows * comparisonSub.cols));
			comparisonSub = comparison.rowRange((startElementVB * pixelsH) / fractionV, (endElementVB * pixelsH) / fractionV).colRange((startElementH * pixelsW) / fractionH, (endElementH * pixelsW) / fractionH);
			double deltaRGB_BR = sum(comparisonSub)[0];
			//imshow("Bottom", comparisonSub);
			deltaRGB_BR /= ((comparisonSub.rows * comparisonSub.cols));
			comparisonSub = comparison.rowRange((startElementVT * pixelsH) / fractionV, (endElementVB * pixelsH) / fractionV).colRange((startElementH * pixelsW) / fractionH, (endElementH * pixelsW) / fractionH);
			double deltaRGB = sum(comparisonSub)[0];
//			imshow("comparisonPart", comparisonSub);
			frameComparison = deltaRGB / (comparisonSub.rows * comparisonSub.cols);
			deltaRGB = frameComparison - previousFrameComparison;
			if (previousFrameComparison > 0) {
				if (seenDrop) {
					if (!amInMarker && (deltaRGB_TL + deltaRGB_BR) < 15) { // nearly black
						amInMarker = true;
						markerTotal = 0;
						markStart = frameNum;
					}
					if (amInMarker) {
						if (deltaRGB > 0 && Math::Abs(deltaRGB / previousFrameComparison) > 0.5) {
							seenDrop = false;
							amInMarker = false;
							if ((frameNum - markStart) > (getFPS() / 2)) { // only pay attention to sections longer than 1 second
								syncMark *pOneMark = new syncMark;
								pOneMark->startFrame = markStart;
								pOneMark->endFrame = frameNum;
								pOneMark->average = markerTotal / (frameNum - markStart);
								addIfLowest(pOneMark);
							}
							scanAccelerated = true; // out the back end of marker, so resume fast scan
						}
						else {

							markerTotal += frameComparison;
						}
					}
					else {
						int rewindDistance = acceleratedRewind * mFramesPerSec;
						if (frameNum > frameDropDetected + (acceleratedRewind * mFramesPerSec)) {
							// scanned beyond the window in slow mode and nothing happened yet, so bac to accelerated
							scanAccelerated = true; // out the back end of marker, so resume fast scan
							seenDrop = false;
						}
					}
				}
				else {
					if (deltaRGB < 0 && Math::Abs(deltaRGB / previousFrameComparison) > 0.5) {
						retv = true;
						frameDropDetected = frameNum;
						if (!scanAccelerated) {
							seenDrop = true;
						}
					}
				}
			}
			previousFrameComparison = frameComparison;
			decorateFrameDisplay(frame, frameNum, mFramesPerSec, frameComparison);
			imshow(videoFrameName, frame);
		}
		return retv;
	}

	void showNVideoFrame(int num) {
		for (int idx = 0; idx < num; idx++) {
			showOneVideoFrame(true);
		}
	}
	void setVideoFrame(int relativeFrame) {
		if (isOpen) {
			frameNum = capture.get(CAP_PROP_POS_FRAMES);
			frameNum += relativeFrame;
			capture.set(CAP_PROP_POS_FRAMES, frameNum);
			frameNum = capture.get(CAP_PROP_POS_FRAMES);
		}

	}
	void setVideoFrameAbs(int absFrame) {
		if (isOpen) {
			frameNum = absFrame;
			capture.set(CAP_PROP_POS_FRAMES, frameNum);
			frameNum = capture.get(CAP_PROP_POS_FRAMES);
		}

	}
	void decorateFrameDisplay(Mat dispFrame, int frameNumber, float framesPerSec, float matchFactor) {
		stringstream ss;
		rectangle(dispFrame, cv::Point(10, 2), cv::Point(800, 20),
			cv::Scalar(255, 255, 255), -1);
		float currTime = (int)(100 * frameNumber / framesPerSec);
		currTime /= 100;
		matchFactor = (int)(100 * matchFactor);
		matchFactor /= 100;
		ss << frameNumber << " / " << framesPerSec << " = " << currTime << "s " << matchFactor;
		//float minAverage = 0;
		//for (int idx = 0; idx < markerCount; idx++) {
		//	int syncIdx = getLowestMark(minAverage);
		//	if (syncIdx < 0)
		//		break;
		//	minAverage = syncMarks[syncIdx]->average;
		//	ss << " " << syncMarks[syncIdx]->startFrame << " " << syncMarks[syncIdx]->endFrame << " " << syncMarks[syncIdx]->average;
		//}
		string frameNumberString = ss.str();
		putText(dispFrame, frameNumberString.c_str(), cv::Point(15, 15),
			FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
	}

	void halfSizeFrame(Mat *inputClr) {
		//		imshow("d1", *inputClr);
		if (mHalfSize) {
			Mat tmp = inputClr->clone();
			//		imshow("d2", tmp);
			//blur(*inputClr, tmp, Size(5, 5), Point(-1, -1));
			resize(tmp, tmp, cv::Size(tmp.cols * 0.5, tmp.rows * 0.5), 0, 0, CV_INTER_LINEAR);
			*inputClr = tmp;
		}
	}
	void reizeFrame(Mat *inputClr, int nRows, int nCols) {
		Mat tmp = inputClr->clone();
		//		imshow("d2", tmp);
		//blur(*inputClr, tmp, Size(5, 5), Point(-1, -1));
		resize(tmp, tmp, cv::Size(nCols, nRows), 0, 0, CV_INTER_LINEAR);
		*inputClr = tmp;
	}
	int rewindProcessLimit = 0;
	bool processNVideoFrame(int numFrames) {
		bool retv = true;
		for (int idx = 0; retv && idx < numFrames; idx++) {
			if (scanAccelerated)
				setVideoFrame(acceleratedStep);
			retv = showOneVideoFrame(false);
			if (retv) {
				bool willScanAccelerated = scanAccelerated;
				bool foundDrop = processOneVideoFrame();
				if (foundDrop && willScanAccelerated) {
					if (frameNum > rewindProcessLimit) {
						rewindProcessLimit = frameNum;
						int rewindDistance = acceleratedRewind * mFramesPerSec;
						scanAccelerated = false;
						setVideoFrame(-rewindDistance);
					}
				}
			}
		}
		return retv;
	}
	std::string openVideo(char* filepathname, char* referencefilepathname)
	{
		std::string retv = "";
		syncMarks.clear();
		accumulator.clear();
		amInMarker = false;
		seenDrop = false;
		frameComparison = -1;
		previousFrameComparison = -1;
		markerCount = 1;

		string partFname;
		namedWindow(videoFrameName);
		namedWindow(refFrameName);

		refFrame = imread(referencefilepathname);
		if (refFrame.empty()) {
			retv = "Unable to open image file: ";
			retv += referencefilepathname;
		} else {
			capture.open(filepathname);
			if (!capture.isOpened()) {
				//error in opening the video input
				retv = "Unable to open video file: ";
				retv += filepathname;
			}
			else {
				if (!capture.read(frame)) {
					retv = "Unable to read video file: ";
					retv += filepathname;
				}
				else {
					rawPixelsW = frame.cols;
					rawPixelsH = frame.rows;
					halfSizeFrame(&frame);
					pixelsW = frame.cols;
					pixelsH = frame.rows;
					retv = mFramesPerSec = capture.get(CV_CAP_PROP_FPS);

					capture.set(CAP_PROP_POS_AVI_RATIO, 1);
					mLastFrame = capture.get(CAP_PROP_POS_FRAMES);
					frameNum = 1;
					capture.set(CAP_PROP_POS_FRAMES, frameNum);

					reizeFrame(&refFrame, pixelsH, pixelsW);
					imshow(refFrameName, refFrame);
					acceleratedStep = (mFramesPerSec > 10) ? (int)(mFramesPerSec / 4) : 1;
					scanAccelerated = true;
					isOpen = true;
					retv = "Reference and video files opend OK";
				}
			}
		}
		return retv;

	}	
	bool exportOneFrame(char* exportFilename, float refTime, float frameOffsetTime, float lclFramesPerSec) {
		bool retv = true;
		float oneFrameNum = refTime + frameOffsetTime; // required frame time in ms
		oneFrameNum /= 1000;  // required frame time in sec
		oneFrameNum *= lclFramesPerSec;
		vidreader.set(CAP_PROP_POS_FRAMES, (int)oneFrameNum);
		if (!vidreader.read(frame)) {
			// always export a frame, just a blank one if beyond the video
			frame = Mat::zeros(rawPixelsH, rawPixelsW, CV_8UC1);
			retv = false;
		}
		if (retv && (subImageTL.x >= 0 && subImageBR.x > 0)) {
			if (subImageTL.x >= frame.cols) subImageTL.x = frame.cols - 1;
			if (subImageBR.x >= frame.cols) subImageBR.x = frame.cols - 1;
			if (subImageTL.y >= frame.rows) subImageTL.y = frame.rows - 1;
			if (subImageBR.y >= frame.rows) subImageBR.y = frame.rows - 1;
			frame = frame.rowRange( subImageTL.y, subImageBR.y).colRange(subImageTL.x, subImageBR.x);
		}
		imwrite(exportFilename, frame);
		cv::imwrite(exportFilename, frame);
		return retv;
	}
	//quasi- static variables to allow re-entrant exporting
	ofstream batchFile;
	std::vector<float> *times;
	std::string extractRetv = "";
	std::string extractRetstr = "";
	float extractFramesPerSec;
	int extractExportedImagesCnt = 0;
	float extractMinAverage = 0;
	float definedTime = -1;
	int extractIdx = 0;
	char videoBpathnameSaved[1024];
	std::string extractVideoBoth(char* videoBpathname, char* timesfilepathname, float definedTimeMS, int *remaining) {
		*remaining = 0;
		extractExportedImagesCnt = 0;
		extractMinAverage = 0;
		extractIdx = 0;
		definedTime = definedTimeMS;
		strcpy(videoBpathnameSaved, videoBpathname);
		char exportBatchFilename[1024];
		sprintf(exportBatchFilename, "%s_makepdf.cmd", videoBpathname);

		batchFile.open(exportBatchFilename, ios::out);
		batchFile << "rem invoke batch file with two arguments, folder for the example images Possition_01 etc and destination folder for the pdfs" << "\n";

		extractRetv = "No times read from ";
		times = readTimes(timesfilepathname);
		if (!(times->size() > 0)) {
			//error in opening the video input
			extractRetv += "Unable to read times from ";
			extractRetv += timesfilepathname;
		}
		else {
			std::vector<float> *retv =  readSubImageCoords(timesfilepathname);
			if (retv->size() == 4) {
				int X = (int)retv->at(0);
				int Y = (int)retv->at(1);
				subImageTL = Point(X, Y);
				X = (int)retv->at(2);
				Y = (int)retv->at(3);
				subImageBR = Point(X, Y);
			}
			else {
				subImageBR = subImageTL = Point(-1, -1);
			}
			vidreader.open(videoBpathname);
			if (!vidreader.isOpened()) {
				//error in opening the video input
				extractRetv = "Unable to open video file: ";
				extractRetv += videoBpathname;
			}
			else {
				extractFramesPerSec = vidreader.get(CV_CAP_PROP_FPS);
				if (!vidreader.read(frame)) {
					extractRetv = "Unable to read video file: ";
					extractRetv += videoBpathname;
				}
				else {
					char exportDesc[256];
					sprintf(exportDesc, "fps %f for %s", extractFramesPerSec, videoBpathname);
					extractRetv = exportDesc;


					//retv = "dummy success";
					if (definedTime > 0) {
						*remaining = times->size();
					}
					else {
						*remaining = markerCount * times->size();
					}
				}
			}
		}
		return extractRetv;
	}
	std::string extractVideoRemaining(int *remaining) {
		char exportBatchFilename[1024];
		int timIdx = extractIdx;
		int batchIdx = 0;
		float extractReferenceTime = definedTime;
		if (definedTime > 0) {
		}
		else {
			timIdx = extractIdx % times->size();
			batchIdx = extractIdx / times->size();
			int syncIdx = getLowestMark(extractMinAverage);
			if (syncIdx < 0) {
				*remaining = 0;
			}
			else {
				if (timIdx == (times->size() - 1)) {
					extractMinAverage = syncMarks[syncIdx]->average;

				}
				float refTime = syncMarks[syncIdx]->endFrame;
				refTime /= mFramesPerSec;
				extractReferenceTime = refTime * 1000; //  now in ms
			}
		}
		if (*remaining > 0) {
			int oneFrameTime = times->at(timIdx);
			sprintf(exportBatchFilename, "%s_%d_%02d_%d.png", videoBpathnameSaved, 1 + batchIdx, (int)(timIdx / 5), (1 + (timIdx % 5)));
			if (exportOneFrame(exportBatchFilename, extractReferenceTime, oneFrameTime, extractFramesPerSec)) {
				extractExportedImagesCnt++;
				batchFile << "copy /y /b " << exportBatchFilename << " student_" << (1 + (timIdx % 5)) << ".png\n";
				if ((timIdx % 5) == 4) {
					sprintf(exportBatchFilename, "Position%02d*.png", (int)(1 + (timIdx / 5)));
					batchFile << "copy /y /b %1\\" << exportBatchFilename << " modelpose.png" << "\n";
					batchFile << "echo " << (int)(1 + (timIdx / 5)) << " > partnum.txt" << "\n";
					batchFile << "copy /b /y annotation_part1.txt + partnum.txt + annotation_part2.txt template.tex" << "\n";
					batchFile << ".\\miktex-portable\\texmfs\\install\\miktex\\bin\\x64\\pdflatex template.tex" << "\n";
					char * fnposn = strrchr(videoBpathnameSaved, '\\');
					sprintf(exportBatchFilename, "%s_%d_%02d.pdf", fnposn, 1 + batchIdx, (int)(1 + (timIdx / 5)));
					batchFile << "copy /y /b template.pdf %2\\" << exportBatchFilename << "\n";
				}
			}
			*remaining = *remaining - 1;
			extractIdx++;
		}
		sprintf(exportBatchFilename, "Exported %d images,%d good  of %d, pass %d", extractIdx, extractExportedImagesCnt, times->size(), 1 + batchIdx);
		extractRetv = exportBatchFilename;
		if (*remaining <= 0) {
			batchFile.close();
			vidreader.release();
		}
		return extractRetv;
	}
	std::string extractVideo(char* videoBpathname, char* timesfilepathname, float definedTimeSec, int *remaining) {
		return extractVideoBoth(videoBpathname, timesfilepathname, definedTimeSec * 1000, remaining);
	}
	std::string extractVideo(char* videoBpathname, char* timesfilepathname, int *remaining) {
		return extractVideoBoth(videoBpathname, timesfilepathname, -1, remaining);
	}

	std::vector<float> *readTimes(char *timesFilename) {
		std::vector<float> *retv = new std::vector<float>();
		std::ifstream str;
		str.open(timesFilename);
		std::string                line;
		bool gotOneTime = false;
		do {
			gotOneTime = false;
			line = "";
			std::getline(str, line);
			if (line.length() > 0) {
				float oneTime = -1;
				try {
					oneTime = std::stof(line);
					gotOneTime = true;
					retv->push_back(oneTime);
				}
				catch (...) {

				}
			}
		} while (gotOneTime);
		return retv;
	}
	std::vector<float> *readSubImageCoords(char *timesFilename) {
		std::vector<float> *retv = new std::vector<float>();
		char coordsFilename[1024];
		strcpy(coordsFilename, timesFilename);
		char *lastPathMarker = strrchr(coordsFilename, '\\');
		if (lastPathMarker != nullptr) {
			lastPathMarker++;
			strcpy(lastPathMarker, "subimagecoords.txt");
		}

		std::ifstream str;
		str.open(coordsFilename);
		std::string                line;
		int gotCoords = 0;
		bool gotOneCoord = false;
		do {
			line = "";
			gotOneCoord = false;
			std::getline(str, line);
			if (line.length() > 0) {
				float oneCoord = -1;
				try {
					oneCoord = std::stof(line);
					gotCoords++;
					retv->push_back(oneCoord);
					gotOneCoord = true;
				}
				catch (...) {

				}
			}
		} while (gotOneCoord);
		str.close();
		return retv;
	}

}