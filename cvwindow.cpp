#include "cvwindow.h"

// DEBUG FUNCTION
void drawPath(cv::Mat &Frame, std::vector<cv::Point> &path)
{
    using namespace cv;

    for (uint8_t i = 0; i < path.size(); i++)
    {
        drawMarker(Frame, path[i], COLOR_WHITE, MARKER_STAR);
    }
}

// DEBUG FUNCTION
void drawDebugLines(cv::Mat &Frame)
{
    using namespace cv;
    line(Frame, Point(0, MINY), Point(Frame.cols, MINY), COLOR_GREEN, 2);
    line(Frame, Point(0, MAXY), Point(Frame.cols, MAXY), COLOR_GREEN, 2);
    line(Frame, Point(ENDLINE, 0), Point(ENDLINE, Frame.rows), COLOR_GREEN, 2);
    line(Frame, Point(ENDLINE-WORKING_DELTA, 0), Point(ENDLINE-WORKING_DELTA, Frame.rows), COLOR_BLUE, 2);
    line(Frame, Point(0, Frame.rows/2 - GATE_DELTA), Point(Frame.cols, Frame.rows/2 - GATE_DELTA), COLOR_RED, 2);
    line(Frame, Point(0, Frame.rows/2 + GATE_DELTA), Point(Frame.cols, Frame.rows/2 + GATE_DELTA), COLOR_RED, 2);
}

void setupWindow()
{
    cvNamedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(TRACKBARS_NAME, CV_WINDOW_FREERATIO);
}

void setupTrackbars()
{
    cvNamedWindow(TRACKBARS_NAME, CV_WINDOW_FREERATIO);
    cvCreateTrackbar("p1", TRACKBARS_NAME, &p1, 255);
    cvCreateTrackbar("p2", TRACKBARS_NAME, &p2, 255);
    cvCreateTrackbar("min", TRACKBARS_NAME, &minRadius, 500);
    cvCreateTrackbar("max", TRACKBARS_NAME, &maxRadius, 500);
    cvCreateTrackbar("MINY", TRACKBARS_NAME, &MINY, 100);
    cvCreateTrackbar("MAXY", TRACKBARS_NAME, &MAXY, 600);
    cvCreateTrackbar("ENDLINE", TRACKBARS_NAME, &ENDLINE, 1024);
    cvCreateTrackbar("WORKING_DELTA", TRACKBARS_NAME, &WORKING_DELTA, 1024);
    cvCreateTrackbar("GATE_DELTA", TRACKBARS_NAME, &GATE_DELTA, 1024);
    cvCreateTrackbar("kx", TRACKBARS_NAME, &kx, 40000);
}
