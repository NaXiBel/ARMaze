#ifndef AREA_H
#define AREA_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <numeric>
#include <iostream>

using namespace cv;

class Area {

	private:
		std::vector<std::vector <Point>> m_Wall; 
		std::vector <Point>				 m_Area;
		std::vector <Point>				 m_Start;
		std::vector <Point>				 m_End;
		Point							 m_StartCenter;
		Point							 m_EndCenter;
	public:
		std::vector<std::vector <Point>> getWall() const;
		std::vector <Point> getArea() const;
		std::vector <Point> getStart() const;
		std::vector <Point> getEnd() const;

		void setWall(const std::vector<std::vector <Point>> & wall);
		void setArea(const std::vector <Point> & area);
		void setStart(const std::vector <Point> & start);
		void setEnd(const std::vector <Point> & end);
};


#endif //AREA_H