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
Mat pattern = imread("/home/kuba/Documents/vision/andrzejeVision/przyklad4.jpg", CV_LOAD_IMAGE_COLOR);

float height = 240;
float width = 240;
float h4 = height/4;
float w4 = width/4;

int main(){
	Point characteristicPoints[8];
	Point valuesPoints[8];
	
	characteristicPoints[0].x = width/2;
	characteristicPoints[0].y = height/2-h4;
	
	characteristicPoints[1].x = width/2+w4;
	characteristicPoints[1].y = height/2-h4;

	characteristicPoints[2].x = width/2+w4;
	characteristicPoints[2].y = height/2;
	
	characteristicPoints[3].x = width/2+w4;
	characteristicPoints[3].y = height/2+h4;
	
	characteristicPoints[4].x = width/2;
	characteristicPoints[4].y = height/2+h4;
	
	characteristicPoints[5].x = width/2-w4;
	characteristicPoints[5].y = height/2+h4;
	
	characteristicPoints[6].x = width/2-w4;
	characteristicPoints[6].y = height/2;
	
	characteristicPoints[7].x = width/2-w4;
	characteristicPoints[7].y = height/2-h4;
	int whichSegment;
	imshow("MEH", pattern);
	for (int i=0; i<8; i++){
		Vec3b point = pattern.at<Vec3b>(characteristicPoints[i]);
		circle( pattern, characteristicPoints[i], 5, Scalar(0, 255, 0), 3, 8, 0);
		//cout<<int(point.val[2])<<endl;
		if (int(point.val[2]) > 200 && int(point.val[1])<100)
			whichSegment = i;
	}

	for (int i=0; i<8; i++){
		valuesPoints[i] = characteristicPoints[(i+whichSegment)%8];
	}

	for (int i =0; i<8; i++){
		Vec3b point = pattern.at<Vec3b>(valuesPoints[i]);
		//circle( pattern, characteristicPoints[i], 5, Scalar(0, 255, 0), 3, 8, 0);
		cout<<int(point.val[2])<<endl;
	}

	cout<<"SEGMENT: "<<whichSegment<<endl;


	waitKey(0);
	return 0;
}
	/*
	Vec3b center = pattern.at<Vec3b>(p);
	cout<<int(center.val[0])<<endl;
	cout<<int(center.val[1])<<endl;
	cout<<int(center.val[2])<<endl;
	*/