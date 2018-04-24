#include "prediction.h"

cv::Point predictPosition(cv::Mat &Frame, std::vector<cv::Point> &Points, int finalx)
{
    using namespace cv;

    if (Points.size() < 2)
    {
        return Point(finalx, Frame.rows/2);
    }

    Vec2f coefs = getExtrapolationCoefficients(Points, Frame);
    float a = coefs[0], b = coefs[1]; // for simplier using
    int y_final, newx = finalx, hitCount = 0;
    Point cp = Points[Points.size()-1];
    Point lp = Points[Points.size()-2];

    do
    {
        y_final = a*finalx + b;
        if (!in_Range(y_final, MINY, MAXY))
        {
            hitCount++;
             if (a > 0)
             {
                 newx = (MAXY-b)/a;
                 a = -a;
                 b = MAXY-a*newx;
             } else
             {
                 newx = (MINY-b)/a;
                 a = -a;
                 b = MINY-a*newx;
             }
             lp = cp;
             cp = Point(newx, y_final);
             ///DEBUG///
             line(Frame, Point(0, a*0 + b), Point(1000, a*1000 + b), Scalar(255,0,255), 2);
             ///END///
             if (hitCount > 5)
             {
                 return Point(ENDLINE, Frame.rows/2);
             }
        }
        else
        {
            if (hitCount >= 2)
            {
                return Point(finalx, Frame.rows/2);
            }
            return Point(finalx, y_final);
        }
        imshow(WINDOW_NAME, Frame);

    } while(true);
}
