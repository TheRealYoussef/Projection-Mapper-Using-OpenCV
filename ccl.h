#ifndef CCL_H
#define CCL_H

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

class CCL
{
public:

    /*
     * Takes texture file and applies CCL to get objects
    */
    void applyCCL(const Mat& image);

    int getNumberOfLabels() const;

    Mat getLabels() const;

private:

    int numberOfLabels;

    Mat labels;

    void binarize(const Mat& inputImage, Mat& outputImage);
};

#endif // CCL_H
