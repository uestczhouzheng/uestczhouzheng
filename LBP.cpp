#include <iostream>  
#include <C:\opencv\opencv\build\include\opencv2/core/core.hpp>  
#include <C:\opencv\opencv\build\include\opencv2/highgui/highgui.hpp>  
#include <C:\opencv\opencv\build\include\opencv2/imgproc/imgproc.hpp>  
#include "intrins.h"  

using namespace cv;
using namespace std;

#define model_rotation  
#define model_equivalent  

int main()
{
	Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);//灰度  
	Mat pic = Mat::zeros(img.rows, img.cols, img.type());
	imshow("src", img);
	//p1    p2  p3  
	//p8    p0  p4  
	//p7    p6  p5  
	for (int i = 1; i < img.rows - 1; i++)
	{
		for (int j = 1; j < img.cols - 1; j++)
		{
			uchar p[9];

			p[0] = img.at<uchar>(i, j);//中心  
			p[1] = img.at<uchar>(i - 1, j - 1);
			p[2] = img.at<uchar>(i - 1, j);
			p[3] = img.at<uchar>(i - 1, j + 1);
			p[4] = img.at<uchar>(i, j + 1);
			p[5] = img.at<uchar>(i + 1, j + 1);
			p[6] = img.at<uchar>(i + 1, j);
			p[7] = img.at<uchar>(i + 1, j - 1);
			p[8] = img.at<uchar>(i, j - 1);

			uchar value = 0;//LBP值  
			for (int k = 1; k <= 8; k++)
			{
				value += (p[k] >= p[0]) << (8 - k);
			}
			//等价模式  
#ifdef model_equivalent  
			uchar temp = _cror(value, 1);
			if (_mm_popcnt_u32(temp & value) > 2)//_mm_popcnt_u32计算二进制数1的个数  
			{
				pic.at<uchar>(i, j) = value;
			}
#else  
			pic.at<uchar>(i, j) = value;
#endif  
			//旋转不变  
#ifdef model_rotation  
			uchar rot[8];
			_rota(value, rot);
			pic.at<uchar>(i, j) = _min(rot);
#endif  
		}
	}
	imshow("LBP_equ_rot", pic);
	waitKey();


	return 0;
}
