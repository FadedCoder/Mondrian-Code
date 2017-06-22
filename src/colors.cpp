#include <opencv2\core.hpp>
#include "colors.h"
using namespace cv;
using namespace std;

/* Default constructor */
Color::Color() {}

/* Constructor with color and ID parameters */
Color::Color(int id, double r, double g, double b, double a) :
	id(id), 
	bgra(cv::Scalar(b, g, r, a)) {}

/* Method which returns the color under the Scalar format */
Scalar Color::getBGRA()
{
	return bgra;
}

/* Method which sets the color's components to a passed Scalar's */
void Color::setBGRA(cv::Scalar bgra)
{
	this->bgra = bgra;
}

/* Method which sets the ID of the color */
void Color::setID(int id)
{
	this->id = id;
}

/* Method which returns the ID of the color */
int Color::getID()
{
	return id;
}

/* These are the predefined Colors used by both the encoder and the decoder */
Color predefColors[] = {	Color(0, 255, 255, 255, 255) /* white */,
							Color(0, 255, 0, 0, 255) /* red */,
							Color(0, 0, 255, 0, 255) /* green */,
							Color(0, 0, 0, 255, 255) /* blue */,
							Color(4, 0, 0, 0, 255) /* black */			};
