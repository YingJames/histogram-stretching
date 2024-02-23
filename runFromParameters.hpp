#ifndef RUN_FROM_PARAMETERS_HPP
#define RUN_FROM_PARAMETERS_HPP
#include "utils.hpp"
using namespace std;
using namespace cv;

void handleRoiImage(Mat src, Mat &tgt, vector<string> parameter);
void runParam(vector<string> parameter);
void loopParams(vector<vector<string>> parameters);
void makeHW0Mat(Mat src, Mat tgt, vector<string> parameter, int currRoi);
void mergeMat(Mat src, Mat tgt, vector<string> parameter, int numRois);
void handleHW0Roi(Mat src, Mat tgt, vector<string> parameter);

void handleFlipRotate(Mat src, Mat tgt, vector<string> parameter, int numRois);
void handleColorFlipRotate(Mat src, Mat tgt, vector<string> parameter, int numRois);

void handleMultColor(Mat src, Mat tgt, vector<string> parameter);
void handleAddColor(Mat src, Mat tgt, vector<string> parameter);

void handleScaleUp(Mat src, Mat tgt,vector<string> parameter);
void handleColorRoi(vector<string> parameter);
#endif // RUN_FROM_PARAMETERS_HPP