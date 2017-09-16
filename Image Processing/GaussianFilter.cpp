#include<iostream>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
double gaussianMask[100][100];
double min_mask_value;


void generate_gaussian_mask(int mask,double sigma){
	double min = 1000000.0;
	for (int i = -mask / 2, m = 0; i <= mask / 2; i++, m++)
	{
		for (int j = -mask / 2, n = 0; j <= mask / 2; j++, n++)
		{
			double temp = (i*i + j*j) / (2.0*sigma*sigma);
			double tmp = exp(-temp);
			double val = tmp / (2.0*3.1416*sigma*sigma);
			if (val <= min)
				min = val;
			cout << val << "  ";
			gaussianMask[m][n] = val;
		}
		cout << endl;
	}
	min_mask_value = min;
}
void show_mask_value_int_form(int mask)
{
	long long sum = 0;
	for (int i = 0; i < mask; i++)
	{
		for (int j = 0; j < mask; j++)
		{
			int val = gaussianMask[i][j] / min_mask_value;
			sum = sum + val;
			cout << val << " ";
		}
		cout << endl;
	}
	cout << endl << "The sum of mask value is : " << sum << endl;



}
int main()
{
	double sigma;
	cout << "Enter the value of sigma: ";
	cin >> sigma;
	double tmp = 5 * sigma;
	int mask = (int)tmp;
	if (mask % 2 == 0)
		mask = mask - 1;
	generate_gaussian_mask(mask,sigma);
	show_mask_value_int_form(mask);
	Mat image = imread("Peppers__.jpg",0);
	Mat finalImage = image.clone();
	Mat img;
	copyMakeBorder(image,img,mask/2,mask/2,mask/2,mask/2,BORDER_CONSTANT,0);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			double sum = 0.0;
			for (int k = -mask / 2,m=0; k <= mask / 2; k++,m++)
			{
				for (int l = -mask / 2,n=0; l <= mask / 2; l++,n++)
				{
					int value = img.at<uchar>(k+i+mask/2,l+j+mask/2);
					double temp = gaussianMask[m][n]*(double)value;
					sum = sum + temp;

				}
			}
			finalImage.at<uchar>(i, j) = (int)sum;
		}
	}
	
	imshow("Original Iamge",image);
	imshow("OutputImage",finalImage);

	waitKey(0);
}