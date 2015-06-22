#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream>
#include <cmath>

using namespace cv;
using namespace std;
Mat pattern = imread("/home/kuba/Documents/vision/andrzejeVision/testel.jpg", CV_LOAD_IMAGE_COLOR);

float height = pattern.rows;
float width = pattern.cols;
float h4 = height/4;
float w4 = width/4;

int main(){
	Point characteristicPoints[8];
	Point valuesPoints[8];
	int pointValues[8][3];
	int segmentValues[8];
	
	int whichSegment;
	Vec3b point;
	int codedValue = 0;

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

	for (int i=0; i<8; i++){
		point = pattern.at<Vec3b>(characteristicPoints[i]);
		if (int(point.val[2]) > 100 && int(point.val[1])<50)
			whichSegment = i;

		//circle( pattern, Point(characteristicPoints[(i+whichSegment)%8].x, characteristicPoints[(i+whichSegment)%8].y), 5, Scalar(0,255,0), 3, 8, 0 );
	}

	for (int i=0; i<8; i++){
		valuesPoints[i] = characteristicPoints[(i+whichSegment)%8];
		point = pattern.at<Vec3b>(valuesPoints[i]);
	}

	for (int i=0; i<8; i++){
		point = pattern.at<Vec3b>(valuesPoints[i]);
		pointValues[i][0] = int(point.val[0]);
		pointValues[i][1] = int(point.val[1]);
		pointValues[i][2] = int(point.val[2]);
	}
	
	//check color/value of the center
	point = pattern.at<Vec3b>(width/2, height/2);
	if (int(point.val[1] > 150))
		codedValue +=1;

	for (int i = 1; i<8; i++){
		cout<<"WART"<<pointValues[i][0]<<endl;

		if (pointValues[i][0]>120){

			segmentValues[i]=1;
			codedValue += pow(2, i);
		}
		else{
			segmentValues[i]=0;

		}
	}
	
	for (int i =1; i<8; i++)
		cout<<segmentValues[i]<<endl;
	
	cout<<"ee"<<endl;
	cout<<endl<<codedValue<<endl;
	
	imshow("pattern", pattern);

	waitKey(0);
	return 0;
}