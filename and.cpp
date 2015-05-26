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

Mat pattern = imread("/home/kuba/Documents/andrzejeVision/k1.jpg", CV_LOAD_IMAGE_COLOR);
//Mat pattern = imread("/home/kuba/Documents/andrzejeVision/template.png", CV_LOAD_IMAGE_COLOR);
//Mat pattern = imread("/home/kuba/Documents/andrzejeVision/template2.png", CV_LOAD_IMAGE_COLOR);
int checkX, checkY;
int howManyTotal=0;
int howMany = 0;

class marker {
public:
	float tempDistX;
	float tempDistY;
	int tabX[4];
	int tabY[4];
	int shortest;
	int middle;
	int longest;
	float avEdge;
	float distances[3];
	int colors[8][3];
	int values[8];
	int codedValue=0;

	void calcDistances(){
		for (int i = 1; i < 4; i++){
			distances[i-1] = sqrt(pow((tabX[0]-tabX[i]), 2.0) + pow((tabY[0]-tabY[i]), 2.0));
			//cout<<distances[i-1]<<" wynik"<<i-1<<endl;
		}
		shortest = 0;
		for (int i=0; i<3; i++){
			if (distances[i] < distances[shortest])
				shortest = i;
		}
		longest = shortest;
		for (int i=0; i<3; i++){
			if (distances[i] > distances[longest])
				longest = i;
		}
		middle = 3 - longest - shortest;
		
		tempDistX = tabX[middle+1] - tabX[0];
		tempDistY = tabY[shortest+1] - tabY[0];

		//cout<<"MIDDLE: "<<distances[middle]<<endl;
		
	}

	void getCentralColors(){
		float h = tabY[middle+1] - tabY[0];
		float angle = sin(h/distances[middle])*180.0/3.14;
		int tempID = 0;
		//cout<<tabX[0]<<"TO TY"<<endl;
		//cout<<tabY[0]<<"TO TY"<<endl;
		//cout<<tabY[0]<<endl;
		//cout<<tempDistY/4<<endl;
		//Point startPoint = Point (tabX[0]+tempDistX/8, tabY[0]+tempDistY/4);
		//circle(pattern, startPoint, 30, Scalar(0, 255, 255), -1, 8, 0);

		for (int j =0; j<2; j++){
			for (int i=0; i<4; i++){
				Point tempPoint = Point(tabX[0]+tempDistX/8 + i*tempDistX/4, tabY[0]+tempDistY/4 + j*tempDistY/2);
				
				Vec3b p = pattern.at<Vec3b>(tempPoint);
				colors[tempID][0] = int(p.val[0]);
				colors[tempID][1] = int(p.val[1]);
				colors[tempID][2] = int(p.val[2]);
				circle( pattern, tempPoint, 3, Scalar(0,255,0), -1, 8, 0 );
				tempID++;
			}
		}		
	}

	void countValue(){
		for (int i =0; i<8; i++){
			if (colors[i][1]==255)
				values[i] = 1;
			else
				values[i] = 0;
		}

		for (int i =0; i<8; i++){
			codedValue += values[i] * pow(2, 7-i);
			cout<<values[i]<<endl;
		}
		cout<<"WARTOSC TO: "<<codedValue<<endl;
	}
};

int main(){
	int indeks = 0;
	Mat test;
	vector<Vec3f> circles;
	Canny(pattern, test, 50, 200, 3 );
	HoughCircles( test, circles, CV_HOUGH_GRADIENT, 1,50, 200, 5, 5, 30 );

	for( size_t i = 0; i < circles.size(); i++ ){ 
    	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		checkX = cvRound(circles[i][0]);
     	checkY = cvRound(circles[i][1]);

		Vec3b p = pattern.at<Vec3b>(center);

		if ((int(p.val[2]) > 200) && int(p.val[1] == 0)){
			howManyTotal++;
		}
	}
	cout<<"TOTAL: "<<howManyTotal<<endl;
	marker tab[howManyTotal/4];
	
	for( size_t i = 0; i < circles.size(); i++ ){
    	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		checkX = cvRound(circles[i][0]);
     	checkY = cvRound(circles[i][1]);

		Vec3b p = pattern.at<Vec3b>(center);

		if ((int(p.val[2]) > 120) && int(p.val[1] < 50) && int(p.val[1] < 50)){

    		int radius = cvRound(circles[i][2]);
      		// circle center
    		circle( pattern, center, 3, Scalar(0,255,0), -1, 8, 0 );
      		// circle outline
      		circle( pattern, center, radius, Scalar(0,0,255), 3, 8, 0 );

      		howMany++;
      		tab[indeks/4].tabX[indeks%4] = checkX;
      		//cout<<checkX<<endl;
      		//cout<<checkY<<endl;
      		tab[indeks/4].tabY[indeks%4] = checkY;
      		indeks++;
  		}
	}
	//cout<<howManyTotal<<endl;
	tab[0].calcDistances();
	tab[0].getCentralColors();
	//tab[0].countValue();

	namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
	imshow("pattern",pattern);
	waitKey(0);
    return 0;
}