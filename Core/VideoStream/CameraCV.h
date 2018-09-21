#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

typedef unsigned char byte;

class CameraCV {
	private :
		cv::VideoCapture capture;
		cv::Mat frame;

	public :
		CameraCV();
		~CameraCV();
		void openStream(int inputId = 0);
		cv::Mat getFrame();
		int getWidth();
		int getHeigth();
		void displayStream();
		byte * getLiveFrame();
};

#endif
