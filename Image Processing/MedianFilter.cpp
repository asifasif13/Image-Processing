#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("Fig0335(a)(ckt_board_saltpep_prob_pt05).tif",0);
	Mat finalImage = image.clone();
	Mat img;

	// let's the mask is 3x3
	copyMakeBorder(image,img,1,1,1,1,BORDER_CONSTANT,0);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			vector<int>v;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					int temp = img.at<uchar>(k+i+1,l+j+1);
					v.push_back(temp);
				}
			}
			sort(v.begin(),v.end());
			finalImage.at<uchar>(i, j) = v[4];
		}
	}
	imshow("Original Image",image);
	imshow("OutputImage",finalImage);
	waitKey(0);
}