#include "Core.h"

Core::Core() {
	m_IsBuilt = false;
	this->m_CameraCV = new CameraCV();

}

Core::Core(CameraCV cam) {
	m_IsBuilt = false;
	this->m_CameraCV = &cam;
	std:cout << this->m_CameraCV << endl;
}

void Core::Start() {

	while(!m_IsBuilt) {
		this->m_CameraCV->readFrame();
		BuildMaze();
	}
	/*
	TransformTracking trtr;
	MazeTransform mt;
	vector<Point> corners = m_Area.getArea();
	vector<Point2d> corners2d;

	for(int i = 0; i < corners.size(); i++)
		corners2d.push_back(corners[i]);

	mt.compute_transform(corners2d);
	trtr.init_from_maze(mt);

	vector<Point> begin = m_Area.getStart();
	Point2d center;
	for(int i = 0; i < 4; i++) {
		center += Point2d(begin[i].x, begin[i].y);
		center /= 4;
	}

	Mat end3d(3, 1, CV_64FC1);

	end3d.at<double>(0, 0) = center.x;
	end3d.at<double>(1, 0) = center.y;
	end3d.at<double>(2, 0) = 1;

	Mat H = trtr.get_H_init();

	Mat unprojectedPoint = H.inv() * end3d;

	unprojectedPoint /= unprojectedPoint.at<double>(2, 0);

	cout << "points end" << unprojectedPoint << endl;
	*/
	if(m_IsBuilt) {
		this->m_CameraCV->readFrame();
		TrackingArea();
	}
	/*
		mt.compute_transform(corners2d);
		trtr.update_from_maze(mt);*/

		// Exit if ESC pressed.
	//	int k = waitKey(1);

}

void Core::Video() {
	std::string window_name = "Capture";

	namedWindow(window_name, WINDOW_AUTOSIZE);

	// Read the video stream
	this->m_CameraCV->openStream(0);
	//if(!this->m_CameraCV->getVid().isOpened()) {
	//	std::cout << "--(!)Error opening video capture" << std::endl;
	//	return -1;
	//}

	//this->m_CameraCV->getVid().set(CV_CAP_PROP_FRAME_WIDTH, 640);
	//this->m_CameraCV->getVid().set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//this->m_CameraCV->getVid().set(CV_CAP_PROP_FOURCC, CV_FOURCC('B', 'G', 'R', '3'));
	this->m_CameraCV->displayStream();
}

void Core::BuildMaze() {
	// initialisation 
	int Xmin = INT_MAX;
	int Xmax = INT_MIN;
	int Ymin = INT_MAX;
	int Ymax = INT_MIN;

	Mat dst = this->m_CameraCV->getFrame().clone(); // ONLY FOR TEST 

	m_Area = Area();

	bool isOk = true;

	if(this->m_CameraCV->getFrame().empty()) {
		std::cout << "(!) No captured frame -- Break!" << std::endl;
		return;
	}

	this->m_CameraCV->readFrame();
	//imshow("sa", this->m_CameraCV->getFrame());

	char ca = waitKey(10);
	Mat fr = this->m_CameraCV->getFrame();
	cvtColor(this->m_CameraCV->getFrame(), fr, CV_BGR2GRAY); // convert gray 
	Mat canny;
	Canny(this->m_CameraCV->getFrame(), canny, 100, 300, 3); // NEED THRESHOLD
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(canny, canny, MORPH_CLOSE, kernel); // erode + dilate : remove small holes (dark regions).

	// find area 
	isOk = isOk & m_Area.buildEdge(canny);
	if(isOk) {
		// find xmin xmax ymin ymax 
		for(int i = 0; i < m_Area.getArea().size(); ++i) {
			if(m_Area.getArea()[i].x < Xmin) {
				Xmin = m_Area.getArea()[i].x + 5;
			}
			else if(m_Area.getArea()[i].x > Xmax) {
				Xmax = m_Area.getArea()[i].x - 5;
			}
			if(m_Area.getArea()[i].y < Ymin) {

				Ymin = m_Area.getArea()[i].y + 5;
			}
			else if(m_Area.getArea()[i].y > Ymax) {
				Ymax = m_Area.getArea()[i].y - 5;
			}
		}

		if(Ymax < 0 || Xmax < 0)
			return;

		m_Area.setSizeX(abs((Xmax + 15) - (Xmin - 15)));
		m_Area.setSizeY(abs((Ymax + 15) - (Ymin - 15)));

		//std::cout << m_Area.getArea()[0] << " " << m_Area.getArea()[1] << std::endl;
		//std::cout << m_Area.getArea()[1] << " " << m_Area.getArea()[2] << std::endl;
		//std::cout << m_Area.getArea()[2] << " " << m_Area.getArea()[3] << std::endl;
		//std::cout << m_Area.getArea()[0] << " " << m_Area.getArea()[3] << std::endl;
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

		if(isOk) {
			// ONLY TEST : DISPLAY END
			line(dst, m_Area.getEnd()[0], m_Area.getEnd()[1], Scalar(0, 0, 255), 2);
			line(dst, m_Area.getEnd()[1], m_Area.getEnd()[2], Scalar(0, 0, 255), 2);
			line(dst, m_Area.getEnd()[2], m_Area.getEnd()[0], Scalar(0, 0, 255), 2);
		}

		// ONLY TEST : DISPLAY START
		if(isOk) {
			line(dst, m_Area.getStart()[0], m_Area.getStart()[1], Scalar(255, 0, 0), 2);
			line(dst, m_Area.getStart()[1], m_Area.getStart()[2], Scalar(255, 0, 0), 2);
			line(dst, m_Area.getStart()[2], m_Area.getStart()[3], Scalar(255, 0, 0), 2);
			line(dst, m_Area.getStart()[0], m_Area.getStart()[3], Scalar(255, 0, 0), 2);
		}

		// find walls
		isOk = isOk & m_Area.buildWalls(mask);

		for(int i = 0; i < m_Area.getWall().size(); i++)
		{
			std::vector<Point> polygon = m_Area.getWall()[i];
			for(int j = 0; j < polygon.size() - 1; j++)
			{
				Scalar color(Scalar(0, 255, 255));
				line(dst, polygon[j], polygon[j + 1], color, 3, LINE_AA);
			}
		}
		//cv::imshow("mask", mask);
		cv::imshow("dst", dst);

	}

	//cv::imshow("Canny", canny);

	int c = waitKey(10);
	m_IsBuilt = isOk;
	if((char)c == 'q') {
		return;
	}
}

