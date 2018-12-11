#include "TransformTracking.h"

TransformTracking::TransformTracking()
{
}

TransformTracking::~TransformTracking()
{
}

void TransformTracking::init(Mat trans, Mat rot, Mat H) {
	trans.copyTo(m_initTrans);
	rot.copyTo(m_initRot);
	trans.copyTo(m_currentTrans);
	rot.copyTo(m_currentRot);

	m_initH = H;
}

void TransformTracking::update(Mat trans, Mat rot) {

	m_deltaTrans = trans - m_currentTrans;
	m_deltaRot = rot - m_currentRot;
	trans.copyTo(m_currentTrans);
	rot.copyTo(m_currentRot);
}

MazeTransform* TransformTracking::get_transform() {
	return current_transform;
}

Mat TransformTracking::get_init_rot() {
	return m_initRot;
}

Mat TransformTracking::get_current_rot() {
	return m_currentRot;
}

Mat TransformTracking::get_delta_rot() {
	return m_deltaRot;
}

Mat TransformTracking::get_init_trans() {
	return m_initTrans;
}

Mat TransformTracking::get_current_trans() {
	return m_currentTrans;
}

Mat TransformTracking::get_delta_trans() {
	return m_deltaTrans;
}

void TransformTracking::init_from_maze(MazeTransform* maze) {
	current_transform = maze;
	init(maze->get_trans(), maze->get_rots(), maze->get_H());
}

void TransformTracking::update_from_maze(MazeTransform* maze) {
	current_transform = maze;
	update(maze->get_trans(), maze->get_rots());
	cout << "updated_from_maze" << endl;
}

Mat TransformTracking::get_H_init() {
	return m_initH;
}
