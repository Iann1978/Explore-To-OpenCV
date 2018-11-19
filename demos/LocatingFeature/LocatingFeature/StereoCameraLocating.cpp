#include "stdafx.h"
//#include <Eigen/Dense>
//using namespace Eigen;
//#include "StereoCameraLocating.h"
//RNG g_rng(12345);
//
//StereoCameraLocating::StereoCameraLocating()
//{
//}
//
//
//StereoCameraLocating::~StereoCameraLocating()
//{
//}
//
//void StereoCameraLocating::UV2View(float viewl[3], float viewr[3], float uvl[2], float uvr[2])
//{
//	float d = cameraParameter.stereoDis;
//	float ur = uvr[0];
//	float ul = uvl[0];
//	float w = cameraParameter.width;
//	float h = cameraParameter.height;
//	float xr = d * (2 * ur - w) / ((2 * ul - w) - (2 * ur - w));
//	//Debug.Log(string.Format("xr:{0:F5},", xr));
//	float fovH = cameraParameter.fovH;
//	float fovV = cameraParameter.fovV;
//	float zr = xr * w / (2 * ur - w) / tan(fovH / 2);
//	//Debug.Log(string.Format("zr:{0:F5},", zr));
//	float vr = uvr[1];
//	float yr = zr * (2 * vr - h) * tan(fovV / 2) / h;
//	//Debug.Log(string.Format("yr:{0:F5},", yr));
//
//
//	viewr[0] = xr;				viewr[1] = yr;		viewr[2] = zr;
//	viewl[0] = viewr[0] + d;	viewl[1] = yr;		viewl[2] = zr;
//}
//
//void StereoCameraLocating::UV2World(Point3f &world, Point2f uvl, Point2f uvr)
//{
//	float d = cameraParameter.stereoDis;
//	float ur = uvr.x;
//	float ul = uvl.x;
//	float vr = uvr.y;
//	float u0 = cameraParameter.width / 2;
//	float v0 = cameraParameter.height / 2;
//	float xr = d * (ur - u0) / (ul - ur);
//	float zr = 516.6 * xr / (ur - u0);
//	float yr = zr * (vr - v0) / 516.6;
//
//
//	world.x = xr + d / 2;
//	world.y = yr;
//	world.z = zr;
//}
//
//void StereoCameraLocating::CalViewMatrix(float matl[4][4], float matr[4][4], vector<Point2f> uvl, vector<Point2f> uvr, vector<Point3f> world)
//{
//	int m = world.size() * 3;
//	int n = 16;
//	MatrixXf M = MatrixXf::Random(m, n);
//	MatrixXf N = MatrixXf::Random(m, 1);
//
//	for (int i = 0; i < uvl.size(); i++)
//	{
//		Point2f pl = uvl[i];
//		Point2f pr = uvr[i];
//		Point3f pw = world[i];
//
//		//u*y' = v*x'
//		M(i * 3 + 0, 0) = pl.y * pw.x;
//		M(i * 3 + 0, 1) = pl.y * pw.y;
//		M(i * 3 + 0, 2) = pl.y * pw.z;
//		M(i * 3 + 0, 3) = pl.y;
//		M(i * 3 + 0, 4) = -pl.x * pw.x;
//		M(i * 3 + 0, 5) = -pl.x * pw.y;
//		M(i * 3 + 0, 6) = -pl.x * pw.z;
//		M(i * 3 + 0, 7) = -pl.x;
//		N(i * 3 + 0) = 0;
//
//
//
//		////u*y' = v*x'
//		M(i * 3 + 1, 8) = pr.y * pw.x;
//		M(i * 3 + 1, 9) = pr.y * pw.y;
//		M(i * 3 + 1, 10) = pr.y * pw.z;
//		M(i * 3 + 1, 11) = pr.y;
//		M(i * 3 + 1, 12) = -pr.x * pw.x;
//		M(i * 3 + 1, 13) = -pr.x * pw.y;
//		M(i * 3 + 1, 14) = -pr.x * pw.z;
//		M(i * 3 + 1, 15) = -pr.x;
//		N(i * 3 + 1) = 0;
//
//
//		////xl'-xr'=1
//		M(i * 3 + 2, 0) = pw.x;
//		M(i * 3 + 2, 1) = pw.y;
//		M(i * 3 + 2, 2) = pw.z;
//		M(i * 3 + 2, 3) = 1;
//		M(i * 3 + 2, 8) = -pw.x;
//		M(i * 3 + 2, 9) = -pw.y;
//		M(i * 3 + 2, 10) = -pw.z;
//		M(i * 3 + 2, 11) = -1;
//		N(i * 3 + 2) = 1;
//
//
//		
//
//	}
//
//
//	MatrixXf x = (M.transpose() * M).inverse() * M.transpose() * N;
//
//
//
//	//Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[0], x[1], x[2], x[3]));
//	//Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[4], x[5], x[6], x[7]));
//	//Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[8], x[9], x[10], x[11]));
//	//Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[12], x[13], x[14], x[15]));
//	//   Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[16], x[17], x[18], x[19]));
// //       Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[20], x[21], x[22], x[23]));
//
//	Point3f RL0(x(0), x(1), x(2));
//	Point3f RL1 = Point3f(x(4), x(5), x(6));
//	Point3f RL2 = -RL0.cross(RL1);
//
//	Point3f RR0 = Point3f(x(8), x(9), x(10));
//	Point3f RR1 = Point3f(x(12), x(13), x(14));
//	Point3f RR2 = -RR0.cross(RR1);
//
//	////MatrixXf matl = MatrixXf::Random(4, 4);
//	matl[0][0] = RL0.x; matl[0][1] = RL0.y; matl[0][2] = RL0.z; matl[0][3] = x(3);
//	matl[1][0] = RL1.x; matl[1][1] = RL1.y; matl[1][2] = RL1.z; matl[1][3] = x(7);
//	matl[2][0] = RL2.x; matl[2][1] = RL2.y; matl[2][2] = RL2.z; matl[2][3] = 0;
//	matl[3][0] = 0;     matl[3][1] = 0;     matl[3][2] = 0;     matl[3][3] = 1;
//
//	////MatrixXf matr = MatrixXf::Random(4, 4);
//	matr[0][0] = RR0.x; matr[0][1] = RR0.y; matr[0][2] = RR0.z; matr[0][3] = x(11);
//	matr[1][0] = RR1.x; matr[1][1] = RR1.y; matr[1][2] = RR1.z; matr[1][3] = x(15);
//	matr[2][0] = RR2.x; matr[2][1] = RR2.y; matr[2][2] = RR2.z; matr[2][3] = 0;
//	matr[3][0] = 0;     matr[3][1] = 0;     matr[3][2] = 0;     matr[3][3] = 1;
//
//	
//	float fovH = cameraParameter.fovH;
//	float fovV = cameraParameter.fovV;
//
//	Point3f pw = world[0];
//	float xxl = matl[0][0] * pw.x + matl[0][1] * pw.y + matl[0][2] * pw.z + matl[0][3];
//	//Debug.Log(string.Format("x':{0:F5}", xxl));
//	float xxxl = tan(fovH/2.0f) * uvl[0].x;
//	//Debug.Log(string.Format("x'':{0:F5}", xxxl));
//	float tmp = matl[2][0] * pw.x + matl[2][1] * pw.y + matl[2][2] * pw.z;
//	//Debug.Log(string.Format("tmp'':{0:F5}", tmp));
//	float ml23 = -xxl / xxxl - tmp;
//
//
//
//	float xxr = matr[0][0] * pw.x + matr[0][1] * pw.y + matr[0][2] * pw.z + matr[0][3];
//	float xxxr =tan(fovH/2.0f) *uvr[0].x;
//	float mr23 = -xxr / xxxr - (matr[2][0] * pw.x + matr[2][1] * pw.y + matr[2][2] * pw.z);
//
//	matl[2][3] = ml23;
//	matr[2][3] = mr23;
//
//
//
//
//	//Debug.Log("ML:\n" + ML);
//	//Debug.Log("MR:\n" + MR);
//
//}
//
//
//
//
//void StereoCameraLocating::InitCapture()
//{
//	cap = new VideoCapture(1);
//	cap->set(CV_CAP_PROP_FRAME_WIDTH, 2560);  //设置捕获视频的宽度
//	cap->set(CV_CAP_PROP_FRAME_HEIGHT, 720);  //设置捕获视频的高度
//	isInitialized = true;
//}
//
//
//void StereoCameraLocating::GetTextures()
//{
//	*cap >> frame;  //读取当前帧
//
//	resize(frame, halfFrame, Size(1280, 360));
//	imshow("HalfFrame", halfFrame);
//
//	leftCamera = halfFrame(Rect(0, 0, 640, 360));
//	rightCamera = halfFrame(Rect(640, 0, 640, 360));
//
//	cvtColor(leftCamera, leftGrey, CV_RGB2GRAY);
//	cvtColor(rightCamera, rightGrey, CV_RGB2GRAY);
//	leftCamera.copyTo(leftResult);
//	rightCamera.copyTo(rightResult);
//
//	imshow("LeftCamera", leftCamera);
//	imshow("RightCamera", rightCamera);
//	imshow("LeftResult", leftResult);
//	imshow("RightResult", rightResult);
//}
//
//void StereoCameraLocating::GetFutures(/*vector<Point2f>& uv, Mat mat*/)
//{
//	//【2】Shi-Tomasi算法（goodFeaturesToTrack函数）的参数准备
//
//	double qualityLevel = 0.01;//角点检测可接受的最小特征值
//	double minDistance = 10;//角点之间的最小距离
//	int blockSize = 3;//计算导数自相关矩阵时指定的邻域范围
//	double k = 0.04;//权重系数
//					//Mat copy = leftGrey.clone();	//复制源图像到一个临时变量中，作为感兴趣区域
//
//					//【3】进行Shi-Tomasi角点检测
//	goodFeaturesToTrack(leftGrey,//输入图像
//		left_corners,//检测到的角点的输出向量
//		1,//角点的最大数量
//		qualityLevel,//角点检测可接受的最小特征值
//		minDistance,//角点之间的最小距离
//		Mat(),//感兴趣区域
//		blockSize,//计算导数自相关矩阵时指定的邻域范围
//		false,//不使用Harris角点检测
//		k);//权重系数
//
//		   //【4】输出文字信息
//	cout << "\t>此次检测到的角点数量为：" << left_corners.size() << endl;
//
//	//【5】绘制检测到的角点
//	int r = 4;
//	for (int i = 0; i < left_corners.size(); i++)
//	{
//		//以随机的颜色绘制出角点
//		circle(leftResult, left_corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
//			g_rng.uniform(0, 255)), -1, 8, 0);
//	}
//	imshow("LeftCamera", leftCamera);
//	imshow("RightCamera", rightCamera);
//	imshow("LeftResult", leftResult);
//	imshow("RightResult", rightResult);
//}
//
//
//void StereoCameraLocating::TracingFuturesInRight()
//{
//	 //查找匹配特征点
//	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
//	vector<uchar> status;
//	vector<float> err;
//	calcOpticalFlowPyrLK(leftGrey,
//		rightGrey,
//		left_corners, 
//		right_corners, 
//		status, 
//		err,
//		Size(31,31),
//		3, termcrit, 0, 0.001);
//	
//	
//	int r = 4;
//	for (int i = 0; i < right_corners.size(); i++)
//	{
//		//以随机的颜色绘制出角点
//		circle(rightResult, right_corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
//			g_rng.uniform(0, 255)), -1, 8, 0);
//	}
//	
//	imshow("LeftCamera", leftCamera);
//	imshow("RightCamera", rightCamera);
//	imshow("LeftResult", leftResult);
//	imshow("RightResult", rightResult);
//}
//void StereoCameraLocating::CalFuturesPosition()
//{
//	for (int i = 0; i < left_corners.size(); i++)
//	{
//		Point2f uvl = left_corners[i];
//		Point2f uvr = right_corners[i];
//		Point3f world;
//		UV2World(world, uvl, uvr);
//		printf("i:%d, world:%f,%f,%f,uvl:%f,%f, uvr:%f,%f\n", i, world.x, world.y, world.z, uvl.x, uvl.y, uvr.x, uvr.y);
//	}
//
//}
//void StereoCameraLocating::CopyToOld()
//{
//	leftGrey.copyTo(oldLeftGrey);
//	rightGrey.copyTo(oldRightGrey);
//	old_left_corners = left_corners;
//	old_right_corners = right_corners;
//}
//
//void StereoCameraLocating::TracingFuturesInLeft()
//{
//	//查找匹配特征点
//	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
//	vector<uchar> status;
//	vector<float> err;
//	calcOpticalFlowPyrLK(oldLeftGrey,
//		leftGrey,
//		old_left_corners,
//		left_corners,
//		status,
//		err,
//		Size(31, 31),
//		3, termcrit, 0, 0.001);
//
//
//	int r = 4;
//	for (int i = 0; i < left_corners.size(); i++)
//	{
//		//以随机的颜色绘制出角点
//		circle(leftResult, left_corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
//			g_rng.uniform(0, 255)), -1, 8, 0);
//	}
//
//	imshow("LeftCamera", leftCamera);
//	imshow("RightCamera", rightCamera);	
//	imshow("LeftResult", leftResult);
//	imshow("RightResult", rightResult);
//	imshow("oldLeftGrey", oldLeftGrey);
//	imshow("oldRightGrey", oldRightGrey);
//
//
//}