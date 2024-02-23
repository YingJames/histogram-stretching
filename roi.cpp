#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "utils.hpp"
#include "roi.hpp"

using namespace std;
using namespace cv;

Mat makeGreyRoiImage(Mat src, Roi roi)
{
    Mat roiImage = Mat(roi.size, roi.size, src.type());
    for (int y = roi.y; y < roi.y + roi.size && y < src.rows; ++y)
    {
        for (int x = roi.x; x < roi.x + roi.size && x < src.cols; ++x)
        {
            int pixel_value = static_cast<int>(src.at<uchar>(y, x));
            set_pixel(src, roiImage, y - roi.y, x - roi.x, pixel_value);
        }
    }
    return roiImage;
}

Mat makeColorRoiImage(Mat src, Roi roi)
{
    Mat roiImage = Mat(roi.size, roi.size, src.type());
    for (int y = roi.y; y < roi.y + roi.size && y < src.rows; ++y)
    {
        for (int x = roi.x; x < roi.x + roi.size && x < src.cols; ++x)
        {
            Vec3b pixelValue = getColorPixel(src, y, x);
            setColorPixel(roiImage, y - roi.y, x - roi.x, pixelValue);
        }
    }
    return roiImage;
}

void mult_Croi(Mat src, Mat tgt, Roi roi, int multiplier)
{
    // get bottom right corner of roi
    int xEnd = roi.x + roi.size;
    int yEnd = roi.y + roi.size;

    for (int y = roi.y; y < yEnd && y < src.rows; ++y)
    {
        for (int x = roi.x; x < xEnd && x < src.cols; ++x)
        {
            Vec3b pixelValue = getColorPixel(src, y, x);
            float B = pixelValue[0];
            float G = pixelValue[1];
            float R = pixelValue[2];

            float B1 = B * multiplier;
            float G1 = G * multiplier;
            float R1 = R * multiplier;

            B1 = check_value(B1);
            G1 = check_value(G1);
            R1 = check_value(R1);

            Vec3b newPixelValue = Vec3b(B1, G1, R1);
            tgt.at<Vec3b>(y, x) = newPixelValue;
        }
    }
}

void add_Croi(Mat src, Mat tgt, Roi roi, int addend)
{
    // get bottom right corner of roi
    int xEnd = roi.x + roi.size;
    int yEnd = roi.y + roi.size;

    for (int y = roi.y; y < yEnd && y < src.rows; ++y)
    {
        for (int x = roi.x; x < xEnd && x < src.cols; ++x)
        {
            Vec3b pixelValue = getColorPixel(src, y, x);
            float B = pixelValue[0];
            float G = pixelValue[1];
            float R = pixelValue[2];

            float B1 = B + addend;
            float G1 = G + addend;
            float R1 = R + addend;

            B1 = check_value(B1);
            G1 = check_value(G1);
            R1 = check_value(R1);

            Vec3b newPixelValue = Vec3b(B1, G1, R1);
            tgt.at<Vec3b>(y, x) = newPixelValue;
        }
    }
}

void scale_Groi(Mat src, Mat tgt, Roi roi, float scaleFactor)
{
    cv::Mat resizedImage((int)((float)src.cols * scaleFactor), (int)((float)src.cols * scaleFactor), src.type());

    // get bottom right corner of roi
    int xEnd = roi.x + roi.size;
    int yEnd = roi.y + roi.size;

    scale_Grey(src, resizedImage, scaleFactor);

    // copy the scaled image to the target image and keep same size
    for (int y = roi.y; y < roi.y + yEnd && y < src.rows; ++y)
    {
        for (int x = roi.x; x < roi.x + xEnd && x < src.cols; ++x)
        {
            int pixel_value = get_pixel(resizedImage, y, x);
            set_pixel(resizedImage, tgt, y, x, pixel_value);
        }
    }
}

void add_Groi(Mat src, Mat tgt, Roi roi, int addendValue)
{
    // get bottom right corner of roi
    int xEnd = roi.x + roi.size;
    int yEnd = roi.y + roi.size;

    for (int y = roi.y; y < yEnd && y < src.rows; ++y)
    {
        for (int x = roi.x; x < xEnd && x < src.cols; ++x)
        {
            int pixel_value = static_cast<int>(src.at<uchar>(y, x)) + addendValue;
            // Ensure the pixel value stays within the [0, 255] range
            pixel_value = std::min(255, std::max(0, pixel_value));
            // tgt.at<uchar>(y, x) = static_cast<uchar>(pixel_value);
            set_pixel(src, tgt, y, x, pixel_value);
        }
    }
}

void binarize_Groi(Mat src, Mat tgt, Roi roi, int pixel)
{
    // get bottom right corner of roi
    int xEnd = roi.x + roi.size;
    int yEnd = roi.y + roi.size;

    for (int y = roi.y; y < yEnd && y < src.rows; ++y)
    {
        for (int x = roi.x; x < xEnd && x < src.cols; ++x)
        {
            int pixel_value = static_cast<int>(src.at<uchar>(y, x));
            // Ensure the pixel value stays within the [0, 255] range
            if (pixel_value > pixel)
            {
                tgt.at<uchar>(y, x) = static_cast<uchar>(255);
            }
            else
            {
                tgt.at<uchar>(y, x) = static_cast<uchar>(0);
            }
        }
    }
}

void threshold_Groi(Mat src, Mat tgt, Roi roi, int T, int V)
{
    // get bottom right corner of roi
    int xEnd = roi.x + roi.size;
    int yEnd = roi.y + roi.size;

    for (int y = roi.y; y < yEnd && y < src.rows; ++y)
    {
        for (int x = roi.x; x < xEnd && x < src.cols; ++x)
        {
            int pixel_value = static_cast<int>(src.at<uchar>(y, x));
            // Decrease the pixel value by V if it's below T
            if (pixel_value < T)
            {
                pixel_value -= V;
                // Ensure the pixel value doesn't go below 0
                pixel_value = std::max(0, pixel_value);
            }
            set_pixel(src, tgt, y, x, pixel_value);
        }
    }
}
