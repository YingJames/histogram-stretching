#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

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

void handleColorRotate(Mat src, Mat tgt, vector<string> parameter, int numRois)
{
    Mat srcCopy = Mat(src.size(), src.type());
    src.copyTo(srcCopy);
    string functionName = parameter[2];
    if (functionName == "flipColorImage")
    {
        string outputName = parameter[1].substr(0, parameter[1].find('.'));
        string flipOutputName = outputName + "_flip.png";

        // image is flipped and should be saved to disk
        // flipColorImage(src, tgt);
        save_image(tgt, flipOutputName);

        // now we need to rotate the flipped image twice and save it to disk
        tgt.copyTo(src);
        for (int i = 0; i < 2; i++)
        {
            int degree = stoi(parameter[3 + i]);
            rotateColor(src, tgt, degree);
            save_image(tgt, outputName + "_rotate" + parameter[3 + i] + ".png");
            srcCopy.copyTo(src);
        }
    }

    srcCopy.release();
}

void handleRotate(Mat src, Mat tgt, vector<string> parameter, int numRois)
{
    Mat srcCopy = Mat(src.size(), src.type());
    src.copyTo(srcCopy);
    string functionName = parameter[2];
    if (functionName == "rotate")
    {
        string outputName = parameter[1].substr(0, parameter[1].find('.'));
        string flipOutputName = outputName + "_flip.png";

        // image is flipped and should be saved to disk
        // if (src.channels() == 1)
        //     flipImage(src, tgt);
        // save_image(tgt, flipOutputName);

        // now we need to rotate the flipped image three times and save it to disk
        tgt.copyTo(src);
        for (int i = 0; i < 3; i++)
        {
            int degree = stoi(parameter[3 + i]);
            rotate(src, tgt, degree);
            save_image(tgt, outputName + "_rotate" + parameter[3 + i] + ".png");
            srcCopy.copyTo(src);
        }
    }

    srcCopy.release();
}