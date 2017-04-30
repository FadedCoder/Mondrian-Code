#pragma once

#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <unordered_map>

struct Color
{
private:
    cv::Scalar rgba;
    int id = 0;
public:
    Color();
    Color(int id, double r, double g, double b, double a);
    cv::Scalar getRGBA();
    void setID(int id);
    int getID();
};
