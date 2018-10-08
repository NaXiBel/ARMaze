#ifndef CORE_H
#define CORE_H

#include "Area.h"

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

using namespace cv;

class Core {

	private:
		VideoCapture m_Capture;
		Mat			 m_Frame;
		Area         m_Area;
		bool		 m_IsBuilt;
		Rect2d       m_TrackBox;

		void Video();
		void BuildMaze();
		void TrackingArea(Ptr<Tracker> tracker);
		
	public:
		Core();
		void Start();
};


#endif //CORE_H