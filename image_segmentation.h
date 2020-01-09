#pragma once
#include <stack>
#include <cassert>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int Threshold = 200;
const uchar max_region_num = 100;
const double min_region_area_factor = 0.01;
const Point PointShift2D[8] =
{
    Point(1, 0),
    Point(1, -1),
    Point(0, -1),
    Point(-1, -1),
    Point(-1, 0),
    Point(-1, 1),
    Point(0, 1),
    Point(1, 1)
};


int readImage(String path,Mat &image);
void grow(cv::Mat& src, cv::Mat& dest, cv::Mat& mask, cv::Point seed, int threshold);
Mat regionGrowing(Mat src);
