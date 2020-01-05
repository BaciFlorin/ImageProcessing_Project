#include"image_2D_to_3D.h"

Mat changeDirection(Mat image, Mat image_seg, int NrPixels)
{
	Mat result = image.clone();
	uint w = image.cols, h = image.rows;
	bool first = true;
	int first_element = 0;
	int last_element = 0;
	Vec3b fillValue;
	for (uint y = 0; y < h; y++)
	{
		first = true;
		for (uint x = 0; x < w; x++)
		{
			if (image_seg.at<uchar>(y,x) == 0)
			{
				if (first)
				{
					// afla indicele primului element pentru a ne da seama cati pixeli vor copia o valoare
					fillValue = image.at<Vec3b>(y, x - 2);
					first_element = x;
					first = false;
				}
				else
				{
					//do nothing
				}
				if ((x - first_element) < (uint)NrPixels)
				{
					//verificam daca nu cumva pixelul actual nu este cumva unul ce trebuie pus cu 0
					result.at<Vec3b>(y, x) = fillValue;
				}
				else
				{
					if (x + NrPixels < w)
					{
						result.at<Vec3b>(y, x + NrPixels) = image.at<Vec3b>(y, x);
						last_element = x + NrPixels;
					}
				}
			}
			else
			{
				
				first = true;
				if (x > (uint)last_element)
				{
					//nu se permite scrierea valorilor decat dupa ce se trece de partea unde se afla obiectul mutat
					result.at<Vec3b>(y, x) = image.at<Vec3b>(y, x);
				}
			}
		}
	}
	return result;
}

Mat transformation_3D(Mat imageL, Mat imageR)
{
	Mat result = imageL.clone();
	uint w = imageL.cols, h = imageL.rows;
	double m[2][9] = {
		{0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{0.299, 0.587, 0.114, 0, 0, 0, 0, 0, 0 }
	};
	for (uint y = 0; y < h; y++)
	{
		for (uint x = 0; x < 3 * w; x += 3)
		{
			uchar r1 = imageL.data[y*w * 3 + x + 2], b1 = imageL.data[y*w * 3 + x], g1 = imageL.data[y*w * 3 + x + 1];
			uchar r2 = imageR.data[y*w * 3 + x + 2], b2 = imageR.data[y*w * 3 + x], g2 = imageR.data[y*w * 3 + x + 1];
			result.data[y*w * 3 + x + 2] = (uchar)(g1 * m[0][1] + r1 * m[0][0] + b1 * m[0][2] + r2 * m[1][0] + g2 * m[1][1] + b2 * m[1][2]);
			result.data[y*w * 3 + x + 1] = (uchar)(g1 * m[0][4] + r1 * m[0][3] + b1 * m[0][5] + r2 * m[1][3] + g2 * m[1][4] + b2 * m[1][5]);
			result.data[y*w * 3 + x] = (uchar)(g1 * m[0][7] + r1 * m[0][6] + b1 * m[0][8] + r2 * m[1][6] + g2 * m[1][7] + b2 * m[1][8]);
		}
	}
	return result;
}