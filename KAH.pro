TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core gui network  widgets
requires(qtConfig(udpsocket))
SOURCES += main.cpp \
    findpuck.cpp \
    extrapolation.cpp \
    prediction.cpp \
    misc.cpp \
    globals.cpp \
    camera.cpp \
    cvwindow.cpp \
    fileio.cpp \
    puckprocess.cpp

INCLUDEPATH += C:\\opencv\\include

LIBS += C:\\opencv\\bin\\libopencv_core411.dll \
C:\\opencv\\bin\\libopencv_highgui411.dll \
C:\\opencv\\bin\\libopencv_objdetect411.dll \
C:\\opencv\\bin\\libopencv_video411.dll \
C:\\opencv\\bin\\libopencv_videoio411.dll \
C:\\opencv\\bin\\libopencv_imgproc411.dll \

HEADERS += \
    timer.h \
    findpuck.h \
    headers.h \
    extrapolation.h \
    prediction.h \
    globals.h \
    misc.h \
    functions.h \
    camera.h \
    cvwindow.h \
    colors.h \
    fileio.h \
    puckprocess.h
