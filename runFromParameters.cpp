#include <string>
#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

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

    // Mat srcColor = imread(srcName, cv::IMREAD_COLOR);
    // Mat tgtColor = Mat(srcColor.size(), srcColor.type());
    // srcColor.copyTo(tgtColor);

    handleHistogramStretch(src, parameter);
    handleLocalHistogramStretch(src, parameter);
    handleRoiImage(src, tgt, parameter);
    
}


void loopParams(vector<vector<string>> parameters)
{
    for (int currParam = 0; currParam < parameters.size(); currParam++)
    {
        runParam(parameters[currParam]);
    }
}
