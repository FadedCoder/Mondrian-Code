#pragma once

#include <opencv2\core.hpp>

struct RenderingInfo
{
	cv::Size2i outputSize;
	int borderWidth; /* border width in px */
	RenderingInfo(cv::Size2i outputSize, int borderWidth);
};
