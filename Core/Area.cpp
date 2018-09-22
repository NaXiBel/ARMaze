#include "Area.h"

std::vector<std::vector<Point>> Area::getWall() const
{
	return m_Wall;
}

std::vector<Point> Area::getArea() const
{
	return m_Area;
}

std::vector<Point> Area::getStart() const
{
	return m_Start;
}

std::vector<Point> Area::getEnd() const
{
	return m_End;
}

void Area::setWall(const std::vector<std::vector <Point>> & wall) {
	m_Wall = wall;
}
void Area::setArea(const std::vector <Point> & area) {
	m_Area = area;
}
void Area::setStart(const std::vector <Point> & start) {
	m_Start = start;
	// calcul center
}
void Area::setEnd(const std::vector <Point> & end) {
	m_End = end;
	// calcul center
}