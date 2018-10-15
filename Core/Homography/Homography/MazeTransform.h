#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

static double dimX = 1.41428571429;
static double dimY = 1.00000000000;
static double FX = 640.;
static double FY = 480.;
static double X0 = 320.;
static double Y0 = 240.;

class MazeTransform
{

private:

	Mat H;
	Mat K;
	Mat rot;
	Mat trans;

public:

	MazeTransform();
	MazeTransform(Mat intrinsic_matrix);

	~MazeTransform();

	void compute_transform(vector<Point2d> corners);
	Mat get_H();
	Mat get_rots();
	Mat get_trans();

};

#ifdef _WIN32
#define DllExport extern "C" __declspec(dllexport)
#else
#define DllExport extern "C"
#endif

DllExport MazeTransform* createMazeTransform();
DllExport MazeTransform* createMazeTransformIM(double** intrinsic_matrix);
DllExport void compute_transform(double corners[][2], MazeTransform* mazeTransform);
DllExport double** get_H(MazeTransform* mazeTransform);
DllExport double** get_rots(MazeTransform* mazeTransform);
DllExport double** get_trans(MazeTransform* mazeTransform);