#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <sstream>

using namespace cv;
using namespace std;

String path = "/home/kuba/Documents/vision/andrzejeVision/testel.jpg";
Mat pattern = imread(path, CV_LOAD_IMAGE_COLOR);
Mat patternGray = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
Mat patternThresh;
int main() {
	vector<Vec3f> circles;
	threshold(patternGray, patternThresh, 120, 255,0);
	HoughCircles( patternThresh, circles, CV_HOUGH_GRADIENT, 1,10, 255, 10, pattern.cols/2-3, pattern.cols/2+3 );
	for( size_t i = 0; i < circles.size(); i++ ) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle( pattern, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}
	cout<<circles.size()<<endl;

	if (circles.size() > 0 && circles.size() < 5){
		cout<<"trolololoo"<<endl;
	}
	else
		cout<<"Nothing to calculate here"<<endl;
	imshow("YHY", pattern);
	waitKey(0);
	return 0;
}