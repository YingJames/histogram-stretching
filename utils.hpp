#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;
using namespace cv;

struct Roi {
    int x; // x coordinate of the top left corner
    int y; // y coordinate of the top left corner
    int size;
};

void convert_pgm(string image_name, string output_name);
int check_value(int value);
int get_pixel(Mat src, int y, int x);
void set_pixel(Mat src, Mat tgt, int y, int x, int pixel_value);
void save_image(Mat tgt, string output_name);
void scale_Grey(Mat src, Mat tgt, float scaleFactor);

Vec3b getColorPixel(Mat src, int y, int x);
void setColorPixel(Mat tgt, int y, int x, Vec3b pixelValue);

#endif // UTILS_HPP