#ifndef CORE_H
#define CORE_H

#include "Area.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
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
		void Video();
		void FindEdge();
		std::vector<std::vector<Point>> FilterInside(std::vector<std::vector<Point>> lines, std::vector<Point> polygon, std::vector<Point> bounds, int seuil = 50);
		std::vector<std::vector<Point>> ConvertToPolygons(std::vector<Vec4i> contours);
		struct myclass {
			bool operator() (std::vector <Point> p1, std::vector <Point> p2) { return (p1.size() < p2.size()); }
		} compareConvexe;

	public:
		Core();
		void Start();
};


#endif //CORE_H