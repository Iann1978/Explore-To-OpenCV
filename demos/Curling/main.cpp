
#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv; //包含cv命名空间
Mat EllipsFillting(Mat& src_image);
Mat FindCorners(Mat& srcImage);
Mat FindLines(Mat& srcImage);
Mat FindEdges(Mat& srcImage);

Vec2f FindIceArena_TopEdge(Mat& srcImage);
Vec2f FindIceArena_LeftEdge(Mat& srcImage);
Vec2f FindIceArena_RightEdge(Mat& srcImage);
void FindIceArena_BigCircle(Mat& srcImage);
void FindIceArena_MiddleCircle(Mat& srcImage);

int main()
{
	Mat srcImage, edgesImage, edgesImage_Gray, edgesImage_Gray_32F, cornersImage_Gray;

	Mat edgeSubCornerImage_Gray;

	Mat linesImage;
	

	srcImage = imread("1.jpg");
	imshow("srcImage", srcImage);

	do
	{
		//FindIceArena_TopEdge(srcImage);
		//FindIceArena_LeftEdge(srcImage);
		//FindIceArena_RightEdge(srcImage);
		//FindIceArena_BigCircle(srcImage);
		FindIceArena_MiddleCircle(srcImage);

		continue;


		edgesImage = FindEdges(srcImage);
		cvtColor(edgesImage, edgesImage_Gray, CV_BGR2GRAY);
		edgesImage_Gray.convertTo(edgesImage_Gray_32F, 5);
		imshow("edgesImage_Gray", edgesImage_Gray);

		cornersImage_Gray = FindCorners(srcImage);
		imshow("cornersImage_Gray", cornersImage_Gray);

		addWeighted(edgesImage_Gray_32F, 1, cornersImage_Gray, -1, 0.0, edgeSubCornerImage_Gray);
		imshow("edgeSubCornerImage_Gray", edgeSubCornerImage_Gray);
		EllipsFillting(edgeSubCornerImage_Gray);

		linesImage = FindLines(srcImage);
		imshow("linesImage", linesImage);
	} while (waitKey(0) != 0x1b);


	//FindCorners(srcImage);
	//waitKey(0);
	//EllipsFillting(srcImage);
	//waitKey(0);

	//Mat mv[3];
	//split(srcImage, mv);
	//imshow("B", mv[0]);
	//imshow("G", mv[1]);
	//imshow("R", mv[2]);

	//Mat midImage, dstImage;//临时变量和目标图的定义



	////【5】显示原始图  
	//imshow("【原始图】", srcImage);

	////【6】边缘检测后的图 
	//imshow("【边缘检测后的图】", midImage);

	////【7】显示效果图  
	//imshow("【效果图】", dstImage);

	waitKey(0);
}
