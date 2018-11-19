#pragma once
class Calibration
{	
	VideoCapture cap;
	Size image_size;							// 图片尺寸
	Size board_size = Size(4, 6);				//标定板上每行、每列的角点数
	Size square_size = Size(10, 10);			//实际测量得到的标定板上每个棋盘格的大小
	vector<Point2f> image_points_buf;			//缓存每幅图像上检测到的角点
	vector<vector<Point2f>> image_points_seq;	//保存检测到的所有角点
	vector<Point3f> object_points_buf;			//缓存每幅图像上检测到的角点的世界坐标
	vector<vector<Point3f>> object_points_seq;  //保存检测到的所有角点的世界坐标
	
	Mat curFrame;


	int frameRemain = 5;

	Mat cameraMatrix, distCoeffs, rvecsMat, tvecsMat;

public:
	void Calculate()
	{	
		cout << "Calculate.\n";
		OpenVideoCapture();

		while (frameRemain)
		{	
			GetOneFrame();
			cout << "Frame." << endl << frameRemain  << "\n";
			
			//if (key == 99)
			{
				if (GetImageCornersFromCurrentFrame())
				{
					GetWorldCornersFrameCurrentFrame();
					frameRemain--;
					waitKey(500);
				}
			}
			int key = waitKey(30);
		}

		//开始标定
		calibrateCamera(object_points_seq, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);

		cout << "cameraMatrix:" << cameraMatrix << endl;

		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		waitKey();
		
	}

	void OpenVideoCapture()
	{	
		if (!cap.isOpened())
		{
			cout << "OpenVideoCapture()\n";
			cap.open(0);
			cap >> curFrame;
			image_size.width = curFrame.cols;
			image_size.height = curFrame.rows;

			imshow("Capture Frame", curFrame);
			waitKey(30);
		}
	}

	void GetOneFrame()
	{
		cout << "GetOneFrame()\n";
		cap >> curFrame;
		imshow("Capture Frame", curFrame);
		waitKey(30);
	}

	bool GetImageCornersFromCurrentFrame()
	{
		cout << "GetCornersFromCurrentFrame()\n";
		bool succeed = false;
		//提取角点
		if (0 == findChessboardCorners(curFrame, board_size, image_points_buf))
		{
			cout << "can not find chessboard corners!\n";
			succeed = false;
			waitKey(30);
		}
		else
		{
			Mat view_gray;
			cvtColor(curFrame, view_gray, CV_BGR2GRAY);
			find4QuadCornerSubpix(view_gray, image_points_buf, Size(5, 5));//亚像素精确化
			image_points_seq.push_back(image_points_buf);//保存亚像素点
			
			//图像上显示角点位置
			drawChessboardCorners(view_gray, board_size, image_points_buf, false);
			imshow("Canmera Calibration", view_gray);
			succeed = true;
			waitKey(30);
		}

		return succeed;
	}

	void GetWorldCornersFrameCurrentFrame()
	{
		cout << "GetWorldCornersFrameCurrentFrame()\n";

		object_points_buf.clear();
		
		for (int i = 0; i<board_size.height; i++)
		{
			for (int j = 0; j<board_size.width; j++)
			{
				Point3f realPoint;
				//假设标定板放在世界坐标系中Z=0的平面上
				realPoint.x = i * square_size.width;
				realPoint.y = j * square_size.height;
				realPoint.z = 0;
				object_points_buf.push_back(realPoint);
			}
		}
		object_points_seq.push_back(object_points_buf);
		waitKey(30);
	}

public:
	Calibration();
	~Calibration();


};

