#include "matcher.h"
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"

Matcher::Matcher(const Mat& textureImage, const Mat& objectImage) {
    ccl.applyCCL(textureImage);
    boundingBoxesCreator.createBoundingBoxes(ccl.getLabels(), ccl.getNumberOfLabels(), objectImage);
    objects = boundingBoxesCreator.getObjects();
    getobjects = boundingBoxesCreator.getBoundingBoxes();
}

//SURF AS OBTAINED FROM THE OPENCV DOCUMENTATION http://docs.opencv.org/2.4/doc/tutorials/features2d/feature_homography/feature_homography.html
void Matcher::surf(Mat& sceneFrame) {
    getScenes.clear();

    for (int i = 0; i < (int)objects.size(); i++) {

        //-- Step 1: Detect the keypoints using SURF Detector
        int minHessian = 400;

        SurfFeatureDetector detector(minHessian);

        std::vector<KeyPoint> keypoints_object, keypoints_scene;

        detector.detect(objects[i], keypoints_object);
        detector.detect(sceneFrame, keypoints_scene);

        //-- Step 2: Calculate descriptors (feature vectors)
        SurfDescriptorExtractor extractor;

        Mat descriptors_object, descriptors_scene;

        extractor.compute(objects[i], keypoints_object, descriptors_object);
        extractor.compute(sceneFrame, keypoints_scene, descriptors_scene);

        //-- Step 3: Matching descriptor vectors using FLANN matcher
        FlannBasedMatcher matcher;
        std::vector<DMatch> matches;
        matcher.match(descriptors_object, descriptors_scene, matches);

        double max_dist = 0;
        double min_dist = 100;

        //-- Quick calculation of max and min distances between keypoints
        for (int i = 0; i < descriptors_object.rows; i++){

            double dist = matches[i].distance;
            if (dist < min_dist)
                min_dist = dist;
            if (dist > max_dist)
                max_dist = dist;
        }

        //-- Get only "good" matches (i.e. whose distance is less than 3*min_dist)
        std::vector<DMatch> good_matches;

        for (int i = 0; i < descriptors_object.rows; i++) {
            if (matches[i].distance < 3 * min_dist) {
                good_matches.push_back(matches[i]);
            }
        }

        //-- Localize the object
        std::vector<Point2f> obj;
        std::vector<Point2f> scene;

        for (int i = 0; i < (int)good_matches.size(); i++) {
            //-- Get the keypoints from the good matches
            obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
            scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
        }

        if(obj.size() > 3 && scene.size() > 3 ) {

            Mat H = findHomography(obj, scene, CV_RANSAC);

            vector<Point2f> obj_corners(4);
            vector<Point2f> scene_corners(4);

            //-- Get the corners from the image_1 ( the object to be "detected" )
            obj_corners[0] = cvPoint(0, 0);
            obj_corners[1] = cvPoint(objects[i].cols, 0);
            obj_corners[2] = cvPoint(objects[i].cols, objects[i].rows);
            obj_corners[3] = cvPoint(0, objects[i].rows);

            perspectiveTransform(obj_corners, scene_corners, H);

            Scalar color;

            if (i == 0)
                color = Scalar(0, 255, 0);
            else
                color = Scalar(0, 0, 255);
/*
            line(sceneFrame, scene_corners[0], scene_corners[1], color, 4);
            line(sceneFrame, scene_corners[1], scene_corners[2], color, 4);
            line(sceneFrame, scene_corners[2], scene_corners[3], color, 4);
            line(sceneFrame, scene_corners[3], scene_corners[0], color, 4);*/

            getScenes.push_back(BoundingBox(scene_corners[0],scene_corners[1],scene_corners[2],scene_corners[3]));
        }
        else {
            getScenes.push_back(BoundingBox(Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)));
        }
    }
}

vector<BoundingBox> Matcher::getScene() {
    return getScenes;
}

vector<BoundingBox> Matcher::getObject() {
    return getobjects;
}
