#pragma once

#include "Helper.h"
#include <cmath>

using namespace std;

int calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

//void writeToJpg(const cv::Mat &source, const char* filename)
//{
//    vector<int> params;
//    params.push_back(CV_IMWRITE_JPEG_QUALITY);
//    params.push_back(100);
//
//    imwrite(filename, source, params);
//}
