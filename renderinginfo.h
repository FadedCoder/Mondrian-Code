#pragma once

#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>

struct RenderingInfo
{
    cv::Vec2i outputSize;
    int borderWidth; /* border width in px */
    RenderingInfo(cv::Vec2i outputSize, int borderWidth);
};
