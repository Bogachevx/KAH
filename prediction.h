#ifndef PREDICTION_H
#define PREDICTION_H

#include "headers.h"
#include "extrapolation.h"

extern int MINY, MAXY, ENDLINE;
cv::Point predictPosition(cv::Mat &Frame, std::vector<cv::Point> &Points, int finalx);

#endif // PREDICTION_H
