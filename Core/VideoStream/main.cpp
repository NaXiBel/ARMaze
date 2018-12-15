#include "main.h"

/*** CameraCV functions ***/
CameraCV * createCamera() {
	std::cout << "Creating camera..." << std::endl;
	return new CameraCV();
}

void disposeCamera(CameraCV * cam) {
	if(cam != NULL) {
		delete cam;
		cam = NULL;
		std::cout << "Camera deleted." << std::endl;
	}
}
MazeTransform getTransform(Area* area, Mat* K, Mat* D) {
	MazeTransform maze(*K, *D);
	vector<Point> corners = area->getArea();

	vector<Point2d> cornersD;
	for (int i = 0; i < 4; i++) {
		Point p = corners[i];
		cornersD.push_back(Point2d(p.x, p.y));
	}

	maze.compute_transform(cornersD);
	return maze;
}

void openStream(CameraCV * cam, int id /* = 0 */) {
	cam->openStream(id);
	std::cout << "Camera stream opened." << std::endl;
}

void displayStream(CameraCV * cam) {
	cam->displayStream();
	std::cout << "Frame displayed." << std::endl;
}

int getWidth(CameraCV * cam) {
	int width = cam->getWidth();
	std::cout << "width : " << width << std::endl;
	return width;
}

int getHeight(CameraCV * cam) {
	int height = cam->getHeigth();
	std::cout << "width : " << height << std::endl;
	return height;
}

uchar * getLiveFrame(CameraCV * cam, int * sizeofMat) {
	return cam->getLiveFrame(sizeofMat);
}

/*** Core functions ***/
Core * createCore() {
	return new Core();
}

bool check_build(Core* core) {
	return core->capture_read() && core->get_isBuild();
}

void build(Core* core) {
	core->BuildMaze();
}

CameraCV * getCameraCV(Core* core) {
	return core->get_camera();
}

void setCameraCV(Core* core, CameraCV* cam) {
	core->set_camera(cam);
}

void setCannyThreshold(Core* core, int thresh) {
	core->setTreshholdCanny1(thresh);
}
void setCannyThreshold2(Core* core, int thresh) {
	core->setTreshholdCanny2(thresh);
}
void setKernelThreshold1(Core* core, int thresh) {
	core->setTreshholdKernel1(thresh);
}
void setKernelThreshold2(Core* core, int thresh) {
	core->setTreshholdKernel2(thresh);
}


void start(Core* core) {
	core->Start();
}

MazeTransform getDefaultTransform(Area* area) {

	MazeTransform maze;
	vector<Point> corners = area->getArea();

	vector<Point2d> cornersD;
	for (int i = 0; i < 4; i++) {
		Point p = corners[i];
		cornersD.push_back(Point2d(p.x, p.y));
	}

	maze.compute_transform(cornersD);
	return maze;
}

Calibrator* create_calibrator(int image_count, int square_size) {

	vector<Point3d> corners;
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 9; ++j)
			corners.push_back(Point3d(j*square_size, i*square_size, 0));

	vector<vector<Point3d>> object_patterns;
	for (int i = 0; i < image_count; i++)
		object_patterns.push_back(corners);

	return new Calibrator(image_count, object_patterns, Size(9,6));

}

void add_pattern_to_calibrator(Calibrator* calibrator, Core* core) {
	core->find_chessboard_for_calibrate(calibrator);
}

bool check_pattern_count(Calibrator* calibrator) {
	return calibrator->is_ready();
}

void calibrate(Calibrator* calibrator, Core* core) {
	calibrator->run_calibration(Size(core->get_camera()->getWidth(), core->get_camera()->getHeigth()));
}

Mat* get_K(Calibrator* calibrator) {
	return new Mat(calibrator->get_intrinsic_matrix());
}

Mat* get_D(Calibrator* calibrator) {
	return new Mat(calibrator->get_dist_coeffs());
}

void init_transform_default(TransformTracking* transformTracking, Area* area) {
	MazeTransform* transform = new MazeTransform(getDefaultTransform(area));
	transformTracking->init_from_maze(transform);
}

void init_transform(TransformTracking* transformTracking, Area* area, Mat* K, Mat* D) {
	MazeTransform* transform = new MazeTransform(getTransform(area, K, D));
	transformTracking->init_from_maze(transform);
}

void init_transform_import_KD(TransformTracking* transformTracking, Area* area,
	double K00, double K01, double K02,
	double K10, double K11, double K12,
	double K20, double K21, double K22,
	double D0, double D1, double D2, double D3, double D4, double D5, double D6, double D7) {

	Mat* K = new Mat(3, 3, CV_64FC1);
	Mat* D = new Mat(8, 1, CV_64FC1);

	K->at<double>(0, 0) = K00; K->at<double>(0, 1) = K01; K->at<double>(0, 2) = K02;
	K->at<double>(1, 0) = K10; K->at<double>(1, 1) = K11; K->at<double>(1, 2) = K12;
	K->at<double>(2, 0) = K20; K->at<double>(2, 1) = K21; K->at<double>(2, 2) = K22;

	D->at<double>(0, 0) = D0;
	D->at<double>(1, 0) = D1;
	D->at<double>(2, 0) = D2;
	D->at<double>(3, 0) = D3;
	D->at<double>(4, 0) = D4;
	D->at<double>(5, 0) = D5;
	D->at<double>(6, 0) = D6;
	D->at<double>(7, 0) = D7;

	MazeTransform* transform = new MazeTransform(getTransform(area, K, D));
	transformTracking->init_from_maze(transform);

}

