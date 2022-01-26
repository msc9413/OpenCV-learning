#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// <summary>
/// Basic Function
/// </summary>
void main() {
	string path = "Resources/test.png";
	Mat img=imread(path);//matrix data type ��opencv����������ͼ��
	Mat imgGray,imgBlur,imgCanny,imgDil,imgErode;

	// cvt��convert����д����ͼ���һ����ɫ�ռ�ת��Ϊ��һ����ɫ�ռ䡣
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	/* GaussianBlur
	��һ��������InputArray���͵�src������ͼ��Mat��Ķ��󡣸ú�����ͨ���Ƕ�������ģ��ҿ��Դ�������ͨ������ͼ�񣬵��Ǵ������ͼ�����Ӧ����CV_8U��CV_16U��CV_16S��CV_32F��CV_64F��
	�ڶ���������OutputArray���͵�dst��Ŀ��ͼ����Ҫ������ͼ������ͬ�ĳߴ�����͡�
	������������Size���͵�lsize���ں˵Ĵ�С��һ����Size(w, h)��д����ʾ��w��h���Բ�ͬ�����Ǳ���������������������Size(3, 3)��Size(5, 5)��
	���ĸ�������double���͵�sigmaX����ʾ��˹�˺�����X�����ϵı�׼ƫ�
	�����������double���͵�sigmaY����ʾ��˹�˺�����Y�����ϵı�׼ƫ����sigmaY��0���ͽ�����ΪsigmaX�����sigmaX��sigmaY����0����ô����ksize.width��ksize.height���������Ϊ�˽������ȷ�ԣ�����ǽ�Size��sigmaX��sigmaYȫ��ָ������
	������������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ��Ĭ��ֵ BORDER_DEFAULT������һ�㲻������
	*/
	GaussianBlur(imgGray, imgBlur,Size(7,7),5,0);//ʹ�ø�˹�˲���ģ��ͼ�񡣸ú�����Դͼ����ָ���ĸ�˹�˽��о��,Size(7,7)�Ǻ˴�С,����Խ��Խģ��
	/* Canny
	https://blog.csdn.net/xddwz/article/details/111585648
	��һ��������InputArray���͵�image������ͼ��Mat����ڿΣ���Ϊ��ͨ��8λͼ��
	�ڶ���������OutputArray���͵�edges������ı�Եͼ����Ҫ������ͼ������ͬ�ĳߴ�����͡�
	������������double���͵�threshold1����һ���ͺ�����ֵ��
	���ĸ�������double���͵�threshold2���ڶ����ͺ�����ֵ��
	�����������int���͵�apertureSize����ʾ���ӵĿ׾��Ĵ�С��Ĭ��ֵʱ3.
	������������bool���͵�L2gradient��һ������ͼ���ݶȸ��Ƶı�ʶ��Ĭ��false��
	*/
	// ��ֵ1����ֵ2�����бȽ�С��ֵ���ڱ�Ե���ӣ��ϴ��ֵ�������Ʊ�Ե�ĳ�ʼ�Σ��Ƽ��ߵ���ֵ����2:1��3:1֮�䡣
	Canny(imgBlur, imgCanny, 25, 75);//��Ե��⣬��ֵ1��2�ɵ���Ŀ�ģ���ʾ����ı�Ե
	
	// https://blog.csdn.net/xddwz/article/details/111371222
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//����һ���ˣ�����Size��ֻ����������������/��ʴ����
	dilate(imgCanny, imgDil, kernel);//���ű�Ե�����ӱ�Ե��ȣ�
	erode(imgDil, imgErode, kernel);//��ʴ��Ե����С��Ե��ȣ�
	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);
	waitKey(0);//������ʱ��0��ʾ����

}

