#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
#include "E:\githome\Explore-To-OpenCV\thirdparty\eigen\Eigen\Dense"
#include "Utils.h"
using namespace cv; //包含cv命名空间
using namespace Eigen;

static struct Line
{
	Point a;
	Point b;
};

static Line GetLine(float rho, float theta)
{
	Point pt1, pt2;
	double a = cos(theta), b = sin(theta);
	double x0 = a * rho, y0 = b * rho;
	pt1.x = cvRound(x0 + 1000 * (-b));
	pt1.y = cvRound(y0 + 1000 * (a));
	pt2.x = cvRound(x0 - 1000 * (-b));
	pt2.y = cvRound(y0 - 1000 * (a));
	Line line;
	line.a = pt1;
	line.b = pt2;
	return line;
}

static Point CalculateIntersectionOfLines(Line line0, Line line1)
{
	// Calc intersection of line ac with bd:
	Vector2f a(line0.a.x, line0.a.y);
	Vector2f b(line1.a.x, line1.a.y);
	Vector2f c(line0.b.x, line0.b.y);
	Vector2f d(line1.b.x, line1.b.y);

	Matrix2f xx;
	xx << c - a, b - d;

	std::cout << "Here is the matrix xx:\n" << xx << std::endl;
	Vector2f x = xx.colPivHouseholderQr().solve(b - a);
	Vector2f intersect1(a + x(0) * (c - a));
	Vector2f intersect2(b + x(1) * (d - b));

	std::cout << "intersect1\n" << intersect1 << std::endl;
	std::cout << "intersect2\n" << intersect2 << std::endl;

	return Point(intersect1(0), intersect1(1));
}

void RebuildIceArena(CurlingArenaRebuildingData& rebuildingData)
{
	Mat iceArena = rebuildingData.srcImage;

	Line topline = GetLine(rebuildingData.topEdge[0], rebuildingData.topEdge[1]);
	Line leftline = GetLine(rebuildingData.leftEdge[0], rebuildingData.leftEdge[1]);
	Line rightline = GetLine(rebuildingData.rightEdge[0], rebuildingData.rightEdge[1]);
	Point topleft = CalculateIntersectionOfLines(topline, leftline);
	Point topright = CalculateIntersectionOfLines(topline, rightline);
	Point center = rebuildingData.bigCircle.box.center;

	
	rebuildingData.srcImage.copyTo(iceArena);
	//circle(iceArena, topleft, 5, cv::Scalar(255,255,255),2);
	circle(iceArena, topleft, 3, cv::Scalar(0, 0, 255), 2);

	//circle(iceArena, topRight, 5, cv::Scalar(255, 255, 255), 2);
	circle(iceArena, topright, 3, cv::Scalar(0, 0, 255), 2);


	circle(iceArena, center, 3, cv::Scalar(0, 0, 255), 2);
	imshow("iceArena", iceArena);

	// affine transform
	int width = 475;
	int height = 488;

	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	srcTriangle[0] = center;
	srcTriangle[1] = topleft;
	srcTriangle[2] = topright;

	Point2f off = Point2f(width / 4, 50);
	dstTriangle[0] = Point2f(width / 4, height/2) + off;
	dstTriangle[1] = Point2f(0, 0) + off;
	dstTriangle[2] = Point2f(width/2, 0)  + off;

	

	Mat warpImage = Mat::zeros(height * 5, width, iceArena.type());
	

	Mat warpMat = getAffineTransform(srcTriangle, dstTriangle);

	warpAffine(iceArena, warpImage, warpMat, warpImage.size());

	imshow("warpImage", warpImage);

}