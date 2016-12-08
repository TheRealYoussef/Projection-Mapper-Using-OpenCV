#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <opencv2/opencv.hpp>

using namespace cv;

class BoundingBox
{
public:

    BoundingBox(const Point& c1, const Point& c2, const Point& c3, const Point& c4) : corner1(c1), corner2(c2), corner3(c3), corner4(c4) {}

    Point getCorner1() const {
        return corner1;
    }

    Point getCorner2() const {
        return corner2;
    }

    Point getCorner3() const {
        return corner3;
    }

    Point getCorner4() const {
        return corner4;
    }

private:

    Point corner1, corner2, corner3, corner4;
};

#endif // BOUNDINGBOX_H
