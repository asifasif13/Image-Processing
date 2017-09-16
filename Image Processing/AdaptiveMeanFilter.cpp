#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void adaptiveMeanFilter(Mat image)
{
	Mat finalImage = image.clone();
	Mat img;
	cout << "Enter the value of gloabal sigma:  ";
	double sigmaN;
	cin >> sigmaN;
	cout << "Enter the mask size: ";
	int mask;
	cin >> mask;
	int border = mask / 2;
	copyMakeBorder(image, img, border, border, border, border, BORDER_CONSTANT, 0);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int sigmaL;
			int meanL;
			// calculate mean
			int sum1 = 0;
			for (int k = -border; k <= border; k++)
			{
				for (int l = -border; l <= border; l++)
				{
					int val = img.at<uchar>(i+k+border,j+l+border);
					sum1 = sum1 +val;
				}
			}
			meanL = sum1 / (mask*mask);
			//calculate local variance
			int sum2 = 0.0;
			for (int k = -border; k <= border; k++)
			{
				for (int l = -border; l <= border; l++)
				{
					int val = img.at<uchar>(i+k+border,j+l+border);
					sum2 = sum2 + pow(meanL-val,2);

				}
			}
			sigmaL = sum2 / (mask*mask);
			// calculate adpative formula
			if (sigmaL < sigmaN)
				sigmaL = sigmaN;
			int val = image.at<uchar>(i,j);
			double temp = (double)val - (sigmaN / sigmaL)*((double)val-meanL);
			finalImage.at<uchar>(i, j) = (int)temp;
		}
	}

	imshow("Output Image",finalImage);
	waitKey(0);
}

int main()
{
	Mat image = imread("Fig0513(a)(ckt_gaussian_var_1000_mean_0).tif",0);
	imshow("Input Image", image);
	adaptiveMeanFilter(image);
}