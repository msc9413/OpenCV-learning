#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Basic Function
/// </summary>
void main() {
	string path = "Resources/test.png";
	Mat img=imread(path);//matrix data type 由opencv引入来处理图像
	Mat imgGray,imgBlur,imgCanny,imgDil,imgErode;

	// cvt是convert的缩写，将图像从一种颜色空间转换为另一种颜色空间。
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	/* GaussianBlur
	第一个参数：InputArray类型的src，输入图像，Mat类的对象。该函数对通道是独立处理的，且可以处理任意通道数的图像，但是待处理的图像深度应该是CV_8U，CV_16U，CV_16S，CV_32F，CV_64F。
	第二个参数：OutputArray类型的dst，目标图像，需要和输入图像有相同的尺寸和类型。
	第三个参数：Size类型的lsize，内核的大小。一般用Size(w, h)的写法表示，w和h可以不同，但是必须是正数和奇数，例如Size(3, 3)，Size(5, 5)。
	第四个参数：double类型的sigmaX，表示高斯核函数在X方向上的标准偏差。
	第五个参数：double类型的sigmaY，表示高斯核函数在Y方向上的标准偏差。如果sigmaY是0，就将它设为sigmaX。如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。为了结果的正确性，最好是将Size、sigmaX、sigmaY全部指定到。
	第六个参数：int类型的borderType，用于推断图像外部像素的某种边界模式，默认值 BORDER_DEFAULT，我们一般不管它。
	*/
	GaussianBlur(imgGray, imgBlur,Size(7,7),5,0);//使用高斯滤波器模糊图像。该函数将源图像与指定的高斯核进行卷积,Size(7,7)是核大小,数字越大越模糊
	/* Canny
	https://blog.csdn.net/xddwz/article/details/111585648
	第一个参数：InputArray类型的image，输入图像，Mat对象节课，需为单通道8位图像。
	第二个参数：OutputArray类型的edges，输出的边缘图，需要和输入图像有相同的尺寸和类型。
	第三个参数：double类型的threshold1，第一个滞后性阈值。
	第四个参数：double类型的threshold2，第二个滞后性阈值。
	第五个参数：int类型的apertureSize，表示算子的孔径的大小，默认值时3.
	第六个参数：bool类型的L2gradient，一个计算图像梯度复制的标识，默认false。
	*/
	// 阈值1和阈值2两者中比较小的值用于边缘连接，较大的值用来控制边缘的初始段，推荐高低阈值比在2:1和3:1之间。
	Canny(imgBlur, imgCanny, 25, 75);//边缘检测，阈值1，2可调，目的：显示更多的边缘
	
	// https://blog.csdn.net/xddwz/article/details/111371222
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//创建一个核，增加Size（只能是奇数）会扩张/侵蚀更多
	dilate(imgCanny, imgDil, kernel);//扩张边缘（增加边缘厚度）
	erode(imgDil, imgErode, kernel);//侵蚀边缘（减小边缘厚度）
	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);
	waitKey(0);//增加延时，0表示无穷

}

