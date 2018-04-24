#ifndef EXTRAPOLATION_H
#define EXTRAPOLATION_H

#include "headers.h"

cv::Vec2f getExtrapolationCoefficients(const std::vector<cv::Point> &Points, cv::Mat &Frame);

#endif // EXTRAPOLATION_H
