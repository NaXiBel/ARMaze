#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

double dimX = 297.;
double dimY = 210.;
int FX = 1200;
int FY = 1200;
int X0 = 320;
int Y0 = 240;

class MazeTransform
{

private:

	Mat H;
	Mat* K;
	vector<Mat> rots;
	vector<Mat> trans;
	vector<Mat> normals;

public:

	void compute_homography(vector<Point2d> corners);
	Mat get_H();
	vector<Mat> get_rots();
	vector<Mat> get_trans();
	vector<Mat> get_normals();

};

void MazeTransform::compute_homography(vector<Point2d> corners) {

	corners = sortPoints(corners);

	vector<Point2d> a4points;
	a4points.push_back(Point2d(0, 0));
	a4points.push_back(Point2d(dimX, 0));
	a4points.push_back(Point2d(dimX, dimY));
	a4points.push_back(Point2d(0, dimY));

	H = findHomography(a4points, corners);

	decomposeHomographyMat(H, getIntrinsicMatrix(), rots, trans, normals);

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