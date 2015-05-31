#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace cv;
using namespace std;

class kontur{
public:
	int LmostX;
	int LmostY;
	int RmostX;
	int RmostY;
	int TmostX;
	int TmostY;
	int BmostX;
	int BmostY;
	int centroidX;
	int centroidY;
};


Mat pattern = imread("/home/kuba/Documents/vision/andrzejeVision/rumcajs2.png", CV_LOAD_IMAGE_COLOR);
Mat patternGray = imread("/home/kuba/Documents/vision/andrzejeVision/rumcajs2.png", CV_LOAD_IMAGE_GRAYSCALE);
Mat patternBlurred, patternThresh, readyToFind;

int main(){
	Scalar color = Scalar(0,255,0);
	GaussianBlur( patternGray, patternBlurred, Size(3, 3), 0 );
	namedWindow("Window", CV_WINDOW_AUTOSIZE);
	threshold(patternGray, patternThresh, 200, 255,0);
	//adaptiveThreshold(patternBlurred, adaThresh,130,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10);  
	bitwise_not(patternGray, readyToFind);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	findContours(patternThresh,contours,hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	
	Mat drawing = Mat::zeros(patternGray.size(),CV_8UC3);
	
	for(int i = 1; i < contours.size(); i++){
		Scalar color = Scalar(0,255,0);
		drawContours(drawing, contours,i,color,-1,8,hierarchy, 0,Point());
	}	
	
	cout<<contours.size()<<endl;
	bitwise_not(patternGray, readyToFind);
	Mat dupa, dupa2, dupa3;
	//dupa3 = dupa2.clone();
	Mat dupamiliontemp;
	Mat dupafinal;
	// first convert the image to grayscale
	cvtColor(drawing, dupa, CV_RGB2GRAY);

	// then adjust the threshold to actually make it binary
	threshold(dupa, dupa2, 100, 255, CV_THRESH_BINARY);
	
	findContours(dupa2,contours,hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	cout<<contours.size()<<endl;
	Mat dupamilion = Mat::zeros(dupa2.size(),CV_8UC3);
	Mat dupamilion1 = Mat::zeros(dupa2.size(),CV_8UC3);
	Mat finalnadupa = Mat::zeros(dupa2.size(),CV_8UC3);
	
	for(int i = 0; i < contours.size(); i++){
		//Scalar color = Scalar(0,255,0);
		drawContours(dupamilion, contours,i,color,2,8,hierarchy, 0,Point());
	}
			
	// first convert the image to grayscale
	cvtColor(dupamilion, dupamiliontemp, CV_RGB2GRAY);

	// then adjust the threshold to actually make it binary
	threshold(dupamiliontemp, dupafinal, 100, 255, CV_THRESH_BINARY);	
	String path;
	String windowName = "lol";
	char a='2';
	for (int i =0; i<contours.size(); i++){
		windowName +=a;
		namedWindow(windowName, CV_WINDOW_AUTOSIZE);
		Mat tempWindow = Mat::zeros(patternGray.size(),CV_8UC3);
		drawContours(tempWindow, contours,i,color,2,8,hierarchy, 0,Point());
		imshow(windowName, tempWindow);
	}
	
	kontur tab[contours.size()];
	uchar* p = dupafinal.data;
	for (int a = 0; a<contours.size(); a++){

	}
	int LmostX=-1;
	int LmostY=-1;
	int RmostX=-1;
	int RmostY=-1;
	int TmostX=-1;
	int TmostY=-1;
	int BmostX=-1;
	int BmostY=-1;
	
	cout<<dupafinal.rows<<endl;
	for (int i = 0; i<dupafinal.rows; i++){
		for (int j = 0; j<dupafinal.cols; j++){
			p = dupafinal.data + dupafinal.cols*i+j;
			if (*p==255){
				if (TmostY == -1)
					TmostY = i;
				if (TmostX == -1)
					TmostX = j;
				BmostX = j;
				BmostY = i;
			}
		}
	}

	for (int i = 0; i<dupafinal.cols; i++){
		for (int j = 0; j<dupafinal.rows; j++){
			p = dupafinal.data + dupafinal.cols*j+i;
			if (*p==255){
				if (LmostX == -1)
					LmostX = i;
				if (LmostY == -1)
					LmostY = j;
				RmostX = i;
				RmostY = j;
			}
		}
	}
	circle( dupafinal, Point(BmostX, BmostY), 5, Scalar(255,255,255), 3, 8, 0 );
	circle( dupafinal, Point(TmostX, TmostY), 5, Scalar(255,255,255), 3, 8, 0 );
	circle( dupafinal, Point(LmostX, LmostY), 5, Scalar(255,255,255), 3, 8, 0 );
	circle( dupafinal, Point(RmostX, RmostY), 5, Scalar(255,255,255), 3, 8, 0 );
	cout<<"TmostX: "<<TmostX<<endl;
	cout<<"TmostY: "<<TmostY<<endl;
	cout<<"BmostX: "<<BmostX<<endl;
	cout<<"BmostY: "<<BmostY<<endl;
	imshow("Window", dupafinal);
	waitKey(0);
	return 0;
}