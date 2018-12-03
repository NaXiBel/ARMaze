#pragma once

#include "MazeTransform.h"

class TransformTracking
{

public:

	TransformTracking();
	~TransformTracking();

	void init_from_maze(MazeTransform* maze);
	void update_from_maze(MazeTransform* maze);

	void init(Mat trans, Mat rot, Mat H);
	void update(Mat trans, Mat rot);

	MazeTransform* get_transform();

	Mat get_init_rot();
	Mat get_current_rot();
	Mat get_delta_rot();

	Mat get_init_trans();
	Mat get_current_trans();
	Mat get_delta_trans();

	Mat get_H_init();

private:

	MazeTransform * current_transform;

	Mat m_initH;

	Mat m_initRot;
	Mat m_currentRot;
	Mat m_deltaRot;

	Mat m_initTrans;
	Mat m_currentTrans;
	Mat m_deltaTrans;

};
