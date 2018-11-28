
#include <opencv2/opencv.hpp> //ͷ�ļ�
#include <vector>
using namespace cv; //����cv�����ռ�
using namespace std;
#include "OpenCVProcess.h"




void OpenCVProcess::Process(Mat& input, Mat& output)
{
	//output.create(input.rows, input.cols, input.type());
	//input.copyTo(output);

	vector<Mat> channels;
	split(input, channels);
	for (int i = 0; i < channels.size(); i++)
	{
		cvtColor(input, channels[i], CV_RGB2GRAY);
	}

	merge(channels, output);

	//cvtColor(input, output, CV_RGB2GRAY);
}