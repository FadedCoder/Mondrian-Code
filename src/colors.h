#pragma once

#include <opencv2\core.hpp>
#include <unordered_map>

struct Color
{
private:
	cv::Scalar bgra;
	int id = 0;
public:
	Color();
	Color(int id, double r, double g, double b, double a);
	cv::Scalar getBGRA();
	void setBGRA(cv::Scalar bgra);
	void setID(int id);
	int getID();
};

extern Color predefColors[5];
