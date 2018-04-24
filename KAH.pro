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
    cvwindow.cpp

INCLUDEPATH += C:\\opencv3_build\\install\\include

LIBS += C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_core341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_features2d341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_flann341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_highgui341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_objdetect341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_video341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_videoio341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_calib3d341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_imgproc341d.dll \
C:\\opencv3_build\\install\\x86\\mingw\\bin\\libopencv_ml341d.dll \

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
    cvwindow.h
