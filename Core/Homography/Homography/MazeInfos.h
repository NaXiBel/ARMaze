#pragma once

#include "MazeTransform.h"
#include "TransformTracking.h"

class MazeInfos
{
public:
	MazeInfos(MazeTransform maze);
	~MazeInfos();

	void setBeginPoint(Point2d point);
	void setEndPoint(Point2d end);

	void addWalls(vector<vector<Point2d> > walls);

private:
	MazeTransform m_transform;

	Point2d m_begin;
	Point2d m_end;

	vector<vector<Point2d> > m_walls;
	
};

