#ifndef ROI_HPP
#define ROI_HPP

using namespace cv;

Mat makeGreyRoiImage(Mat src, Roi roi);
Mat makeColorRoiImage(Mat src, Roi roi);
void add_Groi(Mat src, Mat tgt, Roi roi, int addendValue); // add pixel value to grey scale image
void binarize_Groi(Mat src, Mat tgt, Roi roi, int pixel);
void scale_Groi(Mat src, Mat tgt, Roi roi, float scaleFactor);
void threshold_Groi(Mat src, Mat tgt, Roi roi, int T, int V);
void mult_Croi(Mat src, Mat tgt, Roi roi, int multiplier);
void add_Croi(Mat src, Mat tgt, Roi roi, int addend);
#endif // ROI_HPP