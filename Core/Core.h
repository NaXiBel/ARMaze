#ifndef CORE_H
#define CORE_H

#include "Area.h"
#include "Homography\Homography\TransformTracking.h"

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
		Mat			 m_MaskTracker;
		Area         m_Area;
		bool		 m_IsBuilt;
		Rect2d       m_TrackBox;

		

	public:
		Core();
		void Start();

		void Video();
		void BuildMaze();
		void TrackingArea();

		bool get_isBuild();
		bool capture_read();

		Area* getArea();

};

#ifdef _WIN32
#define DllExport extern "C" __declspec(dllexport)
#else
#define DllExport extern "C"
#endif

DllExport Core* createCore();
DllExport void video(Core*);
DllExport bool check_build(Core*);
DllExport void build(Core*);

DllExport void init_transform(TransformTracking*, Area*);
DllExport void update_transform(TransformTracking*, Area*);

DllExport Area* create_area(Core*);
DllExport bool check_tracking(Core*);

#endif //CORE_H