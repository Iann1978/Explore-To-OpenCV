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
	Mat& srcImage = *(Mat*)data;
	Mat greyImage, edgeImage;
	cvtColor(srcImage, greyImage, CV_BGR2GRAY);
	Canny(greyImage, edgeImage, Canny_threshold1, Canny_threshold2, 3);
	edgeImage.copyTo(processImages.edgeImage);
	//processImages.edgeImage = edgeImage;
	if (debug > 1) imshow("IceArena_MiddleCircle_edgeImage", edgeImage);
}

static int cornerHarris_k = 7;
static void refreshCornerImage(int, void* data)
{
	Mat& srcImage = *(Mat*)data;
	Mat greyImage, cornerImage, cornerImage2;
	cvtColor(srcImage, greyImage, CV_BGR2GRAY);
	cornerHarris(greyImage, cornerImage, 2, 3, 1.0f * cornerHarris_k / 100);
	threshold(cornerImage, cornerImage2, 0.00001, 255, THRESH_BINARY);
	imshow("IceArena_MiddirCircle_cornerImage2", cornerImage2);
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



static bool filterPositionForMiddleCircle(RotatedRect ellipsBox, CurlingArenaRebuildingData& rebuildingData)
{
	// 位置过滤
	if (ellipsBox.center.x < 150)
		return false;

	if (ellipsBox.center.x > 400)
		return false;

	if (ellipsBox.center.y > 200)
		return false;

	float dx = ellipsBox.center.x - rebuildingData.bigCircle.box.center.x;
	float dy = ellipsBox.center.y - rebuildingData.bigCircle.box.center.y;
	if ((dx * dx + dy * dy) > 100)
		return false;

	return true;
}

static bool filterShapeForMiddleCircle(RotatedRect ellipsBox)
{
	//形状过滤          如果长宽比大于30，则排除，不做拟合
	if (MAX(ellipsBox.size.width, ellipsBox.size.height) > MIN(ellipsBox.size.width, ellipsBox.size.height) * 30)
		return false;
	//if (MIN(ellipsBox.size.width, ellipsBox.size.height) < 30)
	//	return false;
	//if (MAX(ellipsBox.size.width, ellipsBox.size.height) < 50)
	//	return false;
	return true;
}

static void refreshContoursImage_MiddleCircleStep(int debug, void* data)
{
	CurlingArenaRebuildingData& rebuildingData = *(CurlingArenaRebuildingData*)data;


	Mat edgeImage0, edgeImage, contoursImage, ellipsImage;

	// Get edge image
	processImages.edgeImage.copyTo(edgeImage0);
	int type = edgeImage0.type();
	int depth = edgeImage0.depth();
	if (debug > 1) imshow("edgeImage0", edgeImage0);

	edgeImage0.copyTo(edgeImage);
	drawContours(edgeImage, rebuildingData.bigCircle.contours, (int)0, Scalar::all(0), 1, 8);
	if (debug > 1) imshow("edgeImage", edgeImage);

	// get contours and contours image
	vector<vector<Point>> contours;
	findContours(edgeImage, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	contoursImage = Mat::zeros(edgeImage.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(contoursImage, contours, (int)i, Scalar::all(255), 1, 8);
	}
	if (debug>1) imshow("contoursImage", contoursImage);


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
		if (!filterPositionForMiddleCircle(box, rebuildingData))
			continue;

		// 过滤形状
		if (!filterShapeForMiddleCircle(box))
			continue;

		// 计算椭圆参数
		EllipsePara ep;
		getEllipsePara(box, ep);

		// 椭圆拟合度过滤
		if (!filterMatching(box, ep, contours[i]))
			continue;

		//processImages.bigCircleContours.push_back(contours[i]);
		drawContours(ellipsImage, contours, (int)i, Scalar::all(255), 1, 8);
		ellipse(ellipsImage, box, Scalar(0, 0, 255), 1, CV_AA);
	}
	if (debug>0) imshow("ellipsImage", ellipsImage);

}
void FindIceArena_MiddleCircle(CurlingArenaRebuildingData& rebuildingData)
{
	processImages.srcImage = rebuildingData.srcImage;

	// Get edge image
	refreshEdgeImage(1, &rebuildingData.srcImage);
	createTrackbar("Canny_threshold1", "IceArena_MiddleCircle_edgeImage", &Canny_threshold1, 200, refreshEdgeImage, &rebuildingData.srcImage);
	createTrackbar("Canny_threshold2", "IceArena_MiddleCircle_edgeImage", &Canny_threshold2, 500, refreshEdgeImage, &rebuildingData.srcImage);
	



	refreshContoursImage_MiddleCircleStep(1, &rebuildingData);
}



