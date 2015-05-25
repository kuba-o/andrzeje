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

int checkX, checkY;
int howManyTotal=0;
int howMany = 0;
class marker {
public:
	int tabX[4];
	int tabY[4];
	int shortest;
	int middle;
	int longest;
	float distances[3];

	
	void calcDistances(){
		for (int i = 1; i < 4; i++){
			distances[i] = sqrt(pow((tabX[0]-tabX[i]), 2.0) + pow((tabY[0]-tabY[i]), 2.0));
			cout<<distances[i]<<" wynik"<<endl;
		}
	}
};
int main(){
	int indeks = 0;
	Mat pattern = imread("/home/kuba/Documents/andrzejeVision/template.png", CV_LOAD_IMAGE_COLOR);
	Mat patternGray = imread("/home/kuba/Documents/andrzejeVision/template.png", CV_LOAD_IMAGE_GRAYSCALE);
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

	marker tab[howManyTotal/4];
	
	for( size_t i = 0; i < circles.size(); i++ ){
    	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		checkX = cvRound(circles[i][0]);
     	checkY = cvRound(circles[i][1]);

		Vec3b p = pattern.at<Vec3b>(center);

		if ((int(p.val[2]) > 200) && int(p.val[1] == 0)){

    		int radius = cvRound(circles[i][2]);
      		// circle center
    		circle( pattern, center, 3, Scalar(0,255,0), -1, 8, 0 );
      		// circle outline
      		circle( pattern, center, radius, Scalar(0,0,255), 3, 8, 0 );
      		cout<<"radius: "<<radius<<endl;
      		cout<<"x: :"<<checkX<<endl;
      		cout<<"y :"<<checkY<<endl<<endl;
      		howMany++;
      		cout<<"tu1"<<endl;
      		tab[indeks/4].tabX[indeks%4] = checkX;
      		tab[indeks/4].tabY[indeks%4] = checkY;
      		cout<<"Tu INDEKS: "<<indeks/4<<endl;
      		cout<<"tu2"<<endl;
      		cout<<"indeks: "<<indeks<<endl;
      		indeks++;
  		}
	}


	cout<<"a tu?"<<endl;
	tab[0].calcDistances();
	
	/*
	int a, b;
	cout<<"tab[0].tabx[0]: "<<tab[0].tabX[0];
	a = tab[0].tabX[0]-tab[0].tabX[1];
	b = tab[0].tabY[0] - tab[0].tabY[1];
	cout<<"tab[0].tabx[1]: "<<tab[0].tabX[1];
	cout<<endl<<"a: "<<tab[0].tabX[0]<<endl;
	cout<<"b :"<<b<<endl;

	cout<<endl<<sqrt(pow(a, 2.0) + pow(b, 2.0))<<endl;
	cout<<endl<<endl<<a<<endl;
	*/
	for (int i =0; i<howMany/4; i++){

	}
	namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
	imshow("pattern",pattern);
	waitKey(0);
    return 0;
}