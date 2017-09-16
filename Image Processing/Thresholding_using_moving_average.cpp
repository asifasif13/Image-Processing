#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

vector<int>v;
vector<double>vv;
double arr[1000][1000];


int main()
{
	Mat image = imread("Fig1049(a)(spot_shaded_text_image).tif",0);
	imshow("Original Image",image);
	cout << image.rows*image.cols << endl;
	for (int i = 0; i < image.rows; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < image.cols; j++)
			{
				int val = image.at<uchar>(i, j);
				v.push_back(val);
			}
		}
		else
		{
			for (int j = image.cols-1; j>=0; j--)
			{
				int val = image.at<uchar>(i, j);
				v.push_back(val);
			}
		}
	}
	vv.push_back(v[0] / 20.0);
	for (int i = 1; i < v.size(); i++)
	{
		long long sum = 0;
		for (int j = i, m = 0; m < 20; m++, j--)
		{
			if (j < 0)
				break;
			sum = sum+v[j];
		}
		vv.push_back(sum/20.0);
	}

	 for (int i = 0; i < vv.size(); i++)
		vv[i] = vv[i] * 0.5;
	cout << vv.size() << endl;
//

	for (int i = 0; i < 686; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < 772; j++)
				arr[i][j] = vv[j];
		}
		else
		{
			for (int j = 771, count = 0; count< 772; count++, j--)
			{
				arr[i][count] = vv[j];
			}
		}
	}
	Mat finalImage = image.clone();
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int value = arr[i][j];
			int val = image.at<uchar>(i,j);
			if (val>value)
				finalImage.at<uchar>(i, j) = 255;
			else
				finalImage.at<uchar>(i, j) = 0;
		}
	}
	imshow("Output", finalImage);
	waitKey(0);
	
	return 0;
}