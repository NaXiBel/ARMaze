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

		cv::Mat			 m_MaskTracker;
		Area         m_Area;
		bool		 m_IsBuilt;
		Rect2d       m_TrackBox;

	public :
		CameraCV();
		~CameraCV();
		void openStream(int inputId = 0);
		cv::VideoCapture getVid();
		cv::Mat getFrame();
		int getWidth();
		int getHeigth();
		void displayStream();
		uchar * getLiveFrame(int * sizeofMat);

		void Start();

		void BuildMaze();
		void TrackingArea();

		bool get_isBuild();
		bool capture_read();

		Area* getArea();
};

#endif
