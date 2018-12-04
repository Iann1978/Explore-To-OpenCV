
#include <opencv2/opencv.hpp> //头文件
#include <vector>
using namespace cv; //包含cv命名空间
using namespace std;
#include "OpenCVProcess.h"
#include "Render\Texture.h"




void OpenCVProcess::Process(Mat** inputs, Mat** outputs)
{
	return;
	
	Mat& mat0 = *Texture::cvTextures[0]->mat;
	Mat& mat1 = *Texture::cvTextures[1]->mat;
	Mat& mat2 = *Texture::cvTextures[2]->mat;
	Mat& mat3 = *Texture::cvTextures[3]->mat;
	
	Mat& mat16 = *Texture::cvTextures[16]->mat;
	

	mat16.create(Size(1024, 1024), CV_8UC3);

	
	mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	mat1.copyTo(mat16(Rect(512, 0, 512, 512)));
	mat2.copyTo(mat16(Rect(0, 512, 512, 512)));
	mat3.copyTo(mat16(Rect(512, 512, 512, 512)));

	

	

}