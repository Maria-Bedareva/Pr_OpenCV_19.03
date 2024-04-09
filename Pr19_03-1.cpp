#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("C:/Users/User/Desktop/suric.jpg");

    if (image.empty())
    {
        cout << "Error" << endl;
        return -1;
    }

    imshow("Original Image", image);
    waitKey(0);

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    imshow("Grey Image", grayImage);
    waitKey(0);

    Mat gaussImage;
    GaussianBlur(grayImage, gaussImage, Size(5, 5), 0);
    imshow("Gauss Image", gaussImage);
    waitKey(0);

    Mat contourImage;
    Canny(grayImage, contourImage, 50, 200);
    imshow("Contour Image", contourImage);
    waitKey(0);

    vector<vector<Point> > finalImage;
    vector<Vec4i> hierarchy;
    findContours(contourImage, finalImage, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < finalImage.size(); i++)
    {
        drawContours(image, finalImage, (int)i, Scalar(0, 0, 255), 1, LINE_8, hierarchy, 0);
    }
    imshow("Final Image", image);
    waitKey(0);



    return 0;
}