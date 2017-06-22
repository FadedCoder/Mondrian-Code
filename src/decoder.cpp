#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>
#include "decoder.h"
#include "rectangle.h"
#include "baseutils.h"
using namespace std;
using namespace cv;

#ifdef DEBUG_OUTPUT
#include <opencv2/highgui/highgui.hpp>
#endif // DEBUG_OUTPUT

/* Constructor which copies the predefined colors to a local array and also converts them to grayscale */
Decoder::Decoder()
{
	for (int i = 0; i < 5; i++)
	{
		predefinedColors.push_back(predefColors[i]);
		predefinedColors[i].setID(i);

		Scalar c = predefColors[i].getBGRA();
		int bw = 0.299 * c[2] + 0.587 * c[1] + 0.114 * c[0];
		bwPredefColorsIntensity.push_back(bw);
	}
}

/* Decode method which takes an image as an input and returns a string with the decoded info */
string Decoder::decode(Mat & im)
{
	/* Copy the image */
	Mat im_copy = im.clone();

	/* Blur image */
	blur(im_copy, im_copy, Size(3, 3), Point(-1, -1));

	/* Convert it to black & white */
	Mat im_bw;
	cvtColor(im_copy, im_bw, CV_BGR2GRAY);
	
	/* Threshold it */
	Mat im_thresh;
	threshold(im_bw, im_thresh, 0, 255, THRESH_BINARY);

#ifdef DEBUG_OUTPUT
	imshow("Blurred Image", im_copy);
	waitKey(0);
	imshow("Grayscale Image", im_bw);
	waitKey(0);
	imshow("Thresholded Image", im_thresh);
	waitKey(0);
#endif // DEBUG_OUTPUT

	/* Find rectangles */
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(im_thresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	/* Approximate contours to polygons + get bounding rects and circles */
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> imageRects(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		imageRects[i] = boundingRect(Mat(contours_poly[i]));
	}
	vector<Rectangle> rectangles;
	/* Get color of each rectangle and decode */
	for (int i = 0; i < imageRects.size(); i++)
	{
		Point2i pos(imageRects[i].x + imageRects[i].size().width / 2.0f, imageRects[i].y + imageRects[i].size().height / 2.0f);
		Scalar intensity = im_bw.at<uchar>(pos);
		/* Check differences to find actual color */
		int minDiff = INT_MAX;
		int ID = 0;
		for (int j = 0; j < 4; j++)
		{
			int diff = abs(bwPredefColorsIntensity[j] - intensity[0]);
			if (diff < minDiff)
			{
				minDiff = diff;
				ID = j;
			}
		}
		rectangles.push_back(Rectangle(Point2i(imageRects[i].x, imageRects[i].y), imageRects[i].size(), predefinedColors[ID]));
	}
	/* Sort the rectangles based on their top-left corner */
	sort(rectangles.begin(), rectangles.end(), below);
	
	/* Time to decode! */
	string decoded;
	char tmp = 0;
	for (int i = 0; i < rectangles.size(); i+=2)
	{
		/* Get the base 4 int formed by 4 bits */
		int base4Int = 0;
		base4Int += rectangles[i].getColor().getID();
		base4Int *= 10;
		base4Int += rectangles[i + 1].getColor().getID();
		vector<int> digits = convertBase(toDigits(base4Int, 10), 4, 2);
		while (digits.size() < 4)
		{
			digits.insert(digits.begin(), 0);
		}
		for (int j = 3, k = 0; j >= 0; j--, k++)
		{
			if (digits[j])
			{
				tmp |= (1 << k);
			}
		}
		/* If we got a byte, add it to the decoded string */
		if ((i + 2) % 4 == 0)
		{
			decoded += tmp;
			tmp = 0;
		}
		else
		{
			tmp <<= 4;
		}
	}
	return decoded;
}
