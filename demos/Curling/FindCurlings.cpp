#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //包含cv命名空间
#include "Utils.h"

static struct ProcessImages
{
	Mat srcImage;
	Mat edgeImage;
	Mat cornerImage;
	vector<EllipseData> ellipses;
	
};
static ProcessImages processImages;


void MaskedImage(Mat& maskImage, Vec2f line)
{
	float rho = line[0];
	float theta = line[1];
	int channels = maskImage.channels();
	int depth = maskImage.depth();
	for (int row = 0; row < maskImage.rows; row++)
	{
		for (int col = 0; col < maskImage.cols; col++)
		{
			float rho1 = col * sin(theta) + row * cos(theta);
			if (rho1 <= rho)
				maskImage.at<uchar>(col, row) = uchar(0);
		}
	}
}


static int Canny_threshold1 = 252;
static int Canny_threshold2 = 523;
static int Canny_apertureSize = 3;
static void refreshEdgeImage(int debug, void* data)
{
	CurlingArenaRebuildingData& rebuildingData = *(CurlingArenaRebuildingData *)data;
	Mat srcImage, greyImage, edgeImage;
	rebuildingData.srcImage.copyTo(srcImage);
	cvtColor(srcImage, greyImage, CV_BGR2GRAY);
	Canny(greyImage, edgeImage, Canny_threshold1, Canny_threshold2, Canny_apertureSize);
	MaskedImage(edgeImage, rebuildingData.topEdge);
	MaskedImage(edgeImage, rebuildingData.leftEdge);
	MaskedImage(edgeImage, rebuildingData.rightEdge);
	edgeImage.copyTo(processImages.edgeImage);
	if (debug) imshow("FindCurlines_edgeImage", edgeImage);
}

static int cornerHarris_k = 20;
static void refreshCornerImage(int, void* data)
{
	CurlingArenaRebuildingData& rebuildingData = *(CurlingArenaRebuildingData*)data;
	Mat srcImage, greyImage, cornerImage, cornerImage2;
	rebuildingData.srcImage.copyTo(srcImage);
	cvtColor(srcImage, greyImage, CV_BGR2GRAY);
	cornerHarris(greyImage, cornerImage, 2, 3, 1.0f * cornerHarris_k / 100);
	threshold(cornerImage, cornerImage2, 0.00001, 255, THRESH_BINARY);
	processImages.cornerImage = cornerImage2;
	imshow("FindCurlines_cornerImage", cornerImage2);
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
	if (MAX(ellipsBox.size.width, ellipsBox.size.height) > MIN(ellipsBox.size.width, ellipsBox.size.height) * 20)
		return false;
	if (MIN(ellipsBox.size.width, ellipsBox.size.height) < 10)
		return false;
	if (MAX(ellipsBox.size.width, ellipsBox.size.height) > 100)
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
	float dev0_threshold = exp(1.0f * slider_dev0/10);

	return dev < dev0_threshold;
}

static int reliability = 100;
static bool filterReliability(RotatedRect ellipsBox, EllipsePara ellipsParam, std::vector<Point> points)
{
	Point mean;
	float dev;
	myMeanStdDev(points, mean, dev);
	if (dev < reliability)
		return false;
	return true;

}

