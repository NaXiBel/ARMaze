#include "Core.h"


Core::Core() {
}
void Core::Video(){
	std::string window_name = "Capture";
	
	namedWindow(window_name, WINDOW_AUTOSIZE);

	// Read the video stream
	m_Capture.open(0);
	if (!m_Capture.isOpened()) {
		std::cout << "--(!)Error opening video capture" << std::endl;
	//	return -1;
	}

	m_Capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	m_Capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	m_Capture.set(CV_CAP_PROP_FOURCC, CV_FOURCC('B', 'G', 'R', '3'));
}

void Core::FindEdge(){
}
std::vector<std::vector<Point>> Core::ConvertToPolygons(std::vector<Vec4i> contours)
{
	std::vector<std::vector<Point>> polygons;
	for (int i = 0; i < contours.size(); i++) {
		std::vector<Point> segment(2);
		segment[0] = Point(contours[i][0], contours[i][1]);
		segment[1] = Point(contours[i][2], contours[i][3]);
		polygons.push_back(segment);
	}
	return(polygons);
}

std::vector<std::vector<Point>> Core::FilterInside(std::vector<std::vector<Point>> lines, 
												   std::vector<Point> polygon, 
												   std::vector<Point> bounds, 
												   int seuil /*= 50*/){
	int xmin = INT_MAX;
	int xmax = INT_MIN;
	int ymin = INT_MAX;
	int ymax = INT_MIN;
	int upperbound = INT_MAX;
	int lowerbound = INT_MIN;
	int leftbound = INT_MAX;
	int rightbound = INT_MIN;

	std::vector<std::vector<Point>> result;

	// Getting the bounds of the map.
	for (int i = 0; i < bounds.size(); i++)
	{
		int x = bounds[i].x;
		int y = bounds[i].y;

		if (y < upperbound) {
			upperbound = y + 20;
		}
		if (y > lowerbound) {
			lowerbound = y - 20;
		}
		if (x < leftbound) {
			leftbound = x + 20;
		}
		if (x > rightbound) {
			rightbound = x - 20;
		}
	}

	// Getting a square bounding box around the polygon.
	for (int i = 0; i < polygon.size(); i++) {
		int x = polygon[i].x;
		int y = polygon[i].y;

		if (x < xmin) {
			xmin = x;
		}
		if (x > xmax) {
			xmax = x;
		}
		if (y < ymin)
		{
			ymin = y;
		}
		if (y > ymax) {
			ymax = y;
		}
	}

	// Looking for points into the bounding box or outside the bounds.
	for (int i = 0; i < lines.size(); i++)
	{
		std::vector<Point> line = lines[i];
		bool isInside = true;
		bool isOutside = false;
		for (int j = 0; j < line.size(); j++)
		{
			isInside = isInside && line[j].x >= xmin - seuil && line[j].x <= xmax + seuil;
			isInside = isInside && line[j].y >= ymin - seuil && line[j].y <= ymax + seuil;
			isOutside = isOutside || line[j].x >= rightbound || line[j].x <= leftbound;
			isOutside = isOutside || line[j].y >= lowerbound || line[j].y <= upperbound;
		}
		if (!isInside && !isOutside)
		{
			result.push_back(line);
		}
	}

	return(result);
}



