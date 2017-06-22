#include "rectangle.h"
#include <random>
using namespace std;
using namespace cv;

/* Constructor which sets the split direction to NOT_DEFINED */
Rectangle::Rectangle() : splitDirection(NOT_DEFINED) {}

/* Constructor which receives a position, a size, and an optional split direction */
Rectangle::Rectangle(Point2i position, Size2i size, SplitDirection splitDirection) : 
	size(size), 
	position(position), 
	splitDirection(splitDirection)
{
	addPoint(Point2i(position.x, position.y));
	addPoint(Point2i(position.x + size.width, position.y));
	addPoint(Point2i(position.x + size.width, position.y - size.height));
	addPoint(Point2i(position.x, position.y - size.height));
}

/* Constructor which receives a position, a size, and an optional color and split direction */
Rectangle::Rectangle(cv::Point2i position, cv::Size2i size, Color col, SplitDirection splitDirection) :
	size(size),
	position(position),
	splitDirection(splitDirection),
	color(col)
{
	addPoint(Point2i(position.x, position.y));
	addPoint(Point2i(position.x + size.width, position.y));
	addPoint(Point2i(position.x + size.width, position.y - size.height));
	addPoint(Point2i(position.x, position.y - size.height));
}

/* Constructor which receives an array of points */
Rectangle::Rectangle(vector<Point2i> va) :
	Polygon(va),
	size(Size2i(norm(va[1] - va[0]), norm(va[0] - va[3]))),
	position(va[0]),
	splitDirection(NOT_DEFINED) {} /* default */

/* Constructor which only receives a size (no position) */
Rectangle::Rectangle(Size2i size) : 
	size(size),
	position(Point2i(0, 0)), /* default */
	splitDirection(NOT_DEFINED)
{
	addPoint(Point2i(0, 0));
	addPoint(Point2i(size.width, 0));
	addPoint(Point2i(size.width, size.height));
	addPoint(Point2i(0, size.height));
}

/* Method which sets the rectangle's size */
void Rectangle::setSize(int x, int y)
{
	size.width = x;
	size.height = y;
}

/* Method which returns the size of the rectangle */
Size2i Rectangle::getSize() const
{
	return size;
}

/* Method which sets the position of the rectangle */
void Rectangle::setPosition(Point2i pos)
{
	position = pos;
}

/* Method which returns the position of the rectangle */
Point2i Rectangle::getPosition() const
{
	return position;
}

/* Method which sets the color of the rectangle */
void Rectangle::setColor(Color col)
{
	color = col;
}

/* Method which returns the color of the rectangle */
Color Rectangle::getColor() const
{
	return color;
}

/* Method which sets the split direction of the rectangle */
void Rectangle::setSplitDirection(SplitDirection direction)
{
	splitDirection = direction;
}

/* Method which returns the split direction of the rectangle */
SplitDirection Rectangle::getSplitDirection() const
{
	return splitDirection;
}

/* Method which splits the rectangle randomly using its own split direction */
vector<Rectangle> Rectangle::randomSplit() /* function overload to use member splitDirection */
{
	return orientedRandomSplit(splitDirection);
}

/* Method which splits the rectangle randomly using a passed split direction */
vector<Rectangle> Rectangle::orientedRandomSplit(SplitDirection split)
{
	vector<Rectangle> out;
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<float> randCut(0.3, nextafter(0.7, FLT_MAX));
	auto random_cut_value = randCut(mt);

	if (split == VERTICAL) /* split it vertically */
	{
		Rectangle rectangleHalf1(position, Size2i(int(size.width * random_cut_value), size.height), HORIZONTAL);
		Rectangle rectangleHalf2(Point(position.x + rectangleHalf1.getSize().width, position.y), Size2i(size.width - rectangleHalf1.getSize().width, size.height), HORIZONTAL);
		out.push_back(rectangleHalf1);
		out.push_back(rectangleHalf2);
	}
	else if (split == HORIZONTAL) /* split it horizontally */
	{
		Rectangle rectangleHalf1(position, Size2i(size.width, int(size.height * random_cut_value)), VERTICAL);
		Rectangle rectangleHalf2(Point(position.x, position.y + rectangleHalf1.getSize().height), Size2i(size.width, size.height - rectangleHalf1.getSize().height), VERTICAL);
		out.push_back(rectangleHalf1);
		out.push_back(rectangleHalf2);
	}
	return out;
}

/* Method which splits the rectangle using a position and a passed split direction */
vector<Rectangle> Rectangle::determinedOrientedSplit(int pos, SplitDirection direction)
{
	vector<Rectangle> out;

	if (direction == VERTICAL) /* split it vertically */
	{
		Rectangle half1(position, Size2i(pos, size.height), HORIZONTAL);
		Rectangle half2(Point(position.x + half1.getSize().width, position.y), Size2i(size.width - half1.getSize().width, size.height), HORIZONTAL);
		out.push_back(half1);
		out.push_back(half2);
	}
	else if (direction == HORIZONTAL) /* split it horizontally */
	{
		Rectangle half1(position, Size2i(size.width, pos), VERTICAL);
		Rectangle half2(Point(position.x, position.y + half1.getSize().height), Size2i(size.width, size.height - half1.getSize().height), VERTICAL);
		out.push_back(half1);
		out.push_back(half2);
	}
	return out;
}

/* Method which shrinks the rectangle by a desired int */
void Rectangle::shrinkRectangleByBorderWidth(int borderWidth)
{
	size.width -= 2 * borderWidth;
	size.height -= 2 * borderWidth;
	position.x += borderWidth;
	position.y += borderWidth;
}
