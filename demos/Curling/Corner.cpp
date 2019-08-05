#include <opencv2/opencv.hpp> //ͷ�ļ�
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //����cv�����ռ�
static int k = 7;
static Mat greyImage_Gray, cornerStrength, harrisCorner;
static void on_Trackbar(int, void* data)
{
	Mat& srcImage = *(Mat*)data;

	cvtColor(srcImage, greyImage_Gray, CV_BGR2GRAY);
	cornerHarris(greyImage_Gray, cornerStrength, 2, 3, 1.0f*k/100);
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("harrisCorner", harrisCorner);
}

Mat FindCorners(Mat& srcImage)
{
	on_Trackbar(0, &srcImage);
	createTrackbar("k", "harrisCorner", &k, 100, on_Trackbar, &srcImage);
	

	return harrisCorner;
}