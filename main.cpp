#include "headers.h"
#include "functions.h"
#include <QDateTime>
#include "puckprocess.h"
using namespace std;
using namespace cv;

extern int p1, p2, minRadius, maxRadius, kx, MINY, MAXY, ENDLINE, WORKING_DELTA, GATE_DELTA, winWidth, winHeight;

extern VideoCapture *camera;
extern QUdpSocket *udpSocket;

int main()
{
    udpSocket = new QUdpSocket();
    setupWindow();
    loadSettings();
    setupCamera(0, winWidth, winHeight);


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
    bool isrec = false;
    ownTimer frameCounter = ownTimer();

    QString clearFname = "file1";//QDateTime::currentDateTime().toString("ddMMyyyyhhmmss");
    QString procFname = "file2";//clearFname;
    clearFname.append("_c.avi");
    procFname.append("_p.avi");
    int ex = static_cast<int>(camera->get(CAP_PROP_FOURCC));
    Size S = Size(camera->get(CAP_PROP_FRAME_WIDTH), camera->get(CAP_PROP_FRAME_HEIGHT));
    VideoWriter cleanOutput = VideoWriter(clearFname.toStdString(), -1, camera->get(CAP_PROP_FPS), S, false);
    //cleanOutput.open;
    VideoWriter procOutput;
    procOutput.open(procFname.toStdString(), ex, camera->get(CAP_PROP_FPS), S);

    while (true)
    {
        frameCounter.start();
        //Получаем очередной кадр
        getCameraFrame(Frame);
        if (isrec)
        {
            cleanOutput << Frame;
        }
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
        Scalar color;
        if (isrec)
        {
            color=Scalar(0,0,255);
        }
        else
        {
            color=Scalar(255,0,0);
        }
        putText(Frame, to_string(int(1 / frameCounter.elapsed_seconds())), Point(20,20), FONT_HERSHEY_COMPLEX, 1, color, 2);
        if (isrec)
        {
            procOutput.write(Frame);
        }
        imshow(WINDOW_NAME, Frame);

        key = waitKey(1);
        switch (key)
        {
            case 'q':
                //saveSettings();
                cleanOutput.release();
                procOutput.release();
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
        case 'r':
            isrec = !isrec;
            break;
        default:
            break;
        }
    }
    delete (udpSocket);
    delete (camera);
    return 0;
}
