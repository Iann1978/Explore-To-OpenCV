#include <opencv2/opencv.hpp> //ͷ�ļ�
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv; //����cv�����ռ�
#include "Utils.h"






static int slider_dev0 = 73;
static int slider_dev1 = 187;

static Mat edge_image;
static Mat cimage;
static void on_Trackbar(int, void* data)
{
	Mat& src_image = *(Mat*)data;

	imshow("ԭͼ", src_image);

	//����
	vector<vector<Point>> contours;

	//ʹ��canny������Ե
	
	src_image.convertTo(edge_image, 0x10);
	//Canny(src_image, edge_image, 50, 200, 3);
	//imshow("canny��Ե", edge_image);

	//��Ե׷�٣�û�д洢��Ե����֯�ṹ
	findContours(edge_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cimage = Mat::zeros(edge_image.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		//��ϵĵ�����Ϊ6
		size_t count = contours[i].size();
		if (count < 6)
			continue;

		//��Բ���
		RotatedRect box = fitEllipse(contours[i]);

		// λ�ù���
		if (box.center.x < 150)
			continue;

		if (box.center.x > 400)
			continue;

		if (box.center.y > 400)
			continue;

		//��״����          �������ȴ���30�����ų����������
		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)
			continue;
		if (MIN(box.size.width, box.size.height) < 10)
			continue;

		// ������Բ����
		EllipsePara ep;
		getEllipsePara(box, ep);
		std::cout << ep.A << " " << ep.B << " " << ep.C << " " << ep.F << std::endl;

		std::vector<float> array;
		std::vector<Point> array1;
		for (int j = 0; j < contours[i].size(); j++)
		{
			float f = ellips_value(ep, contours[i][j]);
			array.push_back(f);
			array1.push_back(contours[i][j]);
		}

		float mean;
		float dev;
		myMeanStdDev(array, mean, dev);
		dev /= MAX(box.size.width, box.size.height);

		Point mean1;
		float dev1;
		myMeanStdDev(array1, mean1, dev1);
		float dev0_threshold = exp( 1.0f * slider_dev0 / 10);
			
		// ��Ͽ��Ŷȹ���
		if (dev1 < slider_dev1)
			continue;

		// ��϶ȹ���
		if (dev > dev0_threshold)
			continue;

		//����׷�ٳ�������
		drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);

		//������ϵ���Բ
		ellipse(cimage, box, Scalar(0, 0, 255), 1, CV_AA);

	}
	imshow("��Բ��Ͻ��", cimage);
}



Mat EllipsFillting(Mat& src_image)
{	
	on_Trackbar(0, &src_image);
	createTrackbar("slider_dev0", "��Բ��Ͻ��", &slider_dev0, 200, on_Trackbar, &src_image);
	createTrackbar("slider_dev1", "��Բ��Ͻ��", &slider_dev1, 200, on_Trackbar, &src_image);
	return cimage;
}
