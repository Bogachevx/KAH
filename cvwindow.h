#ifndef CVWINDOW_H
#define CVWINDOW_H

extern int p1, p2, minRadius, maxRadius, kx, MINY, MAXY, ENDLINE, WORKING_DELTA, GATE_DELTA;

#include "headers.h"
void drawPath(cv::Mat &Frame, std::vector<cv::Point> &path);
void drawDebugLines(cv::Mat &Frame);
void setupWindow();
#endif // CVWINDOW_H
