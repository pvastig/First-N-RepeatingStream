#include "utils.h"

#include <cassert>

void Timer::start()
{
    mBegin = std::chrono::system_clock::now();
}

void Timer::stop()
{
    mEnd = std::chrono::system_clock::now();
}

long Timer::duration(const TimeUnit unit) const
{
    const auto duration = mEnd - mBegin;
    switch (unit) {
    case TimeUnit::nano:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    case TimeUnit::micro:
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    case TimeUnit::mili:
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    case TimeUnit::seconds:
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    default:
        return duration.count();
    }
}
