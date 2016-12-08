#ifndef COORDINATEEXTREMES_H
#define COORDINATEEXTREMES_H


class CoordinateExtremes
{
public:
    CoordinateExtremes(int _maxX, int _minX, int _maxY, int _minY) : maxX(_maxX), minX(_minX), maxY(_maxY), minY(_minY) {}

    void setMaxX(int _maxX) {
        maxX = _maxX;
    }

    void setMinX(int _minX) {
        minX = _minX;
    }

    void setMaxY(int _maxY) {
        maxY = _maxY;
    }

    void setMinY(int _minY) {
        minY = _minY;
    }

    int getMaxX() const {
        return maxX;
    }

    int getMinX() const {
        return minX;
    }

    int getMaxY() const {
        return maxY;
    }

    int getMinY() const {
        return minY;
    }

private:

    int maxX, minX, maxY, minY;
};

#endif // COORDINATEEXTREMES_H
