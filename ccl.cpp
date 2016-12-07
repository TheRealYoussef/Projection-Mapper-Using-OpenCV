#include "ccl.h"

void CCL::applyCCL(const Mat& image) {
    Mat binary(image.rows, image.cols, CV_8UC1, Scalar(0));

    binarize(image, binary);

    //numberOfLabels = connectedComponents(binary, labels);

    //labels.convertTo(labels, CV_8U);
}

void CCL::binarize(const Mat& inputImage, Mat& outputImage) {
    for (int i = 0; i < inputImage.rows; ++i) {
        for (int j = 0; j < inputImage.cols; ++j) {
            Vec3b bgr = inputImage.at<Vec3b>(i, j);
            outputImage.at<uchar>(i, j) = (bgr[0] == bgr[1] && bgr[1] == bgr[2] && bgr[2] == 0) ? 0 : 255;
        }
    }
}

int CCL::getNumberOfLabels() const {
    return numberOfLabels;
}

Mat CCL::getLabels() const {
    return labels;
}