static void refreshContoursImage(int debug, void* data)
{	
	CurlingArenaRebuildingData& rebuildingData = *(CurlingArenaRebuildingData*)data;

	Mat edgeImage, cornerImage, cornerImage1, breakedEdgeImage, contoursImage, ellipsImage;
	
	// Get edge image
	processImages.ellipses.clear();
	processImages.edgeImage.copyTo(edgeImage);
	processImages.cornerImage.copyTo(cornerImage);
	cornerImage.convertTo(cornerImage1, CV_8U);
	//edgeImage = processImages.edgeImage;
	int type = edgeImage.type();
	int depth = edgeImage.depth();
	int type1 = cornerImage1.type();
	int depth1 = cornerImage1.depth();
	if (debug>1) imshow("FindCurlines_Contours_edgeImage", edgeImage);

	breakedEdgeImage = Mat::zeros(edgeImage.size(), edgeImage.type());
	addWeighted(edgeImage, 1, cornerImage1, -1, 0.0, breakedEdgeImage);
	if (debug > 1) imshow("FindCurlines_Contours_breakedEdgeImage", breakedEdgeImage);

	// get contours and contours image
	vector<vector<Point>> contours;
	findContours(breakedEdgeImage, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	contoursImage = Mat::zeros(breakedEdgeImage.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(contoursImage, contours, (int)i, Scalar::all(255), 1, 8);
	}
	if (debug > 1) imshow("FindCurlines_Contours_contoursImage", contoursImage);
	

	// Get ellips image
	ellipsImage = Mat::zeros(breakedEdgeImage.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		//拟合的点至少为6
		size_t count = contours[i].size();
		if (count < 6)
			continue;

		//椭圆拟合
		RotatedRect box = fitEllipse(contours[i]);


		//// 过滤位置
		//if (!filterPosition(box))
		//	continue;

		// 过滤形状
		if (!filterShape(box))
			continue;

		// 计算椭圆参数
		EllipsePara ep;
		getEllipsePara(box, ep);

		// 椭圆拟合度过滤
		if (!filterMatching(box, ep, contours[i]))
			continue;

		// 拟合信度过滤
		//if (filterReliability(box, ep, contours[i]))
		//	continue;

		/*rebuildingData.bigCircle.box = box;
		rebuildingData.bigCircle.param = ep;*/
		EllipseData ellipseData;
		ellipseData.box = box;
		ellipseData.param = ep;
		ellipseData.contours.push_back(contours[i]);
		processImages.ellipses.push_back(ellipseData);

		drawContours(ellipsImage, contours, (int)i, Scalar::all(255), 1, 8);
		ellipse(ellipsImage, box, Scalar(0, 0, 255), 1, CV_AA);


		//rebuildingData.bigCircle.contours.push_back(contours[i]);
	}
	if (debug>0) imshow("FindCurlines_Contours_ellipsImage", ellipsImage);
}

static struct CurlineData
{
	EllipseData topCircle;
	EllipseData bottomCircle;
};

static vector<CurlineData> GetCurlings(vector<EllipseData> ellipses)
{
	vector<CurlineData> curlings;
	for (int i = 0; i < ellipses.size(); i++)
	{
		for (int j = i + 1; j < ellipses.size(); j++)
		{
			EllipseData ellipseData0 = ellipses[i];
			EllipseData ellipseData1 = ellipses[j];
			
			float dx = ellipseData0.box.center.x - ellipseData1.box.center.x;
			float dy = ellipseData0.box.center.y - ellipseData1.box.center.y;
			float dis = sqrt(dx * dx + dy * dy);
			if (dis < 8)
			{
				CurlineData curlineData;
				curlineData.topCircle = ellipseData0;
				curlineData.bottomCircle = ellipseData1;
				curlings.push_back(curlineData);
			}
		}
	}

	Mat curlingsImage = Mat::zeros(500,500, CV_8UC3);
	for (size_t i = 0; i < curlings.size(); i++)
	{
		CurlineData curlingData = curlings[i];
		


		drawContours(curlingsImage, curlingData.bottomCircle.contours, (int)0, Scalar::all(255), 1, 8);
		ellipse(curlingsImage, curlingData.bottomCircle.box, Scalar(0, 0, 255), 1, CV_AA);


		//rebuildingData.bigCircle.contours.push_back(contours[i]);
	}
	imshow("curlingsImage", curlingsImage);
	return curlings;
}


void FindCurlings(CurlingArenaRebuildingData& rebuildingData)
{
	refreshEdgeImage(5, &rebuildingData);
	createTrackbar("Canny_threshold1", "FindCurlines_edgeImage", &Canny_threshold1, 1000, refreshEdgeImage, &rebuildingData);
	createTrackbar("Canny_threshold2", "FindCurlines_edgeImage", &Canny_threshold2, 1000, refreshEdgeImage, &rebuildingData);
	createTrackbar("Canny_apertureSize", "FindCurlines_edgeImage", &Canny_apertureSize, 10, refreshEdgeImage, &rebuildingData);

	refreshCornerImage(5, &rebuildingData);
	createTrackbar("cornerHarris_k", "FindCurlines_cornerImage", &cornerHarris_k, 20, refreshCornerImage, &rebuildingData);
	

	refreshContoursImage(5, &rebuildingData);
	createTrackbar("reliability", "FindCurlines_Contours_ellipsImage", &reliability, 1000, refreshContoursImage, &rebuildingData);
	createTrackbar("slider_dev0", "FindCurlines_Contours_ellipsImage", &slider_dev0, 100, refreshContoursImage, &rebuildingData);

	vector<CurlineData> curlings = GetCurlings(processImages.ellipses);
	
}



