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

// Checks if a matrix is a valid rotation matrix.
bool isRotationMatrix(Mat &R)
{
	Mat Rt;
	transpose(R, Rt);
	Mat shouldBeIdentity = Rt * R;
	Mat I = Mat::eye(3, 3, shouldBeIdentity.type());

	return  norm(I, shouldBeIdentity) < 1e-6;

}

// Calculates rotation matrix to euler angles
// The result is the same as MATLAB except the order
// of the euler angles ( x and z are swapped ).
Mat rotationMatrixToEulerAngles(Mat &R)
{

	assert(isRotationMatrix(R));

	float sy = sqrt(R.at<double>(0, 0) * R.at<double>(0, 0) + R.at<double>(1, 0) * R.at<double>(1, 0));

	bool singular = sy < 1e-6; // If

	float x, y, z;
	if (!singular)
	{
		x = atan2(R.at<double>(2, 1), R.at<double>(2, 2));
		y = atan2(-R.at<double>(2, 0), sy);
		z = atan2(R.at<double>(1, 0), R.at<double>(0, 0));
	}
	else
	{
		x = atan2(-R.at<double>(1, 2), R.at<double>(1, 1));
		y = atan2(-R.at<double>(2, 0), sy);
		z = 0;
	}
	return Mat(3, 1, CV_64FC1,{ x, y, z });

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
	a4points.push_back(Point3f(dimX, 0, 0));
	a4points.push_back(Point3f(dimX, dimY, 0));
	a4points.push_back(Point3f(0, dimY, 0));

	H = findHomography(a4points, corners);

	vector<float> vectNull;

	// find the rotation
	solvePnP(a4points, corners, K, vectNull, rot, trans);
	
	// transform it into euler angles
	Rodrigues(rot, rot);
	Mat cameraMatrix, rotMatrix, transVect, rotMatrixX, rotMatrixY, rotMatrixZ;
	double* _r = rot.ptr<double>();
	double projMatrix[12] = { _r[0],_r[1],_r[2],0,
		_r[3],_r[4],_r[5],0,
		_r[6],_r[7],_r[8],0 };

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
