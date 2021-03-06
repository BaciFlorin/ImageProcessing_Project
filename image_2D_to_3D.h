#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat changeDirection(Mat image, Mat image_seg);
Mat transformation_3D(Mat imageL, Mat imageR);
int get_nr_of_pixels(Mat image_seg);