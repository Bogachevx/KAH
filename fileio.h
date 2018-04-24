#ifndef FILEIO_H
#define FILEIO_H

#include "headers.h"
#include "cvwindow.h"

extern int p1, p2, minRadius, maxRadius, kx, MINY, MAXY, ENDLINE, WORKING_DELTA, GATE_DELTA;

void loadSettings();
void saveSettings();
#endif // FILEIO_H
