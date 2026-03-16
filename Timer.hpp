#ifndef TIMER_HPP
#define TIMER_HPP

#include <sys/time.h>

class Timer {
private:
    timeval startTime;
    timeval endTime;
    bool running;

public: 
    Timer();

    void start();
    void stop();

    double getElapsedSeconds() const; 
    long getElapsedMicroseconds() const;
};

#endif // TIMER_HPP