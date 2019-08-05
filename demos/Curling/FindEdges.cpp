
#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv; //包含cv命名空间
static int threshold1 = 107;
static int threshold2 = 200;
static Mat srcImage_Grey, edges_Grey, edgesImage;
static void on_Trackbar(int, void* data)
{
	Mat& srcImage = *(Mat*)data;
	
	cvtColor(srcImage, srcImage_Grey, CV_BGR2GRAY);//转化边缘检测后的图为灰度图

	Canny(srcImage_Grey, edges_Grey, threshold1, threshold2, 3);//进行一此canny边缘检测
	cvtColor(edges_Grey, edgesImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图
	imshow("edgesImage", edgesImage);
}

Mat FindEdges(Mat& srcImage)
{
	on_Trackbar(0, &srcImage);
	createTrackbar("threshold1", "edgesImage", &threshold1, 200, on_Trackbar, &srcImage);
	createTrackbar("threshold2", "edgesImage", &threshold2, 500, on_Trackbar, &srcImage);
	return edgesImage;
}