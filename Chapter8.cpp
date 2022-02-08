//ѧϰ���ͼ���е��沿
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>//������ͷ�ļ�
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Images
/// </summary>
void main() {
	string path = "Resources/test.png";
	Mat img=imread(path);
	CascadeClassifier faceCascade;/*���ڶ�����ļ�����������*/
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");//���ļ����ط�����(�Ѿ�ѵ���õ�ģ��)

	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }//����ļ��Ƿ���سɹ�

	vector<Rect> faces;
	faceCascade.detectMultiScale(img/*����*/, faces/*���*/, 1.1/*��������*/, 10/*��С�ھ�*/);//������ͼ���м�ⲻͬ��С�Ķ��󡣼�⵽�Ķ����Ծ����б����ʽ���ء�
	
	for (int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i].tl(),faces[i].br(), Scalar(255, 0, 255), 3);//���ƾ���
	}

	imshow("Image", img);
	waitKey(0);//������ʱ��0��ʾ����
}