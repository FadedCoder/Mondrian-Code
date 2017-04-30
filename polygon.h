#pragma once

#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include<string>
#include<vector>

class Polygon
{
protected:
    std::vector<cv::Point2i> points;
public:
    Polygon();
    Polygon(std::vector<cv::Point2i> points);
    void addPoint(cv::Point2i point);
    void setPoint(cv::Point2i pos, int index);
    void clear();
    cv::Point2i getPoint(int index);
};
