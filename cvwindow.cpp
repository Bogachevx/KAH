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
    cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(TRACKBARS_NAME, cv::WINDOW_FREERATIO);
}

void setupTrackbars()
{
    cv::namedWindow(TRACKBARS_NAME, cv::WINDOW_FREERATIO);
    cv::createTrackbar("p1", TRACKBARS_NAME, &p1, 255);
    cv::createTrackbar("p2", TRACKBARS_NAME, &p2, 255);
    cv::createTrackbar("min", TRACKBARS_NAME, &minRadius, 500);
    cv::createTrackbar("max", TRACKBARS_NAME, &maxRadius, 500);
    cv::createTrackbar("MINY", TRACKBARS_NAME, &MINY, 100);
    cv::createTrackbar("MAXY", TRACKBARS_NAME, &MAXY, 600);
    cv::createTrackbar("ENDLINE", TRACKBARS_NAME, &ENDLINE, 1024);
    cv::createTrackbar("WORKING_DELTA", TRACKBARS_NAME, &WORKING_DELTA, 1024);
    cv::createTrackbar("GATE_DELTA", TRACKBARS_NAME, &GATE_DELTA, 1024);
    cv::createTrackbar("kx", TRACKBARS_NAME, &kx, 40000);
}
