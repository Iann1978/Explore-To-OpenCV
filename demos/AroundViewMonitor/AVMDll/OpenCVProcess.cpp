
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
	Mat& mat16 = *Texture::cvTextures[16]->mat;
	Mat& mat17 = *Texture::cvTextures[17]->mat;

	mat0.copyTo(mat16);
	mat1.copyTo(mat17);

	vector<Mat> channels;
	split(mat0, channels);
	for (int i = 0; i < channels.size(); i++)
	{
		cvtColor(mat0, channels[i], CV_RGB2GRAY);
	}
	merge(channels, mat16);

	channels.clear();
	split(mat1, channels);
	for (int i = 0; i < channels.size(); i++)
	{
		cvtColor(mat1, channels[i], CV_RGB2GRAY);
	}
	merge(channels, mat17);

}