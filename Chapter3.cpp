//ѧϰ��ε�����С�Լ��ü�ͼ��

#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Resize and Crop
/// </summary>
void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);//matrix data type ��opencv����������ͼ��
	Mat imgResize, imgCrop;

	cout << img.size() << endl;//��ӡͼ��ߴ�
	//resize(img, imgResize, Size(640, 480));//ָ��ͼƬ�ߴ�����
	resize(img, imgResize, Size(), 0.5, 0.5);//ָ�����ű�������ָ��ͼƬ�ߴ�

	//������������
	Rect roi(200, 100, 300, 300);//�����Ͻ�Ϊ����ԭ�㣬��200��100��Ϊ���ε����Ͻ����꣬300,300Ϊ���γ���
	imgCrop = img(roi);//�ü�ͼ��Ϊ���ҵ��ض����� ��Ӹ��ദ�� roi:region of interest

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);

	waitKey(0);//������ʱ��0��ʾ����
}