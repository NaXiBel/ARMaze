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

/// utilise la matrice intrinsèque par défault
MazeTransform::MazeTransform() {

	K = new Mat(getIntrinsicMatrix());
}

/// utiliser la matrice intrinsèque en argument
MazeTransform::MazeTransform(Mat intrinsicMatrix) {

	K = new Mat(intrinsicMatrix);
}

MazeTransform::~MazeTransform() {

	if (K != 0) {
		delete K;
		K = 0;
	}
}

void MazeTransform::compute_homography(vector<Point2d> corners) {

	corners = sortPoints(corners);

	vector<Point2d> a4points;
	a4points.push_back(Point2d(0, 0));
	a4points.push_back(Point2d(dimX, 0));
	a4points.push_back(Point2d(dimX, dimY));
	a4points.push_back(Point2d(0, dimY));

	H = findHomography(a4points, corners);

	decomposeHomographyMat(H, *K, rots, trans, normals);

	cout << "homographie décomposée" << endl;
}

Mat MazeTransform::get_H() {
	return H;
}

vector<Mat> MazeTransform::get_rots() {
	return rots;
}

vector<Mat> MazeTransform::get_trans() {
	return trans;
}

vector<Mat> MazeTransform::get_normals() {
	return normals;
}