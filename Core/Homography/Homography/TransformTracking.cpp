#include "TransformTracking.h"

TransformTracking::TransformTracking()
{
}

TransformTracking::~TransformTracking()
{
}

void TransformTracking::init(Mat trans, Mat rot) {
	m_initTrans = trans;
	m_initRot = rot;
	m_currentTrans = m_initTrans;
	m_currentRot = m_initRot;
}

void TransformTracking::update(Mat trans, Mat rot) {
	m_deltaTrans = trans * m_currentTrans.inv();
	m_deltaRot = rot * m_currentRot.inv();
	m_currentTrans = trans;
	m_currentRot = rot;
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

Mat TransformTracking::affect_tranform(Mat point, Mat trans, Mat rot) {
	return rot * trans * point;
}

void TransformTracking::init_from_maze(MazeTransform maze) {
	init(maze.get_trans(), maze.get_rots());
}

void TransformTracking::update_from_maze(MazeTransform maze) {
	update(maze.get_trans(), maze.get_rots());
}


