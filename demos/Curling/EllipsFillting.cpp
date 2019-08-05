#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //包含cv命名空间
#include "Utils.h"






static int slider_dev0 = 73;
static int slider_dev1 = 187;

static Mat edge_image;
static Mat cimage;
static void on_Trackbar(int, void* data)
{
	Mat& src_image = *(Mat*)data;

	imshow("原图", src_image);

	//轮廓
	vector<vector<Point>> contours;

	//使用canny检测出边缘
	
	src_image.convertTo(edge_image, 0x10);
	//Canny(src_image, edge_image, 50, 200, 3);
	//imshow("canny边缘", edge_image);

	//边缘追踪，没有存储边缘的组织结构
	findContours(edge_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cimage = Mat::zeros(edge_image.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		//拟合的点至少为6
		size_t count = contours[i].size();
		if (count < 6)
			continue;

		//椭圆拟合
		RotatedRect box = fitEllipse(contours[i]);

		// 位置过滤
		if (box.center.x < 150)
			continue;

		if (box.center.x > 400)
			continue;

		if (box.center.y > 400)
			continue;

		//形状过滤          如果长宽比大于30，则排除，不做拟合
		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)
			continue;
		if (MIN(box.size.width, box.size.height) < 10)
			continue;

		// 计算椭圆参数
		EllipsePara ep;
		getEllipsePara(box, ep);
		std::cout << ep.A << " " << ep.B << " " << ep.C << " " << ep.F << std::endl;

		std::vector<float> array;
		std::vector<Point> array1;
		for (int j = 0; j < contours[i].size(); j++)
		{
			float f = ellips_value(ep, contours[i][j]);
			array.push_back(f);
			array1.push_back(contours[i][j]);
		}

		float mean;
		float dev;
		myMeanStdDev(array, mean, dev);
		dev /= MAX(box.size.width, box.size.height);

		Point mean1;
		float dev1;
		myMeanStdDev(array1, mean1, dev1);
		float dev0_threshold = exp( 1.0f * slider_dev0 / 10);
			
		// 拟合可信度过滤
		if (dev1 < slider_dev1)
			continue;

		// 拟合度过滤
		if (dev > dev0_threshold)
			continue;

		//画出追踪出的轮廓
		drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);

		//画出拟合的椭圆
		ellipse(cimage, box, Scalar(0, 0, 255), 1, CV_AA);

	}
	imshow("椭圆拟合结果", cimage);
}



Mat EllipsFillting(Mat& src_image)
{	
	on_Trackbar(0, &src_image);
	createTrackbar("slider_dev0", "椭圆拟合结果", &slider_dev0, 200, on_Trackbar, &src_image);
	createTrackbar("slider_dev1", "椭圆拟合结果", &slider_dev1, 200, on_Trackbar, &src_image);
	return cimage;
}
