#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include "baseutils.h"
#include "encoder.h"
#include "decoder.h"
#include <iostream> 
using namespace std;
using namespace cv;

int main()
{
	cout << "Copyright Alexandru Bratosin 2017" << endl << endl;
	cout << "Input: ";
	string input;
	getline(cin, input);

	Encoder encoder;
	Decoder decoder;

	do
	{
		Mat rendered = encoder.encodeAndRenderImage(input, RenderingInfo(Size2i(1000, 700), 8));
		cout << decoder.decode(rendered) << endl;
		imshow("Output", rendered);
		waitKey(0);
		imwrite("output.png", rendered);
	} while (waitKey(0));
	
	getchar();
	return 0;
}
