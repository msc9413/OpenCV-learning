//学习如何检测形状或图像中的轮廓
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Shapes
/// </summary>


//! 获取轮廓
void getContours(Mat imgDil, Mat img) {//imgDil是传入的扩张边缘的图像用来查找轮廓，img是要在其上绘制轮廓的图像
	vector<vector<Point>> contours;//轮廓检测到的轮廓。每个轮廓线存储为一个点的向量

	vector<Vec4i> hierarchy;//包含关于映像拓扑的信息  typedef Vec<int, 4> Vec4i;具有4个整数值

	//在二值图像中查找轮廓。该函数利用该算法从二值图像中提取轮廓
	/* findContours  https://www.jianshu.com/p/253df408d222
	参数一：单通道图像矩阵，可以是灰度图，但更常用的是二值图像，一般是经过Canny、拉普拉斯等边缘检测算子处理过的二值图像。
	参数二：定义为“vector<vector<Point>> contours”，是一个向量，并且是一个双重向量，向量内每个元素保存了一组由连续的Point点构成的点的集合的向量，每一组Point点集就是一个轮廓。有多少轮廓，向量contours就有多少元素。
　　参数三：可选的输出向量，包含图像的拓扑信息。其中元素的个数和检测到的轮廓的数量相等。
	参数四：定义轮廓的检索模式：CV_RETR_EXTERNAL只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
	参数五：定义轮廓的近似方法：CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours向量内，拐点与拐点之间直线段上的信息点不予保留
	*/
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// drawContours(img, contours, -1, Scalar(255, 0, 255), 2);//img：要绘制轮廓在什么图片上，contours：要绘制的轮廓，-1定义要绘制的轮廓号（-1表示所有轮廓），Saclar表示轮廓颜色，2表示厚度
	
	vector<vector<Point>> conPoly(contours.size());//conploy的数量应小于contours
	vector<Rect> boundRect(contours.size());
	//过滤器：通过轮廓面积来过滤噪声
	for (int i = 0; i < contours.size(); i++) {//遍历检测到的轮廓
		// 计算轮廓面积
		int area = contourArea(contours[i]);
		cout << area << endl;

		string objectType;
		if (area > 1000) {//轮廓面积＞1000才绘制
			//计算轮廓周长或凹坑长度。该函数计算了曲线长度和封闭的周长。
			/*  arcLength 计算封闭轮廓的 周长 或 曲线的长度
				curve，输入的二维点集（轮廓顶点），可以是 vector 或 Mat 类型。
				closed，用于指示曲线是否封闭。
			*/
			float peri = arcLength(contours[i], true);//计算封闭轮廓周长

			/* approxPolyDP 主要功能是把一个连续光滑曲线折线化，对图像轮廓点进行多边形拟合
			* https://www.cnblogs.com/bjxqmy/p/12347265.html
			InputArray curve:		 一般是由图像的轮廓点组成的点集
			OutputArray approxCurve：表示输出的多边形点集
			double epsilon：		逼近的精度，设定的原始曲线与近似曲线之间的最大距离，即上文提到的的阈值。
			bool closed：			表示输出的多边形是否封闭
			*/
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);//以指定的精度近似多边形曲线。第二个参数conPloy[i]存储近似的结果，是输出。

			// boundingRect、minAreaRect 寻找包裹轮廓的最小正矩形、最小斜矩形
			boundRect[i] = boundingRect(conPoly[i]);//计算边界矩形

			int objCor = (int)conPoly[i].size();//找近似多边形的角点,三角形有3个角点，矩形/正方形有4个角点，圆形>4个角点
			cout << objCor << endl;
			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;//宽高比
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }//矩形的宽高比不会正好等于1
				else objectType = "Rect";
			}
			else if (objCor > 4) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle/*绘制边界矩形*/(img, boundRect[i].tl()/*tl()：topleft矩形左上角坐标*/, boundRect[i].br()/*br()：bottom right矩形右下角坐标*/, Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }/*文字坐标*/, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}

void main() {
	string path = "Resources/shapes.png";
	Mat img=imread(path);
	
	//在检测形状前，对图片预处理：转换为灰度、添加高斯模糊、使用Canny边缘检测器、扩张边缘
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);//cvt是convert的缩写，将图像从一种颜色空间转换为另一种颜色空间。
	GaussianBlur(imgGray, imgBlur,Size(3,3),3,0);//使用高斯滤波器模糊图像。该函数将源图像与指定的高斯核进行卷积,Size(7,7)是核大小,数字越大越模糊
	Canny(imgBlur, imgCanny, 25, 75);//边缘检测，阈值1，2可调，目的：显示更多的边缘
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//创建一个核，增加Size（只能是奇数）会扩张/侵蚀更多
	dilate(imgCanny, imgDil, kernel);//扩张边缘（增加边缘厚度）
	
	getContours(imgDil,img);//img是在其上绘 轮廓 的图片

	imshow("Image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dil", imgDil);*/
	waitKey(0);//增加延时，0表示无穷
}