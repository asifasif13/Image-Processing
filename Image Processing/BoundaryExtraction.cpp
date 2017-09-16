#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat erosion(Mat image)
{
	int mask;
	cout << "Enter the mask size: ";
	cin >> mask;
	Mat finalImage = image.clone();
	Mat img;
	copyMakeBorder(image, img, mask / 2, mask / 2, mask / 2, mask / 2, BORDER_CONSTANT, 0);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j <image.cols; j++)
		{
			int count = 0;
			for (int l = -mask / 2, m = 0; l <= mask / 2; l++)
			{
				for (int k = -mask / 2, n = 0; k <= mask / 2; k++)
				{
					int val = img.at<uchar>(i + l + mask / 2, j + k + mask / 2);
					if (val == 255)
						count++;
				}
			}
			if (count == mask * mask)
				finalImage.at<uchar>(i, j) = 255;
			else
				finalImage.at<uchar>(i, j) = 0;
		}
	}
	
	return finalImage;
}

void extractBoundary(Mat mainImage,Mat erotedImage){
	
	Mat finalImage = mainImage.clone();

	for (int i = 0; i < mainImage.rows; i++)
	{
		for (int j = 0; j < mainImage.cols; j++)
		{
			int val1 = mainImage.at<uchar>(i,j);
			int val2 = erotedImage.at<uchar>(i,j);
			finalImage.at<uchar>(i,j) = val1-val2;
		}
	}
	imshow("Output",finalImage);
	waitKey(0);
}

int main()
{
	Mat image = imread("Fig0914(a)(licoln from penny).tif", 0);
	imshow("Input", image);
	Mat  erotedImage = erosion(image);
	extractBoundary(image,erotedImage);
}