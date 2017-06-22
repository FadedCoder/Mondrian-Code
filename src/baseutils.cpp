#include <opencv2\core.hpp>
#include <algorithm>
#include <queue>
#include <random>
#include <cmath>
#include "baseutils.h"
using namespace std;
using namespace cv;

/* Function which splits a vector at index i
Note: returned vectors have range [0; i) and [i, v.size()) */
vector<vector<int>> splitVector(const vector<int>& v, int i)
{
	vector<vector<int>> out;
	if (i > 0 && i < v.size() - 1)
	{
		vector<int> split_lo(v.begin(), v.begin() + i);
		vector<int> split_hi(v.begin() + i, v.end());
		out.push_back(split_lo);
		out.push_back(split_hi);
	}
	return out;
}

/* Function which returns the digits of a number n in specified base */
vector<int> toDigits(int n, int base)
{
	vector<int> out;
	if (n)
	{
		while (n)
		{
			out.push_back(n % base);
			n /= base;
		}
	}
	else
	{
		out.push_back(0);
	}
	reverse(out.begin(), out.end());
	return out;
}

/* Function which returns the number n in specified base from its digits */
int fromDigits(const vector<int>& digits, const int base)
{
	int n = 0;
	int b = 1;
	for (int i = (int)digits.size() - 1; i >= 0; i--)
	{
		n += digits[i] * b;
		b *= base;
	}
	return n;
}

/* Function which changes the base of a number from b to c */
vector<int> convertBase(const vector<int>& digits, int b, int c)
{
	return toDigits(fromDigits(digits, b), c);
}

/* Function which returns the binary digits of a char as 1 vector */
vector<int> charToBinary1V(const char &c)
{
	vector<int> binary;
	for (int i = 7; i >= 0; i--)
	{
		binary.push_back((c >> i) & 1);
	}
	return binary;
}

/* Function which splits the vector containing the digits of a char into 2 equal length vectors */
vector<vector<int>> charToBinary2V(const char &c)
{
	vector<int> bin = charToBinary1V(c);
	return splitVector(bin, bin.size() / 2);
}

/* Function which splits the vector containing the digits of a char into 2 equal length vectors */
vector<vector<int>> stringToBinary2V(const string &s)
{
	vector<vector<int>> out;
	for (int i = 0; i < s.size(); i++)
	{
		vector<vector<int>> digits = charToBinary2V(s[i]);
		out.push_back(digits[0]);
		out.push_back(digits[1]);
	}
	return out;
}

/* Function which checks if r1's area is smaller than r2's */
bool smallerArea(const Rectangle& r1, const Rectangle& r2)
{
	int r1Area = r1.getSize().width * r1.getSize().height;
	int r2Area = r2.getSize().width * r2.getSize().height;
	return r1Area < r2Area ? true : false;
}

/* Function which checks if r1's area is greater than r2's */
bool greaterArea(const Rectangle& r1, const Rectangle& r2)
{
	int r1Area = r1.getSize().width * r1.getSize().height;
	int r2Area = r2.getSize().width * r2.getSize().height;
	return r1Area > r2Area ? true : false;
}

/* Function which checks if r1 is below r2 */
bool below(const Rectangle& r1, const Rectangle& r2)
{
	if (r1.getPosition().y < r2.getPosition().y)
	{
		return true;
	}
	else if (r1.getPosition().y == r2.getPosition().y)
	{
		if (r1.getPosition().x < r2.getPosition().x)
		{
			return true;
		}
		return false;
	}
	return false;
}

/* Function which checks if r1 is above r2 */
bool above(const Rectangle& r1, const Rectangle& r2)
{
	if (r1.getPosition().y > r2.getPosition().y)
	{
		return true;
	}
	else if (r1.getPosition().y == r2.getPosition().y)
	{
		if (r1.getPosition().x > r2.getPosition().x)
		{
			return true;
		}
		return false;
	}
	return false;
}

/* Function which splits a rectangle into multiple smaller rectangles *numberOfSplits* times */
vector<Rectangle> splitRectangle(Rectangle rect, int numberOfSplits, float dx, float dy) /* the total number of rectangles will be + 1 */
{
	int numberOfBucketsX = ceil(rect.getSize().width / dx);
	int numberOfBucketsY = ceil(rect.getSize().height / dy);

	int minimumRectangleSize = min(rect.getSize().width, rect.getSize().height) / 10.0f; /* TODO: don't hardcode this value */

	vector<Rectangle> out;

	/* Init queue - Order the rectangle queue to prioritise splitting of bigger rectangles */
	priority_queue<Rectangle, vector<Rectangle>, decltype(&smallerArea)> rectQueue(&smallerArea);
	rectQueue.push(rect);

	int count = 0;
	
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<float> randCut(0.3, nextafter(0.7, FLT_MAX)); /* TODO: change the interval at each iteration */

	while (count != numberOfSplits)
	{
		Rectangle rectangle = rectQueue.top();
		rectQueue.pop();

		if (rectangle.getSize().width <= minimumRectangleSize && rectangle.getSize().height <= minimumRectangleSize)
		{
			rectQueue.push(rectangle);
			continue;
		}

		vector<Rectangle> halves;
		float random_cut_value = randCut(mt);

		if (rectangle.getSize().width >= rectangle.getSize().height) /* split it vertically */
		{
			int width = int(rectangle.getSize().width * random_cut_value / dx) * dx;
			halves = rectangle.determinedOrientedSplit(width, SplitDirection::VERTICAL);
		}
		else /* split it horizontally */
		{
			int height = int(rectangle.getSize().height * random_cut_value / dy) * dy;
			halves = rectangle.determinedOrientedSplit(height, SplitDirection::HORIZONTAL);
		}

		rectQueue.push(halves[0]);
		rectQueue.push(halves[1]);

		count++;
	}

	/* create rectangle vector */
	while (rectQueue.size() != 0)
	{
		out.push_back(rectQueue.top());
		rectQueue.pop();
	}

	/* sort it based on the top-left corner of each rectangle.
	if Y coords are equal, the rect with a smaller X is considered higher
	Note: by default, (0, 0) is the top-left corner of the view */
	sort(out.begin(), out.end(), below);

	return out;
}
