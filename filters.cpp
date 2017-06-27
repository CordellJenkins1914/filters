#include<iostream>
#include "filters.h"


using namespace std;
using namespace cv;



class Linear
{
public:
	float factor = 0;       
	float bias = 0;
	float filter[filterWidth][filterHeight] = { {0} };
	Mat image;
};

int geto(int gx, int gy)
{
	return(((gx == 0) && (gy == 0)) ? 0 : int((atan2(gy, gx) * 180 / CV_PI)));
}
int xGradient(Mat image, int x, int y)
{
	return image.at<uchar>(y - 1, x - 1) +
		2 * image.at<uchar>(y, x - 1) +
		image.at<uchar>(y + 1, x - 1) -
		image.at<uchar>(y - 1, x + 1) -
		2 * image.at<uchar>(y, x + 1) -
		image.at<uchar>(y + 1, x + 1);
}


int yGradient(Mat image, int x, int y)
{
	return image.at<uchar>(y - 1, x - 1) +
		2 * image.at<uchar>(y - 1, x) +
		image.at<uchar>(y - 1, x + 1) -
		image.at<uchar>(y + 1, x - 1) -
		2 * image.at<uchar>(y + 1, x) -
		image.at<uchar>(y + 1, x + 1);
}

Mat edgeDetection(Mat src, Mat dst)
{
	int gx, gy, mag;
	double angle;
	double tan;

	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
		{
			dst.at<uchar>(y, x) = 0.0;
		}

	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			gx = xGradient(src, x, y);
			gy = yGradient(src, x, y);
			mag = abs(gx) + abs(gy);
			angle = geto(gx, gy);
			mag = mag > 255 ? 255 : mag;
			mag = sum < 0 ? 0 : mag;
			dst.at<uchar>(y, x) = mag;

		}
	}
	return dst;
}

Mat colorEdges(Mat src, String color)
{
    int red = 0;
    int blue = 0;
    int green = 0;
    
    if(color.compare("Red")==0){
         red = 243;
    }
    else if(color.compare("Green")==0){
         green = 243;
    }
    else if(color.compare("Blue")==0){
         blue = 243;
    }
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
		{
			
			if (src.at<uchar>(y, x)  < 75) {
				Vec3b RGB = dst.at<Vec3b>(y, x);
				RGB.val[0] = 0;
				RGB.val[1] = 0;
				RGB.val[2] = 0;
				dst.at<Vec3b>(Point(x, y)) = RGB;
			}
			else {
				Vec3b RGB = dst.at<Vec3b>(y, x);
				RGB.val[0] = red;
				RGB.val[1] = green;
				RGB.val[2] = blue;
				dst.at<Vec3b>(Point(x, y)) = RGB;
			}

		}
	return dst;

}

