#include "misc.h"

bool in_Range(int x, int a, int b)
{
    return (x >= a)&&(x <= b);
}

//+
std::vector<int> getSpeed(std::vector<cv::Point> &Points, char coord, int &averageSpeed)
{
    averageSpeed = 0;
    int speed;
    std::vector<int> Speed;
    if (coord == 'y')
    {
        for (uint8_t i = 1; i < Points.size(); i++)
        {
            speed = Points[i].y - Points[i - 1].y;
            Speed.push_back(speed);
            averageSpeed += speed;
        }
    }
    else if (coord == 'x')
    {
        for (uint8_t i = 1; i < Points.size(); i++)
        {
            speed = Points[i].x - Points[i - 1].x;
            Speed.push_back(speed);
            averageSpeed += speed;
        }
    }

    averageSpeed = averageSpeed/Points.size();
    return Speed;
}
//+
bool isDirectionChanged(std::vector<int> &Speed)
{
    int positive = 0;
    int negative = 0;

    if (Speed.size() <= 2)
        return false;

    for (uint8_t i = 0; i < Speed.size(); i++)
    {
       if (Speed[i] > 0)
       {
           positive++;
       }
       else if (Speed[i] < 0)
       {
           negative++;
       }
    }
    return !(positive == 0 || negative == 0);
}

void UDPSend(QByteArray datagram)
{
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 49152);
}

void moveTo(const cv::Mat &frame, cv::Point p)
{
    QString package;
    QString num;
    double gateZoneLength = 2*GATE_DELTA;

    double percent = (p.y - (frame.rows/2 - GATE_DELTA))/gateZoneLength;

    percent = percent*100;

    if (percent > 100)
    {
        percent = 100;
    }
    if (percent < 0)
    {
        percent = 0;
    }

    package.push_back(num.setNum(floor(percent)));
    package.push_back(",");
    num.clear();

    if (p.x < ENDLINE)
    {
        package.push_back(num.setNum(100));
    }
    else
    {
        package.push_back(num.setNum(0));
    }

    UDPSend(package.toUtf8());
}


