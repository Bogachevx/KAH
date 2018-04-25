#ifndef PUCKPROCESS_H
#define PUCKPROCESS_H

#include "headers.h"
#include "prediction.h"

extern int p1, p2, minRadius, maxRadius, kx, MINY, MAXY, ENDLINE, WORKING_DELTA, GATE_DELTA;

void processBackward(cv::Mat &Frame, std::vector<cv::Point> &Points, cv::Vec2i averageSpeed);
void processForward(cv::Mat &Frame, cv::Point &puckPoint, std::vector<cv::Point> &Points, int &averagexSpeed);

#endif // PUCKPROCESS_H
