
#include <opencv2/opencv.hpp> //头文件
#include <vector>
using namespace cv; //包含cv命名空间
using namespace std;
#include "OpenCVProcess.h"
#include "Render\Texture.h"

namespace cvBridge
{
	int OpenCVProcess::intValues[32];
	Texture*	OpenCVProcess::cvTextures[32];

	void OpenCVProcess::Process(Mat** inputs, Mat** outputs)
	{
		int w = intValues[0];
		int h = intValues[1];
		int wext = intValues[2];
		int hext = intValues[3];
		int ww = w + wext + wext;
		int hh = h + hext + hext;



		Mat& mat0 = *cvTextures[0]->mat;
		Mat& mat1 = *cvTextures[1]->mat;
		Mat& mat2 = *cvTextures[2]->mat;
		Mat& mat3 = *cvTextures[3]->mat;
		Mat& mat16 = *cvTextures[16]->mat;

		// transform mat0
		Point2f srcTriangle[4];
		Point2f dstTriangle[4];
		srcTriangle[0] = Point2f(0.0f, 0.0f);
		srcTriangle[1] = Point2f(1.0f*mat0.cols, 0.0f);
		srcTriangle[2] = Point2f(0.0f, 1.0f*mat0.rows);
		srcTriangle[3] = Point2f(1.0f*mat0.cols, 1.0f*mat0.rows);

		dstTriangle[0] = Point2f(0, 0);
		dstTriangle[1] = Point2f(1.0f*mat16.cols, 0);
		dstTriangle[2] = Point2f(1.0f*mat16.cols*wext / ww, 1.0f*mat16.rows*hext / hh);
		dstTriangle[3] = Point2f(1.0f*mat16.cols*(wext + w) / ww, 1.0f*mat16.rows*hext / hh);
		Mat trans = getPerspectiveTransform(srcTriangle, dstTriangle);
		warpPerspective(mat0, mat0, trans, Size(mat16.cols, mat16.rows));

		srcTriangle[0] = Point2f(0.0f, 0.0f);
		srcTriangle[1] = Point2f(1.0f*mat1.cols, 0.0f);
		srcTriangle[2] = Point2f(0.0f, 1.0f*mat1.rows);
		srcTriangle[3] = Point2f(1.0f*mat1.cols, 1.0f*mat1.rows);

		dstTriangle[0] = Point2f(0, 1.0f*mat16.rows);
		dstTriangle[1] = Point2f(0, 0);
		dstTriangle[2] = Point2f(1.0f*mat16.cols*wext / ww, 1.0f*mat16.rows*(h + hext) / hh);
		dstTriangle[3] = Point2f(1.0f*mat16.cols*wext / ww, 1.0f*mat16.rows*hext / hh);
		trans = getPerspectiveTransform(srcTriangle, dstTriangle);
		warpPerspective(mat1, mat1, trans, Size(mat16.cols, mat16.rows));


		srcTriangle[0] = Point2f(0.0f, 0.0f);
		srcTriangle[1] = Point2f(1.0f*mat2.cols, 0.0f);
		srcTriangle[2] = Point2f(0.0f, 1.0f*mat2.rows);
		srcTriangle[3] = Point2f(1.0f*mat2.cols, 1.0f*mat2.rows);

		dstTriangle[0] = Point2f(1.0f*mat16.cols, 0);
		dstTriangle[1] = Point2f(1.0f*mat16.cols, 1.0f*mat16.rows);
		dstTriangle[2] = Point2f(1.0f*mat16.cols*(w + wext) / ww, 1.0f*mat16.rows*(hext) / hh);
		dstTriangle[3] = Point2f(1.0f*mat16.cols*(w + wext) / ww, 1.0f*mat16.rows*(h + hext) / hh);
		trans = getPerspectiveTransform(srcTriangle, dstTriangle);
		warpPerspective(mat2, mat2, trans, Size(mat16.cols, mat16.rows));

		srcTriangle[0] = Point2f(0.0f, 0.0f);
		srcTriangle[1] = Point2f(1.0f*mat3.cols, 0.0f);
		srcTriangle[2] = Point2f(0.0f, 1.0f*mat3.rows);
		srcTriangle[3] = Point2f(1.0f*mat3.cols, 1.0f*mat3.rows);

		dstTriangle[2] = Point2f(0, 1.0f*mat16.rows);
		dstTriangle[3] = Point2f(1.0f*mat16.cols, 1.0f*mat16.rows);
		dstTriangle[0] = Point2f(1.0f*mat16.cols*(wext) / ww, 1.0f*mat16.rows*(h + hext) / hh);
		dstTriangle[1] = Point2f(1.0f*mat16.cols*(w + wext) / ww, 1.0f*mat16.rows*(h + hext) / hh);
		trans = getPerspectiveTransform(srcTriangle, dstTriangle);
		warpPerspective(mat3, mat3, trans, Size(mat16.cols, mat16.rows));


		//mat0.copyTo(mat16);
		addWeighted(mat0, 0.5, mat1, 0.5, 0, mat16);
		addWeighted(mat16, 0.5, mat2, 0.5, 0, mat16);
		addWeighted(mat16, 0.5, mat3, 0.5, 0, mat16);


	}
}