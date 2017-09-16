#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("Fig0333(a)(test_pattern_blurring_orig).tif",0);
	Mat min_filter = image.clone();
	Mat finalImage = image.clone();
	cout << "Enter the mask size: ";

	Mat img;
	int mask;
	cin >> mask;

	copyMakeBorder(image, img, mask/2, mask/2, mask/2, mask/2, BORDER_CONSTANT, 0);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int sum = 0;
			for (int k = -mask/2; k <= mask/2; k++)
			{
				for (int l = -mask/2; l <= mask/2; l++)
				{
					int val = img.at<uchar>(k+i+mask/2,l+j+mask/2);
					sum = sum + val;
				}
			}
			int av = sum / (mask*mask);
			finalImage.at<uchar>(i, j) = av;
		}
	}
	
	imshow("Original Image", image);
	imshow("OutputImage",finalImage);
	waitKey(0);
}