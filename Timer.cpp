#include "Timer.h"


void Timer::start(){
    startTime = std::chrono::steady_clock::now();
}

double Timer::stop(){
    std::chrono::time_point endTime = std::chrono::steady_clock::now();
    long durationInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    double durationInSeconds = double(durationInMicroseconds)/1000000.0;
    return durationInSeconds;
}