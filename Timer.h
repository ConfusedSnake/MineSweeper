#pragma once
#include <chrono>
#include "std_lib_facilities.h"

class Timer {
    private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    

    public:
    void start();
    double stop();

};