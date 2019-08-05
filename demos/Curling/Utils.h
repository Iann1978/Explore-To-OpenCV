#pragma once
#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //包含cv命名空间

struct EllipsePara
{
	Point2f c;
	float A;
	float B;
	float C;
	float F;
};

struct EllipseData
{
	RotatedRect box;
	EllipsePara param;
	vector<vector<Point>> contours;
	void Reset()
	{
		contours.clear();
	}
};

struct CurlingArenaRebuildingData
{
	Mat				srcImage;
	EllipseData		bigCircle;
	Vec2f			topEdge;
	Vec2f			leftEdge;
	Vec2f			rightEdge;

	Point			topLeftPoint;
	Point			topRightPoint;
	Point			centerPoint;

	void Reset()
	{
		bigCircle.Reset();
	}
};
void getEllipsePara(RotatedRect& ellipsemege, EllipsePara& EP_t);
void myMeanStdDev(std::vector<float>& array, float& mean, float& dev);
void myMeanStdDev(std::vector<cv::Point>& array, Point& mean, float& dev);
float ellips_value(EllipsePara ep, Point p);