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
};

Mat pattern = imread("/home/kuba/Documents/vision/andrzejeVision/znaczki.png", CV_LOAD_IMAGE_COLOR);
Mat patternGray = imread("/home/kuba/Documents/vision/andrzejeVision/znaczki.png", CV_LOAD_IMAGE_GRAYSCALE);
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
	cout<<contours.size()<<endl;
	
	Mat drawing2 = Mat::zeros(patternGray.size(),CV_8UC3);
	
	vector<Moments> mu(contours.size());
	vector<Point2f> mc(contours.size());
	
	kontur tab[contours.size()];
	String name = "okienko";
	char c = '2';
	String windowName;

	for (int a =0; a<contours.size(); a++){
		Scalar color = Scalar(0,255,0);
		//drawContours(drawing2, contours,i,color,2,8,hierarchy, 0,Point());
		mu[a] = moments(contours[a],false);
		mc[a] = Point2f(mu[a].m10/mu[a].m00, mu[a].m01/mu[a].m00);

		windowName = name + c;
		c++;
		namedWindow(windowName, CV_WINDOW_AUTOSIZE);
		Mat tempWindow(pattern.size(),CV_8UC3, Scalar(0));
		drawContours(tempWindow, contours,a,Scalar(0, 255, 0),2,8,hierarchy, 0,Point());
		uchar* p = tempWindow.data;
		tab[a].centroidX = mc[a].x;
		tab[a].centroidY = mc[a].y;
		tab[a].LmostX=-1;
		tab[a].LmostY=-1;
		tab[a].RmostX=-1;
		tab[a].RmostY=-1;
		tab[a].TmostX=-1;
		tab[a].TmostY=-1;
		tab[a].BmostX=-1;
		tab[a].BmostY=-1;
	
		for (int i = 0; i<tempWindow.rows; i++){
			for (int j = 0; j<tempWindow.cols; j++){
				p = tempWindow.data + tempWindow.cols*i+j;
				Vec3b zxc = tempWindow.at<Vec3b>(i,j);
				if (zxc.val[1]==255){
					if (tab[a].TmostY == -1)
						tab[a].TmostY = i;
					if (tab[a].TmostX == -1)
						tab[a].TmostX = j;
					tab[a].BmostX = j;
					tab[a].BmostY = i;
				}
			}
		}

		for (int i = 0; i<tempWindow.cols; i++){
			for (int j =0; j<tempWindow.rows; j++){
				p = tempWindow.data + tempWindow.cols*j+i;
				Vec3b zxc = tempWindow.at<Vec3b>(j,i);
				if (zxc.val[1]==255){
					if (tab[a].LmostX == -1)
						tab[a].LmostX = i;
					if (tab[a].LmostY == -1)
						tab[a].LmostY = j;
					tab[a].RmostX = i;
					tab[a].RmostY = j;
				}
			}
		}
			
		circle( tempWindow, Point(tab[a].BmostX, tab[a].BmostY), 5, Scalar(200,200,200), 3, 8, 0 );
		circle( tempWindow, Point(tab[a].TmostX, tab[a].TmostY), 5, Scalar(200,200,200), 3, 8, 0 );
		circle( tempWindow, Point(tab[a].RmostX, tab[a].RmostY), 5, Scalar(200,200,200), 3, 8, 0 );
		circle( tempWindow, Point(tab[a].LmostX, tab[a].LmostY), 5, Scalar(200,200,200), 3, 8, 0 );
		circle( tempWindow, Point(tab[a].centroidX, tab[a].centroidY), 5, Scalar(200, 200, 200), 3, 8, 0);
		
		imshow(windowName, tempWindow);	
	}
	//imshow("Window", tempWindow);


	waitKey(0);
	return 0;
}