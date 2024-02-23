#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "runFromParameters.hpp"
#include "utils.hpp"
#include "roi.hpp"
#include "rotateFlip.hpp"

using namespace std;
using namespace cv;

#define ADD_G_VAL 50
#define BINARIZE_G_VAL 150
#define THRESHOLD_G_T 150
#define THRESHOLD_G_V 150

void runParam(vector<string> parameter)
{
    int paramSize = parameter.size();
    int numRois = 0;
    if ((paramSize - 3) % 4 == 0)
        numRois = (paramSize - 3) / 4;

    string srcName = parameter[0];
    string tgtName = parameter[1];
    Mat src = imread(srcName, cv::IMREAD_GRAYSCALE);
    Mat tgt = Mat(src.size(), src.type());
    src.copyTo(tgt);

    Mat srcColor = imread(srcName, cv::IMREAD_COLOR);
    Mat tgtColor = Mat(srcColor.size(), srcColor.type());
    srcColor.copyTo(tgtColor);


    // For Task A
    if (parameter[2] == "multiRoi")
    {
        mergeMat(src, tgt, parameter, numRois);
        save_image(tgt, tgtName);
        return;
    }
    handleHW0Roi(src, tgt, parameter);
    handleColorRoi(parameter);

    handleColorFlipRotate(srcColor, tgtColor, parameter, numRois);
    handleFlipRotate(src, tgt, parameter, numRois);

    handleMultColor(srcColor, tgtColor, parameter);
    handleAddColor(srcColor, tgtColor, parameter);

    handleScaleUp(src, tgt, parameter);
    handleRoiImage(src, tgt, parameter);
}

void handleMultColor(Mat src, Mat tgt, vector<string> parameter)
{
    string functionName = parameter[2];
    if (functionName == "multColor")
    {
        int moreC = stoi(parameter[3]);
        Roi roi;
        roi.x = 0;
        roi.y = 0;
        roi.size = src.rows;
        mult_Croi(src, tgt, roi, moreC);
        save_image(tgt, parameter[1]);
    }
}

void handleAddColor(Mat src, Mat tgt, vector<string> parameter)
{
    string functionName = parameter[2];
    if (functionName == "addColor")
    {
        int moreC = stoi(parameter[3]);
        Roi roi;
        roi.x = 0;
        roi.y = 0;
        roi.size = src.rows;
        add_Croi(src, tgt, roi, moreC);
        save_image(tgt, parameter[1]);
    }
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

// format: inputImage outputImage scaleUp scaleFactor rX rY rS
void handleScaleUp(Mat src, Mat tgt,vector<string> parameter)
{
    if (parameter[2] == "scaleUp") 
    {
        string tgt_name = parameter[1];

        Roi roi;
        float scaleFactor = stof(parameter[3]);
        roi.x = stoi(parameter[4]);
        roi.y = stoi(parameter[5]);
        roi.size = stoi(parameter[6]);

        scale_Groi(src, tgt, roi, scaleFactor);
        save_image(tgt, tgt_name);
    }
}

void handleColorFlipRotate(Mat src, Mat tgt, vector<string> parameter, int numRois)
{
    Mat srcCopy = Mat(src.size(), src.type());
    src.copyTo(srcCopy);
    string functionName = parameter[2];
    if (functionName == "flipColorImage")
    {
        string outputName = parameter[1].substr(0, parameter[1].find('.'));
        string flipOutputName = outputName + "_flip.png";

        // image is flipped and should be saved to disk
        flipColorImage(src, tgt);
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

void handleFlipRotate(Mat src, Mat tgt, vector<string> parameter, int numRois)
{
    Mat srcCopy = Mat(src.size(), src.type());
    src.copyTo(srcCopy);
    string functionName = parameter[2];
    if (functionName == "flipImage")
    {
        string outputName = parameter[1].substr(0, parameter[1].find('.'));
        string flipOutputName = outputName + "_flip.png";

        // image is flipped and should be saved to disk
        if (src.channels() == 1)
            flipImage(src, tgt);
        save_image(tgt, flipOutputName);

        // now we need to rotate the flipped image twice and save it to disk
        tgt.copyTo(src);
        for (int i = 0; i < 2; i++)
        {
            int degree = stoi(parameter[3 + i]);
            rotate(src, tgt, degree);
            save_image(tgt, outputName + "_rotate" + parameter[3 + i] + ".png");
            srcCopy.copyTo(src);
        }
    }

    srcCopy.release();
}

// For Task A
void mergeMat(Mat src, Mat tgt, vector<string> parameter, int numRois)
{
    for (int currRoi = 0; currRoi < numRois; currRoi++)
    {
        // use the same image for the first roi
        if (currRoi != 0)
            tgt.copyTo(src);

        Roi roi;

        makeHW0Mat(src, tgt, parameter, currRoi);
    }
}

// for Task A
void makeHW0Mat(Mat src, Mat tgt, vector<string> parameter, int currRoi)
{
    Roi roi;
    string functionName = parameter[3 + 4 * currRoi];
    roi.x = stoi(parameter[4 + 4 * currRoi]);
    roi.y = stoi(parameter[5 + 4 * currRoi]);
    roi.size = stoi(parameter[6 + 4 * currRoi]);
    cout << "ROI " << currRoi << " is at " << roi.x << " " << roi.y << " " << roi.size << "\n";

    if (functionName == "addG")
    {
        add_Groi(src, tgt, roi, ADD_G_VAL);
    }
    else if (functionName == "binarizeG")
    {
        binarize_Groi(src, tgt, roi, BINARIZE_G_VAL);
    }
    else if (functionName == "thresholdG")
    {
        threshold_Groi(src, tgt, roi, THRESHOLD_G_T, THRESHOLD_G_V);
    }
    // else
    //     cout << "Function " << functionName << " not found\n";
}

// overload for specific roi
void handleHW0Roi(Mat src, Mat tgt, vector<string> parameter)
{
    Roi roi;
    string functionName = parameter[2];
    string tgtName = parameter[1];
    if (functionName == "addG")
    {
        roi.x = stoi(parameter[4]);
        roi.y = stoi(parameter[5]);
        roi.size = stoi(parameter[6]);
        add_Groi(src, tgt, roi, stoi(parameter[3]));
        save_image(tgt, tgtName);
    }
    else if (functionName == "binarizeG")
    {
        roi.x = stoi(parameter[4]);
        roi.y = stoi(parameter[5]);
        roi.size = stoi(parameter[6]);
        binarize_Groi(src, tgt, roi, stoi(parameter[3]));
        save_image(tgt, tgtName);
    }
    else if (functionName == "scaleG")
    {
        roi.x = stoi(parameter[4]);
        roi.y = stoi(parameter[5]);
        roi.size = stoi(parameter[6]);
        scale_Groi(src, tgt, roi, stoi(parameter[3]));
        save_image(tgt, tgtName);
    }
    else if (functionName == "thresholdG")
    {
        roi.x = stoi(parameter[5]);
        roi.y = stoi(parameter[6]);
        roi.size = stoi(parameter[7]);
        threshold_Groi(src, tgt, roi, stoi(parameter[3]), stoi(parameter[4]));
        save_image(tgt, tgtName);
    }
    // else
    //     cout << "Function " << functionName << " not found\n";
}

void loopParams(vector<vector<string>> parameters)
{
    for (int currParam = 0; currParam < parameters.size(); currParam++)
    {
        runParam(parameters[currParam]);
    }
}
