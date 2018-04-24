#ifndef FINDPUCK_H
#define FINDPUCK_H

#include "headers.h"

cv::Point findPuck(cv::Mat &Frame, int param1, int param2, int minRadius, int maxRadius);

#endif // FINDPUCK_H