void update_transform(TransformTracking* transformTracking, Area* area) {
	MazeTransform* maze = transformTracking->get_transform();

	vector<Point> corners = area->getArea();

	vector<Point2d> cornersD;
	for (int i = 0; i < 4; i++) {
		Point p = corners[i];
		cornersD.push_back(Point2d(p.x, p.y));
	}

	maze->compute_transform(cornersD);
	transformTracking->update_from_maze(maze);
}

void tracking(Core* core) {
	core->TrackingArea();
}

Area* get_area(Core* core) {
	return core->getArea();
}

bool check_tracking(Core* core) {
	return core->capture_read();
}

Area* create_area() {
	return new Area;
}

Point2d* get_begin_center(Area* area, TransformTracking* transformTracking) {
	vector<Point> begin = area->getStart();
	Point2d center;
	for(int i = 0; i < 4; i++) {
		center += Point2d(begin[i].x, begin[i].y);
	}
	center /= 4;

	Mat end3d(3, 1, CV_64FC1);

	end3d.at<double>(0, 0) = center.x;
	end3d.at<double>(1, 0) = center.y;
	end3d.at<double>(2, 0) = 1;

	Mat H = transformTracking->get_H_init();

	Mat unprojectedPoint = H.inv() * end3d;
	unprojectedPoint /= unprojectedPoint.at<double>(2, 0);

	return new Point2d(unprojectedPoint.at<double>(0, 0) / dimX, unprojectedPoint.at<double>(1, 0) / dimY);
}

Point2d* get_end_center(Area* area, TransformTracking* transformTracking) {
	vector<Point> end = area->getEnd();
	Point2d center;
	for(int i = 0; i < 3; i++) {
		center += Point2d(end[i].x, end[i].y);
	}
	center /= 3;

	Mat end3d(3, 1, CV_64FC1);

	end3d.at<double>(0, 0) = center.x;
	end3d.at<double>(1, 0) = center.y;
	end3d.at<double>(2, 0) = 1;

	Mat H = transformTracking->get_H_init();

	Mat unprojectedPoint = H.inv() * end3d;
	unprojectedPoint /= unprojectedPoint.at<double>(2, 0);

	return new Point2d(unprojectedPoint.at<double>(0, 0) / dimX, unprojectedPoint.at<double>(1, 0) / dimY);
}

vector<Point2d*>* get_wall(Area* area, TransformTracking* transformTracking, int i) {
	vector<vector<Point>> walls = area->getWall();
	vector<Point> wall = walls[i];

	Mat wallMat(3, 2, CV_64FC1);

	wallMat.at<double>(0, 0) = wall[0].x;
	wallMat.at<double>(1, 0) = wall[0].y;
	wallMat.at<double>(2, 0) = 1;
	wallMat.at<double>(0, 1) = wall[1].x;
	wallMat.at<double>(1, 1) = wall[1].y;
	wallMat.at<double>(2, 1) = 1;

	Mat H = transformTracking->get_H_init();

	Mat unprojectedPoints = H.inv() * wallMat;

	// normalize
	for(int j = 0; j < 2; j++) {
		unprojectedPoints.at<double>(0, j) /= unprojectedPoints.at<double>(2, j);
		unprojectedPoints.at<double>(1, j) /= unprojectedPoints.at<double>(2, j);
	}

	vector<Point2d*>* result = new vector<Point2d*>;
	result->push_back(new Point2d(unprojectedPoints.at<double>(0, 0) / dimX, unprojectedPoints.at<double>(1, 0) / dimY));
	result->push_back(new Point2d(unprojectedPoints.at<double>(0, 1) / dimX, unprojectedPoints.at<double>(1, 1) / dimY));

	return result;
}

Point2d* get_point(int j, vector<Point2d*>* wall) {
	return (*wall)[j];
}

int nb_of_walls(Area* area) {
	return area->getWall().size();
}

int size(vector<Point*>* points) {
	return points->size();
}

double get_x(Point2d* point) {
	return point->x;
}

double get_y(Point2d* point) {
	return point->y;
}

TransformTracking* create_transform_tracking() {
	return new TransformTracking();
}

Mat* get_init_rot(TransformTracking* transformTracking) {
	return new Mat(transformTracking->get_init_rot());
}

Mat* get_delta_rot(TransformTracking* transformTracking) {
	return new Mat(transformTracking->get_delta_rot());
}

double at(int i, int j, Mat* mat) {
	return mat->at<double>(i, j);
}

MazeTransform* createMazeTransform() {
	return new MazeTransform();
}

void compute_transform(double corners[][2], MazeTransform* mazeTransform) {
	vector<Point2d> points;

	for(int i = 0; i < 4; i++) {
		Point2d point = Point2d(corners[i][0], corners[i][1]);
		points.push_back(point);
	}

	mazeTransform->compute_transform(points);
}

double** get_H(MazeTransform* mazeTransform) {
	Mat H = mazeTransform->get_H();

	double** res = new double*[3];
	for(int i = 0; i < 3; i++) {
		res[i] = new double[3];
		for(int j = 0; j < 3; j++)
			res[i][j] = H.at<double>(i, j);
	}

	return res;
}

double** get_rots(MazeTransform* mazeTransform) {
	Mat rots = mazeTransform->get_rots();

	double** res = new double*[3];
	for(int i = 0; i < 3; i++) {
		res[i] = new double[3];
		for(int j = 0; j < 3; j++)
			res[i][j] = rots.at<double>(i, j);
	}

	return res;
}

double** get_trans(MazeTransform* mazeTransform) {
	Mat trans = mazeTransform->get_trans();

	double** res = new double*[3];
	for(int i = 0; i < 3; i++) {
		res[i] = new double[3];
		for(int j = 0; j < 3; j++)
			res[i][j] = trans.at<double>(i, j);
	}

	return res;
}
