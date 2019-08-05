#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
#include "Utils.h"
using namespace cv; //包含cv命名空间



static int Canny_threshold1 = 200;
static int Canny_threshold0 = 155;
static int HoughLines_threshold = 140;
static Mat midImage, dstImage;
static Vec2f resultLine;
static void refreshIceArena_TopEdge(int debug, void* data)
{
	Mat& srcImage = *(Mat*)data;

	Canny(srcImage, midImage, Canny_threshold0, Canny_threshold1, 3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);
	if (debug) imshow("IceArena_TopEdge_midImage", midImage);

	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 360, HoughLines_threshold, 0, 0);

	//【4】依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		if (theta > 1 * CV_PI / 4 && 
			theta < 3 * CV_PI / 4 )
		{
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a * rho, y0 = b * rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
			resultLine = lines[i];
		}

	}
	if (debug) imshow("IceArena_TopEdge_dstImage", dstImage);
}

void FindIceArena_TopEdge(CurlingArenaRebuildingData& rebuildingData)
{
	refreshIceArena_TopEdge(0, &rebuildingData.srcImage);
	createTrackbar("Canny_threshold1", "IceArena_TopEdge_dstImage", &Canny_threshold1, 500, refreshIceArena_TopEdge, &rebuildingData.srcImage);
	createTrackbar("Canny_threshold0", "IceArena_TopEdge_dstImage", &Canny_threshold0, 500, refreshIceArena_TopEdge, &rebuildingData.srcImage);
	createTrackbar("HoughLines_threshold", "IceArena_TopEdge_dstImage", &HoughLines_threshold, 500, refreshIceArena_TopEdge, &rebuildingData.srcImage);
	//return resultLine;
}


