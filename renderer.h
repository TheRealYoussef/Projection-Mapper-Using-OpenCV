#ifndef RENDERER_H
#define RENDERER_H
#include"matcher.h"


class Renderer
{
public:

    Renderer(const Mat& textureImage, const Mat& objectImage);
    void performRender(Mat& frame, const Mat& textureImage);
    ~Renderer();

private:

    Matcher* matcher;
    vector<BoundingBox> getObjects; //draws rectangles around objects in objects image
    vector<BoundingBox> getScenes; //draws rectangles around objects in scenes
};

#endif // RENDERER_H
