#ifndef UTILS_HPP
#define UTILS_HPP

using namespace cv;
using std::vector;

struct Roi {
    int x; // x coordinate of the top left corner
    int y; // y coordinate of the top left corner
    int size;
};

// COLLECT PIXEL DATA
void convert_pgm(std::string image_name, std::string output_name);
int check_value(int value);
int get_pixel(Mat src, int y, int x);
void set_pixel(Mat src, Mat tgt, int y, int x, int pixel_value);
Vec3b getColorPixel(Mat src, int y, int x);
void setColorPixel(Mat tgt, int y, int x, Vec3b pixelValue);

void save_image(Mat tgt, std::string output_name);

// CREATE ROI
Mat makeGreyRoiImage(Mat src, Roi roi);
Mat makeColorRoiImage(Mat src, Roi roi);
void handleRoiImage(Mat src, Mat &tgt, vector<std::string> parameter);
void handleColorRoi(vector<std::string> parameter);

/* ============ IMAGE MANIPULATION ============== */
/* handle functions are used to parse parameters before executing manipulations*/

// rotate
void rotate(Mat src, Mat tgt, int degree);
void rotateColor(Mat src, Mat tgt, int degree);
void handleRotate(Mat src, Mat tgt, vector<std::string> parameter, int numRois);
void handleColorRotate(Mat src, Mat tgt, vector<std::string> parameter, int numRois);

// histogram manipulation
void histogramStretchRoi(Mat src, Mat tgt, Roi roi, float a, float b);
void colorHistogramStretchRoi(Mat src, Mat tgt, Roi roi, std::string channel, float a, float b);
void handleHistogramStretch(Mat src, vector<std::string> parameter);
void handleLocalHistogramStretch(Mat src, vector<std::string> parameter);

// for debugging
void saveHistogramImg(Mat roi, Mat modifiedRoi, std::string name);

/* ============ PARAMETER HANDLING ============= */
void loopParams(vector<vector<std::string>> parameters);
vector<vector<std::string>> getParametersFromFile();

#endif // UTILS_HPP