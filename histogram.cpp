#include <string>
#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

using namespace cv;

void histogramStretchRoi(Mat src, Mat tgt, Roi roi, float a, float b)
{
    // Mat result = Mat(roi.size, roi.size, src.type());
    vector<int> intensities;
    for (int i = roi.x; i < roi.x + roi.size && i < src.rows; i++)
    {
        for (int j = roi.y; j < roi.y + roi.size && i < src.cols; j++)
        {
            int val = src.at<uchar>(i-roi.x, j-roi.y);
            intensities.push_back(val);
        }
    }
    std::sort(intensities.begin(), intensities.end());
    int c = intensities[0] * 1.05;
    int d = intensities[intensities.size() - 1] * 0.95;

    for (int i = roi.x; i < roi.x + roi.size && i < src.rows; i++)
    {
        for (int j = roi.y; j < roi.y + roi.size && i < src.cols; j++)
        {
            int val = src.at<uchar>(i, j);

            // check if the values are within the range of the intensities

            // map the values to the new range
            if (val < c)
                tgt.at<uchar>(i, j) = a;
            else if (val > d)
                tgt.at<uchar>(i, j) = b;
            else
            {
                float fraction = (b-a) / (d-c);
                float stretchedVal = (val - c) * fraction + a;
                // uchar stretchedVal = (val - c) * ((b - a) / (d - c)) + (a);
                stretchedVal = check_value(stretchedVal);
                tgt.at<uchar>(i, j) = static_cast<uchar>(stretchedVal);
            }
        }
    }
    // return result;
}

void colorHistogramStretchRoi(Mat src, Mat tgt, Roi roi, std::string channel, float a, float b)
{
    
}


void handleHistogramStretch(Mat src, vector<std::string> parameter)
{
    std::string functionName = parameter[2];
    if (functionName == "histStretch")
    {
        int a = stof(parameter[3]);
        int b = stof(parameter[4]);

        Roi roi;
        roi.x = stoi(parameter[5]);
        roi.y = stoi(parameter[6]);
        roi.size = stoi(parameter[7]);

        // Mat srcRoi = makeGreyRoiImage(src, roi);
        // Mat tgt = Mat(srcRoi.size(), srcRoi.type());
        Mat tgt = Mat(src.size(), src.type());
        tgt = src.clone();
        histogramStretchRoi(src, tgt, roi, a, b);

        saveHistogramImg(src, tgt, "test");
        save_image(tgt, parameter[1]);
    }
}

void handleLocalHistogramStretch(Mat src, vector<std::string> parameter)
{
    std::string functionName = parameter[2];
    if (functionName == "localHistStretch")
    {
        int a = stof(parameter[3]);
        int b = stof(parameter[4]);

        Roi roi;
        roi.x = stoi(parameter[5]);
        roi.y = stoi(parameter[6]);
        roi.size = stoi(parameter[7]);

        // split roi into 4 quadrants
        int halfSize = roi.size / 2;
        Roi q1 = {roi.x, roi.y, halfSize};
        Roi q2 = {roi.x + halfSize, roi.y, halfSize};
        Roi q3 = {roi.x, roi.y + halfSize, halfSize};
        Roi q4 = {roi.x + halfSize, roi.y + halfSize, halfSize};

        Mat tgt = Mat(src.size(), src.type());
        tgt = src.clone();

        histogramStretchRoi(src, tgt, q1, a, b);
        histogramStretchRoi(src, tgt, q2, a, b);
        histogramStretchRoi(src, tgt, q3, a, b);
        histogramStretchRoi(src, tgt, q4, a, b);

        saveHistogramImg(src, tgt, "test");
        save_image(tgt, parameter[1]);
    }
}

void saveHistogramImg(Mat roi, Mat modifiedRoi, std::string name) 
{

    // each index is a bin/intensity, the count is the freq of those intensities
    std::vector<int> origHistogram(255+1, 0);
    std::vector<int> modifiedHistogram(255+1, 0);
    for (int i = 0; i < roi.size().width; i++)
    {
        for (int j = 0; j < roi.size().height; j++)
        {
            int val = roi.at<uchar>(i, j);
            origHistogram[val]++;

            int modifiedVal = modifiedRoi.at<uchar>(i, j);
            modifiedHistogram[modifiedVal]++;
        }
    }

    // normalize hist height so everything fits
    // int total = roi.size().height * roi.size().width;
    int originalHistHeight = *std::max_element(origHistogram.begin(), origHistogram.end());
    int modifiedHistHeight = *std::max_element(modifiedHistogram.begin(), modifiedHistogram.end());

    int histogramHeight = std::max(originalHistHeight, modifiedHistHeight);

    // create the histogram mat
    cv::Mat histImg = Mat::zeros(histogramHeight, 255+1, roi.type());
    cv::Mat modifiedHistImg = Mat::zeros(histogramHeight, 255+1, roi.type());

    // plot the histogram
    for (int xIndex = 0; xIndex < 255; xIndex++)
    {
        int freq = origHistogram[xIndex];
        int origHeight = histogramHeight - freq - 1;
        for (int yIndex = origHeight; yIndex < histogramHeight; yIndex++)
            histImg.at<uchar>(yIndex, xIndex) = 255;
        // histImg.at<uchar>(freq, i) = 255;

        int modifiedFreq = modifiedHistogram[xIndex];
        int modifiedHeight = histogramHeight - modifiedFreq - 1;
        for (int yIndex = modifiedHeight; yIndex < histogramHeight; yIndex++)
            modifiedHistImg.at<uchar>(yIndex, xIndex) = 255;
        // modifiedHistImg.at<uchar>(modifiedFreq, i) = 255;
    }

    save_image(histImg, "originalHistogram.pgm");
    save_image(modifiedHistImg, "modifiedHistogram.pgm");
}
