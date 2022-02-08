//学习检测图片中的颜色，来创建特定对象的对象检测器
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Color Detection
/// </summary>
int hmin = 0, smin = 0, vmin = 0;
int hmax = 0, smax = 255, vmax = 255;//如何确定这6个值，每次都更改所有这些再次运行很痛苦 -->创建跟踪栏（使我们可以实时更改这些值）
void main() {
	string path = "Resources/lambo.png";
	Mat img=imread(path);

	// https://blog.csdn.net/qq_37791134/article/details/80984508
	Mat imgHSV,mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);//转换图像到HSV空间，在其中查找颜色更加容易
	namedWindow("Trackbars", (640, 200));//(640,200)是尺寸
	//运行时，把3个min的都移到最小值，把3个max的都移到最大值，然后移动使其保持为白色
	/*  createTrackbar 用来创建一个可以调节输入变量值的滑动条，并将改控件依附于指定的窗口上。
		参数1：滑动条名字
		参数2：想要把该滑动条依附到的窗口名字, namedWindow()函数中的相同
		参数3：创建滑动条时，滑动条的初始值
		参数4：滑动条的最大值，即所有滑动条的数据变动都要在0-count之间，滑动条最小值为0
	*/
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);//对于hue色相饱和度最大180,对于另外两个色相饱和度最大255
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);
	
	while (true) {
		//检查数组元素是否位于其他两个数组的元素之间。
		//imgHSV为输入图像，mask为输出图像

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		/* inRange
		将在两个阈值内的像素值设置为白色（255），而不在阈值区间内的像素值设置为黑色（0），该功能类似于之间所讲的双阈值化操作。
		参数1：输入要处理的图像，可以为单通道或多通道。
		参数2：包含下边界的数组或标量。
		参数3：包含上边界数组或标量。
		参数4：输出图像，二值化之后的图像,与输入图像src 尺寸相同且为CV_8U 类型。
		*/
		inRange(imgHSV, lower, upper, mask);//定义颜色下限和上限，因为由于照明和不同的阴影，颜色的值将不完全相同，会是一个值的范围
		imshow("Image", img);
		// imshow("Image HSV", imgHSV);
		imshow("Image mask", mask);
		waitKey(1);//增加延时
	}
}