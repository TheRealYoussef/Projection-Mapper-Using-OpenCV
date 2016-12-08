#ifndef BOUNDINGBOXESCREATOR_H
#define BOUNDINGBOXESCREATOR_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "boundingbox.h"
#include "coordinateextremes.h"

using namespace cv;
using namespace std;

class BoundingBoxesCreator
{
public:

    void createBoundingBoxes(const vector<vector<int> >& labels, int numberOfLabels, const Mat& image);

    vector<Mat> getObjects() const;

    vector<BoundingBox> getBoundingBoxes() const;

private:

    vector<Mat> objects;

    vector<BoundingBox> boundingBoxes;
};

#endif // BOUNDINGBOXESCREATOR_H
