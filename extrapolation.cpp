#include "extrapolation.h"

//+
cv::Vec2f getExtrapolationCoefficients(const std::vector<cv::Point> &Points, cv::Mat &Frame)
{
    using namespace cv;

    int sumy = 0, sumx = 0, sumx2 = 0, sumxy = 0;
    float n = Points.size(), a, b;

    for (int i = 0; i < n; i++)
    {
        sumy += Points[i].y;
        sumx += Points[i].x;
        sumx2 += Points[i].x*Points[i].x;
        sumxy += Points[i].x*Points[i].y;
    }

    a = (sumxy - (sumx*sumy/n))/(sumx2 - sumx*sumx/n);
    b = (sumy - a*sumx)/n;

    ///DEBUG///
    line(Frame, Point(0, a*0 + b), Point(1000, a*1000 + b), Scalar(255,0,255), 2);
    ///END///

    return Vec2f(a, b);
}
