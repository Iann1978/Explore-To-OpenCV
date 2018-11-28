
#include <opencv2/opencv.hpp> //头文件
#include <vector>
using namespace cv; //包含cv命名空间
using namespace std;
#include "OpenCVProcess.h"
#include "Render\Texture.h"




void OpenCVProcess::Process(Mat** inputs, Mat** outputs)
{
	
	Mat& input = *Texture::cvTextures[0]->mat;
	Mat& output = *Texture::cvTextures[16]->mat;

	vector<Mat> channels;
	split(input, channels);
	for (int i = 0; i < channels.size(); i++)
	{
		cvtColor(input, channels[i], CV_RGB2GRAY);
	}

	merge(channels, output);

	Mat& mat17 = *Texture::cvTextures[17]->mat;

	output.copyTo(mat17);

}