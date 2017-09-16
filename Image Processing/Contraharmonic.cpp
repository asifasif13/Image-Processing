                                                                                                                                                                                                                                                                                               #include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void contraHarmonic(Mat image,double Q)
{
	Mat finalImage = image.clone();
	Mat img;
	copyMakeBorder(image,img,1,1,1,1,BORDER_CONSTANT,0);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			double sum1 = 0.0;
			double sum2 = 0.0;
			for (int l = -1; l <= 1; l++)
			{
				for (int k = -1; k <= 1; k++)
				{
					int val = img.at<uchar>(i+l+1,j+k+1);
					sum1 = sum1 + pow(val, Q + 1);
					sum2 = sum2 + pow(val,Q);
				}
			}
			double res = sum1 / sum2;
			finalImage.at<uchar>(i,j) = (int)res;
		}
	}
	imshow("Output Image",finalImage);
	waitKey(0);
}

int main()
{
	cout << "Enter the order of the filter: ";
	double Q;
	cin >> Q;
	Mat image;
	if (Q>0.0)
	 image = imread("Fig0508(a)(circuit-board-pepper-prob-pt1).tif", 0);
	else
	 image = imread("Fig0508(b)(circuit-board-salt-prob-pt1).tif", 0);

	imshow("Input",image);
	contraHarmonic(image,Q);
}