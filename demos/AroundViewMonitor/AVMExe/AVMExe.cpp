// AVMExe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp> //头文件
#include <math.h>
using namespace cv; //包含cv命名空间

Mat mat0s, mat1s, mat2s, mat3s;
Mat mat0, mat1, mat2, mat3;
int front_deita0 = 0;
int front_deita1 = 1;
int front_deita2 = 0;

int front_top_width_scale = 100;
int front_bottom_width = 512;
int front_top_offcet = 0;
int front_bottom_offcet = 256;

int left_top_width_scale = 100;
int left_bottom_width = 512;
int left_top_offcet = 0;
int left_bottom_offcet = 256;

void on_Trackbar(int, void*)
{
	mat0s.copyTo(mat0);
	mat1s.copyTo(mat1);
	mat2s.copyTo(mat2);
	mat3s.copyTo(mat3);

	// transform mat0
	Point2f srcTriangle[4];
	Point2f dstTriangle[4];
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(512, 0);
	srcTriangle[2] = Point2f(0, 256);
	srcTriangle[3] = Point2f(512, 256);

	dstTriangle[0] = Point2f(512 - front_bottom_width * exp(1.0f*front_top_width_scale/ 100) / 2, -front_top_offcet * 10);
	dstTriangle[1] = Point2f(512 + front_bottom_width * exp(1.0f*front_top_width_scale / 100) / 2, -front_top_offcet * 10);
	dstTriangle[2] = Point2f(512 - front_bottom_width / 2, front_bottom_offcet);
	dstTriangle[3] = Point2f(512 + front_bottom_width / 2, front_bottom_offcet);

	Mat trans = getPerspectiveTransform(srcTriangle, dstTriangle);
	warpPerspective(mat0, mat0, trans, Size(1024, 1024));

	// transform mat1
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(512, 0);
	srcTriangle[2] = Point2f(0, 256);
	srcTriangle[3] = Point2f(512, 256);

	dstTriangle[0] = Point2f(-left_top_offcet * 10, 512 + left_bottom_width * exp(1.0f*left_top_width_scale / 100) / 2);
	dstTriangle[1] = Point2f(-left_top_offcet * 10, 512 - left_bottom_width * exp(1.0f*left_top_width_scale / 100) / 2);
	dstTriangle[2] = Point2f(left_bottom_offcet, 512 + left_bottom_width / 2);
	dstTriangle[3] = Point2f(left_bottom_offcet, 512 - left_bottom_width / 2);

	trans = getPerspectiveTransform(srcTriangle, dstTriangle);
	warpPerspective(mat1, mat1, trans, Size(1024, 1024));

	// transform mat2
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(512, 0);
	srcTriangle[2] = Point2f(0, 256);
	srcTriangle[3] = Point2f(512, 256);

	dstTriangle[0] = Point2f(1024, 0);
	dstTriangle[1] = Point2f(1024, 512);
	dstTriangle[2] = Point2f(1024-256, 0);
	dstTriangle[3] = Point2f(1024-256, 512);

	trans = getPerspectiveTransform(srcTriangle, dstTriangle);
	warpPerspective(mat3, mat3, trans, Size(1024, 1024));

	// rotate mat2
	//Mat rot3 = getRotationMatrix2D(Point2f(128.0f, 128.0f), -90.0f, 1.0f);
	//warpAffine(mat3, mat3, rot3, Size(mat3.rows, mat3.cols));





	imshow("mat0", mat0);
	imshow("mat1", mat1);
	imshow("mat2", mat2);
	imshow("mat3", mat3);


	Mat mat16(1024, 1024, CV_8UC3);
	mat0.copyTo(mat16(Rect(0, 0, 1024, 1024)));

	addWeighted(mat16, 0.6, mat1, 0.6, 0., mat16);
	//addWeighted(mat16, 0.6, mat3, 0.6, 0., mat16);

	//mat1.copyTo(mat16(Rect(0, 512 - 256, 256, 512)));
	//mat3.copyTo(mat16(Rect(1024 - 256, 512 - 256, 256, 512)));
	//mat3.copyTo(mat16(Rect(512-128,1024-256, 256, 256)));

	imshow("AVM", mat16);
}
int main()
{
    std::cout << "Hello World!\n"; 

	mat0s = imread("0.png");
	mat1s = imread("1.png");
	mat2s = imread("2.png");
	mat3s = imread("3.png");
	resize(mat0s, mat0s, mat0s.size() / 2, 0, 0);
	resize(mat1s, mat1s, mat1s.size() / 2, 0, 0);
	resize(mat2s, mat2s, mat2s.size() / 2, 0, 0);
	resize(mat3s, mat3s, mat3s.size() / 2, 0, 0);

	Mat flipy_x(mat0s.size(), CV_32FC1);
	Mat flipy_y(mat0s.size(), CV_32FC1);

	for (int row = 0; row < mat0s.rows; row++)
	{
		for (int col = 0; col < mat0s.cols; col++)
		{
			flipy_x.at<float>(row, col) = static_cast<float>(col);
			flipy_y.at<float>(row, col) = static_cast<float>(mat0s.rows - row);
		}
	}



	remap(mat0s, mat0s, flipy_x, flipy_y, INTER_LINEAR);
	remap(mat1s, mat1s, flipy_x, flipy_y, INTER_LINEAR);
	remap(mat2s, mat2s, flipy_x, flipy_y, INTER_LINEAR);
	remap(mat3s, mat3s, flipy_x, flipy_y, INTER_LINEAR);

	
	namedWindow("AVM", 1);
	createTrackbar("ft_width_s", "AVM", &front_top_width_scale, 500, on_Trackbar);
	createTrackbar("ft_offcet", "AVM", &front_top_offcet, 512, on_Trackbar);

	createTrackbar("fb_width", "AVM", &front_bottom_width, 800, on_Trackbar);
	createTrackbar("fb_offcet", "AVM", &front_bottom_offcet, 512, on_Trackbar);

	createTrackbar("lt_width_s", "AVM", &left_top_width_scale, 500, on_Trackbar);
	createTrackbar("lt_offcet", "AVM", &left_top_offcet, 512, on_Trackbar);


	createTrackbar("lb_width", "AVM", &left_bottom_width, 800, on_Trackbar);
	createTrackbar("lb_offcet", "AVM", &left_bottom_offcet, 512, on_Trackbar);

	on_Trackbar(0, 0);
	
	waitKey();
	return 0;
	

}