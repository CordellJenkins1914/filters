#include <iostream>
#include "filters.h"

using namespace cv;
using namespace cgicc;

int main(int argc, char *argv[])
{
	Mat image, result;
	Cgicc formData;
	Cgicc cgi;

    cout << HTTPHTMLHeader() << endl;
    cout << HTMLDoctype(HTMLDoctype::eStrict) << endl;
    cout << html().set("lang", "EN").set("dir", "LTR") << endl;
    cout << html() << head() << title("Cgicc example") << head() << endl;
    cout << body().set("bgcolor","#cccccc").set("text","#000000").set("link","#0000ff").set("vlink","#000080") << endl;
	
	
	form_iterator fvalue = formData.getElement("dropdown");
    if( !fvalue->isEmpty() && fvalue != (*formData).end()) {
            String type = **fvalue).c_str();
        }
        
     cout << "<br/>\n";
     // get list of files to be uploaded
   const_file_iterator file = cgi.getFile("userfile");
   if(file != cgi.getFiles().end()) {
      // send data type at cout.
      cout << HTTPContentHeader(file->getDataType());
      // write content at cout.
      file->writeToStream(cout);
   }
     cout << "</body>\n";
     cout << "</html>\n";
        
	if(!file.data){
	    return 0;
	}
	
	
	
	image = imread(file, CV_LOAD_IMAGE_COLOR);
	result = image.clone();

	Mat src = imread(file, CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = src.clone();
	Mat temp = src.clone();
	Mat color;
	
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
		{
			Vec3b RGB = result.at<Vec3b>(y, x);
			RGB.val[0] = 0;
			RGB.val[1] = 0;
			RGB.val[2] = 0;
			result.at<Vec3b>(Point(x, y)) = RGB;
		}
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
		{
	
			
			dst.at<uchar>(y, x) = 0;
			temp.at<uchar>(y, x) = 0;
			
		}
		
	if (type.compare("emboss") == 0){
	    
	    choice = 1;
	    Linear object = chooseFilter(choice);
	    result = applyFilter(image, result, object);
	    namedWindow("final", CV_WINDOW_AUTOSIZE);
	    imshow("final", result);
	    
	}
	else if (type.compare("blur") == 0){
		choice = 2;
		Linear object = chooseFilter(choice);
	    result = applyFilter(image, result, object);
	    namedWindow("final", CV_WINDOW_AUTOSIZE);
	    imshow("final", result);
    }

	else if (type.compare("edge") == 0){
		choice = 3;
        Linear object = chooseFilter(choice);
	    result = applyFilter(image, result, object);
	    namedWindow("final", CV_WINDOW_AUTOSIZE);
	    imshow("final", result);
    }
	 
	else if (type.compare("median") == 0)
	{
		dst = medianFilter(src, dst);

		namedWindow("final", CV_WINDOW_AUTOSIZE);
		imshow("final", dst);
		
	}
	else if (type.compare("Red") == 0)
	{

		dst = edgeDetection(src, dst);
		color = colorEdges(dst,type);

		namedWindow("Edge color", CV_WINDOW_AUTOSIZE);
		imshow("Edge color", color);
		
	}
	else if (type.compare("Blue") == 0)
	{

		dst = edgeDetection(src, dst);
		color = colorEdges(dst,type);

		namedWindow("Edge color", CV_WINDOW_AUTOSIZE);
		imshow("Edge color", color);
		
	}
	else if (type.compare("Green") == 0)
	{

		dst = edgeDetection(src, dst);
		color = colorEdges(dst,type);

		namedWindow("Edge color", CV_WINDOW_AUTOSIZE);
		imshow("Edge color", color);
		
	}
	else if (type.compare("cartoon") == 0)
	{
		dst = cartoonify(image, src, dst, temp);
		namedWindow("Cartoon", CV_WINDOW_AUTOSIZE);
		imshow("Cartoon", dst);
		
	}
	waitKey();
	return 0;
}