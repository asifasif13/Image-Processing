















#include <iostream>
#include <math.h>
#include <set>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

double pK[256];

void draw_histogram(Mat image,string name)
{
	int nK[256] = { 0 };
	for (int i = 0; i <image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int val = image.at<uchar>(i,j);
			nK[val]++;
		}
	}
	
	for (int i = 0; i < 256; i++)
	{
		double val =(double) nK[i] / (double)(image.rows*image.cols);
		pK[i] = val;
	}
	Mat histo(300,256,CV_8UC1,255);
	double max = 0.0;
	for (int i = 0; i < 256; i++)
	{
		if (pK[i]>max)
			max = pK[i];
	}
	double relation = 300 / max;
	for (int i = 0; i < 256; i++)
	{
		int val = relation*pK[i];
		line(histo,Point(i,300-val),Point(i,300),0,1);
	}
	imshow(name,image);
	imshow("Histogram of "+name,histo);
}
void histogram_equalization(Mat image)
{

	Mat histImage = image.clone();
	double sK[256];
	sK[0] = 255 * pK[0];
	for (int i = 1; i < 256; i++)
	{
		sK[i] = sK[i - 1] + (255 * pK[i]);
	}
	int norm_sK[256];
	for (int i = 0; i < 256; i++)
	{
		double temp = floor(sK[i] + .50);
		norm_sK[i] = (int)temp;
	}
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int val = image.at<uchar>(i, j);
			histImage.at<uchar>(i, j) = norm_sK[val];
		}
	}
	draw_histogram(histImage,"Output");
	waitKey(0);
}

int main() {

	Mat image = imread("Fig0316(1)(top_left).tif",0);
	draw_histogram(image, "Input");
	histogram_equalization(image);
	return 0;
}