
#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv; //包含cv命名空间
void EllipsFillting(Mat src_image);
Mat FindCorners(Mat srcImage);
Mat FindEdges(Mat srcImage)
int main()
{
	// 【1】读入一张图片
	//Mat srcImage = imread("1.jpg");
	//imshow("srcImage", srcImage);

	//Mat edgesImage = FindEdges(srcImage);
	//imshow("edgesImage", edgesImage);


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
