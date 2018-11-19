#include "main.h"

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

Core * createCore() {
	return new Core();
}

Area* create_area() {
	return new Area;
}

Point2d* get_begin_center(Area* area, TransformTracking* transformTracking) {
	vector<Point> begin = area->getStart();
	Point2d center;
	for (int i = 0; i < 4; i++) {
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

	return new Point2d(unprojectedPoint.at<double>(0, 0) / dimX, unprojectedPoint.at<double>(1, 0));
}

Point2d* get_end_center(Area* area, TransformTracking* transformTracking) {
	vector<Point> end = area->getEnd();
	Point2d center;
	for (int i = 0; i < 3; i++) {
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

	return new Point2d(unprojectedPoint.at<double>(0,0) / dimX, unprojectedPoint.at<double>(1,0));
}

vector<Point2d*>* get_wall(Area* area, TransformTracking* transformTracking, int i) {
	vector<vector<Point>> walls = area->getWall();
	vector<Point> wall = walls[i];

	Mat wallMat(3,2,CV_64FC1);

	wallMat.at<double>(0, 0) = wall[0].x;
	wallMat.at<double>(1, 0) = wall[0].y;
	wallMat.at<double>(2, 0) = 1;
	wallMat.at<double>(0, 1) = wall[1].x;
	wallMat.at<double>(1, 1) = wall[1].y;
	wallMat.at<double>(2, 1) = 1;

	Mat H = transformTracking->get_H_init();

	Mat unprojectedPoints = H.inv() * wallMat;

	// normalize
	for (int i = 0; i < 2; i++) {
		unprojectedPoints.at<double>(0, i) /= unprojectedPoints.at<double>(2, i);
		unprojectedPoints.at<double>(1, i) /= unprojectedPoints.at<double>(2, i);
	}

	vector<Point2d*>* result = new vector<Point2d*>;
	result->push_back(new Point2d(unprojectedPoints.at<double>(0, 0) / dimX, unprojectedPoints.at<double>(1, 0)));
	result->push_back(new Point2d(unprojectedPoints.at<double>(0, 1) / dimX, unprojectedPoints.at<double>(1, 1)));

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

Core* createCore() {
	return new Core;
}

void video(Core* core) {
	core->Video();
}

bool check_build(Core* core) {
	return core->capture_read() && core->get_isBuild();
}

void build(Core* core) {
	core->BuildMaze();
}

void tracking(Core* core) {
	core->TrackingArea();
}

Area* get_area(Core* core) {
	return core->getArea();
}

MazeTransform getTransform(Area* area) {
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

void init_transform(TransformTracking* transformTracking, Area* area) {
	MazeTransform transform = getTransform(area);
	transformTracking->init_from_maze(transform);
}

void update_transform(TransformTracking* transformTracking, Area* area) {
	MazeTransform transform = getTransform(area);
	transformTracking->update_from_maze(transform);
}

bool check_tracking(Core* core) {
	return core->capture_read();
}

MazeTransform* createMazeTransform() {
	return new MazeTransform();
}

MazeTransform* createMazeTransformIM(double** intrinsic_matrix) {
	Mat intrinsic_matrix_mat = Mat(3, 3, CV_64FC1);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			intrinsic_matrix_mat.at<double>(i, j) = intrinsic_matrix[i][j];
	return new MazeTransform(intrinsic_matrix_mat);
}

void compute_transform(double corners[][2], MazeTransform* mazeTransform) {
	vector<Point2d> points;

	for (int i = 0; i < 4; i++) {
		Point2d point = Point2d(corners[i][0], corners[i][1]);
		points.push_back(point);
	}

	mazeTransform->compute_transform(points);
}

double** get_H(MazeTransform* mazeTransform) {
	Mat H = mazeTransform->get_H();

	double** res = new double*[3];
	for (int i = 0; i < 3; i++) {
		res[i] = new double[3];
		for (int j = 0; j < 3; j++)
			res[i][j] = H.at<double>(i, j);
	}

	return res;
}

double** get_rots(MazeTransform* mazeTransform) {
	Mat rots = mazeTransform->get_rots();

	double** res = new double*[3];
	for (int i = 0; i < 3; i++) {
		res[i] = new double[3];
		for (int j = 0; j < 3; j++)
			res[i][j] = rots.at<double>(i, j);
	}

	return res;
}

double** get_trans(MazeTransform* mazeTransform) {
	Mat trans = mazeTransform->get_trans();

	double** res = new double*[3];
	for (int i = 0; i < 3; i++) {
		res[i] = new double[3];
		for (int j = 0; j < 3; j++)
			res[i][j] = trans.at<double>(i, j);
	}

	return res;
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

Mat* get_init_trans(TransformTracking* transformTracking) {
	return new Mat(transformTracking->get_init_trans());
}

Mat* get_delta_trans(TransformTracking* transformTracking) {
	return new Mat(transformTracking->get_delta_trans());
}

double at(int i, int j, Mat* mat) {
	return mat->at<double>(i, j);
}