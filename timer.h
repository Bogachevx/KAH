#pragma once
#include <Windows.h>

class ownTimer {
private:
	LARGE_INTEGER StartingTime, EndingTime, Elapsed, Frequency;

public:
    ownTimer() {
		QueryPerformanceFrequency(&Frequency);
	}

    void start() {
		QueryPerformanceCounter(&StartingTime);
	}

    void stop() {
		QueryPerformanceCounter(&EndingTime);
	}

    LONGLONG elapsed_microseconds() {
		Elapsed.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
		Elapsed.QuadPart *= 1000000;
		Elapsed.QuadPart /= Frequency.QuadPart;
		return (long long)Elapsed.QuadPart;
	}

    double elapsed_seconds() {
		return (this->elapsed_microseconds() / 1000000.0);
	}

    ~ownTimer() {}
};

