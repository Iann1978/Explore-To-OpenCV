#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //包含cv命名空间
#include "Utils.h"

static struct ProcessImages
{
	Mat srcImage;
	Mat edgeImage;
};
static ProcessImages processImages;

static int Canny_threshold1 = 107;
static int Canny_threshold2 = 200;
static void refreshEdgeImage(int debug, void* data)
{
	CurlingArenaRebuildingData& rebuildingData = *(CurlingArenaRebuildingData *)data;
	Mat& srcImage = rebuildingData.srcImage;
	Mat greyImage, edgeImage;
	cvtColor(srcImage, greyImage, CV_BGR2GRAY);
	Canny(greyImage, edgeImage, Canny_threshold1, Canny_threshold2, 3);
	processImages.edgeImage = edgeImage;
	if (debug) imshow("IceArena_BigCircle_edgeImage", edgeImage);
}

static int cornerHarris_k = 7;
static void refreshCornerImage(int, void* data)
{
	Mat& srcImage = *(Mat*)data;
	Mat greyImage, cornerImage, cornerImage2;
	cvtColor(srcImage, greyImage, CV_BGR2GRAY);
	cornerHarris(greyImage, cornerImage, 2, 3, 1.0f * cornerHarris_k / 100);
	threshold(cornerImage, cornerImage2, 0.00001, 255, THRESH_BINARY);
	imshow("IceArena_BigCircle_cornerImage2", cornerImage2);
}

static bool filterPosition(RotatedRect ellipsBox)
{
	// 位置过滤
	if (ellipsBox.center.x < 150)
		return false;

	if (ellipsBox.center.x > 400)
		return false;

	if (ellipsBox.center.y > 200)
		return false;

	return true;
}

static bool filterShape(RotatedRect ellipsBox)
{
	//形状过滤          如果长宽比大于30，则排除，不做拟合
	if (MAX(ellipsBox.size.width, ellipsBox.size.height) > MIN(ellipsBox.size.width, ellipsBox.size.height) * 30)
		return false;
	if (MIN(ellipsBox.size.width, ellipsBox.size.height) < 30)
		return false;
	if (MAX(ellipsBox.size.width, ellipsBox.size.height) < 50)
		return false;
	return true;
}

static int slider_dev0 = 73;
static bool filterMatching(RotatedRect ellipsBox, EllipsePara ellipsParam, std::vector<Point> points)
{
	std::vector<float> array;
	for (int j = 0; j < points.size(); j++)
	{
		float f = ellips_value(ellipsParam, points[j]);
		array.push_back(f);
	}
	float mean;
	float dev; 
	myMeanStdDev(array, mean, dev);
	dev /= MAX(ellipsBox.size.width, ellipsBox.size.height);
	float dev0_threshold = exp(1.0f * slider_dev0 / 10);

	return dev < dev0_threshold;
}

static void refreshContoursImage(int debug, void* data)
{	
	CurlingArenaRebuildingData& rebuildingData = *(CurlingArenaRebuildingData*)data;

	Mat edgeImage, contoursImage, ellipsImage;
	
	// Get edge image
	edgeImage = processImages.edgeImage;
	int type = edgeImage.type();
	int depth = edgeImage.depth();
	if (debug>1) imshow("IceArena_BigCircle_Contours_edgeImage", edgeImage);

	// get contours and contours image
	vector<vector<Point>> contours;
	findContours(edgeImage, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	contoursImage = Mat::zeros(edgeImage.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(contoursImage, contours, (int)i, Scalar::all(255), 1, 8);
	}
	if (debug > 1) imshow("IceArena_BigCircle_Contours_contoursImage", contoursImage);
	

	// Get ellips image
	ellipsImage = Mat::zeros(edgeImage.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		//拟合的点至少为6
		size_t count = contours[i].size();
		if (count < 6)
			continue;

		//椭圆拟合
		RotatedRect box = fitEllipse(contours[i]);


		// 过滤位置
		if (!filterPosition(box))
			continue;

		// 过滤形状
		if (!filterShape(box))
			continue;

		// 计算椭圆参数
		EllipsePara ep;
		getEllipsePara(box, ep);

		// 椭圆拟合度过滤
		if (!filterMatching(box, ep, contours[i]))
			continue;

		drawContours(ellipsImage, contours, (int)i, Scalar::all(255), 1, 8);
		ellipse(ellipsImage, box, Scalar(0, 0, 255), 1, CV_AA);

		rebuildingData.bigCircle.box = box;
		rebuildingData.bigCircle.param = ep;
		rebuildingData.bigCircle.contours.push_back(contours[i]);
	}
	if (debug>0) imshow("IceArena_BigCircle_Contours_ellipsImage", ellipsImage);
}

void FindIceArena_BigCircle(CurlingArenaRebuildingData& rebuildingData)
{
	//processImages.srcImage = rebuildingData.srcImage;
	refreshEdgeImage(0, &rebuildingData);
	createTrackbar("Canny_threshold1", "IceArena_BigCircle_edgeImage", &Canny_threshold1, 200, refreshEdgeImage, &rebuildingData);
	createTrackbar("Canny_threshold2", "IceArena_BigCircle_edgeImage", &Canny_threshold2, 500, refreshEdgeImage, &rebuildingData);

	//refreshCornerImage(0, &srcImage);
	//createTrackbar("cornerHarris_k", "IceArena_BigCircle_cornerImage2", &cornerHarris_k, 100, refreshCornerImage, &srcImage);


	refreshContoursImage(1, &rebuildingData);
}



