#ifndef ROTATE_FLIP_HPP
#define ROTATE_FLIP_HPP

using namespace cv;
void rotate(Mat src, Mat tgt, int degree);
void rotateColor(Mat src, Mat tgt, int degree);
void flipImage(Mat src, Mat tgt);
void flipColorImage(Mat src, Mat tgt);

#endif // ROTATE_FLIP_HPP