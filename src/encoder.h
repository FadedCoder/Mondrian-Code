#pragma once

#include <opencv2\core.hpp>
#include <string>
#include <vector>
#include "colors.h"
#include "renderinginfo.h"

class Encoder
{
	std::vector<Color> predefinedColors;
public:
	Encoder();
	std::vector<Color> encode(const std::string text);
	std::vector<Color> encodeBits(std::vector<std::vector<int>> bits);
	std::string Encoder::encodeAndOutputText(std::string input);
	cv::Mat Encoder::encodeAndRenderImage(std::string input, RenderingInfo encInfo);
};
