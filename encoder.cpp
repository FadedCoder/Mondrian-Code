#include "encoder.h"
#include <iostream> //REMOVE
#include "baseutils.h"
using namespace std;
using namespace cv;

/* Default constructor - define predefined colors used for encoding */
Encoder::Encoder() 
{
    predefinedColors.push_back(Color(0, 255, 255, 255, 255)); /* white */
    predefinedColors.push_back(Color(1, 255, 0, 0, 255)); /* red */
    predefinedColors.push_back(Color(2, 0, 255, 0, 255)); /* green */
    predefinedColors.push_back(Color(3, 0, 0, 255, 255)); /* blue */
}

/* Encode function which returns a vector of colors */
vector<Color> Encoder::encode(const string &text)
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
string Encoder::encodeAndOutputText(string &input)
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
//Mat* Encoder::renderImage(RenderingInfo encInfo)
//{
//    int inputSize = input.size();
//    int totalNumberOfSquares = inputSize * 4; /* 1 byte is 4 colors */
//    vector<Color> colors = this->colors;
//
//    int squareSize = encInfo.squareSize;
//    int borderWidth = encInfo.borderWidth;
//    int numberOfSquaresPerXAxis;
//    int numberOfSquaresPerYAxis;
//
//    if (sqrt(float(inputSize)) == int(sqrt(inputSize))) /* square mode */
//    {
//        numberOfSquaresPerXAxis = numberOfSquaresPerYAxis = sqrt(totalNumberOfSquares);
//    }
//    else /* rectangle mode */
//    {
//        /* here, according to the input direction (VERTICAL / HORIZONTAL) 
//           we find a rectangle with the smallest difference between width and height */
//        int squareRoot = (int)sqrt(totalNumberOfSquares) + 1; /* we only need to go until sqrt(n) because factors repeat themselves*/
//        vector<int> width;
//        vector<int> height;
//        for (int i = 1; i < squareRoot; i++) /* we get all the factors of the number of pairs */
//        {
//            if (totalNumberOfSquares % i == 0)
//            {
//                width.push_back(i);
//                height.push_back(totalNumberOfSquares / i);
//                if (i != totalNumberOfSquares / i)
//                {
//                    width.push_back(totalNumberOfSquares / i);
//                    height.push_back(i);
//                }
//
//            }
//        }
//         
//        /* next, we find the rectangle with the smallest difference between width and height */
//        int pairIndex = 0; /* the index of the pair with the smallest difference */
//        int smallest_diff = abs(width[pairIndex] - height[pairIndex]);
//        
//        for (int i = 1; i < width.size(); i++)
//        {
//            if (abs(width[i] - height[i]) <= smallest_diff)
//            {
//                if (abs(width[i] - height[i]) == smallest_diff)
//                {
//                    if (encInfo.direction == HORIZONTAL)
//                    {
//                        if (width[i] >= width[pairIndex])
//                        {
//                            numberOfSquaresPerXAxis = width[i];
//                            numberOfSquaresPerYAxis = height[i];
//                            pairIndex = i;
//                        }
//                    }
//                    else
//                    {
//                        if (height[i] >= height[pairIndex])
//                        {
//                            numberOfSquaresPerXAxis = width[i];
//                            numberOfSquaresPerYAxis = height[i];
//                            pairIndex = i;
//                        }
//                    }
//                }
//                else
//                {
//                    numberOfSquaresPerXAxis = width[i];
//                    numberOfSquaresPerYAxis = height[i];
//                    smallest_diff = abs(width[i] - height[i]);
//                    pairIndex = i;
//                }
//
//            }
//        }
//    }
//
//    int outputSizeX = numberOfSquaresPerXAxis*squareSize + (numberOfSquaresPerXAxis + 1)*borderWidth;
//    int outputSizeY = numberOfSquaresPerYAxis*squareSize + (numberOfSquaresPerYAxis + 1)*borderWidth;
//
//    vector<Vec4b> colorArray; /* W B G R - OpenCV standard*/
//    colorArray.push_back(Vec4b(255, 255, 255, 255));
//    colorArray.push_back(Vec4b(0, 0, 255, 255));
//    colorArray.push_back(Vec4b(0, 255, 0, 255));
//    colorArray.push_back(Vec4b(255, 0, 0, 255));
//    colorArray.push_back(Vec4b(0, 0, 0, 255));
//
//    Mat* output = new Mat(outputSizeY, outputSizeX, CV_8UC4, Scalar(0, 0, 0, 255)); /* solid black for borders */
//    
//    int coloredRowIndex = 0; /* index of each colored row */
//    int rowSquareIndex = 0; /* index of the square we're coloring on a row*/
//    
//    for (int rows = borderWidth; rows < output->rows - borderWidth; rows++)
//    {
//        for (int cols = borderWidth; cols < output->cols - borderWidth; cols++)
//        {
//            output->at<Vec4b>(rows, cols) = colorArray[colors[rowSquareIndex]];
//            
//            if (cols + 1 - borderWidth*(rowSquareIndex%numberOfSquaresPerXAxis + 1))
//            {
//                /* if the number of columns - the borders' size is a multiple of the squares' size
//                    it means we finished drawing a part of the current square */
//                if ((cols + 1 - borderWidth*(rowSquareIndex%numberOfSquaresPerXAxis + 1)) % squareSize == 0)
//                {
//                    cols += borderWidth; /* add border width */
//                    rowSquareIndex++; /* increment square index */
//                }
//            }
//        }
//        if (rows + 1 - borderWidth*(coloredRowIndex + 1))
//        {
//            /* if the number of rows - the borders' size is a multiple of the squares' size
//            it means we finished drawing an entire colored row */
//            if ((rows + 1 - borderWidth*(coloredRowIndex + 1)) % squareSize == 0)
//            {
//                coloredRowIndex++; /* increment the number of colored rows */
//                rows += borderWidth; /* add border width*/
//            }
//            else /* otherwise, we're simply coloring the next row */
//            {
//                rowSquareIndex -= numberOfSquaresPerXAxis; /* we reset the square index to the first one of the last row */
//            }
//        }
//    }
//    /* OpenCV debug output */
//    namedWindow("Display window", WINDOW_AUTOSIZE);
//    imshow("Display window", *output);
//    waitKey(0);
//    imwrite("ouput.png", *output);
//    return output;
//}

