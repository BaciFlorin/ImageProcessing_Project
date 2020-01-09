#include"image_segmentation.h"

int readImage(String path,Mat &image)
{
    image = imread(path, IMREAD_COLOR);
    if (!image.data)
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    return 1;
}


void grow(Mat& src, Mat& dest, Mat& mask, Point seed, int threshold)
{

    stack<Point> point_stack;
    point_stack.push(seed);

    while (!point_stack.empty()) {
        Point center = point_stack.top();
        mask.at<uchar>(center) = 1;
        point_stack.pop();

        for (int i = 0; i < 8; ++i) {
            Point estimating_point = center + PointShift2D[i];
            if (estimating_point.x < 0
                || estimating_point.x > src.cols - 1
                || estimating_point.y < 0
                || estimating_point.y > src.rows - 1)
            {
                continue;
            }
            else
            {
                int delta = int(pow(src.at<Vec3b>(center)[0] - src.at<Vec3b>(estimating_point)[0], 2)
                    + pow(src.at<Vec3b>(center)[1] - src.at<Vec3b>(estimating_point)[1], 2)
                    + pow(src.at<Vec3b>(center)[2] - src.at<Vec3b>(estimating_point)[2], 2));
            if (dest.at<uchar>(estimating_point) == 0 && mask.at<uchar>(estimating_point) == 0 && delta < threshold)
            {
                    mask.at<uchar>(estimating_point) = 1;
                    point_stack.push(estimating_point);
                }
            }
        }
    }
}

Mat regionGrowing(Mat src)
{
    Mat returnValue;
    assert(!src.empty());
    //used just for test
    /*if (src.cols > 500 || src.rows > 500)
    {
        resize(src, src, Size(0, 0), 0.5, 0.5); // resize for speed
    }*/
    //imshow("src", src);


    //ready for seed grow
    int min_region_area = int(min_region_area_factor * src.cols * src.rows);  // small region will be ignored

    // "dest" records all regions using different padding number
    // 0 - undetermined, 255 - ignored, other number - determined
    uchar padding = 1;  // use which number to pad in "dest"
    Mat dest = Mat::zeros(src.rows, src.cols, CV_8UC1);

    // "mask" records current region, always use "1" for padding
    Mat mask = Mat::zeros(src.rows, src.cols, CV_8UC1);

    // traversal the whole image, apply "seed grow" in undetermined pixels
    for (int x = 0; x < src.cols; ++x)
    {
        for (int y = 0; y < src.rows; ++y)
        {
            if (dest.at<uchar>(Point(x, y)) == 0)
            {
                grow(src, dest, mask, Point(x, y), Threshold);

                int mask_area = (int)sum(mask).val[0];  // calculate area of the region that we get in "seed grow"
                if (mask_area > min_region_area)
                {
                    dest = dest + mask * padding;   // record new region to "dest"
                    return mask * 255;
                    if (++padding > max_region_num)
                    {
                        printf("run out of max_region_num...");
                    }
                }
                else
                {
                    dest = dest + mask * 255;   // record as "ignored"
                }
                mask = mask - mask;     // zero mask, ready for next "seed grow"
            }
        }
    }
}
