#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int main(int argc,char* argv[])
{
	ifstream fin("calibdata.txt");//�궨����ͼ�ļ�·��
	ofstream fout("caliberation_result.txt");//����궨������ļ�

	//��ȡÿһ��ͼ�񣬴�����ȡ�ǵ㣬Ȼ��Խǵ���������ؾ�ȷ��
	cout<<"��ʼ��ȡ�ǵ�......";//ͼƬ����
	int image_count = 0;
	Size image_size;//ͼƬ�ߴ�
	Size board_size = Size(4,6);//�궨����ÿ�С�ÿ�еĽǵ���
	vector<Point2f> image_points_buf;//����ÿ��ͼ���ϼ�⵽�Ľǵ�
	vector<vector<Point2f>> image_points_seq;//�����⵽�����нǵ�
	string filename;
	int count = -1;//���ڴ洢�ǵ���
	
	while(getline(fin,filename))
	{
		image_count++;
		//���ڹ۲������
		cout<<"image_count = "<<image_count<<endl;
		//�������
		cout<<"-->count == 1"<<count;
		Mat imageInput = imread(filename);
		if(image_count == 1)
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			cout<<"image_size.width = "<<image_size.width<<endl;
			cout<<"image_size.height = "<<image_size.height<<endl;
		}

		//��ȡ�ǵ�
		if(0 == findChessboardCorners(imageInput,board_size,image_points_buf))
		{
			cout<<"can not find chessboard corners!\n";
			exit(1);
		}
		else
		{
			Mat view_gray;
			cvtColor(imageInput,view_gray,CV_BGR2GRAY);
			find4QuadCornerSubpix(view_gray,image_points_buf,Size(5,5));//�����ؾ�ȷ��
			image_points_seq.push_back(image_points_buf);//���������ص�

			//ͼ������ʾ�ǵ�λ��
			drawChessboardCorners(view_gray,board_size,image_points_buf,false);
			imshow("Canmera Calibration",view_gray);
			waitKey(500);
		}
	}

	int total = image_points_seq.size();
	cout<<"total = "<<total<<endl;
	int CornerNum = board_size.width*board_size.height;//ÿ��ͼƬ���ܵĽǵ���
	for(int ii=0;ii<total;ii++)
	{
		if(0 == ii%CornerNum)
		{
			int i = -1;
			i = ii / CornerNum;
			int j = i + i;
			cout<<"-->��"<< j <<"ͼƬ������-->: "<<endl;
		}
		if(0 == ii % 3)
		{
			cout<<endl;
		}
		else
		{
			cout.width(10);
		}
		cout<<" -->"<<image_points_seq[ii][0].x;
		cout<<" -->"<<image_points_seq[ii][0].y;
	}
	cout<<"\n�ǵ���ȡ���!\n";

	//������������궨
	cout<<"��ʼ�궨....."<<endl;
	//������ά��Ϣ
	Size square_size = Size(10,10);//ʵ�ʲ����õ��ı궨����ÿ�����̸�Ĵ�С
	vector<vector<Point3f>> object_points;
	//�������
	Mat cameraMatrix = Mat(3,3,CV_32FC1,Scalar::all(0));//����ڲ�
	vector<int> point_counts;//ÿ��ͼ���нǵ������
	Mat distCoeffs = Mat(1,5,CV_32FC1,Scalar::all(0));//�������5������ϵ��k1,k2,p1,p2,k3
	vector<Mat> tvecsMat;//ÿ��ͼ�����ת����
	vector<Mat> rvecsMat;//ÿ��ͼ���ƽ������

	//��ʼ���궨���Ͻǵ����ά����
	int i,j,t;
	for(t=0;t<image_count;t++)
	{
		vector<Point3f> tempPointSet;
		for(i=0;i<board_size.height;i++)
		{
			for(j=0;j<board_size.width;j++)
			{
				Point3f realPoint;
				//����궨�������������ϵ��Z=0��ƽ����
				realPoint.x = i*square_size.width;
				realPoint.y = j*square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}
	//��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨��
	for(i=0;i<image_count;i++)
	{
		point_counts.push_back(board_size.width*board_size.height);
	}
	//��ʼ�궨
	calibrateCamera(object_points,image_points_seq,image_size,cameraMatrix,distCoeffs,rvecsMat,tvecsMat,0);
	cout<<"�궨���~��"<<endl;
	//�Ա궨�����������
	cout<<"��ʼ���۱궨���......"<<endl;
	double total_err = 0.0;//����ͼ���ƽ�������ܺ�
	double err = 0.0;//ÿ��ͼ���ƽ�����
	vector<Point2f> image_points2;//�������¼���õ���ͶӰ��
	cout<<"\tÿ��ͼ��ı궨��"<<endl;
	fout<<"ÿ��ͼ��ı궨��"<<endl;
	for(i=0;i<image_count;i++)
	{
		vector<Point3f> tempPointSet = object_points[i];
		//ͨ���õ������������������Կռ����ά���������ͶӰ����
		projectPoints(tempPointSet,rvecsMat[i],tvecsMat[i],cameraMatrix,distCoeffs,image_points2);
		//�����ĵ�ͶӰ��;ɵ�ͶӰ��֮������
		vector<Point2f> tempImagePoint = image_points_seq[i];
		Mat tempImagePointMat = Mat(1,tempImagePoint.size(),CV_32FC2);
		Mat image_points2Mat = Mat(1,image_points2.size(),CV_32FC2);
		for(int j=0;j<tempImagePoint.size();j++)
		{
			image_points2Mat.at<Vec2f>(0,j) = Vec2f(image_points2[j].x,image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0,j) = Vec2f(tempImagePoint[j].x,tempImagePoint[j].y);
		}
		err = norm(image_points2Mat,tempImagePointMat,NORM_L2);
		total_err += err /= point_counts[i];
		cout<<"��"<<i+1<<"��ͼ���ƽ����"<<err<<"����"<<endl;
		fout<<"��"<<i+1<<"��ͼ���ƽ����"<<err<<"����"<<endl;
	}
	cout<<"����ƽ����"<<total_err/image_count<<"����"<<endl;
	fout<<"����ƽ����"<<total_err/image_count<<"����"<<endl<<endl;
	cout<<"�������!"<<endl;
	//����궨���
	cout<<"��ʼ����궨���......."<<endl;
	Mat rotation_matrix = Mat(3,3,CV_32FC1,Scalar::all(0));//����ÿ��ͼ�����ת����
	fout<<"����ڲ�������"<<endl;
	fout<<cameraMatrix<<endl<<endl;
	fout<<"����ϵ����"<<endl;
	fout<<distCoeffs<<endl<<endl<<endl;
	for(int i=0;i<image_count;i++)
	{
		fout<<"��"<<i+1<<"��ͼ�����ת������"<<endl;	
		fout<<tvecsMat[i]<<endl;
		//����ת����ת��Ϊ���Ӧ����ת����
		Rodrigues(tvecsMat[i],rotation_matrix);
		fout<<"��"<<i+1<<"��ͼ�����ת����"<<endl;
		fout<<rotation_matrix<<endl;
		fout<<"��"<<i+1<<"��ͼ���ƽ��������"<<endl;
		fout<<rvecsMat[i]<<endl<<endl;
	}
	cout<<"��ɱ���"<<endl;
	fout<<endl;

	//��ʾ�궨���
	Mat mapx = Mat(image_size,CV_32FC1);
	Mat mapy = Mat(image_size,CV_32FC1);
	Mat R = Mat::eye(3,3,CV_32F);
	cout<<"�������ͼ��"<<endl;
	string imageFileName;
	stringstream StrStm;
	for(int i=0;i!=image_count;i++)
	{
		cout<<"Frame #"<<i+1<<"..."<<endl;
		initUndistortRectifyMap(cameraMatrix,distCoeffs,R,cameraMatrix,image_size,CV_32FC1,mapx,mapy);
		StrStm.clear();
		imageFileName.clear();
		string filePath = "chess";
		StrStm<<i+1;
		StrStm>>imageFileName;
		filePath += imageFileName;
		filePath += ".bmp";
		Mat imageSource = imread(filePath);
		Mat newimage = imageSource.clone();
		if(!imageSource.data)
		{
			cout<<"��ȡͼƬ����"<<endl;
		}

		remap(imageSource,newimage,mapx,mapy,CV_INTER_LINEAR);
		StrStm.clear();
		filePath.clear();
		StrStm<<i+1;
		StrStm>>imageFileName;
		imageFileName += "_d.jpg";
		imwrite(imageFileName,newimage);
	}
	cout<<"�������"<<endl;
	return 0;
}