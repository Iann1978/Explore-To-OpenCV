
#include <opencv2/opencv.hpp> //头文件
#include <vector>
using namespace cv; //包含cv命名空间
using namespace std;
#include "OpenCVProcess.h"
#include "Render\Texture.h"




void OpenCVProcess::Process(Mat** inputs, Mat** outputs)
{
	
	Mat& mat0 = *Texture::cvTextures[0]->mat;
	Mat& mat1 = *Texture::cvTextures[1]->mat;
	Mat& mat2 = *Texture::cvTextures[2]->mat;
	Mat& mat3 = *Texture::cvTextures[3]->mat;
	//Mat& mat1 = *Texture::cvTextures[1]->mat;
	//Mat& mat1 = *Texture::cvTextures[1]->mat;
	Mat& mat16 = *Texture::cvTextures[16]->mat;
	//Mat& mat16 = *Texture::cvTextures[16]->mat;

	mat16.create(Size(1024, 1024), CV_8UC3);

	
	mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	mat1.copyTo(mat16(Rect(512, 0, 512, 512)));
	mat2.copyTo(mat16(Rect(0, 512, 512, 512)));
	mat3.copyTo(mat16(Rect(512, 512, 512, 512)));

	

	//Mat map_x(mat0.size(), CV_32FC1);
	//Mat map_y(mat0.size(), CV_32FC1);

	//for (int row = 0; row < mat0.rows; row++)
	//{
	//	for (int col = 0; col < mat0.cols; col++)
	//	{
	//		map_x.at<float>(row, col) = static_cast<float>(col);
	//		map_y.at<float>(row, col) = static_cast<float>(row*2);
	//	}
	//}

	//remap(mat0, mat16, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	

}