Linear chooseFilter(int choice) {
	
	int emboss[25] = { -1, -1, -1, -1,  0, -1, -1, -1,  0,  1, -1, -1,  0,  1,  1, -1,  0,  1,  1,  1, 0,  1,  1,  1,  1 };
	int blur[25] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
	int edge[25] = { -1, -1, -1,-1,-1,-1,  -1, -1,-1,-1,-1, -1, 24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int x = 0;
	Linear object;
	
	switch (choice)
	{
		case 1:	
			for (int filterX = 0; filterX < filterWidth; filterX++)
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					object.filter[filterX][filterY] = emboss[x];
					x++;
				}


		object.factor = 1.0;
		object.bias = 128.0;
		break;

		case 2:
			for (int filterX = 0; filterX < filterWidth; filterX++)
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					object.filter[filterX][filterY] = blur[x];
					x++;
				}


			object.factor = 1.0/5.0;
			object.bias = 0.0;
			break;

		case 3:
			for (int filterX = 0; filterX < filterWidth; filterX++)
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					object.filter[filterX][filterY] = edge[x];
					x++;
				}



			object.factor = 1.0;
			object.bias = 0.0;
			break;
	}
	return object;

}
Mat applyFilter(Mat image, Mat result,Linear object) {

	int val;
	for (int x = 0; x < image.cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			double red = 0.0, green = 0.0, blue = 0.0;

			
			for (int filterX = 0; filterX < filterWidth; filterX++)
				for (int filterY = 0; filterY < filterHeight; filterY++)
				{
					int imageX = (x - filterWidth / 2 + filterX + image.cols) % image.cols;
					int imageY = (y - filterHeight / 2 + filterY + image.rows) % image.rows;
					Vec3b RGB = image.at<Vec3b>(imageY, imageX);
					red += RGB.val[2] * object.filter[filterX][filterY];
					green += RGB.val[1] * object.filter[filterX][filterY];
					blue += RGB.val[0] * object.filter[filterX][filterY];
				}

			
			Vec3b RGBC = result.at<Vec3b>(y, x);

			RGBC.val[2] = min(max(int(object.factor * red + object.bias), 0), 255);


			RGBC.val[1] = min(max(int(object.factor * green + object.bias), 0), 255);


			RGBC.val[0] = min(max(int(object.factor * blue + object.bias), 0), 255);


			result.at<Vec3b>(y, x) = RGBC;
		}
	return result;
}
Mat medianFilter(Mat image, Mat dst)
{
	uchar gray[filterWidth * filterHeight];
	for (int x = 0; x < image.cols; x++)
		for (int y = 0; y < image.rows; y++)
		{
			int n = 0;

			
			for (int filterX = 0; filterX < filterWidth; filterX++)
				for (int filterY = 0; filterY < filterHeight; filterY++)
				{
					int imageX = (x - filterWidth / 2 + filterX + image.cols) % image.cols;
					int imageY = (y - filterHeight / 2 + filterY + image.rows) % image.rows;
					gray[n] = image.at<uchar>(imageY, imageX);
					n++;
				}
			int amount = filterWidth * filterHeight;
			 int gap = amount;
			 bool swapped = false;
			 while(gap > 1 || swapped)
			 {
				
				gap = (gap * 10) / 13;
				if(gap == 9 || gap == 10) gap = 11;
				if (gap < 1) gap = 1;
				swapped = false;
				for (int i = 0; i < amount - gap; i++)
				{
					int j = i + gap;
					if (gray[i] > gray[j])
					{
						gray[i] += gray[j]; 
						gray[j] = gray[i] - gray[j]; 
						gray[i] -= gray[j]; 
						swapped = true;
					}
				}
			}
			 if ((filterWidth * filterHeight) % 2 == 1)
			 {
				 dst.at<uchar>(y, x) = gray[filterWidth * filterHeight / 2];
			 }
			 else if (filterWidth >= 2)
			 {
				 dst.at<uchar>(y, x) = (gray[filterWidth * filterHeight / 2] + gray[filterWidth * filterHeight / 2 + 1]) / 2;
				 
			 }

		}
	return dst;
}
Mat cartoonify(Mat image, Mat src, Mat dst, Mat temp)
{
	temp = medianFilter(src, dst);
	Size size = image.size();
	Mat mask = Mat(size, CV_8U);
	Mat edges = Mat(size, CV_8U);
	Laplacian(temp, edges, CV_8U, 5);
	threshold(edges, mask, 80, 255, THRESH_BINARY_INV);
	Size smallSize;
	smallSize.width = size.width / 2;
	smallSize.height = size.height / 2;
	Mat smallImg = Mat(smallSize, CV_8UC3);
	resize(image, smallImg, smallSize, 0, 0, INTER_LINEAR);
	Mat tmp = Mat(smallSize, CV_8UC3);
	int repetitions = 7;
	for (int i = 0; i<repetitions; i++)
	{
		int size = 9;
		double sigmaColor = 9;
		double sigmaSpace = 7;
		bilateralFilter(smallImg, tmp, size, sigmaColor, sigmaSpace);
		bilateralFilter(tmp, smallImg, size, sigmaColor, sigmaSpace);
	}

	resize(smallImg, image, size, 0, 0, INTER_LINEAR);
	image.copyTo(dst, mask);
	return dst;
}
