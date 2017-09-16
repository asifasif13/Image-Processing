#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("Fig0310(b)(washed_out_pollen_image).tif",0);
	Mat finalImage = image.clone();
	int max=0, min=300;
	double average=0.0;
	int count = 0;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			
			int value = image.at<uchar>(i, j);
			average = average + value;
			count++;
			if (value>max)
				max = value;
			if (value < min)
				min = value;
		}
	}
	cout << "Maximum pixel value : "<<max <<endl<<"Minimum pixel value: " << min << endl;
	cout << "Average of pixel value: "<<(int)average / count << endl;

	cout << "Enter the value of Point 1: ";
	int r1, s1;
	cin >> r1 >> s1;
	cout << "Enter the value of Point 2: ";
	int r2, s2;
	cin >> r2 >> s2;

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int value = image.at<uchar>(i,j);
			if (value >= 0 && value <= r1)
			{
				double y = (double)(value*s1) / (double)r1;
				finalImage.at<uchar>(i, j) = (int)y;
			}
			else if (value>r1 && value <= r2)
			{
				double y = ((double)((value - r1)*(s1 - s2)) / (double)(r1 - r2))+s1;
				finalImage.at<uchar>(i, j) = (int)y;
			}
			else
			{
				double y = ((double)((value - r2)*(s2 - 255)) / (double)(r2 - 255))+s2;
				finalImage.at<uchar>(i, j) = (int)y;
			}
		}
	}

	imshow("Original Image",image);
	imshow("Output Image",finalImage);
	waitKey(0);

}