//ѧϰ���Ť��ͼ����ɨ���ĵ�
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Warp Images
/// </summary>
float w = 250, h = 350;//ͼƬ��С
Mat matrix, imgWarp;
void main() {
	//ͼƬ�û�ͼ�򿪣�����Ļ���½ǻ���ʾ�������
	string path = "Resources/cards.jpg";
	Mat img = imread(path);//matrix data type ��opencv����������ͼ��
	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };//Point2f��ʾ������
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };//Point2f��ʾ������

	// ����ǰ������ȷ�� �任����
	matrix = getPerspectiveTransform(src, dst);
	// ��img��͸�ӱ任
	warpPerspective(img, imgWarp, matrix, Size(w, h));

	// ȷ��src�����Ƿ���ȷ
	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}

	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	waitKey(0);//������ʱ��0��ʾ����
}