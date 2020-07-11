#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "bmpFile.h"
#include"CsrLocatePos.h"

typedef unsigned char BYTE;
using namespace std;

void debug(BYTE*pGryImg, int width, int height, const char * name)
{
	char str[256];
	sprintf(str, "%s", name);
	namedWindow(str, WINDOW_NORMAL);
	Mat pMat = Mat(height, width, CV_8UC1, pGryImg);
	imshow(str, pMat);
	waitKey(0);
}

//文本检测
int main()
{
	char seqFileName[256];
	bool flag = false;
	BYTE *pGryImg;
	int width, height, id;
	CsrLocatePos myImg;
	for (id = 3; id < 6; id++)
	{
		//----------------step1.读图像----------------------//
		sprintf(seqFileName, "..\\040%dGry.bmp", id);
		pGryImg = Rmw_Read8BitBmpFile2Img(seqFileName, &width, &height);
		if (!pGryImg)
		{
			printf("*file open err!\n");
			getchar();
			return 0;
		}

		//----------------step2.区域搜索--------------------//
		flag = myImg.Initialize(false, width, height, 2);//初始化，灰度图
		if (!flag)
		{
			printf("CsrLocatePos.Initialize() error!\n");
			return 0;
		}
		flag = myImg.CsrSearchRectTarget(pGryImg, width, height, 28, 28, 10, pGryImg);

		//----------------step3.保存结果--------------------//
		if (flag)
		{
			sprintf(seqFileName, "..\\040%dGryDetectRes.bmp", id);
			Rmw_Write8BitImg2BmpFileMark(pGryImg, width, height, seqFileName);
		}
		else printf("第 %d 幅图像定位失败！\n", id);

	}
	delete pGryImg;
	return 0;
}
