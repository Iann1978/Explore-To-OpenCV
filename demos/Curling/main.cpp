
#include <opencv2/opencv.hpp> //头文件
#include<opencv2/imgproc/imgproc.hpp>
#include "Utils.h"

using namespace cv; //包含cv命名空间


void FindIceArena_TopEdge(CurlingArenaRebuildingData& rebuildingData);
void FindIceArena_LeftEdge(CurlingArenaRebuildingData& rebuildingData);
void FindIceArena_RightEdge(CurlingArenaRebuildingData& rebuildingData);
void FindIceArena_BigCircle(CurlingArenaRebuildingData& rebuildingData);
void FindIceArena_MiddleCircle(CurlingArenaRebuildingData& rebuildingData);
void RebuildIceArena(CurlingArenaRebuildingData& rebuildingData);

int main()
{
	CurlingArenaRebuildingData rebuildingData;
	Mat srcImage = imread("1.jpg");
	imshow("srcImage", srcImage);

	do
	{
		rebuildingData.Reset();
		rebuildingData.srcImage = srcImage;

		FindIceArena_TopEdge(rebuildingData);
		FindIceArena_LeftEdge(rebuildingData);
		FindIceArena_RightEdge(rebuildingData);
		FindIceArena_BigCircle(rebuildingData);
		FindIceArena_MiddleCircle(rebuildingData);
		RebuildIceArena(rebuildingData);
		continue;
	} while (waitKey(0) != 0x1b);

	waitKey(0);
}
