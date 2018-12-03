#include "TransformTracking.h"

TransformTracking::TransformTracking()
{
}

TransformTracking::~TransformTracking()
{
}

void TransformTracking::init(Mat trans, Mat rot, Mat H) {
	m_initTrans = trans;
	m_initRot = rot;
	m_currentTrans = m_initTrans;
	m_currentRot = m_initRot;

	m_initH = H;
}

void TransformTracking::update(Mat trans, Mat rot) {
	m_deltaTrans = trans - m_currentTrans;
	m_deltaRot = rot - m_currentRot;
	m_currentTrans = trans;
	m_currentRot = rot;
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
}

Mat TransformTracking::get_H_init() {
	return m_initH;
}
