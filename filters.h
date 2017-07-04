#ifndef VARIABLE
#define VARIABLE
// Write your header file here.
#include<iostream>
#include<string>
#include<math.h> 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#define filterWidth 5
#define filterHeight 5


class Linear
{
public:
	double factor;       
	double bias;
	double filter[filterWidth][filterHeight];
	cv::Mat image;
};
cv::Mat Color_Init(cv::Mat image, cv::Mat result);
cv::Mat Gray_Init(cv::Mat image, cv::Mat result);
int geto(int gx, int gy);
int xGradient(cv::Mat image, int x, int y);
int yGradient(cv::Mat image, int x, int y);
cv::Mat edgeDetection(cv::Mat src, cv::Mat dst);
cv::Mat colorEdges(cv::Mat src, int color);
Linear chooseFilter(int choice);
cv::Mat applyFilter(cv::Mat image, cv::Mat result,Linear object);
cv::Mat medianFilter(cv::Mat image, cv::Mat dst);
cv::Mat cartoonify(cv::Mat image, cv::Mat src, cv::Mat dst, cv::Mat temp);
void Filter_Type(cv::Mat image, cv::Mat result, cv::Mat src, cv::Mat dst, cv::Mat temp,cv::Mat color,std::string type);
#endif
