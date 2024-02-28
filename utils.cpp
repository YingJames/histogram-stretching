#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "utils.hpp"

using namespace std;
using namespace cv;

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

void convert_pgm(string image_name, string output_name)
{
    cv::Mat png_image = cv::imread(image_name, cv::IMREAD_GRAYSCALE);

    // Check if the image was loaded successfully
    if (!png_image.empty())
    {
        // Save the image in PPM format
        cv::imwrite(output_name, png_image);
        std::cout << "PNG image converted to PGM successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to load the PNG image." << std::endl;
    }
}

int check_value(int value)
{
    return std::min(255, std::max(0, value));
}

int get_pixel(Mat src, int y, int x)
{
    int pixel_value = static_cast<int>(src.at<uchar>(y, x));
    // Ensure the pixel value stays within the [0, 255] range
    pixel_value = std::min(255, std::max(0, pixel_value));
    return pixel_value;
}

void set_pixel(Mat src, Mat tgt, int y, int x, int pixel_value)
{
    tgt.at<uchar>(y, x) = static_cast<uchar>(pixel_value);
}

Vec3b getColorPixel(Mat src, int y, int x)
{
    Vec3b pixel_value = src.at<cv::Vec3b>(y, x);
    // Ensure the pixel value stays within the [0, 255] range
    // pixel_value. = std::min(255, std::max(0, pixel_value));
    pixel_value[0] = std::min(255, std::max(0, static_cast<int>(pixel_value[0])));
    pixel_value[1] = std::min(255, std::max(0, static_cast<int>(pixel_value[1])));
    pixel_value[2] = std::min(255, std::max(0, static_cast<int>(pixel_value[2])));
    return pixel_value;
}

void setColorPixel(Mat tgt, int y, int x, Vec3b pixelValue)
{
    tgt.at<cv::Vec3b>(y, x) = pixelValue;
}

void save_image(Mat tgt, string output_name)
{
    // Save the image in PPM format
    cv::imwrite(output_name, tgt);
    std::cout << "Image " << output_name << " saved successfully" << std::endl;
    if (tgt.empty())
    {
        cout << "Saving an empty image as " << output_name << endl;
    }
}