void Core::Start(){

	// video acquisition 
	Video();
	// while -> find all elements
	while (m_Capture.read(m_Frame)) {
		// initialisation 
		int Xmin = INT_MAX;
		int Xmax = INT_MIN;
		int Ymin = INT_MAX;
		int Ymax = INT_MIN;
		Mat dst = m_Frame.clone(); // ONLY FOR TEST 

		m_Area = Area();

		if (m_Frame.empty()) {
			std::cout << "(!) No captured frame -- Break!" << std::endl;
			break;
		}
		imshow("Capture", m_Frame); // display video 
		cvtColor(m_Frame, m_Frame, CV_BGR2GRAY); // convert gray 
		Mat canny;
		Canny(m_Frame, canny, 100, 200, 3); // NEED THRESHOLD
		Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
		morphologyEx(canny, canny, MORPH_CLOSE, kernel); // erode + dilate : remove small holes (dark regions).

		// find all edge
		std::vector<std::vector<Point> > contours;
		findContours(canny.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		std::vector<Point> approx;
		sort(contours.begin(), contours.end(), compareConvexe); // sort connection

		// find area 
		double max = 0;
		for (int index = 0; index < contours.size(); ++index) {
			if (fabs(contourArea(Mat(contours[index]))) <= 1000) {
				continue;
			}
			approxPolyDP(Mat(contours[index]), approx, arcLength(cv::Mat(contours[index]), true) * 0.1, true);

			if (approx.size() == 4) {
				if (fabs(contourArea(Mat(approx))) > max) {
					max = fabs(contourArea(Mat(approx)));
					m_Area.setArea(approx);
				}
			}
		}
		// find xmin xmax ymin ymax 
		for (int i = 0; i < m_Area.getArea().size(); ++i) {
			if (m_Area.getArea()[i].x < Xmin) {
				Xmin = m_Area.getArea()[i].x + 15;
			}
			else if (m_Area.getArea()[i].x > Xmax) {
				Xmax = m_Area.getArea()[i].x - 15;
			}
			if (m_Area.getArea()[i].y < Ymin) {

				Ymin = m_Area.getArea()[i].y + 15;
			}
			else if (m_Area.getArea()[i].y > Ymax) {
				Ymax = m_Area.getArea()[i].y - 15;
			}
		}

		std::cout << m_Area.getArea()[0] << " " << m_Area.getArea()[1] << std::endl;
		std::cout << m_Area.getArea()[1] << " " << m_Area.getArea()[2] << std::endl;
		std::cout << m_Area.getArea()[2] << " " << m_Area.getArea()[3] << std::endl;
		std::cout << m_Area.getArea()[0] << " " << m_Area.getArea()[3] << std::endl;
		std::cout << std::endl;
		std::cout << Xmin << " " << Xmax << std::endl;
		std::cout << Ymin << " " << Ymax << std::endl;

		// ONLY TEST DISPLAY AREA
		line(dst, m_Area.getArea()[0], m_Area.getArea()[1], Scalar(133, 255, 50), 2);
		line(dst, m_Area.getArea()[1], m_Area.getArea()[2], Scalar(133, 255, 50), 2);
		line(dst, m_Area.getArea()[2], m_Area.getArea()[3], Scalar(133, 255, 50), 2);
		line(dst, m_Area.getArea()[0], m_Area.getArea()[3], Scalar(133, 255, 50), 2);
		
		// create mask with area coord 
		Mat mask = Mat::zeros(canny.rows, canny.cols, CV_8UC1);
		std::vector <std::vector <Point>> pointMask;
		std::vector <Point> newArea;
		newArea.push_back(Point(Xmin, Ymin));
		newArea.push_back(Point(Xmax, Ymin));
		newArea.push_back(Point(Xmax, Ymax));
		newArea.push_back(Point(Xmin, Ymax));
		pointMask.push_back(newArea);
		drawContours(mask, pointMask, -1, Scalar(255), -1);
		canny.copyTo(mask, mask);
		

		// find start and end
		for (int i = 0; i < contours.size(); i++)
		{
			if (fabs(contourArea(Mat(contours[i]))) <= 1000) {
				continue;
			}
			// Approximate contour with accuracy proportional
			// to the contour perimeter

			cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.1, true);
			
			if (approx.size() == 3)
			{
				if (m_Area.getEnd().empty()) {

					bool isOk2 = true;
					for (int index = 0; index < approx.size(); ++index) {
						if (approx[index].x < Xmin || approx[index].x > Xmax) {
							isOk2 = false;
						}
						if (approx[index].y < Ymin || approx[index].y > Ymax) {
							isOk2 = false;
						}
					}
					if (isOk2) {
						m_Area.setEnd(approx);
						// ONLY TEST : DISPLAY END
						line(dst, approx[0], approx[1], Scalar(19, 190, 255), 2);
						line(dst, approx[1], approx[2], Scalar(19, 190, 255), 2);
						line(dst, approx[0], approx[2], Scalar(19, 190, 255), 2);
					}
				}

			}
			else if (approx.size() == 4)
			{
				if (m_Area.getStart().empty()) {
					bool isOk = true;
					for (int index = 0; index < approx.size(); ++index) {
						if (approx[index].x < Xmin || approx[index].x > Xmax) {
							isOk = false;
						}
						if (approx[index].y < Ymin || approx[index].y > Ymax) {
							isOk = false;
						}
					}
					if (isOk) {
						m_Area.setStart(approx);
						// ONLY TEST : DISPLAY START
						line(dst, approx[0], approx[1], Scalar(255, 0, 0), 2);
						line(dst, approx[1], approx[2], Scalar(255, 0, 0), 2);
						line(dst, approx[2], approx[3], Scalar(255, 0, 0), 2);
						line(dst, approx[0], approx[3], Scalar(255, 0, 0), 2);
					}
				}
			}
		}

		// find walls
		std::vector<Vec4i> Hugue;
		HoughLinesP(mask, Hugue, 1, CV_PI / 180, 50, 58, 10);

		std::vector<Point> square = m_Area.getStart();

		std::vector<Point> triangle = m_Area.getEnd();

		std::vector<std::vector<Point>> polygons;
		polygons = ConvertToPolygons(Hugue);
		polygons = FilterInside(polygons, square, m_Area.getArea());
		polygons = FilterInside(polygons, triangle, m_Area.getArea());

		std::vector<std::vector<Point>> filteredPolygons = polygons;

		for (int i = 0; i < polygons.size(); i++)
		{
			filteredPolygons = FilterInside(filteredPolygons, polygons[i], m_Area.getArea());
			filteredPolygons.push_back(polygons[i]);
		}

		for (int i = 0; i < filteredPolygons.size(); i++)
		{
			std::vector<Point> polygon = filteredPolygons[i];
			for (int j = 0; j < polygon.size() - 1; j++)
			{
				Scalar color(Scalar(0, 0, 255));
				line(dst, polygon[j], polygon[j + 1], color, 3, LINE_AA);
			}
		}
		//		cv::imshow("src", src);
		cv::imshow("dst", dst);
		cv::imshow("mask", mask);
		cv::imshow("Canny", canny);

		int c = waitKey(10);
		if ((char)c == 'q') {
			break;
		}
	}
}
