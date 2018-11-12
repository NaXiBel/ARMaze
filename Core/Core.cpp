#include "Core.h"

Core::Core() {
	m_IsBuilt = false;
}

void Core::Video() {
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

void Core::BuildMaze() {
	// initialisation 
	int Xmin = INT_MAX;
	int Xmax = INT_MIN;
	int Ymin = INT_MAX;
	int Ymax = INT_MIN;

	Mat dst = m_Frame.clone(); // ONLY FOR TEST 

	m_Area = Area();

	bool isOk = true;
	if (m_Frame.empty()) {
		std::cout << "(!) No captured frame -- Break!" << std::endl;
		return;
	}
	cvtColor(m_Frame, m_Frame, CV_BGR2GRAY); // convert gray 
	Mat canny;
	Canny(m_Frame, canny, 50, 200, 3); // NEED THRESHOLD
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(canny, canny, MORPH_CLOSE, kernel); // erode + dilate : remove small holes (dark regions).

	// find area 
	isOk = isOk & m_Area.buildEdge(canny);
	if (isOk) {
		// find xmin xmax ymin ymax 
		for (int i = 0; i < m_Area.getArea().size(); ++i) {
			if (m_Area.getArea()[i].x < Xmin) {
				Xmin = m_Area.getArea()[i].x + 5;
			}
			else if (m_Area.getArea()[i].x > Xmax) {
				Xmax = m_Area.getArea()[i].x - 5;
			}
			if (m_Area.getArea()[i].y < Ymin) {

				Ymin = m_Area.getArea()[i].y + 5;
			}
			else if (m_Area.getArea()[i].y > Ymax) {
				Ymax = m_Area.getArea()[i].y - 5;
			}

		}
		if (Ymax < 0 || Xmax < 0)
			return;

		m_Area.setSizeX(abs((Xmax + 15) - (Xmin - 15)));
		m_Area.setSizeY(abs((Ymax + 15) - (Ymin - 15)));

		std::cout << m_Area.getArea()[0] << " " << m_Area.getArea()[1] << std::endl;
		std::cout << m_Area.getArea()[1] << " " << m_Area.getArea()[2] << std::endl;
		std::cout << m_Area.getArea()[2] << " " << m_Area.getArea()[3] << std::endl;
		std::cout << m_Area.getArea()[0] << " " << m_Area.getArea()[3] << std::endl;
//		std::cout << std::endl;
//		std::cout << Xmin << " " << Xmax << std::endl;
//		std::cout << Ymin << " " << Ymax << std::endl;

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


		// find start/end
		isOk = isOk & m_Area.buildStartEnd(mask, Xmin, Xmax, Ymin, Ymax);

		if (isOk) {
			// ONLY TEST : DISPLAY END
			line(dst, m_Area.getEnd()[0], m_Area.getEnd()[1], Scalar(0, 0, 255), 2);
			line(dst, m_Area.getEnd()[1], m_Area.getEnd()[2], Scalar(0, 0, 255), 2);
			line(dst, m_Area.getEnd()[2], m_Area.getEnd()[0], Scalar(0, 0, 255), 2);
		}

		// ONLY TEST : DISPLAY START
		if (isOk) {
			line(dst, m_Area.getStart()[0], m_Area.getStart()[1], Scalar(255, 0, 0), 2);
			line(dst, m_Area.getStart()[1], m_Area.getStart()[2], Scalar(255, 0, 0), 2);
			line(dst, m_Area.getStart()[2], m_Area.getStart()[3], Scalar(255, 0, 0), 2);
			line(dst, m_Area.getStart()[0], m_Area.getStart()[3], Scalar(255, 0, 0), 2);
		}

		// find walls
		isOk = isOk & m_Area.buildWalls(mask);

		for (int i = 0; i < m_Area.getWall().size(); i++)
		{
			std::vector<Point> polygon = m_Area.getWall()[i];
			for (int j = 0; j < polygon.size() - 1; j++)
			{
				Scalar color(Scalar(0, 255, 255));
				line(dst, polygon[j], polygon[j + 1], color, 3, LINE_AA);
			}
		}
		cv::imshow("mask", mask);
		cv::imshow("dst", dst);

	}

	cv::imshow("Canny", canny);

	int c = waitKey(10);
	m_IsBuilt = isOk;
	if ((char)c == 'q') {
		return;
	}

}



void Core::TrackingArea() {

	Mat dst = m_Frame.clone(); // ONLY FOR TEST 

	if (m_Frame.empty()) {
		std::cout << "(!) No captured frame -- Break!" << std::endl;
		return;
	}
	Mat canny;
	Canny(m_Frame, canny, 100, 200, 3); // NEED THRESHOLD
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(canny, canny, MORPH_CLOSE, kernel); // erode + dilate : remove small holes (dark regions).

	// initialisation 
	int Xmin = INT_MAX;
	int Xmax = INT_MIN;
	int Ymin = INT_MAX;
	int Ymax = INT_MIN;

	for (int i = 0; i < m_Area.getArea().size(); ++i) {
		if (m_Area.getArea()[i].x < Xmin) {
			Xmin = m_Area.getArea()[i].x - 40;
		}
		else if (m_Area.getArea()[i].x > Xmax) {
			Xmax = m_Area.getArea()[i].x + 40;
		}
		if (m_Area.getArea()[i].y < Ymin) {

			Ymin = m_Area.getArea()[i].y - 40;
		}
		else if (m_Area.getArea()[i].y > Ymax) {
			Ymax = m_Area.getArea()[i].y + 40;
		}
	}
	if (Ymax < 0 || Xmax < 0)
		return;
	std::cout << "COORD : " << Xmin << " " << Xmax << std::endl;
	int distX = abs(Xmax - Xmin);
	int distY = abs(Ymax - Ymin);
	std::cout << "SIZE : " << distX << " " << distY << std::endl;
	std::cout << "SIZE AREA: " << m_Area.getSizeX() << " " << m_Area.getSizeY() << std::endl;
	Mat mask = Mat::zeros(canny.rows, canny.cols, CV_8UC1);
	std::vector <std::vector <Point>> pointMask2;
	std::vector <Point> newArea2;
	newArea2.push_back(Point(Xmin, Ymin));
	newArea2.push_back(Point(Xmax, Ymin));
	newArea2.push_back(Point(Xmax, Ymax ));
	newArea2.push_back(Point(Xmin, Ymax ));
	pointMask2.push_back(newArea2);
	drawContours(mask, pointMask2, -1, Scalar(255), -1);

	canny.copyTo(mask, mask);

	imshow("MaskTracker", mask);

	//m_Area.buildEdge(mask);
	m_Area.tracking(mask, Xmin, Xmax , Ymin , Ymax );

	// ONLY TEST DISPLAY AREA
	line(dst, m_Area.getArea()[0], m_Area.getArea()[1], Scalar(133, 255, 50), 2);
	line(dst, m_Area.getArea()[1], m_Area.getArea()[2], Scalar(133, 255, 50), 2);
	line(dst, m_Area.getArea()[2], m_Area.getArea()[3], Scalar(133, 255, 50), 2);
	line(dst, m_Area.getArea()[0], m_Area.getArea()[3], Scalar(133, 255, 50), 2);
	m_Area.setSizeX(abs(Xmax - Xmin));
	m_Area.setSizeY(abs(Ymax - Ymin));
	imshow("Tracker", dst);
}



void Core::Start() {
	Video();
	while (m_Capture.read(m_Capture.getFrame()) && !m_IsBuilt) {

		BuildMaze();
	}

	do 
	{
		TrackingArea();
		// Exit if ESC pressed.
		int k = waitKey(1);
		if (k == 27)
		{
			break;
		}
	} while (m_Capture.read(m_Frame));
}

bool Core::get_isBuild() {
	return m_IsBuilt;
}

bool Core::capture_read() {
	return m_Capture.read(m_Frame);
}

Area* Core::getArea() {
	return &m_Area;
}