/* Function which encodes and renders an input text */
Mat* Encoder::encodeAndRenderImage(string &input, RenderingInfo encInfo)
{
    vector<Color> colors = encode(input);
    int inputSize = input.size(); /* total number of bytes */
    int totalNumberOfRectangles = inputSize * 4; /* 1 byte is 4 colors */
    int borderWidth = encInfo.borderWidth; 
    int halfBorderWidth = borderWidth / 2;

    Rectangle outputRect(encInfo.outputSize);

    Rectangle initRect = outputRect; /* a copy of the output rectangle, used for splitting */
    initRect.shrinkRectangleByBorderWidth(halfBorderWidth); /* we shrink it by half the border width in order to ensure perfect layout */

    vector<Rectangle> rectangles = splitRectangle(initRect, totalNumberOfRectangles - 1);
    for (Rectangle& r : rectangles)
        r.shrinkRectangleByBorderWidth(halfBorderWidth);

    Mat* output = new Mat(encInfo.outputSize[1], encInfo.outputSize[0], CV_8UC4, Scalar(0, 0, 0, 255));

    for (int i = 0; i < rectangles.size(); i++)
    {
        Rectangle currentRect = rectangles[i];
        Rect rect(currentRect.getPosition().x, currentRect.getPosition().y, currentRect.getSize()[0], currentRect.getSize()[1]);
        Scalar color = colors[i].getRGBA();
        rectangle(*output, rect, color, -1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    namedWindow("Display window", WINDOW_AUTOSIZE);         // Create a window for display.
    imshow("Display window", *output);                      // Show our image inside it.
    waitKey(0);                                             // Wait for a keystroke in the window
    /////////////////////////////////////////////////////////////////////////////////////////////

    imwrite("ouput.png", *output);
    return output;
}
