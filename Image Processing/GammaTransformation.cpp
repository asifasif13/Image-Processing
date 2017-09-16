// Formula s = c*(r/255)^gamma*255

#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("Fig0308(a)(fractured_spine).tif",0);
	Mat finalImage = image.clone();
	cout << "Enter the value of Gamma: ";
	double gamma;
	cin >> gamma;

	// let the value of c is 1
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int r = image.at<uchar>(i,j);
			double temp = pow((double)r / 255.0, gamma)*255.0;
			finalImage.at<uchar>(i, j) = (int)temp;
		}
	}

	imshow("Original Image",image);
	imshow("Output Image",finalImage);
	waitKey(0);
}