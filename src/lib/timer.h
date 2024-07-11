#pragma once
#include <cstdint>

class Timer {
public:
    Timer();
    void reset();
    uint64_t getElapsedMs() const;

private:
    uint64_t start_ticks;
    static uint64_t getTicks();
    static uint64_t getTicksPerMs();
};