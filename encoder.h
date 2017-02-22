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

#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
using namespace cv;

#include<string>
#include<vector>
using namespace std;

#include "colors.h"

enum Direction
{
    VERTICAL,
    HORIZONTAL
};
struct EncodingInfo
{
    int squareSize, borderWidth;
    Direction direction;
    EncodingInfo(int squareSize, int borderWidth, Direction direction) : squareSize(squareSize), borderWidth(borderWidth), direction(direction) {}
};
class Encoder
{
    string input;
    vector<Color> colors;
public:
    Encoder();
    Encoder(const string &text);
    vector<Color> encode();
    vector<Color> encodeBits(vector<vector<int>> bits);
    Mat* renderImage(EncodingInfo encInfo);
    string outputText();
};
