#include "renderer.h"

Renderer::Renderer(const Mat& textureImage, const Mat& objectImage){
    matcher = new Matcher(textureImage, objectImage);
    getObjects = matcher->getObject();
}

Renderer::~Renderer() {
    delete matcher;
}

void Renderer::performRender(Mat& frame, const Mat& texture){
    matcher->surf(frame);

    getScenes = matcher->getScene();

    for (int i = 0; i < (int)getScenes.size(); i++){

        double sceneArea, objectArea;
        vector<Point> sceneTemp, objectTemp; //A vector to extract the points and calculate both areas

        sceneTemp.push_back(getScenes[i].getCorner1());
        sceneTemp.push_back(getScenes[i].getCorner2());
        sceneTemp.push_back(getScenes[i].getCorner3());
        sceneTemp.push_back(getScenes[i].getCorner4());
        sceneArea = contourArea(sceneTemp); //Returns the area of the four points

        objectTemp.push_back(getObjects[i].getCorner1());
        objectTemp.push_back(getObjects[i].getCorner2());
        objectTemp.push_back(getObjects[i].getCorner3());
        objectTemp.push_back(getObjects[i].getCorner4());
        objectArea = contourArea(objectTemp); //Returns the area of the four points

        double scaleFactor;
        if(objectArea > 0)
           scaleFactor = sceneArea * 1.0 / objectArea; //Gets a scale factor
        else
            scaleFactor = 1.0;
        if(scaleFactor == 0.0)
            scaleFactor = 1.0;

        if (scaleFactor > 0.5 && scaleFactor < 10.0) {

            Rect tempRectangle = boundingRect(objectTemp);
            Mat tempTexture = texture(tempRectangle);

            resize(tempTexture, tempTexture, Size(0,0), scaleFactor, scaleFactor); //Resizes the texture image by the scale factor to make both the same size

            int minX, maxX, minY, maxY;
            minX = sceneTemp[0].x;
            maxX = sceneTemp[1].x;
            minY = sceneTemp[0].y;
            maxY = sceneTemp[2].y;

            if (minX >= 0 && maxX >= 0 && minY >= 0 && maxY >= 0) {
                for (int j = minX; j < maxX; j++) {
                    for (int k = minY; k < maxY; k++) {
                        if (j < frame.cols && k < frame.rows && k - minY < tempTexture.rows && j - minX < tempTexture.cols && (tempTexture.at<Vec3b>(k - minY, j - minX)[0] != 0 || tempTexture.at<Vec3b>(k - minY, j - minX)[1] != 0 || tempTexture.at<Vec3b>(k - minY, j - minX)[2] != 0)) {
                            frame.at<Vec3b>(k, j)[0] = tempTexture.at<Vec3b>(k - minY, j - minX)[0];
                            frame.at<Vec3b>(k, j)[1] = tempTexture.at<Vec3b>(k - minY, j - minX)[1];
                            frame.at<Vec3b>(k, j)[2] = tempTexture.at<Vec3b>(k - minY, j - minX)[2];
                        }
                    }
                }
            }
        }
    }

    imshow("Scene", frame);
}
