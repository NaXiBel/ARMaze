#pragma once

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

using namespace std;
using namespace cv;

class Calibrator
{
public:

	Calibrator(int image_count, vector<vector<Point3d>> object_points);
	~Calibrator();

	void add_pattern(vector<Point2d> image_point);
	bool is_ready();
	void run_calibration(Size image_size);

	Mat get_intrinsic_matrix();
	Mat get_dist_coeffs();

private:

	int m_image_count;
	vector<vector<Point2d>> m_patterns;
	vector<vector<Point3d>> m_object_points;
	Mat m_intrinsic_matrix;
	Mat m_dist_coeffs;

};
