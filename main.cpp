#include "filters.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	Mat image, result;
	String file = "TwoTime.jpg";
	String type = "Blue";	
	image = imread(file, CV_LOAD_IMAGE_COLOR);
	result = image.clone();
	Mat src = imread(file, CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = src.clone();
	Mat temp = src.clone();
	Mat color;
	result = Color_Init(image,result);
	dst = Gray_Init(image,dst);
	temp = Gray_Init(image,temp);
	Filter_Type(image,result,src,dst,temp,color,type);
	waitKey();
	return 0;
}		
