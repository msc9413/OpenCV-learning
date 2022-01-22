#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// import image
/// </summary>
int main() {
	string path = "Resources/test.png";
	Mat img=imread(path);	// matrix data type 由opencv引入来处理图像
	imshow("Image", img);
	waitKey(0);				// 增加延时，0表示无穷,类似sleep
	return 0;
}

