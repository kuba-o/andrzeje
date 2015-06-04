#include "cv.h"
#include "highgui.h"

using namespace cv;
using namespace std;

int main() {

    // read in the apple (change path to the file)
    Mat img0 = imread("/home/kuba/Documents/vision/andrzejeVision/apple.jpg", 1);

    Mat img1;
    cvtColor(img0, img1, CV_RGB2GRAY);

    // apply your filter
    Canny(img1, img1, 100, 200);

    // find the contours
    vector< vector<Point> > contours;
    findContours(img1, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // you could also reuse img1 here
    Mat mask = Mat::zeros(img1.rows, img1.cols, CV_8UC1);

    // CV_FILLED fills the connected components                  @
    drawContours(mask, contours, -1, Scalar(255), CV_FILLED);

    // let's create a new image now
    Mat crop(img0.rows, img0.cols, CV_8UC3);

    // and copy the magic apple
    img0.copyTo(crop, mask);

    // normalize so imwrite(...)/imshow(...) shows the mask correctly!
    normalize(mask.clone(), mask, 0.0, 255.0, CV_MINMAX, CV_8UC1);

    imshow("original", img0);
    imshow("mask", mask);
    imshow("canny", img1);
    imshow("cropped", crop);

    waitKey();
    return 0;
}