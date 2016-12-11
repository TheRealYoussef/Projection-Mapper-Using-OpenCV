#ifndef MATCHER_H
#define MATCHER_H
#include "ccl.h"
#include "boundingboxescreator.h"


class Matcher
{
public:

    Matcher(const Mat& textureImage, const Mat& objectImage);

    vector<BoundingBox> getScene();

    vector<BoundingBox> getObject();

    //Apply SURF
    void surf(Mat&);

private:

    BoundingBoxesCreator boundingBoxesCreator;
    CCL ccl;
    vector<BoundingBox> getobjects; //draws rectangles around objects in objects image
    vector<BoundingBox> getScenes; //draws rectangles around objects in scenes
    vector<Mat> objects;
    Mat binary; // a temporary Mat for getting objects
};

#endif // MATCHER_H
