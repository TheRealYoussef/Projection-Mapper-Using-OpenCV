#ifndef CCL_H
#define CCL_H

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class CCL
{
public:

    /*
     * Takes texture file and applies CCL to get objects
    */
    void applyCCL(const Mat& image);

    int getNumberOfLabels() const;

    vector<vector<int> > getLabels() const;

private:

    int numberOfLabels;

    vector<vector<int> > labels;

    void countLabels();
};

#endif // CCL_H
