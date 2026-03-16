#include "Timer.hpp"

Timer::Timer() : running(false) {
    startTime.tv_sec = 0;
    startTime.tv_usec = 0;
    endTime.tv_sec = 0;
    endTime.tv_usec = 0;
}

void Timer::start() {
    gettimeofday(&startTime, nullptr);
    running = true;
}

void Timer::stop() {
    gettimeofday(&endTime, nullptr);
    running = false;
}

double Timer::getElapsedTime() const {
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long microseconds = endTime.tv_usec - startTime.tv_usec;

    return seconds + microseconds / 1000000.0;
}

long Timer::getElapsedMicroseconds() const {
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long microseconds = endTime.tv_usec - startTime.tv_usec;

    return seconds * 1000000 + microseconds;
}