#include "puckprocess.h"

void processForward(cv::Mat &Frame, cv::Point &puckPoint, std::vector<cv::Point> &Points, int &averagexSpeed)
{
    using namespace cv;

    Point predictedPoint;
    Point attackPoint;
    // Предсказываем, куда придёт шайба

    predictedPoint = predictPosition(Frame, Points, ENDLINE);
    circle(Frame, predictedPoint, 20, COLOR_ORANGE,2);
    circle(Frame, predictedPoint, WORKING_DELTA, COLOR_YELLOW, 2);
    //Vec2f c = getExtrapolationCoefficients(Points, Frame);
    //float a = c[0];
    //float dx = cos(atan(a))*WORKING_DELTA;
    attackPoint = predictPosition(Frame, Points, ENDLINE-WORKING_DELTA);
    circle(Frame, attackPoint, 20, COLOR_ORANGE,2);

    if (puckPoint.x < ENDLINE)
    {
        // Шайба не в рабочей зоне
        if (!in_Range(puckPoint.x, ENDLINE- WORKING_DELTA - kx*averagexSpeed/1000, ENDLINE))
        {
            // Если шайба попадает в зону отбития
            //if (in_Range(predictedPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
            //{
                //Идём в неё
                moveTo(Frame, predictedPoint);
            //}
            //else
            //{
            //    moveTo(Frame, HOMEPOINT);
            //}
        }
        else
        {
            if (in_Range(attackPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
            {
                // Идём в неё
                if (in_Range(predictedPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
                {
                    moveTo(Frame, attackPoint);
                }
            }
        }
    }
    else
    {
        moveTo(Frame, Point(ENDLINE, MAXY));
        moveTo(Frame, HOMEPOINT);
    }
}

void processBackward(cv::Mat &Frame, std::vector<cv::Point> &Points, cv::Vec2i averageSpeed)
{
    using namespace cv;

    Point predictedPoint;
    Point attackPoint;
    Point puckPoint = Points[Points.size()-1];
    int averagexSpeed = averageSpeed[0];
    int averageySpeed = averageSpeed[1];

    predictedPoint = predictPosition(Frame, Points, ENDLINE);//-WORKING_DELTA);
    circle(Frame, predictedPoint, 20, COLOR_ORANGE,2);
    circle(Frame, predictedPoint, WORKING_DELTA, COLOR_YELLOW, 2);
    //Vec2f c = getExtrapolationCoefficients(Points, Frame);
    //float a = c[0];
    //float dx = cos(atan(a))*WORKING_DELTA;
    attackPoint = predictPosition(Frame, Points, ENDLINE-WORKING_DELTA);
    circle(Frame, attackPoint, 20, COLOR_ORANGE,2);

    // Шайба уходит от нас, но находится в нашей рабочей зоне
    if (in_Range(puckPoint.x, ENDLINE-WORKING_DELTA, ENDLINE))
    {
        std::cout << averageySpeed << std::endl;
        // Если почти стоит
        if (averageySpeed < 40)
        {
            if (in_Range(puckPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
            {
                moveTo(Frame, puckPoint);
            }
        }
        if (Points.size() > 2)
        {

            if (in_Range(puckPoint.x, ENDLINE-WORKING_DELTA/2, ENDLINE))
            {
                if (in_Range(attackPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
                {
                    if (in_Range(predictedPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
                    {
                        moveTo(Frame, predictedPoint);
                    }
                }
            }
            else
            {
                if (in_Range(attackPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
                {
                    if (in_Range(predictedPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
                    {
                        moveTo(Frame, attackPoint);
                    }
                }
            }
        }
    }
    else
    {
        moveTo(Frame, HOMEPOINT);
        Points.clear();
    }

}
