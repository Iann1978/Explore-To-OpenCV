#pragma once
#include <opencv2/opencv.hpp> //ͷ�ļ�
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //����cv�����ռ�

static struct EllipsePara
{
	Point2f c;
	float A;
	float B;
	float C;
	float F;
};

void getEllipsePara(RotatedRect& ellipsemege, EllipsePara& EP_t);
void myMeanStdDev(std::vector<float>& array, float& mean, float& dev);
void myMeanStdDev(std::vector<cv::Point>& array, Point& mean, float& dev);
float ellips_value(EllipsePara ep, Point p);