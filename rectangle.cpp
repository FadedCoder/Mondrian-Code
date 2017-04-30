#include "rectangle.h"
#include <random>
using namespace std;
using namespace cv;

Rectangle::Rectangle() : splitDirection(VERTICAL) {}

Rectangle::Rectangle(Point2i position, Vec2i size, SplitDirection splitDirection) : 
    size(size), 
    position(position), 
    splitDirection(splitDirection)
{
    addPoint(Point2i(position.x, position.y));
    addPoint(Point2i(position.x + size[0], position.y));
    addPoint(Point2i(position.x + size[0], position.y - size[1]));
    addPoint(Point2i(position.x, position.y - size[1]));
}

Rectangle::Rectangle(vector<Point2i> va) :
    Polygon(va),
    size(Vec2i(norm(va[1] - va[0]), norm(va[0] - va[3]))),
    position(va[0]),
    splitDirection(VERTICAL) {} /* default */

Rectangle::Rectangle(Vec2i size) : 
    size(size),
    position(Point2i(0, 0)), /* default */
    splitDirection(VERTICAL)
{
    addPoint(Point2i(0, 0));
    addPoint(Point2i(size[0], 0));
    addPoint(Point2i(size[0], size[1]));
    addPoint(Point2i(0, size[1]));
}

Vec2i Rectangle::getSize()
{
    return size;
}

Point2i Rectangle::getPosition()
{
    return position;
}

vector<Rectangle> Rectangle::split(SplitDirection split)
{
    vector<Rectangle> out;
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<float> randCut(0.3, nextafter(0.7, FLT_MAX));
    auto random_cut_value = randCut(mt);

    if (split == VERTICAL) /* split it vertically */
    {
        Rectangle rectangleHalf1(position, Vec2i(int(size[0] * random_cut_value), size[1]), HORIZONTAL);
        Rectangle rectangleHalf2(Point(position.x + rectangleHalf1.getSize()[0], position.y), Vec2i(size[0] - rectangleHalf1.getSize()[0], size[1]), HORIZONTAL);
        out.push_back(rectangleHalf1);
        out.push_back(rectangleHalf2);
    }
    else if (split == HORIZONTAL) /* split it horizontally */
    {
        Rectangle rectangleHalf1(position, Vec2i(size[0], int(size[1] * random_cut_value)), VERTICAL);
        Rectangle rectangleHalf2(Point(position.x, position.y + rectangleHalf1.getSize()[1]), Vec2i(size[0], size[1] - rectangleHalf1.getSize()[1]), VERTICAL);
        out.push_back(rectangleHalf1);
        out.push_back(rectangleHalf2);
    }
    return out;
}

vector<Rectangle> Rectangle::split() /* function overload to use member splitDirection */
{
    return split(splitDirection);
}

void Rectangle::setPosition(Point2i pos)
{
    position = pos;
}

void Rectangle::shrinkRectangleByBorderWidth(int borderWidth)
{
    size[0] -= 2 * borderWidth;
    size[1] -= 2 * borderWidth;
    position.x += borderWidth;
    position.y += borderWidth;
}