void Core::TrackingArea() {
	Mat dst = this->m_CameraCV->getFrame().clone(); // ONLY FOR TEST 

	if(this->m_CameraCV->getFrame().empty()) {
		std::cout << "(!) No captured frame -- Break!" << std::endl;
		return;
	}
	Mat canny;
	Canny(this->m_CameraCV->getFrame(), canny, 100, 300, 3); // NEED THRESHOLD
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(canny, canny, MORPH_CLOSE, kernel); // erode + dilate : remove small holes (dark regions).

	// initialisation 
	int Xmin = INT_MAX;
	int Xmax = INT_MIN;
	int Ymin = INT_MAX;
	int Ymax = INT_MIN;

	for(int i = 0; i < m_Area.getArea().size(); ++i) {
		if(m_Area.getArea()[i].x < Xmin) {
			Xmin = m_Area.getArea()[i].x - 200;
		}
		else if(m_Area.getArea()[i].x > Xmax) {
			Xmax = m_Area.getArea()[i].x + 200;
		}
		if(m_Area.getArea()[i].y < Ymin) {

			Ymin = m_Area.getArea()[i].y - 200;
		}
		else if(m_Area.getArea()[i].y > Ymax) {
			Ymax = m_Area.getArea()[i].y + 200;
		}
	}
	if(Ymax < 0 || Xmax < 0)
		return;
	//	std::cout << "COORD : " << Xmin << " " << Xmax << std::endl;
	int distX = abs(Xmax - Xmin);
	int distY = abs(Ymax - Ymin);
	//std::cout << "SIZE : " << distX << " " << distY << std::endl;
	//std::cout << "SIZE AREA: " << m_Area.getSizeX() << " " << m_Area.getSizeY() << std::endl;
	Mat mask = Mat::zeros(canny.rows, canny.cols, CV_8UC1);
	std::vector <std::vector <Point>> pointMask2;
	std::vector <Point> newArea2;
	newArea2.push_back(Point(Xmin, Ymin));
	newArea2.push_back(Point(Xmax, Ymin));
	newArea2.push_back(Point(Xmax, Ymax));
	newArea2.push_back(Point(Xmin, Ymax));
	pointMask2.push_back(newArea2);
	drawContours(mask, pointMask2, -1, Scalar(255), -1);

	canny.copyTo(mask, mask);

	//imshow("MaskTracker", mask);

	//m_Area.buildEdge(mask);
	m_Area.tracking(mask, Xmin, Xmax, Ymin, Ymax, distX, distY);

	// ONLY TEST DISPLAY AREA
	line(dst, m_Area.getArea()[0], m_Area.getArea()[1], Scalar(133, 255, 50), 2);
	line(dst, m_Area.getArea()[1], m_Area.getArea()[2], Scalar(133, 255, 50), 2);
	line(dst, m_Area.getArea()[2], m_Area.getArea()[3], Scalar(133, 255, 50), 2);
	line(dst, m_Area.getArea()[0], m_Area.getArea()[3], Scalar(133, 255, 50), 2);
	m_Area.setSizeX(abs(Xmax - Xmin));
	m_Area.setSizeY(abs(Ymax - Ymin));
	imshow("Tracker", dst);
	imshow("MaskTracker", mask);
	int c = waitKey(10);
	if ((char)c == 'q') {
		return;
	}
}

bool Core::get_isBuild() {
	return m_IsBuilt;
}

bool Core::capture_read() {
	return this->m_CameraCV->readFrame();
}

CameraCV * Core::get_camera() {
	return this->m_CameraCV;
}

void Core::set_camera(CameraCV * camera) {
	this->m_CameraCV = camera;
}

Area* Core::getArea() {
	return &m_Area;
}
