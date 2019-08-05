#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //包含cv命名空间



static int Canny_threshold1 = 200;
static int Canny_threshold0 = 50;
static int HoughLines_threshold = 200;
static Mat midImage, dstImage;

static void refreshTopLine(int, void* data)
{
	Mat& srcImage = *(Mat*)data;

	Canny(srcImage, midImage, Canny_threshold0, Canny_threshold1, 3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);
	imshow("FindLines_midImage", midImage);

	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 360, HoughLines_threshold, 0, 0);

	//【4】依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}

	imshow("FindLines_dstImage", dstImage);
}

static vector<Vec2f> FindTopLine(Mat& srcImage)
{
	
	refreshTopLine(0, &srcImage);
	createTrackbar("Canny_threshold1", "FindLines_midImage", &Canny_threshold1, 500, refreshTopLine, &srcImage);
	createTrackbar("Canny_threshold0", "FindLines_midImage", &Canny_threshold0, 500, refreshTopLine, &srcImage);
	createTrackbar("HoughLines_threshold", "FindLines_midImage", &HoughLines_threshold, 500, refreshTopLine, &srcImage);
	return vector<Vec2f>();
}

Mat FindLines(Mat& srcImage)
{
	FindTopLine(srcImage);
	
	return dstImage;
}



