#ifndef MISC_H
#define MISC_H

#include "headers.h"

extern QUdpSocket *udpSocket;
extern int ENDLINE;
extern int GATE_DELTA;
void UDPSend(QByteArray datagram);
bool in_Range(int x, int a, int b);
std::vector<int> getSpeed(std::vector<cv::Point> &Points, char coord, int &averageSpeed);
bool isDirectionChanged(std::vector<int> &Speed);
void moveTo(const cv::Mat &frame, cv::Point p);

void processForward(cv::Mat &Frame, cv::Point &puckPoint, std::vector<cv::Point> &Points, int &averagexSpeed);
void processBackward(cv::Mat &Frame, std::vector<cv::Point> &Points, cv::Vec2i averageSpeed);


#endif // MISC_H
