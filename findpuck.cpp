#include "findpuck.h"

//+
cv::Point findPuck(cv::Mat &Frame, int param1, int param2, int minRadius, int maxRadius)
{
    using namespace cv;
    using namespace std;

    vector<Vec3f> circles;
    HoughCircles(Frame, circles, CV_HOUGH_GRADIENT, 1, Frame.rows/2,
                param1, param2, minRadius, maxRadius);
    cvtColor(Frame, Frame, CV_GRAY2BGR);

    if (circles.size() != 1)
    {
        return Point(-1, -1);
    }

    Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
    ///DEBUG///
    int radius = cvRound(circles[0][2]);
    std::cout << "Radius: " << radius << endl;
    circle(Frame, center, radius, Scalar(0,0,255), 10);
    ///END///
    return center;
}

