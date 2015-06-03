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
	float centroidX;
	float centroidY;
	float area;
	vector <Point2f> corners;
};
String path = "/home/kuba/Documents/vision/andrzejeVision/jprdl2.jpg";
Mat pattern = imread(path, CV_LOAD_IMAGE_COLOR);
Mat patternGray = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
Mat patternThresh, drawing1Gray, drawing1Thresh;

int main(){
	namedWindow("Window", CV_WINDOW_AUTOSIZE);
	threshold(patternGray, patternThresh, 120, 255,0);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(patternThresh,contours,hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	Mat drawing1 = Mat::zeros(patternGray.size(),CV_8UC3);
	for (int i =1; i<contours.size(); i++){
		drawContours(drawing1, contours,i,Scalar(255, 255, 255),-1,8,hierarchy, 0,Point());
	}
	
	cvtColor(drawing1, drawing1Gray, CV_RGB2GRAY);
	threshold(drawing1Gray, drawing1Thresh, 120, 255,0);		
	findContours(drawing1Thresh,contours,hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	//cout<<contours.size()<<endl;
	
	Mat drawing2 = Mat::zeros(patternGray.size(),CV_8UC3);
	
	vector<Moments> mu(contours.size());
	vector<Point2f> mc(contours.size());

	vector<kontur> tab;
	//kontur tab[contours.size()];
	String name = "Window #";
	char c = '2';
	String windowName;
	//cout<<contours.size()<<endl;
	for (int a =0; a<contours.size(); a++){
		kontur asd;
		Scalar color = Scalar(0,255,0);
		//drawContours(drawing2, contours,i,color,2,8,hierarchy, 0,Point());
		mu[a] = moments(contours[a],false);
		mc[a] = Point2f(mu[a].m10/mu[a].m00, mu[a].m01/mu[a].m00);
		
		windowName = name + c;
		c++;

		asd.centroidX = mc[a].x;
		asd.centroidY = mc[a].y;
		asd.area = contourArea(contours[a]);
		asd.LmostX=-1;
		asd.LmostY=-1;
		asd.RmostX=-1;
		asd.RmostY=-1;
		asd.TmostX=-1;
		asd.TmostY=-1;
		asd.BmostX=-1;
		asd.BmostY=-1;
		if (asd.area > 10000){
			namedWindow(windowName, CV_WINDOW_AUTOSIZE);
			Mat tempWindow(pattern.size(),CV_8UC3, Scalar(0));
			drawContours(tempWindow, contours,a,Scalar(0, 255, 0),2,8,hierarchy, 0,Point());
			uchar* p = tempWindow.data;
			tab.push_back(asd);
			for (int i = 0; i<tempWindow.rows; i++){
				for (int j = 0; j<tempWindow.cols; j++){
					p = tempWindow.data + tempWindow.cols*i+j;
					Vec3b zxc = tempWindow.at<Vec3b>(i,j);
					if (zxc.val[1]==255){
						if (asd.TmostY == -1)
							asd.TmostY = i;
						if (asd.TmostX == -1)
							asd.TmostX = j;
						asd.BmostX = j;
						asd.BmostY = i;
					}
				}
			}

			for (int i = 0; i<tempWindow.cols; i++){
				for (int j =0; j<tempWindow.rows; j++){
					p = tempWindow.data + tempWindow.cols*j+i;
					Vec3b zxc = tempWindow.at<Vec3b>(j,i);
					if (zxc.val[1]==255){
						if (asd.LmostX == -1)
							asd.LmostX = i;
						if (asd.LmostY == -1)
							asd.LmostY = j;
						asd.RmostX = i;
						asd.RmostY = j;
					}
				}
			}

			circle( tempWindow, Point(asd.BmostX, asd.BmostY), 5, Scalar(200,200,200), 3, 8, 0 );
			circle( tempWindow, Point(asd.TmostX, asd.TmostY), 5, Scalar(200,200,200), 3, 8, 0 );
			circle( tempWindow, Point(asd.RmostX, asd.RmostY), 5, Scalar(200,200,200), 3, 8, 0 );
			circle( tempWindow, Point(asd.LmostX, asd.LmostY), 5, Scalar(200,200,200), 3, 8, 0 );
			circle( tempWindow, Point(asd.centroidX, asd.centroidY), 5, Scalar(200, 200, 200), 3, 8, 0);
			Point2f pt = Point (asd.LmostX, asd.LmostY);
			asd.corners.push_back(pt);
			pt = Point (asd.RmostX, asd.RmostY);
			asd.corners.push_back(pt);
			pt = Point (asd.TmostX, asd.TmostY);
			asd.corners.push_back(pt);
			pt = Point (asd.BmostX, asd.BmostY);
			asd.corners.push_back(pt);
			imshow(windowName, tempWindow);	

			cout<<asd.area<<endl;

		}


	}
	imshow("Window", patternThresh);


	waitKey(0);
	return 0;
}