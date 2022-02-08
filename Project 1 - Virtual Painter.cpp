#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

 //<summary>
 //Project 1
 //ʹ��HSV�ռ�����ɫ���ҵ���������λ�á�ȡ������λ��Ȼ�󴴽�һ��Բ
 //</summary>

Mat img;
vector<vector<int>> newPoints;

vector<vector<int>> myColors{ {98,109,54,127,255,255},//��ɫ��hmin smin vmin hmax smax vmax��
								{35,0,0,77,245,255} };//��ɫ��hmin smin vmin hmax smax vmax��

vector<Scalar> myColorValues{ {255,0,255},//��ɫ
								{0,255,0} };//��ɫ

//! ��ȡ����
Point getContours(Mat imgDil) {//imgDil�Ǵ�������ű�Ե��ͼ����������������img��Ҫ�����ϻ���������ͼ��
	vector<vector<Point>> contours;//������⵽��������ÿ�������ߴ洢Ϊһ���������

	vector<Vec4i> hierarchy;//��������ӳ�����˵���Ϣ  typedef Vec<int, 4> Vec4i;����4������ֵ

	//�ڶ�ֵͼ���в����������ú������ø��㷨�Ӷ�ֵͼ������ȡ����
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//img��Ҫ����������ʲôͼƬ�ϣ�contours��Ҫ���Ƶ�������-1����Ҫ���Ƶ������ţ�-1��ʾ������������Saclar��ʾ������ɫ��2��ʾ���
	
	vector<vector<Point>> conPoly(contours.size());//conploy������ӦС��contours
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);

	//��������ͨ�������������������
	for (int i = 0; i < contours.size(); i++) {//������⵽������
		int area = contourArea(contours[i]);
		
		//cout << area << endl;

		string objectType;
		if (area > 1000) {//���������1000�Ż���
			//���������ܳ��򰼿ӳ��ȡ��ú������������߳��Ⱥͷ�յ��ܳ���
			float peri = arcLength(contours[i], true);//�����������ܳ�
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//��ָ���ľ��Ƚ��ƶ�������ߡ��ڶ�������conPloy[i]�洢���ƵĽ�����������

			boundRect[i] = boundingRect(conPoly[i]);//����߽����

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			rectangle/*���Ʊ߽����*/(img, boundRect[i].tl()/*tl()��topleft�������Ͻ�����*/, boundRect[i].br()/*br()��bottom right�������½�����*/, Scalar(0, 255, 0), 5);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			
		}
	}
	return myPoint;
}


vector<vector<int>> findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);//ת��ͼ��HSV�ռ䣬�����в�����ɫ��������

	for (int i = 0; i < myColors.size(); i++)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);//������ɫ���޺����ޣ���Ϊ���������Ͳ�ͬ����Ӱ����ɫ��ֵ������ȫ��ͬ������һ��ֵ�ķ�Χ
		//imshow(to_string(i), mask);
		Point myPoint=getContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0) {//û��⵽������ʱ��Ͳ������µ�
			newPoints.push_back({ myPoint.x,myPoint.y,i });//iΪ��ɫ����
		}
	}
	return newPoints;
	
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {
	for (int i = 0; i < newPoints.size(); i++) {
		circle(img, Point(newPoints[i][0], newPoints[i][1]),6,myColorValues[newPoints[i][2]],FILLED);
	}
}

void main() {
	VideoCapture cap(0);//���id=0
	

	while (true) {
		cap.read(img);

		newPoints=findColor(img);
		drawOnCanvas(newPoints,myColorValues);
		imshow("Image", img);
		waitKey(1);//������ʱ 1ms������̫��
	}

}