#include "polygon.h"
using namespace std;
using namespace cv;

/* Default constructor */
Polygon::Polygon() {}

/* Constructor which receives an array of points */
Polygon::Polygon(vector<Point2i>points) : points(points) {}

/* Method which adds a point to the polygon's array */
void Polygon::addPoint(Point2i point)
{
	points.push_back(point);
}

/* Method which clears the array of points - basically deletes polygon */
void Polygon::clear()
{
	points.clear();
}

/* Method which sets the point at the desired index to a passed point */
void Polygon::setPoint(Point2i pos, int index)
{
	points[index] = pos;
}

/* Method which returns the point at the desired index */
Point2i Polygon::getPoint(int index)
{
	return points[index];
}
