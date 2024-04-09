#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("C:/Users/User/Desktop/text.png");

    if (image.empty())
    {
        cout << "Error" << endl;
        return -1;
    }

    imshow("Original Image", image);
    waitKey(0);

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat gaussImage;
    GaussianBlur(grayImage, gaussImage, Size(3, 3), 0);
    Mat contourImage;
    Canny(grayImage, contourImage, 50, 200);
    vector<vector<Point> > finalImage;
    vector<Vec4i> hierarchy;
    findContours(contourImage, finalImage, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Scalar color = Scalar(0, 0, 255);
    Mat newImage = Mat::zeros(image.size(), CV_8UC3);
    for (size_t i = 0; i < finalImage.size(); i++)
    {
        drawContours(newImage, finalImage, i, color, 2, LINE_8, hierarchy, 0);
    }
    imshow("Final Image", newImage);
    waitKey(0);



    return 0;
}
