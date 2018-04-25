#include "camera.h"

// DEBUG FUNCTION
void skipFrames(int frames)
{
    for (int i = 0; i < frames; i++)
    {
        cv::Mat c;
        camera->read(c);
    }
}

void setupCamera(int cameraAddress, int Width, int Height)
{
    camera = new cv::VideoCapture(cameraAddress);
    //camera = new VideoCapture("E:\\outVideo3.avi");

    if (!camera->isOpened())
    {
        std::cout << "Error opening camera!" << std::endl;
        exit(-1);
    }
    camera->set(CV_CAP_PROP_FRAME_WIDTH, Width);
    camera->set(CV_CAP_PROP_FRAME_HEIGHT, Height);
    camera->set(CV_CAP_PROP_FPS, 90);

    skipFrames(0);
}

void getCameraFrame(cv::Mat &Frame)
{
    if (!camera->isOpened())
    {
        exit(-100);
    }
    camera->read(Frame);
    cv::cvtColor(Frame, Frame, CV_BGR2GRAY);
}
