#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "rotateFlip.hpp"

using namespace std;
using namespace cv;

void rotate(Mat src, Mat tgt, int degree)
{
    if (degree % 90 != 0)
    {
        throw std::invalid_argument("Angles must be a multiple of 90");
    }

    // if angle is negative
    if (degree < 0)
        degree = 360 + degree;

    // amount of iterations to rotate the image
    int times = (degree / 90) % 4;

    // this does all the rotation
    for (int t = 0; t < times; t++)
    {
        int imageSize = src.rows;
        for (int i = 0; i < imageSize; i++)
        {
            for (int j = 0; j < imageSize; j++)
            {
                tgt.at<uchar>(i, j) = src.at<uchar>(j, i);
            }
        }
        for (int i = 0; i < imageSize; i++)
        {
            for (int j = 0; j < imageSize / 2; j++)
            {
                std::swap(tgt.at<uchar>(i, j), tgt.at<uchar>(i, imageSize - j - 1));
            }
        }
        tgt.copyTo(src); // copy the target matrix back to source for next rotation
    }
}

void rotateColor(Mat src, Mat tgt, int degree)
{
    if (degree % 90 != 0)
    {
        throw std::invalid_argument("Angles must be a multiple of 90");
    }

    // if angle is negative
    if (degree < 0)
        degree = 360 + degree;

    // amount of iterations to rotate the image
    int times = (degree / 90) % 4;

    // this does all the rotation
    for (int t = 0; t < times; t++)
    {
        int imageSize = src.rows;
        for (int i = 0; i < imageSize; i++)
        {
            for (int j = 0; j < imageSize; j++)
            {
                tgt.at<Vec3b>(i, j) = src.at<Vec3b>(j, i);
            }
        }
        for (int i = 0; i < imageSize; i++)
        {
            for (int j = 0; j < imageSize / 2; j++)
            {
                std::swap(tgt.at<Vec3b>(i, j), tgt.at<Vec3b>(i, imageSize - j - 1));
            }
        }
        tgt.copyTo(src); // copy the target matrix back to source for next rotation
    }
}

void flipImage(Mat src, Mat tgt)
{
    int imageSize = src.rows;
    for (int y = 0; y < src.rows; ++y)
    {
        const uchar *srcRowStart = src.ptr<uchar>(y);
        uchar *dstRowStart = tgt.ptr<uchar>(y);

        // Copy each row in reverse order to the destination
        for (int x = 0; x < src.cols; ++x)
            dstRowStart[x] = srcRowStart[(src.cols - 1) - x];
    }
}
void flipColorImage(Mat src, Mat tgt)
{
    for (int y = 0; y < src.rows; ++y)
    {
        const Vec3b *srcRowStart = src.ptr<Vec3b>(y);
        Vec3b *dstRowStart = tgt.ptr<Vec3b>(y);

        // Copy each row in reverse order to the destination
        for (int x = 0; x < src.cols; ++x)
            dstRowStart[x] = srcRowStart[(src.cols - 1) - x];
    }
}