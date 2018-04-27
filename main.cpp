#include "headers.h"
#include "functions.h"
#include "puckprocess.h"
using namespace std;
using namespace cv;

extern int p1, p2, minRadius, maxRadius, kx, MINY, MAXY, ENDLINE, WORKING_DELTA, GATE_DELTA;

extern VideoCapture *camera;
extern QUdpSocket *udpSocket;
/*
void processForward(cv::Mat &Frame, cv::Point &puckPoint, std::vector<cv::Point> &Points, int &averagexSpeed)
{
    using namespace cv;

    Point predictedPoint;
    Point attackPoint;
    // Предсказываем, куда придёт шайба

    predictedPoint = predictPosition(Frame, Points, ENDLINE);
    circle(Frame, predictedPoint, 20, COLOR_ORANGE,2);
    circle(Frame, predictedPoint, WORKING_DELTA, COLOR_YELLOW, 2);
    attackPoint = predictPosition(Frame, Points, ENDLINE-WORKING_DELTA);
    circle(Frame, attackPoint, 20, COLOR_ORANGE,2);

    if (puckPoint.x < ENDLINE)
    {
        // Шайба не в рабочей зоне
        if (!in_Range(puckPoint.x, ENDLINE-WORKING_DELTA - kx*averagexSpeed/1000, ENDLINE))
        {
            // Если шайба попадает в зону отбития
            if (in_Range(predictedPoint.y, Frame.rows/2 - GATE_DELTA, Frame.rows/2 + GATE_DELTA))
            {
                // Идём в неё
                moveTo(Frame, predictedPoint);
            }
            else
            {
                moveTo(Frame, HOMEPOINT);
            }
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
    attackPoint = predictPosition(Frame, Points, ENDLINE-WORKING_DELTA);
    circle(Frame, attackPoint, 20, COLOR_ORANGE,2);

    // Шайба уходит от нас, но находится в нашей рабочей зоне
    if (in_Range(puckPoint.x, ENDLINE-WORKING_DELTA, ENDLINE))
    {
        // Если почти стоит
        if (averagexSpeed < 5 && averageySpeed < 5)
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

*/
int main()
{
    udpSocket = new QUdpSocket();

    setupCamera(0, 1024, 544);
    setupWindow();
    Mat Frame;
    Point puckPoint;
    //Point predictedPoint;
    //Point attackPoint;
    vector<Point> Points;
    vector<int> Speedx;
    vector<int> Speedy;
    int averagexSpeed = 0;
    int averageySpeed = 0;
    char key = -1;
    int skippedFrames = 0;
    loadSettings();
    ownTimer frameCounter = ownTimer();
    while (true)
    {
        frameCounter.start();
        //Получаем очередной кадр
        getCameraFrame(Frame);

        //Определяем координаты центра шайбы
        puckPoint = findPuck(Frame, p1, p2, minRadius, maxRadius);

        // Если нашли шайбу
        if (puckPoint.x > 0)
        {
            // Если эта первая точка, то просто добавляем её в массив
            if (Points.size() == 0)
            {
                Points.push_back(puckPoint);
            }
            else
            {
                // Добавляем точку
                Points.push_back(puckPoint);

                // Посчитаем среднюю скорость
                Speedy = getSpeed(Points, 'y' ,averageySpeed);
                Speedx = getSpeed(Points, 'x', averagexSpeed);

                //std::cout << averagexSpeed << " " << averageySpeed << std::endl;
                // Если направление изменилось
                if (isDirectionChanged(Speedx) || isDirectionChanged(Speedy))
                {
                    Points.clear();
                }

                // Шайба идёт на нас
                if (puckPoint.x > Points[Points.size()-2].x)
                {
                    processForward(Frame, puckPoint, Points, averagexSpeed);
                }
                // Шайба идёт от нас
                else
                {
                    processBackward(Frame, Points, Vec2i(averagexSpeed, averageySpeed));
                }

                // Обнуляем число пропущеных кадров
                skippedFrames = 0;
            }
        }
        else
        {
            // Увеличиваем число пропущенных кадров
            skippedFrames++;
            // Если пропустили много кадров подряд то шайбу точно потеряли
            // очищаем вектор точек, так как он уже 99% неверный
            if (skippedFrames > MAX_SKIPPED_FRAMES)
            {
                moveTo(Frame, HOMEPOINT);
                Points.clear();
            }
        }

        if (Points.size() == POINT_VECTOR_LENGTH)
        {
            Points.erase(Points.begin());
        }
        drawDebugLines(Frame);
        drawPath(Frame, Points);
        frameCounter.stop();
        putText(Frame, to_string(int(1 / frameCounter.elapsed_seconds())), Point(20,20), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,0), 2);
        imshow(WINDOW_NAME, Frame);

        key = waitKey(1);
        switch (key)
        {
            case 'q':
                return 0;
                break;
        case 's':
        {
            saveSettings();
            break;
        }
        case 'l':
        {
            loadSettings();
            break;
        }
        default:
            break;
        }
    }
    delete (udpSocket);
    delete (camera);
    return 0;
}
