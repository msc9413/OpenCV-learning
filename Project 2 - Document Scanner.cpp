#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat imgOriginal, image, imgGray, imgBlur, imgCanny, imgDilate, imgWarp, imgCrop;
vector<Point> initPoints, docPoints;
int crop = 10;
int w = 420, h = 596;

Mat proprecessing(Mat img) {
	// �Ҷȴ�����˹ģ������Ե���
	cvtColor(img, imgGray, COLOR_BGR2GRAY);		
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	// ��Ե����
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel);

	return imgDilate;
}

void drawPoints(vector<Point> points, Scalar color) {
	for (int i = 0; i < points.size(); i++) {
		circle(imgOriginal, points[i], 5, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

vector<Point> getContours(Mat img) {
	
	// �ҵ���������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// �ҵ������������
	// ����Ĭ�� ������� Ϊ �ĵ�����
	int maxArea = 0, maxAreaIndex = 0;
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (area > maxArea) {
			maxArea = area;
			maxAreaIndex = i;
		}
	}

	// ��������
	vector<Point> conPoly;
	float peri = arcLength(contours[maxAreaIndex], true);
	approxPolyDP(contours[maxAreaIndex], conPoly, 0.02 * peri, true);
	
	
	//drawPoints(conPoly, Scalar(0, 0, 255));
	drawContours(imgOriginal, contours, maxAreaIndex, Scalar(255, 0, 255), 2);

	return conPoly;
}

/// ������
/// x + y ���Ϊ����, ��СΪ����
/// x - y ���Ϊ���ϣ���СΪ����
vector<Point> reorder(vector<Point> points) {
	vector<int> sumPoints, subPoints;
	for (Point& point : points) {
		sumPoints.push_back(point.x + point.y);
		subPoints.push_back(point.x - point.y);
	}

	vector<Point> retPoints;
	retPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	// 0
	retPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	// 1
	retPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);	// 2
	retPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);	// 3

	return retPoints;
}

Mat getWarp(Mat img, vector<Point> points) {

	Point2f src[4] = { points[0], points[1], points[2],points[3] };							// �任ǰλ��
	Point2f dst[4] = { Point(0.0f, 0.0f), Point(w, 0.0f), Point(0.0f, h), Point(w, h) };	// �任��λ��

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	return imgWarp;
}

int main() {
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);

	// resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
	image = imgOriginal.clone();

	// Ԥ����
	proprecessing(imgOriginal);

	// ��ȡ�������
	initPoints = getContours(imgDilate);

	// ���� ���ε��˳��
	docPoints = reorder(initPoints);
	drawPoints(docPoints, Scalar(0, 255, 0));

	// ��ԭͼ�����͸�ӱ任
	imgWarp = getWarp(image, docPoints);

	// ��ͼ��߽��ʵ��޼�
	Rect roi(crop, crop, w - 2 * crop, h - 2 * crop);
	imgCrop = imgWarp(roi);

	imshow("image", image);
	imshow("imgOriginal", imgOriginal);
	imshow("imgDilate", imgDilate);
	imshow("imgCrop", imgCrop);
	waitKey(0);
	return 0;
}
