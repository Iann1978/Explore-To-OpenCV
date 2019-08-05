
#include "Utils.h"
void getEllipsePara(RotatedRect& ellipsemege, EllipsePara& EP_t)
{
	float theta = ellipsemege.angle * CV_PI / 180.0;
	float a = ellipsemege.size.width / 2.0;
	float b = ellipsemege.size.height / 2.0;

	EP_t.c.x = ellipsemege.center.x;
	EP_t.c.y = ellipsemege.center.y;

	EP_t.A = a * a * sin(theta) * sin(theta) + b * b * cos(theta) * cos(theta);
	EP_t.B = (-2.0) * (a * a - b * b) * sin(theta) * cos(theta);
	EP_t.C = a * a * cos(theta) * cos(theta) + b * b * sin(theta) * sin(theta);
	EP_t.F = (-1.0) * a * a * b * b;
}

void myMeanStdDev(std::vector<float>& array, float& mean, float& dev)
{
	cv::Mat   img = cv::Mat_<float>(array.size(), 1);
	for (int i = 0; i < array.size(); i++)
	{
		img.at<float>(i, 0) = array[i];
	}


	cv::Scalar     _mean;
	cv::Scalar     _dev;

	cv::meanStdDev(img, _mean, _dev);
	mean = _mean.val[0];
	dev = _dev.val[0];
	//std::cout << m << ",\t" << s;

}



void myMeanStdDev(std::vector<cv::Point>& array, Point& mean, float& dev)
{
	mean.x = mean.y = 0;
	for (int i = 0; i < array.size(); i++)
	{
		mean += array[i];
	}
	mean.x = mean.x / array.size();
	mean.y = mean.y / array.size();

	dev = 0;
	for (int i = 0; i < array.size(); i++)
	{
		Point p = array[i];
		dev += (p.x - mean.x) * (p.x - mean.x) + (p.y - mean.y) * (p.y - mean.y);
	}
	dev /= array.size();
}

float ellips_value(EllipsePara ep, Point p)
{
	float x = p.x - ep.c.x;
	float y = p.y - ep.c.y;
	return ep.A * x * x + ep.B * x * y + ep.C * y * y + ep.F;
}







