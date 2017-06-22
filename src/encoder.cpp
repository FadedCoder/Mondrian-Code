#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include "encoder.h"
#include "baseutils.h"
using namespace std;
using namespace cv;

/* Constructor which copies the predefined colors to a local array */
Encoder::Encoder()
{
	predefinedColors = vector<Color>(begin(predefColors), end(predefColors));
	for (int i = 0; i < predefinedColors.size(); i++)
	{
		predefinedColors[i].setID(i);
	}
}

/* Encode function which returns a vector of colors */
vector<Color> Encoder::encode(const string text)
{
	vector<Color> colors;
	if (text.size() > 0)
	{
		vector<vector<int>> bits = stringToBinary2V(text);
		colors = encodeBits(bits);
	}
	return colors;
}

/* Function which returns a vector of colors from binary */
vector<Color> Encoder::encodeBits(vector<vector<int>> bits)
{
	vector<Color> out;
	for (int i = 0; i < bits.size(); i++)
	{
		vector<int> i_digits = toDigits(fromDigits(bits[i], 2), 4);
		if (i_digits.size() == 1)
		{
			i_digits.insert(i_digits.begin(), 0);
		}
		out.push_back(predefinedColors[i_digits[0]]);
		out.push_back(predefinedColors[i_digits[1]]);
	}
	return out;
}

/* Function which encodes and outputs to console an input text */
string Encoder::encodeAndOutputText(string input)
{
	vector<Color> colors = encode(input);
	string output;
	char colorArray[4] = { 'W','R','G','B' };
	for (int i = 0; i < colors.size() - 1; i+=2)
	{
		output += "(";
		output += colorArray[colors[i].getID()];
		output += ",";
		output += colorArray[colors[i + 1].getID()];
		output += ")";
		if (i < colors.size() - 2)
		{
			output += ", ";
		}
	}
	return output;
}

/* Function which encodes and renders an input text */
Mat Encoder::encodeAndRenderImage(string in, RenderingInfo encInfo)
{
#ifdef DEBUG_OUTPUT
	string outxt = encodeAndOutputText(in);
	cout << outxt << endl;
#endif // DEBUG_OUTPUT
	vector<Color> colors = encode(in);
	int inputSize = in.size(); /* total number of bytes */
	int numberOfRects = inputSize * 4; /* 1 byte is 4 colors */
	int borderWidth = encInfo.borderWidth; 
	int halfBorderWidth = borderWidth / 2;

	Rectangle outputRect(encInfo.outputSize);

	Rectangle initRect = outputRect; /* a copy of the output rectangle, used for splitting */
	initRect.shrinkRectangleByBorderWidth(halfBorderWidth); /* we shrink it by half the border width in order to ensure perfect layout */

	int numberOfSplits = numberOfRects - 1;
	int numberOfLevels = ceil(log2(numberOfRects));
	int numberOfHorizontalSplits = numberOfLevels / 2;
	if (initRect.getSplitDirection() == SplitDirection::HORIZONTAL)
		numberOfHorizontalSplits++;

	// TODO: take care of info above
	// float dy = initRect.getSize().height / (k*numberOfHorizontalSplits + 1);

	//setting the values below to 1 makes no difference
	float dx = ceil(initRect.getSize().height / float((5 * borderWidth))); 
	float dy = ceil(initRect.getSize().height / float((3 * borderWidth)));

	vector<Rectangle> rectangles = splitRectangle(initRect, numberOfSplits, dx, dy);
	for (Rectangle& r : rectangles)
	{
		r.shrinkRectangleByBorderWidth(halfBorderWidth);
	}

	Mat output(encInfo.outputSize.height, encInfo.outputSize.width, CV_8UC4, predefinedColors[4].getBGRA());

	for (int i = 0; i < rectangles.size(); i++)
	{
		Rectangle currentRect = rectangles[i];
		Rect rect(currentRect.getPosition().x, currentRect.getPosition().y, currentRect.getSize().width, currentRect.getSize().height);
		Scalar color = colors[i].getBGRA();
		rectangle(output, rect, color, -1);
	}

	return output;
}
