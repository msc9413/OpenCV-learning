//ѧϰ��λ�����״��Բ�Ρ����Ρ��߶Σ��������ͼƬ��д��

#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Draw Shapes and Text
/// </summary>
void main() {
	//�����հ�ͼ��
	//Scalar(255, 0, 255)������ɫ��255��0��0��������ɫ��255��0��255��������ɫ��0��0��0��������ɫ��255��255��255��
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));//(512,512)ΪͼƬ��С��CV8UC3��8U��ʾÿ�����ص�ֵ��0��255��3��ʾ3����ɫͨ��BGR,Scalar(255, 0, 0)��ʾͼ�����ɫ

	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);//��һ��������ͼƬ���ڶ���������Բ�����꣬������������Բ��С�����ĸ���������ɫ������������Ǻ�ȣ����Բ�д������Ҫ��������FILLED
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);//��һ��Point���������Ͻ����꣬�ڶ���Point���������½�����
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);//��һ��Point��������ꡢ�ڶ���Point���յ�����
	// Ҫ���Ƶ�ͼƬ ��������  ��ʼ��  ����  ��С   ��ɫ   ���
	putText(img, "moshaocongĪ�ٴ�", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2);

	imshow("Image", img);
	waitKey(0);//������ʱ��0��ʾ����
}