#ifndef VARIABLE
#define VARIABLE
// Write your header file here.
#include<string>
#include<math.h> 

#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>

#define filterWidth 5
#define filterHeight 5


using namespace std;
using namespace cv;
using namespace cgicc;


class Linear
{
public:
	float factor = 0;       
	float bias = 0;
	float filter[filterWidth][filterHeight] = { {0} };
	Mat image;
};

int geto(int gx, int gy);
int xGradient(Mat image, int x, int y);
int yGradient(Mat image, int x, int y);
Mat edgeDetection(Mat src, Mat dst);
Mat colorEdges(Mat src, String color);
Linear chooseFilter(int choice);
Mat applyFilter(Mat image, Mat result,Linear object);
Mat medianFilter(Mat image, Mat dst);
Mat cartoonify(Mat image, Mat src, Mat dst, Mat temp);
#endif