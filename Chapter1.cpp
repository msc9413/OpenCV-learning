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
//	Mat img=imread(path);	// matrix data type ��opencv����������ͼ��
//	imshow("Image", img);
//	waitKey(0);				// ������ʱ��0��ʾ����,����sleep
//	return 0;
//}

///////////////////  video  ///////////////////
//// ��Ƶ��һϵ��ͼ����Ҫ��������ͼ���֡ һһ������ʾ����˽�ʹ��whileѭ��
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
// �뵼����Ƶ��ͬ���ǣ�����Ҫ��Ƶ·����ֻ��Ҫ�����ID��id=0��ʾĬ�ϵ�����ͷ
int main() {
	VideoCapture cap(0);	// ��������ͷͼ��
	Mat img;				// ����ͼƬ��Ϣ
	while (true) {
		cap.read(img);		// ��ȡһ��ͼƬ��img��
		imshow("webcam video", img);
		waitKey(1);
	}
	return 0;
}
