#ifndef CAMERA_H
#define CAMERA_H

#include "headers.h"
extern cv::VideoCapture *camera;

void skipFrames(int frames);
void setupCamera(int cameraAddress, int Width, int Height);
void getCameraFrame(cv::Mat &Frame);

#endif // CAMERA_H
