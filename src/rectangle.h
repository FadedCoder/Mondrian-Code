#pragma once

#include <opencv2\core.hpp>
#include "polygon.h"
#include "splitdirection.h"
#include "colors.h"

class Rectangle : public Polygon
{
	cv::Size2i size;
	cv::Point2i position; /* top left corner position */
	SplitDirection splitDirection; /* 0 == horizontal, 1 == vertical */
	Color color;
public:
	Rectangle();
	Rectangle(cv::Point2i position, cv::Size2i size, SplitDirection splitDirection = NOT_DEFINED);
	Rectangle(cv::Point2i position, cv::Size2i size, Color col = Color(0, 255, 255, 255, 255), SplitDirection splitDirection = NOT_DEFINED);
	Rectangle(cv::Size2i size);
	Rectangle(std::vector<cv::Point2i> va);

	void setSize(int x, int y);
	cv::Size2i getSize() const;

	void setPosition(cv::Point2i pos);
	cv::Point2i getPosition() const;

	void setColor(Color col);
	Color getColor() const;

	void setSplitDirection(SplitDirection direction);
	SplitDirection getSplitDirection() const;

	std::vector<Rectangle> randomSplit();
	std::vector<Rectangle> orientedRandomSplit(SplitDirection split);
	std::vector<Rectangle> determinedOrientedSplit(int pos, SplitDirection direction);

	void shrinkRectangleByBorderWidth(int borderWidth);
};
