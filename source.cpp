#include <iostream> //temporary
#include "baseutils.h"
#include "encoder.h"
using namespace std;
using namespace cv;

int main()
{
    cout << "Input: ";
    string input;
    getline(cin, input);

    Encoder encoder;
    string output = encoder.encodeAndOutputText(input);
    cout << output << endl;
    Mat rendered = encoder.encodeAndRenderImage(input, RenderingInfo(Vec2i(800, 500), 8));
    imwrite("output.png", rendered);

    getchar();
    return 0;
}
