#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

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

void handleColorRoi(vector<string> parameter)
{
    Mat src = imread(parameter[0], cv::IMREAD_COLOR);
    Mat tgt = Mat(src.size(), src.type());
    src.copyTo(tgt);

    string functionName = parameter[2];
    if (functionName == "colorRoi")
    {
        Roi roi;
        roi.x = stoi(parameter[3]);
        roi.y = stoi(parameter[4]);
        roi.size = stoi(parameter[5]);

        tgt = makeColorRoiImage(src, roi);
        save_image(tgt, parameter[1]);
    }
}

void handleRoiImage(Mat src, Mat &tgt, vector<string> parameter)
{
    if (parameter[2] == "greyRoi")
    {
        Roi roi;
        roi.x = stoi(parameter[3]);
        roi.y = stoi(parameter[4]);
        roi.size = stoi(parameter[5]);

        tgt = makeGreyRoiImage(src, roi);
        save_image(tgt, parameter[1]);
    }
}