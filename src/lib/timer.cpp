#include "timer.h"

Timer::Timer() {
    reset();
}

void Timer::reset() {
    start_ticks = getTicks();
}

uint64_t Timer::getElapsedMs() const {
    uint64_t elapsed_ticks = getTicks() - start_ticks;
    return elapsed_ticks / getTicksPerMs();
}

uint64_t Timer::getTicks() {
    uint32_t low, high;
    __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

uint64_t Timer::getTicksPerMs() {
    // This is a rough estimate and may need calibration
    return 1000000; 
}