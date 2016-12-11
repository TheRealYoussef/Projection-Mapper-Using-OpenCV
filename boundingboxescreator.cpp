#include "boundingboxescreator.h"
#include <algorithm>

void BoundingBoxesCreator::createBoundingBoxes(const vector<vector<int> >& labels, int numberOfLabels, const Mat& image) {
    if (labels.size() > 0) {
        vector<CoordinateExtremes> coordinatesExtremes(numberOfLabels + 1, CoordinateExtremes(0, labels[0].size() - 1, 0, labels.size() - 1));

        for (int i = 0; i < (int)labels.size(); ++i) {
            for (int j = 0; j < (int)labels[i].size(); ++j) {
                if (labels[i][j] != 0) {
                    coordinatesExtremes[labels[i][j]].setMaxX(max(coordinatesExtremes[labels[i][j]].getMaxX(), j));
                    coordinatesExtremes[labels[i][j]].setMinX(min(coordinatesExtremes[labels[i][j]].getMinX(), j));
                    coordinatesExtremes[labels[i][j]].setMaxY(max(coordinatesExtremes[labels[i][j]].getMaxY(), i));
                    coordinatesExtremes[labels[i][j]].setMinY(min(coordinatesExtremes[labels[i][j]].getMinY(), i));
                }
            }
        }

        for (int i = 1; i < (int)coordinatesExtremes.size(); ++i) {
            boundingBoxes.push_back(BoundingBox(Point(coordinatesExtremes[i].getMinX(), coordinatesExtremes[i].getMinY()), Point(coordinatesExtremes[i].getMaxX(), coordinatesExtremes[i].getMinY()), Point(coordinatesExtremes[i].getMaxX(), coordinatesExtremes[i].getMaxY()), Point(coordinatesExtremes[i].getMinX(), coordinatesExtremes[i].getMaxY())));

            vector<Point> objectTemp;

            objectTemp.push_back(boundingBoxes[boundingBoxes.size() - 1].getCorner1());
            objectTemp.push_back(boundingBoxes[boundingBoxes.size() - 1].getCorner2());
            objectTemp.push_back(boundingBoxes[boundingBoxes.size() - 1].getCorner3());
            objectTemp.push_back(boundingBoxes[boundingBoxes.size() - 1].getCorner4());
            double objectArea = contourArea(objectTemp); //Returns the area of the four points

            if (objectArea < 10000.0)
                boundingBoxes.pop_back();
            else
                objects.push_back(image(Rect(coordinatesExtremes[i].getMinX(), coordinatesExtremes[i].getMinY(), coordinatesExtremes[i].getMaxX() - coordinatesExtremes[i].getMinX(), coordinatesExtremes[i].getMaxY() - coordinatesExtremes[i].getMinY())));
        }
    }
}

vector<Mat> BoundingBoxesCreator::getObjects() const {
    return objects;
}

vector<BoundingBox> BoundingBoxesCreator::getBoundingBoxes() const {
    return boundingBoxes;
}
