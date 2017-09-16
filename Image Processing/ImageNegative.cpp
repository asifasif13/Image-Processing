#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("Fig0304(a)(breast_digital_Xray).tif",0);
	Mat negativeImage = image.clone();
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols; j++)
		{
			int r = image.at<uchar>(i,j);
			int s = 255 - r;
			negativeImage.at<uchar>(i, j) = s;
		}

	}

	imshow("Original Image",image);
	imshow("Negative Image",negativeImage);
	waitKey(0);
}