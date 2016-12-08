#include "ccl.h"
#include <fstream>

void CCL::applyCCL(const Mat& image) {
    labels.resize(image.rows, vector<int>(image.cols, 0)); //Initialize labels with 0's

    vector<int> equalities(1, 0); //equalities[l] = e means that the lowest label connected to l is e
    int label = 1; //Start labeling with 1

    //Loop on the image
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            Vec3b bgr = image.at<Vec3b>(i, j);
            if (bgr[0] != 0 || bgr[1] != 0 || bgr[2] != 0) { //If the pixel is foreground (not black)
                //Find the lowest neighbouring label that is not 0
                int lowestLabel = label;
                if (i - 1 >= 0) {
                    if (equalities[labels[i - 1][j]] != 0)
                        lowestLabel = min(lowestLabel, equalities[labels[i - 1][j]]);
                    if (j - 1 >= 0)
                        if (equalities[labels[i - 1][j - 1]] != 0)
                            lowestLabel = min(lowestLabel, equalities[labels[i - 1][j - 1]]);
                    if (j + 1 < image.cols)
                        if (equalities[labels[i - 1][j + 1]] != 0)
                            lowestLabel = min(lowestLabel, equalities[labels[i - 1][j + 1]]);
                }
                if (j - 1 >= 0)
                    if (equalities[labels[i][j - 1]] != 0)
                        lowestLabel = min(lowestLabel, equalities[labels[i][j - 1]]);
                if (lowestLabel == label) { //If there are no neighbouring labels that are not 0
                    labels[i][j] = label++; //Put a new label
                    equalities.push_back(labels[i][j]); //equalities[label] = label
                }
                else { //There are one or more neighbouring labels that are not 0
                    labels[i][j] = lowestLabel; //Assign the lowest neighbouring label
                    //Update the equalities of the neighbouring labels
                    if (i - 1 >= 0) {
                        if (equalities[labels[i - 1][j]] != 0 && equalities[labels[i - 1][j]] != lowestLabel)
                            equalities[labels[i - 1][j]] = lowestLabel;
                        if (j - 1 >= 0)
                            if (equalities[labels[i - 1][j - 1]] != 0 && equalities[labels[i - 1][j - 1]] != lowestLabel)
                                equalities[labels[i - 1][j - 1]] = lowestLabel;
                        if (j + 1 < image.cols)
                            if (equalities[labels[i - 1][j + 1]] != 0 && equalities[labels[i - 1][j + 1]] != lowestLabel)
                                equalities[labels[i - 1][j + 1]] = lowestLabel;
                    }
                    if (j - 1 >= 0)
                        if (equalities[labels[i][j - 1]] != 0 && equalities[labels[i][j - 1]] != lowestLabel)
                            equalities[labels[i][j - 1]] = lowestLabel;
                }
            }
        }
    }

    countLabels(); //Get the number of labels
}

int CCL::getNumberOfLabels() const {
    return numberOfLabels;
}

vector<vector<int> > CCL::getLabels() const {
    return labels;
}

void CCL::countLabels() {
    numberOfLabels = 0;

    for (int i = 0; i < labels.size(); ++i) {
        for (int j = 0; j < labels[i].size(); ++j) {
            numberOfLabels = max(numberOfLabels, labels[i][j]);
        }
    }
}
