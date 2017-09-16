#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("max.jpg",0);
	Mat finalImage = image.clone();
	Mat img;
	
	// let's the size of the mask is 3x3
	copyMakeBorder(image,img,1,1,1,1,BORDER_CONSTANT,0);

	for (int i = 0; i < image.rows; i++)
	{
		uchar*row = finalImage.ptr<uchar>(i);
		for (int j = 0; j < image.cols; j++)
		{
			int max = -1;
			for (int k = -1; k <= 1; k++)
			{
				uchar* tmp = img.ptr<uchar>(k+i+1);
				for (int l = -1; l <= 1; l++)
				{
					int temp = (int)tmp[l + 1 + j];
					if (temp>max)
						max = temp;
				}
			}
			row[j] = max;
		}
	}
	imshow("Original Image",image);
	imshow("Output Image",finalImage);
	waitKey(0);
}