/* Copyright 2017 Alexandru Bratosin,
 *                Sergey Popov,
 *                Sampriti Panda,
 *                Urtkash Dixit
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <random>
#include "encoder.h"
#include <iostream> //REMOVE
using namespace std;
#include "baseutils.h"

Encoder::Encoder() {}
Encoder::Encoder(const string &text) : input(text) {}

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
        out.push_back((Color)i_digits[0]);
        out.push_back((Color)i_digits[1]);
    }
    return out;
}
vector<Color> Encoder::encode()
{
    if (input.size() > 0)
    {
        vector<vector<int>> bits = string_to_binary_int2(input);
        colors = encodeBits(bits);
    }
    return colors;
}
string Encoder::outputText()
{
    string output;
    char colorArray[4] = { 'W','R','G','B' };
    for (int i = 0; i < colors.size() - 1; i++)
    {
        output += "(";
        output += colorArray[colors[i]];
        output += ",";
        output += colorArray[colors[i + 1]];
        output += ")";
        if (i < colors.size() - 2)
        {
            output += ", ";
        }
    }
    return output;
}

Mat* Encoder::renderImage(EncodingInfo encInfo)
{
    int inputSize = input.size();
    int totalNumberOfSquares = inputSize * 4; /* 1 byte is 4 colors */
    vector<Color> colors = this->colors;

    int squareSize = encInfo.squareSize;
    int borderWidth = encInfo.borderWidth;
    int numberOfSquaresPerXAxis;
    int numberOfSquaresPerYAxis;

    if (sqrt(float(inputSize)) == int(sqrt(inputSize))) /* square mode */
    {
        numberOfSquaresPerXAxis = numberOfSquaresPerYAxis = sqrt(totalNumberOfSquares);
    }
    else /* rectangle mode */
    {
        /* here, according to the input direction (VERTICAL / HORIZONTAL) 
           we find a rectangle with the smallest difference between width and height */
        int squareRoot = (int)sqrt(totalNumberOfSquares) + 1; /* we only need to go until sqrt(n) because factors repeat themselves*/
        vector<int> width;
        vector<int> height;
        for (int i = 1; i < squareRoot; i++) /* we get all the factors of the number of pairs */
        {
            if (totalNumberOfSquares % i == 0)
            {
                width.push_back(i);
                height.push_back(totalNumberOfSquares / i);
                if (i != totalNumberOfSquares / i)
                {
                    width.push_back(totalNumberOfSquares / i);
                    height.push_back(i);
                }

            }
        }
         
        /* next, we find the rectangle with the smallest difference between width and height */
        int pairIndex = 0; /* the index of the pair with the smallest difference */
        int smallest_diff = abs(width[pairIndex] - height[pairIndex]);
        
        for (int i = 1; i < width.size(); i++)
        {
            if (abs(width[i] - height[i]) <= smallest_diff)
            {
                if (abs(width[i] - height[i]) == smallest_diff)
                {
                    if (encInfo.direction == HORIZONTAL)
                    {
                        if (width[i] >= width[pairIndex])
                        {
                            numberOfSquaresPerXAxis = width[i];
                            numberOfSquaresPerYAxis = height[i];
                            pairIndex = i;
                        }
                    }
                    else
                    {
                        if (height[i] >= height[pairIndex])
                        {
                            numberOfSquaresPerXAxis = width[i];
                            numberOfSquaresPerYAxis = height[i];
                            pairIndex = i;
                        }
                    }
                }
                else
                {
                    numberOfSquaresPerXAxis = width[i];
                    numberOfSquaresPerYAxis = height[i];
                    smallest_diff = abs(width[i] - height[i]);
                    pairIndex = i;
                }

            }
        }
    }

    int outputSizeX = numberOfSquaresPerXAxis*squareSize + (numberOfSquaresPerXAxis + 1)*borderWidth;
    int outputSizeY = numberOfSquaresPerYAxis*squareSize + (numberOfSquaresPerYAxis + 1)*borderWidth;

    vector<Vec4b> colorArray; /* W B G R - OpenCV standard*/
    colorArray.push_back(Vec4b(255, 255, 255, 255));
    colorArray.push_back(Vec4b(0, 0, 255, 255));
    colorArray.push_back(Vec4b(0, 255, 0, 255));
    colorArray.push_back(Vec4b(255, 0, 0, 255));
    colorArray.push_back(Vec4b(0, 0, 0, 255));

    Mat* output = new Mat(outputSizeY, outputSizeX, CV_8UC4, Scalar(0, 0, 0, 255)); /* solid black for borders */
    
    int coloredRowIndex = 0; /* index of each colored row */
    int rowSquareIndex = 0; /* index of the square we're coloring on a row*/
    
    for (int rows = borderWidth; rows < output->rows - borderWidth; rows++)
    {
        for (int cols = borderWidth; cols < output->cols - borderWidth; cols++)
        {
            output->at<Vec4b>(rows, cols) = colorArray[colors[rowSquareIndex]];
            
            if (cols + 1 - borderWidth*(rowSquareIndex%numberOfSquaresPerXAxis + 1))
            {
                /* if the number of columns - the borders' size is a multiple of the squares' size
                    it means we finished drawing a part of the current square */
                if ((cols + 1 - borderWidth*(rowSquareIndex%numberOfSquaresPerXAxis + 1)) % squareSize == 0)
                {
                    cols += borderWidth; /* add border width */
                    rowSquareIndex++; /* increment square index */
                }
            }
        }
        if (rows + 1 - borderWidth*(coloredRowIndex + 1))
        {
            /* if the number of rows - the borders' size is a multiple of the squares' size
            it means we finished drawing an entire colored row */
            if ((rows + 1 - borderWidth*(coloredRowIndex + 1)) % squareSize == 0)
            {
                coloredRowIndex++; /* increment the number of colored rows */
                rows += borderWidth; /* add border width*/
            }
            else /* otherwise, we're simply coloring the next row */
            {
                rowSquareIndex -= numberOfSquaresPerXAxis; /* we reset the square index to the first one of the last row */
            }
        }
    }
    /* OpenCV debug output */
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", *output);
    waitKey(0);
    imwrite("ouput.png", *output);
    return output;
}
