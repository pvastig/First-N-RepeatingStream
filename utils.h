#pragma once

#include <chrono>

enum class TimeUnit { ticks, nano, micro, mili, seconds };

class Timer
{
public:
    void start();
    void stop();
    long duration(TimeUnit unit = TimeUnit::ticks) const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> mBegin, mEnd;
};
