#include "headers.h"
#include "functions.h"
//#include "process.h"
using namespace std;
using namespace cv;

extern int p1, p2, minRadius, maxRadius, kx, MINY, MAXY, ENDLINE, WORKING_DELTA, GATE_DELTA;

extern VideoCapture *camera;
extern QUdpSocket *udpSocket;

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
    int averagexSpeed;
    int averageySpeed;
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
        putText(Frame, to_string(1 / frameCounter.elapsed_seconds()), Point(20,20), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,0), 2);
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
