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
MazeTransform::MazeTransform(Mat intrinsic_matrix, Mat dist_coefs) {
	K = intrinsic_matrix;
	D = dist_coefs;
}

MazeTransform::~MazeTransform() {

}

void MazeTransform::compute_transform(vector<Point2d> corners) {

	corners = sortPoints(corners);
	for (int i = 0; i < corners.size(); i++)
		cout << corners[i] << endl;

	vector<Point3f> a4points;
	a4points.push_back(Point3f(0, 0, 0));
	a4points.push_back(Point3f(dimX*200, 0, 0));
	a4points.push_back(Point3f(dimX*200, dimY*200, 0));
	a4points.push_back(Point3f(0, dimY*200, 0));

	H = findHomography(a4points, corners);

	vector<float> vectNull;

	/*
	Mat R(3, 3, CV_64FC1);

	float norm1 = (float)norm(H.col(0));
	float norm2 = (float)norm(H.col(1));
	float tnorm = (norm1 + norm2) / 2.0f;

	Mat p1 = H.col(0);       // Pointer to first column of H
	Mat p2 = R.col(0);    // Pointer to first column of pose (empty)

	cv::normalize(H.col(0), R.col(0));   // Normalize the rotation, and copies the column to pose

	p1 = H.col(1);           // Pointer to second column of H
	p2 = R.col(1);        // Pointer to second column of pose (empty)

	cv::normalize(H.col(1), R.col(1));   // Normalize the rotation and copies the column to pose

	p1 = R.col(0);
	p2 = R.col(1);

	Mat p3 = R.col(0).cross(R.col(1));   // Computes the cross-product of p1 and p2
	Mat c2 = R.col(2);    // Pointer to third column of pose
	p3.copyTo(R.col(2));       // Third column is the crossproduct of columns one and two

	trans = H.col(2) / tnorm;  //vector t [R|t] is the last column of pose

	Rodrigues(R, rot);
	*/

	solvePnP(a4points, corners, K, vectNull, rot, trans);
	Rodrigues(rot, rot);

	Mat cameraMatrix, rotMatrix, transVect, rotMatrixX, rotMatrixY, rotMatrixZ;
	double* _r = rot.ptr<double>();
	double projMatrix[12] = { _r[0],_r[1],_r[2],trans.at<double>(0,0),
		_r[3],_r[4],_r[5],trans.at<double>(1,0),
		_r[6],_r[7],_r[8],trans.at<double>(2,0) };

	decomposeProjectionMatrix(Mat(3, 4, CV_64FC1, projMatrix),
		cameraMatrix,
		rotMatrix,
		transVect,
		rotMatrixX,
		rotMatrixY,
		rotMatrixZ,
		rot);

	cout << "homographie décomposee : " << rot << trans << endl;

}

Mat MazeTransform::get_H() {
	return H;
}

Mat MazeTransform::get_rots() {
	return rot;
}

Mat MazeTransform::get_trans() {
	return trans;
}
