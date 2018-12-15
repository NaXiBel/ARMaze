#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "../Area.h"
#include "../Homography\Homography\TransformTracking.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/tracking/tracking.hpp>
#include <opencv2/tracking/tracker.hpp>
#include <opencv2/imgproc.hpp>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
typedef unsigned char byte;

class CameraCV {
	private :
		cv::VideoCapture capture;
		cv::Mat frame;

	public :
		CameraCV();
		~CameraCV();
		bool openStream(int inputId = 0);
		cv::VideoCapture getVid();
		bool readFrame();
		cv::Mat getFrame();
		int getWidth();
		int getHeigth();
		void displayStream();
		uchar * getLiveFrame(int * sizeofMat);
};

#endif
