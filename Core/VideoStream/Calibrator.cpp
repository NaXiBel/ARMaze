#include "Calibrator.h"

Calibrator::Calibrator(int image_count, vector<vector<Point3d>> object_points, Size pattern_size)
{
	m_image_count = image_count;
	m_object_points = object_points;
	m_pattern_size = pattern_size;
}

Calibrator::~Calibrator()
{
}

void Calibrator::add_pattern(vector<Point2d> pattern) {
	m_patterns.push_back(pattern);
}

bool Calibrator::is_ready() {
	return m_image_count == m_patterns.size();
}

void Calibrator::run_calibration(Size image_size) {
	m_intrinsic_matrix = Mat::eye(3, 3, CV_64F);
	m_dist_coeffs = Mat::zeros(8, 1, CV_64F);
	Mat tvec, rvec;
	calibrateCamera(m_object_points, m_patterns, image_size, m_intrinsic_matrix, m_dist_coeffs, rvec, tvec, CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5);
}

Mat Calibrator::get_intrinsic_matrix() {
	return m_intrinsic_matrix;
}

Mat Calibrator::get_dist_coeffs() {
	return m_dist_coeffs;
}

Size Calibrator::get_pattern_size() {
	return m_pattern_size;
}
