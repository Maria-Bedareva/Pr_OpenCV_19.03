#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string figure(const vector<Point>& contour) {
    double epsilon = 0.04 * arcLength(contour, true);
    vector<Point> approx;
    approxPolyDP(contour, approx, epsilon, true);

    if (approx.size() == 3) {
        return "Triangle";
    }
    else if (approx.size() == 4) {
        Rect rect = cv::boundingRect(contour);
        double aspectRatio = static_cast<double>(rect.width) / rect.height;
        if (aspectRatio >= 0.95 && aspectRatio <= 1.05) {
            return "Rectangle";
        }
        else {
            return "Circle";
        }
    }
    else {
        return "Circle";
    }
}

int main() {
    Mat image = imread("C:/Users/User/Desktop/image.png"); 

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
    GaussianBlur(grayImage, gaussImage, Size(0, 0), 1);
    Mat contourImage;
    Canny(gaussImage, contourImage, 0, 0);
    vector<vector<Point> > contours;
    findContours(contourImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours.size(); ++i) {
        drawContours(image, contours, static_cast<int>(i), cv::Scalar(0, 255, 0), 2);
        string shape = figure(contours[i]);
        Moments mu = moments(contours[i]);
        Point center(mu.m10 / mu.m00, mu.m01 / mu.m00);
        putText(image, shape, center, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    }

    imshow("Final Image", image); 
    waitKey(0);

    return 0;
}
