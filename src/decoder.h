#pragma once

#include <opencv2\core.hpp>
#include <string>
#include "colors.h"

class Decoder
{
	std::vector<Color> predefinedColors;
	std::vector<int> bwPredefColorsIntensity;
public:
	Decoder();
	std::string decode(cv::Mat & im);
};
