#include "ccl.h"
#include <qdebug.h>
#include <fstream>

void CCL::applyCCL(const Mat& image) {
    labels.resize(image.rows, vector<int>(image.cols, 0));

    vector<int> equalities(1, 0);
    int label = 1;

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            Vec3b bgr = image.at<Vec3b>(i, j);
            if (bgr[0] != 0 || bgr[1] != 0 || bgr[2] != 0) {
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
                if (lowestLabel == label) {
                    labels[i][j] = label++;
                    equalities.push_back(labels[i][j]);
                }
                else {
                    labels[i][j] = lowestLabel;
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

    numberOfLabels = 0;

    for (int i = 0; i < labels.size(); ++i) {
        for (int j = 0; j < labels[i].size(); ++j) {
            numberOfLabels = max(numberOfLabels, labels[i][j]);
        }
    }

    ofstream out2("out2.txt");

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            Vec3b bgr = image.at<Vec3b>(i, j);
            out2 << "(" << (int)bgr[0] << ", " << (int)bgr[1] << ", " << (int)bgr[2] << ")";
            if (j < image.cols - 1)
                out2 << ' ';
            else
                out2 << '\n';
        }
    }

    ofstream out("out.txt");

    for (int i = 0; i < labels.size(); ++i) {
        for (int j = 0; j < labels[i].size(); ++j) {
            out << labels[i][j];
            if (j < labels[i].size() - 1)
                out << ' ';
            else
                out << '\n';
        }
    }

    qDebug() << numberOfLabels;
}

int CCL::getNumberOfLabels() const {
    return numberOfLabels;
}

vector<vector<int> > CCL::getLabels() const {
    return labels;
}
