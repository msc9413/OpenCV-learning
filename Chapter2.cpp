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
	Mat img=imread(path);	// matrix data type ��opencv����������ͼ��
	imshow("Image", img);
	waitKey(0);				// ������ʱ��0��ʾ����,����sleep
	return 0;
}

