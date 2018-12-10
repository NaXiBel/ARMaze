#ifndef CORE_H
#define CORE_H

#include "Area.h"
#include "Homography\Homography\TransformTracking.h"
#include "VideoStream\CameraCV.h"
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
 
using namespace cv;

class Core {

	private:
		VideoCapture	 m_Capture;
		Mat				 m_Frame;
		Mat				 m_MaskTracker;
		Area			 m_Area;
		bool			 m_IsBuilt;
		Rect2d			 m_TrackBox;

	public:
		Core();
		void Start();

		void Video();
		void BuildMaze();
		void TrackingArea();

		bool get_isBuild();
		bool capture_read();
		void set_frame(Mat frame);
		Area* getArea();

};

#endif //CORE_H