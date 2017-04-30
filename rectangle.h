#pragma once

#include "polygon.h"
#include "splitdirection.h"

class Rectangle : public Polygon
{
    cv::Vec2i size;
    cv::Point2i position; /* top left corner position */
    SplitDirection splitDirection; /* 0 == horizontal, 1 == vertical */
public:
    Rectangle();
    Rectangle(cv::Point2i position, cv::Vec2i size, SplitDirection splitDirection = VERTICAL);
    Rectangle(cv::Vec2i size);
    Rectangle(std::vector<cv::Point2i> va);
    cv::Vec2i getSize();
    cv::Point2i getPosition();
    std::vector<Rectangle> split();
    std::vector<Rectangle> split(SplitDirection split);
    void setPosition(cv::Point2i pos);
    void shrinkRectangleByBorderWidth(int borderWidth);
};
