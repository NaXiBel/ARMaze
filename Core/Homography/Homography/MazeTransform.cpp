#include "MazeTransform.h"

Mat getIntrinsicMatrix() {

	Mat K = Mat(3, 3, CV_64FC1);

	K.at<double>(0, 0) = FX;
	K.at<double>(0, 1) = 0.0f;
	K.at<double>(0, 2) = X0;

	K.at<double>(1, 0) = 0.0f;
	K.at<double>(1, 1) = FY;
	K.at<double>(1, 2) = Y0;

	K.at<double>(2, 0) = 0.0f;
	K.at<double>(2, 1) = 0.0f;
	K.at<double>(2, 2) = 1.0f;

	return K;
}

bool sortByY(Point2d p1, Point2d p2) {
	return p1.y < p2.y;
}

vector<Point2d> sortPoints(vector<Point2d> coord) {

	sort(coord.begin(), coord.end(), sortByY);

	if (coord[0].x > coord[1].x) swap(coord[0], coord[1]);
	if (coord[3].x > coord[2].x) swap(coord[2], coord[3]);

	return coord;
}

MazeTransform::MazeTransform() {
	K = getIntrinsicMatrix();
}
MazeTransform::MazeTransform(Mat intrinsic_matrix) {
	K = intrinsic_matrix;
}

MazeTransform::~MazeTransform() {

}

void MazeTransform::compute_transform(vector<Point2d> corners) {

	corners = sortPoints(corners);

	vector<Point2d> a4points;
	a4points.push_back(Point2d(0, 0));
	a4points.push_back(Point2d(dimX, 0));
	a4points.push_back(Point2d(dimX, dimY));
	a4points.push_back(Point2d(0, dimY));

	H = findHomography(a4points, corners);

	Mat distCoeffs = Mat::zeros(3, 4, CV_64FC1);

	solvePnP(a4points, corners, getIntrinsicMatrix(), distCoeffs, rots, trans);

	cout << "homographie décomposée" << endl;

}

Mat MazeTransform::get_H() {
	return H;
}

Mat MazeTransform::get_rots() {
	return rots;
}

Mat MazeTransform::get_trans() {
	return trans;
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