#pragma once
#include <opencv2\opencv.hpp>  
using namespace cv;
using namespace std;
#include "math.h"


using namespace cv;
using namespace std;

class StereoCameraLocating
{
	class StereoCameraParameter
	{
	public:
		float stereoDis = 0.06;
		float fovH, fovV;
		float width = 640;
		float height = 360;
	};

	StereoCameraParameter	cameraParameter;
	bool					isInitialized = false;
	VideoCapture			*cap = nullptr;
	Mat						frame, halfFrame, leftCamera, rightCamera, leftGrey, rightGrey, leftResult, rightResult;
	Mat						oldLeftGrey, oldRightGrey;
	vector<Point2f>			left_corners, right_corners;
	vector<Point2f>			old_left_corners, old_right_corners;
	vector<Point3f>			cornerPosition;
	



public:
	StereoCameraLocating();
	~StereoCameraLocating();

public:
	void InitCapture();
	void GetTextures();
	void GetFutures();
	void TracingFuturesInRight();
	void CalFuturesPosition();
	void CopyToOld();

	void TracingFuturesInLeft();
	//void TracingFuturesInLeft();

	void UpdateCameraLocation(/*float matl[4][4], float matr[4][4]*/)
	{
		if (!isInitialized)
		{
			InitCapture();
			GetTextures();
			GetFutures();
			TracingFuturesInRight();
			CalFuturesPosition();
		}
		else
		{
			CopyToOld();
			GetTextures();
			TracingFuturesInLeft();
			TracingFuturesInRight();
		}
	}












public:
	void UV2View(float viewl[3], float viewr[3], float uvl[2], float uvr[2]);
	void UV2World(Point3f &world, Point2f uvl, Point2f uvr);

	void CalViewMatrix(float matl[4][4], float matr[4][4], vector<Point2f> uvl, vector<Point2f> uvr, vector<Point3f> world);



	void ReLocateFutures(vector<Point2f>& uvl, vector<Point2f>& uvr, Mat left, Mat right)
	{

	}


public:
	
	
	


	



	
};

