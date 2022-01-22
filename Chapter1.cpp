#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// import image
/// </summary>
//int main() {
//	string path = "Resources/test.png";
//	Mat img=imread(path);	// matrix data type 由opencv引入来处理图像
//	imshow("Image", img);
//	waitKey(0);				// 增加延时，0表示无穷,类似sleep
//	return 0;
//}

///////////////////  video  ///////////////////
//// 视频是一系列图像，需要遍历所有图像或帧 一一捕获并显示，因此将使用while循环
//int main() {
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//	while (true) {
//		cap.read(img);
//		imshow("video", img);
//		waitKey(20);
//	}
//	return 0;
//}

/////////////////  webcam  ///////////////////
// 与导入视频不同的是，不需要视频路径，只需要给相机ID，id=0表示默认的摄像头
int main() {
	VideoCapture cap(0);	// 捕获摄像头图像
	Mat img;				// 保存图片信息
	while (true) {
		cap.read(img);		// 读取一张图片到img中
		imshow("webcam video", img);
		waitKey(1);
	}
	return 0;
}
