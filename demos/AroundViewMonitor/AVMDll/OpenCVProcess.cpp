
#include <opencv2/opencv.hpp> //头文件
#include <vector>
using namespace cv; //包含cv命名空间
using namespace std;
#include "OpenCVProcess.h"
#include "Render\Texture.h"


int OpenCVProcess::intValues[32];

void OpenCVProcess::Process(Mat** inputs, Mat** outputs)
{
	int a = intValues[0];
	int b = intValues[1];
	int Wf = intValues[2];
	int Hf = intValues[3];
	int Wt = intValues[4];
	int Ht = intValues[5];


	Mat mat0 = *Texture::cvTextures[0]->mat;
	Mat& mat16 = *Texture::cvTextures[16]->mat;

	// transform mat0
	Point2f srcTriangle[4];
	Point2f dstTriangle[4];
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(Wf, 0);
	srcTriangle[2] = Point2f(0, Hf);
	srcTriangle[3] = Point2f(Wf, Hf);

	dstTriangle[0] = Point2f(0, 0);
	dstTriangle[1] = Point2f(Wt,0);
	dstTriangle[2] = Point2f(b,a);
	dstTriangle[3] = Point2f(Wt - b, a);
	Mat trans = getPerspectiveTransform(srcTriangle, dstTriangle);
	warpPerspective(mat0, mat0, trans, Size(Wt, Ht));

	mat0.copyTo(mat16);


}