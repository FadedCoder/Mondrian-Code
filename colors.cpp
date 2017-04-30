#include "colors.h"
using namespace cv;
using namespace std;

Color::Color() {}

Color::Color(int id, double r, double g, double b, double a) :
    id(id), 
    rgba(cv::Scalar(b, g, r, a)) {}

Scalar Color::getRGBA()
{
    return rgba;
}

void Color::setID(int id)
{
    this->id = id;
}

int Color::getID()
{
    return id;
}
