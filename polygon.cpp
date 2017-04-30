#include "polygon.h"
using namespace std;
using namespace cv;

Polygon::Polygon() {}
Polygon::Polygon(vector<Point2i>points) : points(points) {}

void Polygon::addPoint(Point2i point)
{
    points.push_back(point);
}

void Polygon::setPoint(Point2i pos, int index)
{
    points[index] = pos;
}

void Polygon::clear()
{
    points.clear();
}

Point2i Polygon::getPoint(int index)
{
    return points[index];
}